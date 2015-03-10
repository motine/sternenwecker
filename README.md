# sternenwecker

## Circuit

### Parts

- Arduino Uno ([shop](http://www.amazon.de/SainSmart-Kompatibel-Entwicklungsbrett-ATmega328P-enthaltend/dp/B00760RLFO/ref=sr_1_6?ie=UTF8&qid=1425220236&sr=8-6&keywords=Sainsmart) - uno compatible)
- Adafruit NeoPixel 8x8 ([shop](http://www.flikto.de/products/adafruit-neopixel-neomatrix-8x8-64-rgb-led-pixel-matrix))
- Rotary encoder with button functionality (since we could not find pods with push-down button function included)
- External power source > 4A ([shop](http://www.amazon.de/dp/B004S7U4IO), the matrix [needs](https://learn.adafruit.com/adafruit-neopixel-uberguide/power) 3.8A at max, there are lots of alternatives at [conrad.de](http://conrad.de))
- 500 Ohm resistor, 1000uF capacitor
- Some cables ([shop](http://www.amazon.de/dp/B00PXBVRZS)) (maybe a bread board for developing)
- 3mm MDF sheet(s) ([shop](http://www.modulor.de/en/Wood-Cork/Fibreboards/MDF-Boards/MDF-brown-uncoated.html))
- 3mm Mat acrylic glass sheet (WH10) ([shop](http://www.modulor.de/en/Plastics-Rubber/Sheets-Mats-Films/Acrylic-Glass-GS-Sheets-and-Blocks/Plexiglas-GS-white-milky.html))

### Setup & layout

I cut the cord of the power source and attached 5V & GND to the LED matrix. The LED matrix's data connection was connected to the running Arduino. Since, it did not light up straight away, I unplugged it very quickly and swapped the cables. Then the LEDs light up. In my case the cable with text was 5V. Since I was a little bit of a coward, I did not power the Arduino with my laptop, but with a USB battery I had lying around... Now, I have soldered a red cable to 5V and a black cable to GND of the power source's cord. Only then I did try the matrix with full power. **Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs**.

For now, please see the circuit [here](http://www.instructables.com/file/F7F8GS5HRCK17ZT) (thanks to [Friedlc](http://www.instructables.com/id/25D-Edge-Lighting-Pixel-LED-Cube/step4/Wire-them-up/)).

* [ ] Do we need a resistor or a capacitor as mentioned [here](https://learn.adafruit.com/adafruit-neopixel-uberguide/power)?

## Display and modes

### Notes

When waking, use a gradient from red over blue to white.

Use the pot to set the alarm. One can only set alarms between 6:00-9:55. The pot operates in 5 min steps. For displaying the hour use 3x5 digit and twice 2x5 for the minutes. This leaves one pixel space between hour and minutes.
The time is only shown if the pot is pushed down. The time then scrolls through.

When the alarm is ongoing, show the time occasionally. The surrounding pixels which are not needed to show the scrolling digits shall then still be bright white.

The alarm does not include sound as a fail safe, because you would usually set another device anyway.

### TODO

- [ ] Finish laser cut for box
- [ ] Add Conrad order to parts
- [ ] Solder the resistor into the cable (surround with shrinking hose)
- [ ] Solder the resistor into the cable (surround with shrinking hose)
- [ ] Rethink name of the project
- [ ] Test the hour on top of the minutes on one 8x8 screen with the 3x4 font (see sketches).
- [ ] Make drawings for icons
- [ ] Program encoder library ()
- [ ] Program menu icons
- [ ] Program shift animations

### Programming

Here the **libraries** the program uses:

- Adafruit GFX Library ([GitHub](https://github.com/adafruit/Adafruit-GFX-Library) & [tutorial](https://learn.adafruit.com/adafruit-gfx-graphics-library/overview))
- Adafruit NeoMatrix Library ([GitHub](https://github.com/adafruit/Adafruit_NeoMatrix) & [Uberguide](https://learn.adafruit.com/adafruit-neopixel-uberguide/neomatrix-library))
- Adafruit NeoPixel ([GitHub](https://github.com/adafruit/Adafruit_NeoPixel) & see Uberguide above)

Here some weird stuff (**known issues**):

- If you make the matrix use lot's of power (MAX_BRIGHTNESS > 20), you may not be able to upload your sketch. Just unplug the matrix's 5V, upload your sketch and replug.

## Box

Here is the idea for the housing...
![box](https://raw.githubusercontent.com/motine/lightalarmy/master/studies/box-retro.jpg)

The front/top side will be bent. Here some resources for checking out how to do this:

* [A guy testing patterns](http://m.instructables.com/id/Curved-laser-bent-wood/?ALLSTEPS)
* [Some calculations in math](http://www.deferredprocrastination.co.uk/blog/2012/minimum-bend-radius/)
* [More resources](http://www.deferredprocrastination.co.uk/blog/category/def-proc/lattice-hinges/)


## Credits

* Thanks to my wife, because she pretends to be really interested in my little projects.
* Thanks to Michael to listen to me, even if I am over excited.
* Thanks to Stefan who shared his experiences, so I didn't have to try and fail so often. 
* Thanks to Armin for feedback on the button issue.
* Thanks to Marcel for answering a couple of questions regarding the circuit.
* I used [picmonkey](http://www.picmonkey.com/) to create the collages.
