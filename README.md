# Lightalarmy

## Parts

- Arduino ([shop](http://www.amazon.de/SainSmart-Kompatibel-Entwicklungsbrett-ATmega328P-enthaltend/dp/B00760RLFO/ref=sr_1_6?ie=UTF8&qid=1425220236&sr=8-6&keywords=Sainsmart) - uno compatible)
- Adafruit NeoPixel 8x8 ([shop](http://www.flikto.de/products/adafruit-neopixel-neomatrix-8x8-64-rgb-led-pixel-matrix))
- DS1307 Real Time clock ([shop](http://www.amazon.de/DS1307-AT24C32-Module-Arduino-Mega2560/dp/B00G6B6MGS/ref=sr_1_6?ie=UTF8&qid=1425019440&sr=8-6&keywords=Ds1307))
- Rotary encoder with button functionality (since we could not find pods with push-down button function included)

## Display and modes

### Notes

When waking, use a gradient from red over blue to white.

Use the pot to set the alarm. One can only set alarms between 6:00-9:55. The pot operates in 5 min steps. For displaying the hour use 3x5 digit and twice 2x5 for the minutes. This leaves one pixel space between hour and minutes.
The time is only shown if the pot is pushed down. The time then scrolls through.

When the alarm is ongoing, show the time occasionally. The surrounding pixels which are not needed to show the scrolling digits shall then still be bright white.

The alarm does not include sound as a fail safe, because you would usually set another device anyway.

### TODO

- [ ] Test the hour on top of the minutes on one 8x8 screen with the 3x4 font (see sketches).

### Programming

Here the libraries the program uses:

- Adafruit GFX Library ([GitHub](https://github.com/adafruit/Adafruit-GFX-Library) & [tutorial](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview))
- Adafruit NeoMatrix Library ([GitHub](https://github.com/adafruit/Adafruit_NeoMatrix) & [Uberguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library))
- Adafruit NeoPixel ([GitHub](https://github.com/adafruit/Adafruit_NeoPixel) & see Uberguide above)


## Box

Here is the idea for the housing...
![box](https://raw.githubusercontent.com/motine/lightalarmy/master/studies/box-retro.jpg)

The front/top side will be bent. Here some resources for checking out how to do this:

* [A guy testing patterns](http://m.instructables.com/id/Curved-laser-bent-wood/?ALLSTEPS)
* [Some calculations in math](http://www.deferredprocrastination.co.uk/blog/2012/minimum-bend-radius/)
* [More resources](http://www.deferredprocrastination.co.uk/blog/category/def-proc/lattice-hinges/)


## Credits

I used [picmonkey](http://www.picmonkey.com/) to create the collages.