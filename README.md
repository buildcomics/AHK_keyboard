# Raspberry Pi Pico AutoHotkey Streamdeck / Keyboard with LEDs
This is the GitHub repository for the project: https://buildcomics.com/3d-printing/a-microsoft-teams-adventure/ \
You will also find the "instructions"  there!

## Current state
Not able to get a HID Control request to the Device using the "control_leds.ahk" autohotkey script. Time to signal for help: https://www.autohotkey.com/boards/viewtopic.php?t=89209\

Find all the models for the Keyboard here: https://www.prusaprinters.org/prints/64087-streamdeck-for-autohotkey

## Wiring
Refer to the Busylight repo for resistors and wiring of RGB LEDS: https://github.com/buildcomics/busylight \
The switches are wired one side to ground and the other to a pin.
The exact pins are as defined in the pin definitions main.c, these are the defaults, but change at will:
```
#define BUTTON_NUMBER 4
#define BTN_1_GPIO 4
#define BTN_2_GPIO 8
#define BTN_3_GPIO 10
#define BTN_4_GPIO 11

#define LED_1_RED_GPIO 2
#define LED_2_RED_GPIO 3
#define LED_3_RED_GPIO 5
#define LED_4_RED_GPIO 9

#define LED_1_GREEN_GPIO 6
#define LED_2_GREEN_GPIO 12
#define LED_3_GREEN_GPIO 14
#define LED_4_GREEN_GPIO 15

#define LED_1_BLUE_GPIO 21
#define LED_2_BLUE_GPIO 16
#define LED_3_BLUE_GPIO 22
#define LED_4_BLUE_GPIO 17

```
## Basic installation
1. Download main.uf2 from the releases page: https://github.com/buildcomics/Busylight/releases.
2. Press the button on your raspberry pi Pico, and then connect it to your computer.
3. copy the "main.uf2" from the release page to the "RPI2" that shows up as a mass storage USB device.
4. Install autohotkey: https://www.autohotkey.com/
5. Use an AHK script to control your computer. See AHK Scripts for an example to control microsoft teams.

## Still TODO
1. Find away to "feedback"  the mute and camera status to the keyboard from AHK. As of now the buttons change colour when you press them, so it is (VERY) possible to "misalign"  the colours and the actual microphone and camera state. You can help me out here:     https://github.com/hathach/tinyusb/discussions/667 \
    https://www.autohotkey.com/boards/viewtopic.php?t=89209

## Main Code
The main code is based on Tinyusb: https://github.com/hathach/tinyusb \
The device mimics a standard keyboard \
It sends the keys F14-F18 which can be picked up by AHK. It switches the colour of the first two buttons when pressed.

### Compiling the code
If you want to change the code and nteed to compile it, do the following:
Assuming you have the raspberry pi pico c SDK installed(https://github.com/raspberrypi/pico-sdk) \
The following (standard) commands will create "main.uf2" that can be copied onto the raspberry pi in bootsel mode:
1. git clone git@github.com:buildcomics/AHK_keyboard.git
2. cd AHK_keyboard
3. mkdir build
4. cd build
5. cmake ..
6. make
7. Now press the button on your raspbery pi pico, connect it and copy the main.uf2 to the pico that should show up ass a mass storage device

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
