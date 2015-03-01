Lightalarmy

# Parts

- Arduino
- Adafruit NeoPixel 8x8 ([shop](http://www.flikto.de/products/adafruit-neopixel-neomatrix-8x8-64-rgb-led-pixel-matrix))
- DS1307 Real Time clock ([shop](http://www.amazon.de/DS1307-AT24C32-Module-Arduino-Mega2560/dp/B00G6B6MGS/ref=sr_1_6?ie=UTF8&qid=1425019440&sr=8-6&keywords=Ds1307))
- Potentiometer with button functionality

# Notes

When waking, use a gradient from red over blue to white.

Use the pot to set the alarm. One can only set alarms between 6:00-9:55. The pot operates in 5 min steps. For displaying the hour use 3x5 digit and twice 2x5 for the minutes. This leaves one pixel space between hour and minutes.
The time is only shown if the pot is pushed down. The time then scrolls through.

When the alarm is ongoing, show the time occasionally. The surrounding pixels which are not needed to show the scrolling digits shall then still be bright white.


# Maybe

Sound as a fail safe at the end (but you would usually set another device anyway).

# TODO

* Test the hour on top of the minutes on one 8x8 screen with the 3x4 font (see sketches).