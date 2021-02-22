// vim:ft=arduino

#include "M5Atom.h"
#include <BleKeyboard.h>


BleKeyboard bleKeyboard;

#define ZOOM_MODE 1
#define HANGOUTS_MODE 2

#define HANGOUTS

#if defined(ZOOM)
    int color = 0x0000ff;
#elif defined(HANGOUTS)
    int color = 0xff0000;  // FIXME: why 0x00ff00 gives red? is it GRB?
#endif

const int BRIGHTNESS = 20;


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

    fill(color);
    delay(500);
}

void toggleMic()
{
#if defined(ZOOM)
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.write('a');
    delay(10);
    bleKeyboard.release(KEY_LEFT_ALT);
#elif defined(HANGOUTS)
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.write('d');
    delay(10);
    bleKeyboard.release(KEY_LEFT_CTRL);
#endif
}

void loop()
{
    if (M5.Btn.wasPressed()) {
        toggleMic();
        fill(color);

        for (int b = BRIGHTNESS; b > 0; b--) {
            M5.dis.setBrightness(b);
            delay(2 * BRIGHTNESS - b);
        }
    }
    M5.update();
}
