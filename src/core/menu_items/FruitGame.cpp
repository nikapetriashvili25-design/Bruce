#include "FruitGame.h"
#include "core/display.h"
#include "core/utils.h"
#include <globals.h>

static void drawCherry(int x, int y) {
    tft.drawLine(x - 5, y - 12, x - 1, y - 20, TFT_GREEN);
    tft.drawLine(x - 1, y - 20, x + 5, y - 13, TFT_GREEN);
    tft.fillCircle(x - 6, y - 5, 6, TFT_RED);
    tft.fillCircle(x + 6, y - 5, 6, TFT_RED);
    tft.fillCircle(x - 8, y - 7, 2, TFT_WHITE);
}

static void drawWatermelon(int x, int y) {
    tft.fillTriangle(x - 18, y + 10, x + 18, y + 10, x, y - 16, TFT_GREEN);
    tft.fillTriangle(x - 13, y + 7, x + 13, y + 7, x, y - 11, TFT_RED);
    tft.fillCircle(x - 5, y - 1, 1, TFT_BLACK);
    tft.fillCircle(x + 3, y - 4, 1, TFT_BLACK);
    tft.fillCircle(x + 7, y + 2, 1, TFT_BLACK);
}

static void drawOrange(int x, int y) {
    tft.fillCircle(x, y, 15, TFT_ORANGE);
    tft.fillCircle(x - 5, y - 5, 3, TFT_YELLOW);
    tft.fillCircle(x, y - 16, 3, TFT_GREEN);
}

static void drawApple(int x, int y) {
    tft.fillCircle(x - 7, y, 11, TFT_RED);
    tft.fillCircle(x + 7, y, 11, TFT_RED);
    tft.fillRect(x - 7, y - 2, 14, 12, TFT_RED);
    tft.drawLine(x, y - 10, x + 3, y - 18, TFT_GREEN);
    tft.fillCircle(x + 7, y - 17, 4, TFT_GREEN);
}

static void drawGrapes(int x, int y) {
    tft.fillCircle(x, y - 11, 5, TFT_PURPLE);
    tft.fillCircle(x - 7, y - 5, 5, TFT_PURPLE);
    tft.fillCircle(x + 7, y - 5, 5, TFT_PURPLE);
    tft.fillCircle(x - 10, y + 3, 5, TFT_PURPLE);
    tft.fillCircle(x, y + 3, 5, TFT_PURPLE);
    tft.fillCircle(x + 10, y + 3, 5, TFT_PURPLE);
    tft.fillCircle(x, y + 12, 5, TFT_PURPLE);
}

static void drawFruit(int type, int x, int y) {
    switch (type) {
        case 0: drawCherry(x, y); break;
        case 1: drawWatermelon(x, y); break;
        case 2: drawOrange(x, y); break;
        case 3: drawApple(x, y); break;
        case 4: drawGrapes(x, y); break;
    }
}

void FruitGame::optionsMenu() {
    int fruit[3] = {0, 1, 2};
    int offset[3] = {0, 0, 0};
    bool spinning = false;

    unsigned long lastFrame = millis();
    unsigned long spinStart = 0;

    while (!check(EscPress)) {
        unsigned long now = millis();

        if (check(SelPress)) {
            spinning = true;
            spinStart = now;
        }
        if (spinning && now - spinStart > 1800) {
            spinning = false;

            for (int i = 0; i < 3; i++) {
                fruit[i] = random(0, 5);
                offset[i] = 0;
            }
        }

        if (now - lastFrame >= 45) {
            lastFrame = now;

            if (spinning) {
                for (int i = 0; i < 3; i++) {
                    offset[i] += 7;

                    if (offset[i] >= 42) {
                        offset[i] -= 42;
                        fruit[i] = random(0, 5);
                    }
                }
            }
            tft.fillScreen(bruceConfig.bgColor);

            tft.setTextColor(
                bruceConfig.priColor,
                bruceConfig.bgColor
            );

            tft.drawCentreString(
                "FRUIT GAME",
                tftWidth / 2,
                4,
                2
            );

            int reelW = 64;
            int reelH = 75;
            int startX = (tftWidth - reelW * 3 - 20) / 2;
            int topY = 30;

            for (int r = 0; r < 3; r++) {
                int x = startX + r * (reelW + 10);

                tft.drawRect(
                    x,
                    topY,
                    reelW,
                    reelH,
                    bruceConfig.priColor
                );
                for (int row = -1; row <= 2; row++) {
                    int fy = topY + 25 + row * 42 + offset[r];
                    int shown = (fruit[r] + row + 5) % 5;
                    drawFruit(shown, x + reelW / 2, fy);
                }
            }
            tft.drawCentreString(
                spinning ? "SPINNING..." : "SELECT = SPIN",
                tftWidth / 2,
                tftHeight - 18,
                1
            );
        }

        delay(1);
    }

    EscPress = false;
}

void FruitGame::drawIcon(float scale) {
    clearIconArea();

    tft.fillCircle(iconCenterX, iconCenterY, 12 * scale, TFT_RED);
    tft.fillCircle(iconCenterX + 10 * scale, iconCenterY, 12 * scale, TFT_RED);
    tft.drawLine(
        iconCenterX + 2 * scale,
        iconCenterY - 10 * scale,
        iconCenterX + 7 * scale,
        iconCenterY - 20 * scale,
        TFT_GREEN
    );
}
