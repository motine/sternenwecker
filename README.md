# sternenwecker

This branch is about the "LED strip behind the bed" version.
There is also a [table top version](https://github.com/motine/sternenwecker/tree/single_matrix).

## Work to do...

* Make this Readme nice
* Adjust box design and readme for this version
* Change part list to Arduino Pro Mini with USB

## Circuit
### Parts

- [Arduino Pro Mini](http://www.amazon.de/dp/B00PLD3E1S) + [FTDI Board](http://www.exp-tech.de/foca-v2-2-ft232rl-tiny-breakout-usb-to-serial-uart-interface)
- [Connectors](http://www.exp-tech.de/waterproof-dc-power-cable-set-5-5-2-1mm)
- [Adafruit Bicolor LED Square Pixel Matrix with I2C Backpack](http://www.exp-tech.de/adafruit-bicolor-led-square-pixel-matrix-with-i2c-backpack)
- [60 RGB LED Strip WS2812B](http://r.ebay.com/bDToHk)
- [Rotary encoder with button](http://www.conrad.com/ce/en/product/700708/Encoder-5-Vdc-0001-A-360-ALPS-STEC12E08-1-pcs) with [cap](http://www.conrad.com/ce/en/product/700619/ALPS-DK13-164A645-Rotary-Knob-For-Encoder-With-Plastic-Shaft-Rotary-button-?ref=oz)
- [Tiny RTC](http://www.amazon.de/dp/B00NW50PA0) (Real Time Clock)
- [External power source](http://www.amazon.de/dp/B004S7U4IO) with around 4A
- 470 Ohm resistor
- [Some cables](http://www.amazon.de/dp/B00PXBVRZS) (maybe a bread board for developing)
- [3mm MDF sheet(s)](http://www.modulor.de/en/Wood-Cork/Fibreboards/MDF-Boards/MDF-brown-uncoated.html)

### Setup & layout

![circuit](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/circuit.png)

The chosen power supply says that it is regulated (german _stabilisiert_), but when I measured the idle output the voltage was higher than 5V (5.5V). I was surprised that, an unregulated 5V power supply gives more that the 5V if you don't draw close to the maximum current. Regulated then means that the power supply does _not_ exceed its voltage even if there is less current drawn. With this in mind I wanted to make sure that nothing blows, so I am using Arduino's `RAW` pin instead of `VCC`. This way we include the Arduino's onboard voltage regulator.

I cut the cord of the power source and attached 5V & GND to the LED matrix. The LED matrix's data connection was connected to the running Arduino. Since, it did not light up straight away, I unplugged it very quickly and swapped the cables. Then the LEDs light up. In my case the cable with text was 5V. Since I was a little bit of a coward during the first try, I did not power the Arduino with my laptop, but with a USB battery I had lying around... Now, I have soldered a red cable to 5V and a black cable to GND of the power source's cord. Only then I did try the matrix with full power. **Do not run the program with a brightness above 20 when powering the LED matrix via Arduino's power PINs**. The matrix [needs](https://learn.adafruit.com/adafruit-neopixel-uberguide/power) 3.8A at max!

After I proudly introduced my nightstand to its new companion (the alarm), I found that the time drifts very much. So I woke a little earlier than expected. After this experience I decided to add the real time module.

## Programming

We need the Adafruit's '[NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) and [LED-Backpack](https://github.com/adafruit/Adafruit-LED-Backpack-Library) (with [GFX](https://github.com/adafruit/Adafruit-GFX-Library)) libs from GitHub.
And the [RTClib](https://github.com/jcw/rtclib).

Please run the following in a shell (needs `git` installed):

```bash
# This applies to Mac OSX, please adjust the paths if you have another OS.
mkdir -p ~/Documents/Arduino/libraries/
cd ~/Documents/Arduino/libraries/
# get LED-Backpack (needs a new version)
git clone https://github.com/adafruit/Adafruit-LED-Backpack-Library.git
mv Adafruit-LED-Backpack-Library Adafruit_LEDBackpack
# get GFX
git clone https://github.com/adafruit/Adafruit-GFX-Library.git
mv Adafruit-GFX-Library Adafruit_GFX
# get NeoPixel
git clone https://github.com/adafruit/Adafruit_NeoPixel.git
# get RTC
git clone https://github.com/jcw/rtclib.git
mv rtclib RTClib
```

**Notes**

* Note, I wanted to use the more elaborate `NeoMatrix` library, but it turns out that it only uses 16 bit for colors. This makes my color gradients look choppy.
* I used the [ALPS STEC12E Encoder](http://www.reichelt.de/Drehimpulsgeber/STEC12E08/3/index.html?;ACTION=3;LA=5000;GROUP=B29;GROUPID=3714;ARTICLE=73923;START=0;SORT=artnr;OFFSET=16;SID=12T8NM5n8AAAIAAFaMoB8531a88b7cd82ed0595530ee4614f0159) with the data sheet [specification](https://cdn-reichelt.de/documents/datenblatt/F100/402097STEC12E08.PDF).
* I tried to use interrupts for the encoder, because the bounce was too hard. I do it in the `loop` now and works fine. As it seems as I do not need to debounce the signal in my case. But if you decide to do so, I found this [nice article](https://hifiduino.wordpress.com/2010/10/20/rotaryencoder-hw-sw-no-debounce) (i.e. see "updated" part). Also there is a [Arduino Playground page](http://playground.arduino.cc/code/bounce) about it.
* For the DS1307 Real Time Clock Module, I found some [documentation](http://www.sainsmart.com/arduino-i2c-rtc-ds1307-at24c32-real-time-clock-module-board-for-avr-arm-pic.html) (not necessarily what I bought, but better than nothing). Also [Adafruit's page](https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/arduino-library) was helpful.

## Uploading

**Add note about hitting reset**
**Add instructions what to choose in the Arduino GUI**

In order to program the Arduino Pro Mini, please use a FTDI board (the Arduino does not have a USB connection, so we have to go through a serial connection).
Here my wiring for the setup (note that I did not solder the headers to the Arduino so I can easily remove it):

![USB - FTDI - Arduino Pro Mini](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/usb-serial-aruino.png)

## Troubleshooting

**Add reference to TESTING.md**

## Box

![tinybox](https://raw.githubusercontent.com/motine/sternenwecker/master/box/boxes-assembled.jpg)

## Credits

* Thanks to my wife, because she pretends to be really interested in my little projects.
* Thanks to Michael to listen to me, even if I am over excited.
* Thanks to Stefan who shared his experiences, so I didn't have to try and fail so often. 
* Thanks to Armin for feedback on the "where to put the button" issue.
* Thanks to Marcel for answering a couple of questions regarding the circuit.

I used to following software:

* TextMate for text editing
* Arduino GUI for compiling and uploading (with the external editor setting enabled)
* omniGraffle for the box design (for the laser cutter)
