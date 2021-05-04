// vim:ft=arduino

#include "M5Atom.h"
#include "ButtonKing.h"
#include <BleKeyboard.h>


BleKeyboard bleKeyboard;

// FIXME: why 0x00ff00 gives red? is it GRB?
int micColor = 0xff0000;
int camColor = 0xffff00;

const int BRIGHTNESS = 20;

ButtonKing button(39, true);


void fill(int color)
{
    for (int pos = 0; pos < 25; pos++) {
        M5.dis.drawpix(pos, color);
    }
}

void fadeOut()
{
    for (int b = BRIGHTNESS; b > 0; b--) {
        M5.dis.setBrightness(b);
        delay(5);
    }
}

void waitForConnection()
{
    uint8_t x = 1;
    while (! bleKeyboard.isConnected()) {
        fill(x ? CRGB::Blue : 0);
        x ^= 1;
        delay(200);
    }
}

/* toggle mic */
void onClick()
{
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.write('d');
    delay(10);
    bleKeyboard.release(KEY_LEFT_CTRL);
    /* fill(micColor); */
    /* fadeOut(); */
}

/* switch workspace back and forth */
void onDoubleClick()
{
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write(KEY_ESC);
    delay(10);
    bleKeyboard.release(KEY_LEFT_GUI);
}

/* switch to workspace 1 */
void onTripleClick()
{
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.write('1');
    delay(10);
    bleKeyboard.release(KEY_LEFT_GUI);
}

/* toggle cam */
void onRelease()
{
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.write('e');
    delay(10);
    bleKeyboard.release(KEY_LEFT_CTRL);
    /* fill(camColor); */
    /* fadeOut(); */
}

void setup()
{
    M5.begin(true, false, true);
    M5.dis.setBrightness(BRIGHTNESS);

    bleKeyboard.begin();
    waitForConnection();

    button.setClick(onClick);
    button.setDoubleClick(onDoubleClick);
    button.setTripleClick(onTripleClick);
    button.setRelease(onRelease);

    fill(micColor);
    delay(100);
    fadeOut();
}

void loop()
{
    button.isClick();
    /* M5.update(); */
    delay(10);
}
