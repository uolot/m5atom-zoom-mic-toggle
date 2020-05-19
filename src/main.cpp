// vim:ft=arduino

#include "M5Atom.h"
#include <BleKeyboard.h>


#define BRIGHTNESS 20

BleKeyboard bleKeyboard;


void fill(int color)
{
    for (int pos = 0; pos < 25; pos++) {
        M5.dis.drawpix(pos, color);
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

void setup()
{
    M5.begin(true, false, true);
    M5.dis.setBrightness(BRIGHTNESS);
    bleKeyboard.begin();
    waitForConnection();
    fill(CRGB::Blue);
    delay(500);
}

void toggleMic()
{
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write('a');
    delay(10);
    bleKeyboard.release(KEY_LEFT_ALT);
}

void loop()
{
    if (M5.Btn.wasPressed()) {
        toggleMic();
        fill(CRGB::Blue);

        for (int b = BRIGHTNESS; b > 0; b--) {
            M5.dis.setBrightness(b);
            delay(2 * BRIGHTNESS - b);
        }
    }
    M5.update();
}
