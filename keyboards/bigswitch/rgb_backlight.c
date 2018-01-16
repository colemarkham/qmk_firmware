#include "timer.h"
#include "backlight.h"
#include <avr/sfr_defs.h>
#include "print.h"

extern backlight_config_t backlight_config;

#if defined(BACKLIGHT_ENABLE)


#define RED 0
#define GREEN 1
#define BLUE 2

#define RGBLED_LEVELS 255

// Color arrays
#define black   { 0, 0, 0 }
#define white   { 100, 100, 100 }
#define red     { 100, 0, 0 }
#define green   { 0, 100, 0 }
#define blue    { 0, 0, 100 }
#define yellow  { 40, 95, 0 }
//#define dimWhite { 30, 30, 30 }

void crossFade(uint8_t color[3]);
void crossfade_task(void);

uint8_t colorsequence[][3] = {black, red, green, blue, yellow, white};

//static const uint8_t backlight_pins[] = RGBLED_PINS;
int16_t rgbbacklight_levels[3];
int16_t crossfade_step[3];
uint16_t crossfade_tick;
uint16_t crossfade_lastTime;
bool crossfade_running;

#ifndef BACKLIGHT_ON_STATE
#define BACKLIGHT_ON_STATE 0
#endif

__attribute__ ((weak))
void backlight_init_ports(void)
{
  println("backlight_init_ports");
  crossfade_running = 0;
  rgbbacklight_levels[RED] = 0;
  rgbbacklight_levels[GREEN] = 0;
  rgbbacklight_levels[BLUE] = 0;
  // Setup backlight pin as output and output to on state.
  // DDRx |= n
  for (uint8_t idx = 1; idx <= 3; idx++) {
    DDRB |= idx;
//    _SFR_IO8((backlight_pins[idx] >> 4) + 1) |= _BV(backlight_pins[idx] & 0xF);
#if BACKLIGHT_ON_STATE == 0
    // PORTx &= ~n
    PORTB |= ~idx;
//    _SFR_IO8((backlight_pins[idx] >> 4) + 2) &= ~_BV(backlight_pins[idx] & 0xF);
#else
    // PORTx |= n
    PORTB |= idx;
//    _SFR_IO8((backlight_pins[idx] >> 4) + 2) |= _BV(backlight_pins[idx] & 0xF);
#endif
  }

  backlight_init();
}

__attribute__ ((weak))
void backlight_set(uint8_t level)
{
  crossFade(colorsequence[level]);

  rgbbacklight_levels[RED] = (colorsequence[level][RED] * RGBLED_LEVELS) / 100;
  rgbbacklight_levels[GREEN] = (colorsequence[level][GREEN] * RGBLED_LEVELS) / 100;
  rgbbacklight_levels[BLUE] = (colorsequence[level][BLUE] * RGBLED_LEVELS) / 100;
}

uint8_t backlight_tick = 0;

void backlight_task(void) {
  for (uint8_t idx = 0; idx < 3; idx++) {
    if ((0xFFFF >> ((RGBLED_LEVELS - rgbbacklight_levels[idx]) * ((RGBLED_LEVELS + 1) / 2))) & (1 << backlight_tick)) {
      #if BACKLIGHT_ON_STATE == 0
        // PORTx &= ~n
        PORTB &= ~(idx+1);
//        _SFR_IO8((backlight_pins[idx] >> 4) + 2) &= ~_BV(backlight_pins[idx] & 0xF);
      #else
        // PORTx |= n
        PORTB |= (idx+1);
//        _SFR_IO8((backlight_pins[idx] >> 4) + 2) |= _BV(backlight_pins[idx] & 0xF);
      #endif
    } else {
      #if BACKLIGHT_ON_STATE == 0
        // PORTx |= n
      PORTB |= (idx+1);
//        _SFR_IO8((backlight_pins[idx] >> 4) + 2) |= _BV(backlight_pins[idx] & 0xF);
      #else
        // PORTx &= ~n
      PORTB &= ~(idx+1);
//        _SFR_IO8((backlight_pins[idx] >> 4) + 2) &= ~_BV(backlight_pins[idx] & 0xF);
      #endif
    }
  }
  backlight_tick = (backlight_tick + 1) % 16;
//  if (backlight_tick == 0){
//    crossfade_task();
//  }
}

/*
* Code for cross-fading 3 LEDs, red, green and blue (RGB)
* To create fades, you need to do two things:
*  1. Describe the colors you want to be displayed
*  2. List the order you want them to fade in
*
* DESCRIBING A COLOR:
* A color is just an array of three percentages, 0-100,
*  controlling the red, green and blue LEDs
*
* Red is the red LED at full, blue and green off
*   uint8_t red = { 100, 0, 0 }
* Dim white is all three LEDs at 30%
*   uint8_t dimWhite = {30, 30, 30}
* etc.
*
* Some common colors are provided below, or make your own
*
* LISTING THE ORDER:
* In the main part of the program, you need to list the order
*  you want to colors to appear in, e.g.
*  crossFade(red);
*  crossFade(green);
*  crossFade(blue);
*
* Those colors will appear in that order, fading out of
*    one color and into the next
*
* In addition, there are 5 optional settings you can adjust:
* 1. The initial color is set to black (so the first color fades in), but
*    you can set the initial color to be any other color
* 2. The internal loop runs for 1020 interations; the 'wait' variable
*    sets the approximate duration of a single crossfade. In theory,
*    a 'wait' of 10 ms should make a crossFade of ~10 seconds. In
*    practice, the other functions the code is performing slow this
*    down to ~11 seconds on my board. YMMV.
* 3. If 'repeat' is set to 0, the program will loop indefinitely.
*    if it is set to a number, it will loop that number of times,
*    then stop on the last color in the sequence. (Set 'return' to 1,
*    and make the last color black if you want it to fade out at the end.)
* 4. There is an optional 'hold' variable, which pasues the
*    program for 'hold' milliseconds when a color is complete,
*    but before the next color starts.
* 5. Set the DEBUG flag to 1 if you want debugging output to be
*    sent to the serial monitor.
*
*    The internals of the program aren't complicated, but they
*    are a little fussy -- the inner workings are explained
*    below the main loop.
*
* April 2007, Clay Shirky <clay.shirky@nyu.edu>
*/

