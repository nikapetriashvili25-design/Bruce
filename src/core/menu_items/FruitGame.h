#ifndef FRUITGAME_H
#define FRUITGAME_H

#include <MenuItemInterface.h>

class FruitGame : public MenuItemInterface {
public:
    FruitGame() : MenuItemInterface("Fruit Game") {}

    void optionsMenu(void) override;
    void drawIcon(float scale) override;

    bool hasTheme() override { return false; }
    const String& themePath() override {
        static String empty = "";
        return empty;
    }
};

#endif
