#ifndef COLORCROSSFADE_H
#define COLORCROSSFADE_H

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
*   int red = { 100, 0, 0 }
* Dim white is all three LEDs at 30%
*   int dimWhite = {30, 30, 30}
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

void crossFade(int color[3]);

// Output
const int redPin = 6;   // Red LED,   connected to digital pin 9
const int grnPin = 9;  // Green LED, connected to digital pin 10
const int bluPin = 10;  // Blue LED,  connected to digital pin 11

// Color arrays
const int black[3]  = { 0, 0, 0 };
const int white[3]  = { 100, 100, 100 };
const int red[3]    = { 100, 0, 0 };
const int green[3]  = { 0, 100, 0 };
const int blue[3]   = { 0, 0, 100 };
const int yellow[3] = { 40, 95, 0 };
const int dimWhite[3] = { 30, 30, 30 };
// etc.

#endif
