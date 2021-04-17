#include <stdio.h>
#include <stdio.h>
#include <string.h>

#include "pico/stdlib.h"

#include "bsp/board.h"
#include "tusb.h"

#include "usb_descriptors.h"

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

#define START_KEY HID_KEY_F14

#define EVENT_MASK_LOW 0x1
#define EVENT_MASK_HIGH 0x2

/* Wiring
LED flat side pin 1:RED, 68 ohm ==> GPIO
LED flat side pin 2:CC, ==> GND
LED flat side pin 3:BLUE, 15 ohm ==> GPIO
LED flat side pin 4:GREEN, 39 ohm ==> GPIO
*/

//Function Prototypes
void hid_task(void);
void test_lights();

const uint buttons[BUTTON_NUMBER] = {BTN_1_GPIO, BTN_2_GPIO, BTN_3_GPIO, BTN_4_GPIO};
const uint leds[BUTTON_NUMBER][3] = {{LED_1_RED_GPIO, LED_1_GREEN_GPIO, LED_1_BLUE_GPIO},
                                     {LED_2_RED_GPIO, LED_2_GREEN_GPIO, LED_2_BLUE_GPIO},
                                     {LED_3_RED_GPIO, LED_3_GREEN_GPIO, LED_3_BLUE_GPIO},
                                     {LED_4_RED_GPIO, LED_4_GREEN_GPIO, LED_4_BLUE_GPIO}};
const bool led_state_buttons[BUTTON_NUMBER] = {true, true, false, false}; //Defines which buttons should have statefull LEDS
bool button_state[BUTTON_NUMBER] = {false, false, false, false};
bool led_state[BUTTON_NUMBER] = {false, false, false, false};

int main() {
    stdio_init_all(); //Initialize debug interface
    printf("DEBUG: starting up buildcomics HID device...\n");

    board_init();
    tusb_init();
    printf("DEBUG: HID Device initialized\n");

    for (int i = 0; i<BUTTON_NUMBER; i++) { //For all buttons
        printf("DEBUG: Setting up gpio.\n");
        gpio_pull_up(buttons[i]); //Enable pullup
        for (int j = 0; j<3; j++) { //For all LEDS (one under each button)
            gpio_init(leds[i][j]); //Initialize as output for LED
            gpio_set_dir(leds[i][j], GPIO_OUT);
        }
    }

    printf("DEBUG: GPIO setting finished.\n");
    test_lights();
    printf("DEBUG: Light Test Finished.\n");

    for (int i = 0; i<BUTTON_NUMBER; i++) { //For all buttons
        if (led_state_buttons[i]) {
            gpio_put(leds[i][1], 1); //Set green LED on for statefull buttons
        }
    }

    while (true){ // MAIN LOOP
        hid_task(); //HID Task
        tud_task(); // tinyusb device task
    }
    return 0;
}

/* Test the lights (one led under each button) by cycling through all the colours */
void test_lights() {
     for (int j = 0; j<3; j++) {
         for (int i = 0; i<BUTTON_NUMBER; i++) {
           gpio_put(leds[i][j], 1);
         }
         sleep_ms(200);
         for (int i = 0; i<BUTTON_NUMBER; i++) {
           gpio_put(leds[i][j], 0);
         }
    }
}

// Invoked when device is mounted
void tud_mount_cb(void) {
    printf("DEBUG: Mounted\n");
}

// Invoked when device is unmounted
void tud_umount_cb(void) {
    printf("DEBUG: Unmounted\n");
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en) {
    (void) remote_wakeup_en;
    printf("DEBUG: Suspended\n");
}

// Invoked when usb bus is resumed
void tud_resume_cb(void) {
    printf("DEBUG: Resumed Mounted\n");
}

// USB HID Task
void hid_task(void) {
    // Poll every 10ms
    const uint32_t interval_ms = 10;
    static uint32_t start_ms = 0;

    if (board_millis() - start_ms < interval_ms) return; // not enough time
    start_ms += interval_ms;

    for (int i = 0; i<BUTTON_NUMBER; i++) {
        if (!gpio_get(buttons[i])) { //If the button is pressed
            if (tud_suspended()) { //Wakeup if we are sleeping
                tud_remote_wakeup();
            }
            if (!button_state[i]) { //If the button state was previously different
                printf("DEBUG: Button pressed!\n" );
               if (tud_hid_ready()) {
                   uint8_t keycode[6] = {0};
                   keycode[0] = START_KEY + i;
                   tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0 , keycode);
                   button_state[i] = true;

                   if (led_state_buttons[i]) { //This button has a statefull LED
                      if (led_state[i]) { //Current value is true = green, change to false = red
                        gpio_put(leds[i][0], 0); //Set red LED off
                        gpio_put(leds[i][1], 1); //Set green LED on
                        led_state[i] = false;
                      }
                      else {
                        gpio_put(leds[i][0], 1); //Set red LED on
                        gpio_put(leds[i][1], 0); //Set green LED off
                        led_state[i] = true;
                      }
                   }
               }
           }
        }
        else { //If the button is depressed
           if (button_state[i]) { //If the button state was previously different
               if (tud_hid_ready()) {
                   tud_hid_keyboard_report(REPORT_ID_KEYBOARD, 0, NULL); //Release Key
                   button_state[i] = false;
               }
           }
        }
    }
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t *buffer, uint16_t reqlen) {
    // TODO not Implemented
    printf("DEBUG: tud_hid_get_report_cb triggered\n");
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t report_id, hid_report_type_t report_type, uint8_t const *buffer, uint16_t bufsize) {
    // TODO set LED based on CAPLOCK, NUMLOCK etc...
    printf("DEBUG: tud_hid_set_report_cb triggered\n");
    printf("DEBUG: report_id: %X\n", report_id);
    printf("DEBUG: report_type: %X\n", report_type);
    printf("DEBUG: bufsize: %d\n", bufsize);

    printf("DEBUG: buffer content:\n");
    for (int i = 0; i < bufsize; i++) {
        printf("%02X ", buffer[i]);
    }
    printf(" - End \n");
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) bufsize;
}
