#include "../include/input.h"

Input::Input() {
    this->button.up = 
    this->button.down = 
    this->button.left =
    this->button.right =
    this->button.escape =
    this->button.attack = 
    false;
}

Input::~Input() {}

Input::Button Input::getButton() const {
    return this->button;
}

void Input::inputHandler(Event event, RenderWindow& window){
    if(event.type == Event::Closed){
        window.close();
    }

    if(event.type == Event::KeyPressed){
        switch(event.key.code){
            case Keyboard::Escape:
                this->button.escape = true;
                break;
            case Keyboard::Up:
                this->button.up = true;
                break;
            case Keyboard::Down:
                this->button.down = true;
                break;
            case Keyboard::Left:
                this->button.left = true;
                break;
            case Keyboard::Right:
                this->button.right = true;
                break;
            default:
                break; 
        }
    }

    if(event.type == Event::KeyReleased){
        switch(event.key.code){
            case Keyboard::Escape:
                this->button.escape = false;
                break;
            case Keyboard::Up:
                this->button.up = false;
                break;
            case Keyboard::Down:
                this->button.down = false;
                break;
            case Keyboard::Left:
                this->button.left = false;
                break;
            case Keyboard::Right:
                this->button.right = false;
                break;
            default:
                break; 
        }
    }

    if(event.type == Event::MouseButtonPressed){
        if(event.mouseButton.button == Mouse::Left){
            this->button.attack = true;
        }
    }


    if(event.type == Event::MouseButtonReleased){
        if(event.mouseButton.button == Mouse::Left){
            this->button.attack = false;
        }
    }
}