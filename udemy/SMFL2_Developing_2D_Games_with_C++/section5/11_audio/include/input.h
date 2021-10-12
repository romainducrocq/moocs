#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Input{
    struct Button{ 
        bool down, right, up, left, attack, magic, escape;
    };

    private:
        Button button;

    public:
        Input();
        ~Input();

        Button getButton() const;

        void inputHandler(Event event, RenderWindow& window);
};

#endif