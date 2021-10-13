#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Input{
    struct Button {bool left, right, up, down, escape; };

    private:
        Button button;

    public:
        Input();
        ~Input();

        Button getButton(void) const;
        void inputHandler(Event event, RenderWindow& window);
};

#endif