# Basic Raspberry Pi Pico Microsoft Teams Keyboard
This is the GitHub repository for the project: https://buildcomics.com/ (TO Be Determined) \
You will also find the "instructions"  there!

## Models for 3D Printing
Find all the models for the Keyboard here: (TODO)

## Wiring
I used one common cathode RGB LED 5mm wired with resistors. The led pinout goes as follows, counted from pin 1 as being the pin closest to the flat in the bottom of the LED:\
1. Pin 1:RED, 68 ohm ==> GPIO 5
2. Pin 2:CC, ==> GND
3. Pin 3:BLUE, 15 ohm ==> GPIO 6
4. Pin 4:GREEN, 39 ohm ==> GPIO 7

Note, the GPIO pins are based on the following piece of code in main.c. You can freely change these (apart from GPIO 0 & 1) by changing this code:
```
#define LED_1_RED_GPIO 5
#define LED_1_GREEN_GPIO 7
#define LED_1_BLUE_GPIO 6
```
## Basic installation
1. Download main.uf2 from the releases page: https://github.com/buildcomics/Busylight/releases
2. Press the button on your raspberry pi Pico, and then connect it to your computer
3. copy the "main.uf2" from the release page to the "RPI2" that shows up as a mass storage usb devcie
4. Make sure your PC side software is installed

## Main Code
The main code is based on Tinyusb: https://github.com/hathach/tinyusb \
The device mimics a standard keyboard \
It sends the keyboard shortcut for Microsoft Teams as defined here: https://support.microsoft.com/en-us/office/keyboard-shortcuts-for-microsoft-teams-2e8e2a70-e8d8-4a19-949b-4c36dd5292d2

### Compiling the code
If you want to change the code and nteed to compile it, do the following:
Assuming you have the raspberry pi pico c SDK installed(https://github.com/raspberrypi/pico-sdk) \
The following (standard) commands will create "main.uf2" that can be copied onto the raspberry pi in bootsel mode:
1. git clone git@github.com:buildcomics/Busylight.git
2. cd Busylight
3. mkdir build
4. cd build
5. cmake ..
6. make
7. Now press the button on your raspbery pi pico, connect it and copy the main.uf2 to the pico that should show up ass a mass storage device

## Testing
Command to test HID descriptor of file: \
`sudo usbhid-dump -a 1:58 | grep -v : | xxd -r  -p | hidrd-convert -o spec`
\
using the hidrd tool from: https://github.com/DIGImend/hidrd

## License
MIT License

Copyright (c) 2021 buildcomics

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
