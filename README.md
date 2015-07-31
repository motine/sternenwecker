# sternenwecker

![sternenwecker](https://raw.githubusercontent.com/motine/sternenwecker/master/sternenwecker.jpg)

This branch is about the "LED strip behind the bed" version.
There is also a [table top version](https://github.com/motine/sternenwecker/tree/single_matrix).

## Circuit
### Parts

- [Arduino Nano v3](http://www.amazon.de/dp/B00PL70XWW)
- [Connectors](http://www.exp-tech.de/waterproof-dc-power-cable-set-5-5-2-1mm)
- [Adafruit Bicolor LED Square Pixel Matrix with I2C Backpack](http://www.exp-tech.de/adafruit-bicolor-led-square-pixel-matrix-with-i2c-backpack)
- [60 RGB LED Strip WS2812B](http://r.ebay.com/bDToHk)
- [Rotary encoder / button](http://www.conrad.com/ce/en/product/700708/Encoder-5-Vdc-0001-A-360-ALPS-STEC12E08-1-pcs) with [cap](http://www.conrad.com/ce/en/product/700619/ALPS-DK13-164A645-Rotary-Knob-For-Encoder-With-Plastic-Shaft-Rotary-button-?ref=oz)
- [Tiny RTC](http://www.amazon.de/dp/B00NW50PA0) (Real Time Clock)
- [External power source](http://www.amazon.de/dp/B004S7U4IO) with around 4A
- 470 Ohm resistor, 1000μF
- [Some cables](http://www.amazon.de/dp/B00PXBVRZS) (maybe a bread board for developing)
- [3mm MDF sheet(s)](http://www.modulor.de/en/Wood-Cork/Fibreboards/MDF-Boards/MDF-brown-uncoated.html)

For testing the individual components, I wrote a couple of test programs. You can find them in `TESTING.md`.

### Setup & layout

![circuit](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/circuit.png)

The chosen power supply says that it is regulated (german _stabilisiert_), but when I measured the idle output the voltage was higher than 5V (5.5V).
An unregulated 5V power supply gives more that the 5V if you don't draw close to the maximum current.
Regulated then means that the power supply does _not_ exceed its voltage even if there is less current drawn.
With this in mind I wanted to make sure that nothing blows, so I am using Arduino's `RAW` pin instead of `VCC`.
This way we include the Arduino's onboard voltage regulator.

I cut the cord of the power source and attached 5V & GND to the LED strip. Test which cable is which with a voltmeter.
Since I did not have a voltmeter at the time and had no way of knowing which cable is which, I connected the strip and send some test over (see `TESTING.md`).
As per Murphy's law, the strip did not light up straight away, so I unplugged it very quickly and swapped the cables.
Then the LEDs light up. In my case the cable with text was 5V.

**Do not run the program with a brightness above 20 when powering the LED strip via Arduino's power PINs / via the computers USB.**
The strip [needs](https://learn.adafruit.com/adafruit-neopixel-uberguide/power) 3.8A at max! This exceeds the Arduino's spec.

After I proudly introduced my nightstand to its new companion (the alarm), I found that the time drifted very much.
So I woke a little earlier than expected. After this experience I decided to add the real time module...

![matrix-orientation](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/matrix-orientation.jpg)
![soldering-encoder](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/soldering-encoder.jpg)
![soldering-multi-shrink](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/soldering-multi-shrink.jpg)
![soldering-resistor](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/soldering-resistor.jpg)
![soldering-strip](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/soldering-strip.jpg)

## Programming

We need the Adafruit's '[NeoPixel](https://github.com/adafruit/Adafruit_NeoPixel) and [LED-Backpack](https://github.com/adafruit/Adafruit-LED-Backpack-Library) (with [GFX](https://github.com/adafruit/Adafruit-GFX-Library)) libs from GitHub.
And the [RTClib](https://github.com/jcw/rtclib).

Please run the following in a shell (needs `git` installed):

```bash
# This applies to Mac OSX, please adjust the paths if you have another OS.
mkdir -p ~/Documents/Arduino/libraries/
cd ~/Documents/Arduino/libraries/
# get LED-Backpack
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

**Notes and resources**

* I wanted to use the more elaborate `NeoMatrix` library (compared to `NeoPixel`), but it turns out that it only uses 16 bit for colors. This makes my color gradients look choppy.
* I used the [ALPS STEC12E Encoder](http://www.reichelt.de/Drehimpulsgeber/STEC12E08/3/index.html?ACTION=3&GROUPID=3714&ARTICLE=73923&START=0&OFFSET=16&WKID=0&) with this data sheet [specification](https://cdn-reichelt.de/documents/datenblatt/F100/402097STEC12E08.PDF).
* I tried to use interrupts for [reading the encoder](http://playground.arduino.cc/Main/RotaryEncoders), but the [bounce](https://hifiduino.wordpress.com/2010/10/20/rotaryencoder-hw-sw-no-debounce/) was too hard. Now, I do it in the `loop` now and works fine. As it seems as I do not need to debounce the signal in my case. But if you decide to do so, I found this [nice article](https://hifiduino.wordpress.com/2010/10/20/rotaryencoder-hw-sw-no-debounce) (i.e. see "updated" part). Also there is a [Arduino Playground page](http://playground.arduino.cc/code/bounce) about it.
* For the DS1307 Real Time Clock Module, I found some [documentation](http://www.sainsmart.com/arduino-i2c-rtc-ds1307-at24c32-real-time-clock-module-board-for-avr-arm-pic.html) (not necessarily for the one I bought, but better than nothing). Also [Adafruit's page](https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/arduino-library) was helpful.
* At one point, I wanted to check my code for code style mistakes and wrote the script `indent_code.sh`. It checks all files and asks you to correct them according to this project's style.

## Uploading

I used the [Arduino GUI](https://www.arduino.cc/en/Main/Software) for compiling and uploading the software.
With my version of the Arduino with USB, I selected `Arduino Nano`, chose `ATmega328` and selected the `/dev/cu.usbserial-xxxxxx` port.
If you have downloaded the libraries as mentioned above, you should be able to compile and upload.

**With some models of the Arduino you may have to hit the reset button during upload.**.
Go to the settings of the Arduino GUI and activate verbose output during upload.
Then when you see a big banner like the following, quickly press the reset button on the board.

```text
avrdude: Version 6.0.1, compiled on Apr 14 2015 at 16:30:25
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2009 Joerg Wunsch

         System wide configuration file is "/opt/homebrew-cask/Caskroom/arduino/1.6.5/Arduino.app/Contents/Java/hardware/tools/avr/etc/avrdude.conf"
         User configuration file is "/Users/motine/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : /dev/cu.usbserial-A50285BI
         Using Programmer              : arduino
         Overriding Baud Rate          : 57600
```

<!--In order to program the Arduino Pro Mini, please use a FTDI board (the Arduino does not have a USB connection, so we have to go through a serial connection).
Here my wiring for the setup (note that I did not solder the headers to the Arduino so I can easily remove it):

![USB - FTDI - Arduino Pro Mini](https://raw.githubusercontent.com/motine/sternenwecker/master/wiring/usb-serial-aruino.png)
-->

## Box

![boxes assembled](https://raw.githubusercontent.com/motine/sternenwecker/master/box/boxes-assembled.jpg)

I went to [FabLab Berlin](https://fablab.berlin/en/) and laser cut a small and a large version of the box.
The larger version (`smallbox.svg`, not `tinybox.svg`) did fit and look better. In the file, the blue path means _cut_ and the green one means _mark_.
This time, I did not shrink the jags to fit on by pressing them in. I did glue the box together:

![boxes cut](https://raw.githubusercontent.com/motine/sternenwecker/master/box/box-cut.jpg)
![boxes glued](https://raw.githubusercontent.com/motine/sternenwecker/master/box/box-glue-bracket.jpg)
![boxes glue](https://raw.githubusercontent.com/motine/sternenwecker/master/box/box-glue.jpg)

## Concept

![drawings](https://raw.githubusercontent.com/motine/sternenwecker/master/concept/digits-1-trim.jpeg)

There was a lot of thinking about how the sternenwecker shall work. I have hardly documented anything.
Feel free to browse the `concept` folder, [prior commits](https://github.com/motine/sternenwecker/commits/master) or the [other branch](https://github.com/motine/sternenwecker/tree/single_matrix).

Please also feel free to contact me (see my [profile](https://github.com/motine)).

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