/* BELOW THIS LINE IS THE MATH -- YOU SHOULDN'T NEED TO CHANGE THIS FOR THE BASICS
*
* The program works like this:
* Imagine a crossfade that moves the red LED from 0-10,
*   the green from 0-5, and the blue from 10 to 7, in
*   ten steps.
*   We'd want to count the 10 steps and increase or
*   decrease color values in evenly stepped increments.
*   Imagine a + indicates raising a value by 1, and a -
*   equals lowering it. Our 10 step fade would look like:
*
*   1 2 3 4 5 6 7 8 9 10
* R + + + + + + + + + +
* G   +   +   +   +   +
* B     -     -     -
*
* The red rises from 0 to 10 in ten steps, the green from
* 0-5 in 5 steps, and the blue falls from 10 to 7 in three steps.
*
* In the real program, the color percentages are converted to
* 0-RGBLED_LEVELS values, and there are 1020 steps (RGBLED_LEVELS*4).
*
* To figure out how big a step there should be between one up- or
* down-tick of one of the LED values, we call calculateStep(),
* which calculates the absolute gap between the start and end values,
* and then divides that gap by 1020 to determine the size of the step
* between adjustments in the value.
*/

uint8_t calculateStep(uint8_t prevValue, uint8_t endValue) {
  uint8_t step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero,
    step = 1020/step;              //   divide by 1020
  }
  return step;
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1.
*  (R, G, and B are each calculated separately.)
*/

uint8_t calculateVal(uint8_t step, uint8_t val, uint8_t i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;
    }
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    }
  }
  // Defensive driving: make sure val stays in the range 0-RGBLED_LEVELS
  if (val > RGBLED_LEVELS) {
    val = RGBLED_LEVELS;
  }
  else if (val < 0) {
    val = 0;
  }
  return val;
}

/* crossFade() converts the percentage colors to a
*  0-RGBLED_LEVELS range, then loops 1020 times, checking to see if
*  the value needs to be updated each time, then writing
*  the color values to the correct pins.
*/

void crossFade(uint8_t color[3]) {

  print("Crossfading to color: ");
  print_dec(color[RED]); print(", ");
  print_dec(color[GREEN]); print(", ");
  print_dec(color[BLUE]); println(".");
  // Convert to 0-RGBLED_LEVELS
  uint8_t R = (color[0] * RGBLED_LEVELS) / 100;
  uint8_t G = (color[1] * RGBLED_LEVELS) / 100;
  uint8_t B = (color[2] * RGBLED_LEVELS) / 100;
  print("Crossfade running: ");
  print_dec(crossfade_running);
  println();
  print("crossfade_tick: ");
  print_dec(crossfade_tick);
  println();

  print("Current colors: ");
  print_dec(rgbbacklight_levels[RED]); print(", ");
  print_dec(rgbbacklight_levels[GREEN]); print(", ");
  print_dec(rgbbacklight_levels[BLUE]); println(".");
  crossfade_step[RED] = calculateStep(rgbbacklight_levels[RED], R);
  crossfade_step[GREEN] = calculateStep(rgbbacklight_levels[GREEN], G);
  crossfade_step[BLUE] = calculateStep(rgbbacklight_levels[BLUE], B);

  print("Steps: ");
  print_dec(crossfade_step[RED]); print(", ");
  print_dec(crossfade_step[GREEN]); print(", ");
  print_dec(crossfade_step[BLUE]); println(".");
  println();

  crossfade_tick = 0;
  crossfade_running = 1;
  crossfade_lastTime = timer_read();
}

void crossfade_task(void) {
  uint16_t time = timer_read();

//  for (uint8_t i = 0; i <= 1020; i++) {
  uint16_t diff = time - crossfade_lastTime;

//  print("crossfade_task time:");
//        print_dec(time);
//        println();
  if (diff >= 2) {
    // Update every time through the loop to keep fresh
     crossfade_lastTime = time;
    if (crossfade_running){
      // In case it skipped more than 1ms, jump the tick by however many ms were elapsed
      crossfade_tick ++;
//      if (crossfade_tick % 100 == 0) {
//        print("crossfade_tick:");
//        print_dec(crossfade_tick);
//        println();
//      }
      rgbbacklight_levels[RED] = calculateVal(crossfade_step[RED], rgbbacklight_levels[RED], crossfade_tick);
      rgbbacklight_levels[GREEN] = calculateVal(crossfade_step[GREEN], rgbbacklight_levels[GREEN], crossfade_tick);
      rgbbacklight_levels[BLUE] = calculateVal(crossfade_step[BLUE], rgbbacklight_levels[BLUE], crossfade_tick);
      if (crossfade_tick > 1020) {
        // end the crossfade on the next iteration
        crossfade_running = 0;
        println("Crossfade complete");
      }
    }
  }



//    delay(wait); // Pause for 'wait' milliseconds before resuming the loop

//      if (i == 0 or i % loopCount == 0) { // beginning, and every loopCount times
//        print("Loop/RGB: #");
//        print(i);
//        print(" | ");
//        print(redVal);
//        print(" / ");
//        print(grnVal);
//        print(" / ");
//        println(bluVal);
//      }
//  }
}

#endif // backlight
