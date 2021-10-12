#ifndef _INPUT_H
#define _INPUT_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Input{
    struct Button{ 
        bool up, down, left, right, escape, attack; 
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