# sternenwecker

## Circuit

### Parts

- Arduino Uno ([shop](http://www.amazon.de/SainSmart-Kompatibel-Entwicklungsbrett-ATmega328P-enthaltend/dp/B00760RLFO/ref=sr_1_6?ie=UTF8&qid=1425220236&sr=8-6&keywords=Sainsmart) - uno compatible)
- Adafruit NeoPixel 8x8 ([shop](http://www.flikto.de/products/adafruit-neopixel-neomatrix-8x8-64-rgb-led-pixel-matrix))
- Rotary encoder with button functionality "Encoder 5 Vdc 0.001 A 360 ° ALPS STEC12E08" ([shop](http://www.conrad.com/ce/en/product/700708/Encoder-5-Vdc-0001-A-360-ALPS-STEC12E08-1-pcs)) with cap ([shop](http://www.conrad.com/ce/en/product/700619/ALPS-DK13-164A645-Rotary-Knob-For-Encoder-With-Plastic-Shaft-Rotary-button-?ref=oz))
- External power source with around 4 Amperes ([shop](http://www.amazon.de/dp/B004S7U4IO), the matrix [needs](https://learn.adafruit.com/adafruit-neopixel-uberguide/power) 3.8A at max, there are lots of alternatives at [conrad.de](http://conrad.de))
- 470 Ohm resistor
- Some cables ([shop](http://www.amazon.de/dp/B00PXBVRZS)) (maybe a bread board for developing)
- 3mm MDF sheet(s) ([shop](http://www.modulor.de/en/Wood-Cork/Fibreboards/MDF-Boards/MDF-brown-uncoated.html))
- 3mm Mat acrylic glass sheet (WH10) ([shop](http://www.modulor.de/en/Plastics-Rubber/Sheets-Mats-Films/Acrylic-Glass-GS-Sheets-and-Blocks/Plexiglas-GS-white-milky.html))

### Setup & layout

I cut the cord of the power source and attached 5V & GND to the LED matrix. The LED matrix's data connection was connected to the running Arduino. Since, it did not light up straight away, I unplugged it very quickly and swapped the cables. Then the LEDs light up. In my case the cable with text was 5V. Since I was a little bit of a coward, I did not power the Arduino with my laptop, but with a USB battery I had lying around... Now, I have soldered a red cable to 5V and a black cable to GND of the power source's cord. Only then I did try the matrix with full power. **Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs**.

## Display and modes

### Notes

When waking, use a gradient from red over blue to white.

Use the pot to set the alarm. One can only set alarms between 6:00-9:55. The pot operates in 5 min steps. For displaying the hour use 3x5 digit and twice 2x5 for the minutes. This leaves one pixel space between hour and minutes.
The time is only shown if the pot is pushed down. The time then scrolls through.

When the alarm is ongoing, show the time occasionally. The surrounding pixels which are not needed to show the scrolling digits shall then still be bright white.

The alarm does not include sound as a fail safe, because you would usually set another device anyway.

After I did my design I found this great [8x8 icon set](http://graphicriver.net/item/nano-icons-8x8/4453769).

## Programming

I only use the Adafruit NeoPixel ([GitHub](https://github.com/adafruit/Adafruit_NeoPixel) & see Uberguide above) library. Please install it from Github directly, because they recently added the `clear()` method. It turns out that the NeoMatrix library uses only 16 bit for colors. This makes my color gradients look choppy.

Here some more info:

* I used the [ALPS STEC12E Encoder](http://www.reichelt.de/Drehimpulsgeber/STEC12E08/3/index.html?;ACTION=3;LA=5000;GROUP=B29;GROUPID=3714;ARTICLE=73923;START=0;SORT=artnr;OFFSET=16;SID=12T8NM5n8AAAIAAFaMoB8531a88b7cd82ed0595530ee4614f0159) with the data sheet [specification](https://cdn-reichelt.de/documents/datenblatt/F100/402097STEC12E08.PDF).

* I tried to use interrupts for the encoder, because the bounce was too hard. I do it in the `loop` now and works fine. As it seems as I do not need to debounce the signal in my case. But if you decide to do so, I found this [nice article](https://hifiduino.wordpress.com/2010/10/20/rotaryencoder-hw-sw-no-debounce) (i.e. see "updated" part). Also there is a [Arduino Playground page](http://playground.arduino.cc/code/bounce) about it.

Here some weird stuff (**known issues**):

- If you make the matrix use lot's of power (MAX_BRIGHTNESS > 20), you may not be able to upload your sketch. Just unplug the matrix's 5V, upload your sketch and replug.

## Box

Here is the idea for the housing...
![box](https://raw.githubusercontent.com/motine/sternenwecker/master/studies/box-retro.jpg).

To assemble:

1. Assemble the support.
1. Take some [blue tack](http://en.wikipedia.org/wiki/Blu-Tack) and stick the matrix to the support (or use glue if you are sure what you are doing).
1. Then assemble the rest of the top bit (top+side+support+side+back).
1. Put everything on the bottom.
1. Slide in the drawer.

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


I used to following software:

* TextMate for text editing
* Arduino GUI for compiling and uploading (with the external editor setting enabled)
* [fritzing](fritzing.org) for circuit design
* omniGraffle for the box design (for the laser cutter)
* [picmonkey](http://www.picmonkey.com/) to create the collages
