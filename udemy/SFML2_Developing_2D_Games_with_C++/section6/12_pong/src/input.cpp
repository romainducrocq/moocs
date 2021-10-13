#include "../include/input.h"

Input::Input(){
    this->button.left =
    this->button.right = 
    this->button.up = 
    this->button.down = 
    this->button.escape = 
    false;
}

Input::~Input() {}

Input::Button Input::getButton(void) const{
    return this->button;
}

void Input::inputHandler(Event event, RenderWindow& window){
    if(event.type == Event::Closed){
        window.close();
    }else if(event.type == Event::KeyPressed){
        switch(event.key.code){
        case Keyboard::Escape:
            this->button.escape = true;
            break;
        case Keyboard::Left:
            this->button.left = true;
            break;
        case Keyboard::Right:
            this->button.right = true;
            break;
        case Keyboard::Up:
            this->button.up = true;
            break;
        case Keyboard::Down:
            this->button.down = true;
            break;        
        default:
            break;
        }
    }else if(event.type == Event::KeyReleased){
        switch(event.key.code){
        case Keyboard::Escape:
            this->button.escape = false;
            break;
        case Keyboard::Left:
            this->button.left = false;
            break;
        case Keyboard::Right:
            this->button.right = false;
            break;
        case Keyboard::Up:
            this->button.up = false;
            break;
        case Keyboard::Down:
            this->button.down = false;
            break;        
        default:
            break;
        }
    }
}

