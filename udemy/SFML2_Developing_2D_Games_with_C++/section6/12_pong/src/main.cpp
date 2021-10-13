#include "../include/main.h"

RenderWindow window;
Input input;
Font font;
Text text;

float posXPaddleLeft = 50, posYPaddleLeft = WIN_HEIGHT / 2;
float posXPaddleRight = WIN_WIDTH - 70, posYPaddleRight =  WIN_HEIGHT / 2, speedPaddle= 0.5f;
int heightPaddle = 150, widthPaddle = 20;

float posXBall = WIN_WIDTH / 2, posYBall = WIN_HEIGHT / 2, radBall = 7.5, speedBall = 0.05f;
Vector2f dirBall = Vector2f(1.5f, 2.0f); 

int scoreP1 = 0, scoreP2 = 0;

int main(){
    window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "PONG SFML", Style::Default);

    font.loadFromFile(RES_DIR + "font/poppins.ttf");
    setText(text, to_string(scoreP1) + " | " + to_string(scoreP2));

    CircleShape circleShapeBall(radBall * 2);
    circleShapeBall.setPosition(posXBall, posYBall);

    RectangleShape rectangleShapePaddleLeft(Vector2f(widthPaddle, heightPaddle));
    rectangleShapePaddleLeft.setPosition(posXPaddleLeft, posYPaddleLeft);

    RectangleShape rectangleShapePaddleRight(Vector2f(widthPaddle, heightPaddle));
    rectangleShapePaddleRight.setPosition(posXPaddleRight, posYPaddleRight);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            input.inputHandler(event, window);
        }

        checkButton();
        autoPaddleRight();

        rectangleShapePaddleLeft.setPosition(posXPaddleLeft, posYPaddleLeft);
        rectangleShapePaddleRight.setPosition(posXPaddleRight, posYPaddleRight);

        updateBall();

        circleShapeBall.setPosition(posXBall, posYBall);

        window.clear(Color::Black);

        window.draw(text);
        window.draw(circleShapeBall);
        window.draw(rectangleShapePaddleLeft);
        window.draw(rectangleShapePaddleRight);

        window.display();

    }

    return 0;
}

void setText(Text& txt, string str){
    txt.setFont(font);
    txt.setString(str);
    txt.setCharacterSize(26);
    txt.setFillColor(Color::White);
    txt.setPosition((WIN_WIDTH / 2) - 40, 10);
}

void checkButton(){
    if(input.getButton().up == true){
        posYPaddleLeft -= speedPaddle;
        if(posYPaddleLeft < 0){
            posYPaddleLeft = 0;
        }
    }else if(input.getButton().down == true){
        posYPaddleLeft += speedPaddle;
        if(posYPaddleLeft > WIN_HEIGHT - heightPaddle){
            posYPaddleLeft = WIN_HEIGHT - heightPaddle;
        }
    }

    if(input.getButton().left == true){
        posYPaddleRight -= speedPaddle;
        if(posYPaddleRight < 0){
            posYPaddleRight = 0;
        }
    }else if(input.getButton().right == true){
        posYPaddleRight += speedPaddle;
        if(posYPaddleRight > WIN_HEIGHT - heightPaddle){
            posYPaddleRight = WIN_HEIGHT - heightPaddle;
        }
    }

    if(input.getButton().escape == true){
        window.close();
    }
}

void updateBall(){
    posXBall += dirBall.x * speedBall;
    posYBall += dirBall.y * speedBall;

    if((
        posXBall < posXPaddleLeft + widthPaddle &&
        posXBall > posXPaddleLeft &&
        posYBall < posYPaddleLeft + heightPaddle - radBall &&
        posYBall > posYPaddleLeft - radBall
    ) || (
        posXBall > posXPaddleRight - widthPaddle &&
        posXBall < posXPaddleRight &&
        posYBall < posYPaddleRight + heightPaddle - radBall &&
        posYBall > posYPaddleRight - radBall
    )){
        dirBall.x *= -1;
    }

    if(posXBall < 0){
        scoreP2++;
        posXBall = WIN_WIDTH / 2;
        posYBall = WIN_HEIGHT / 2;
        dirBall.x = fabs(dirBall.x);
        dirBall.y *= -1;
        setText(text, to_string(scoreP1) + " | " + to_string(scoreP2));
    }

    if(posXBall > WIN_WIDTH){
        scoreP1++;
        posXBall = WIN_WIDTH / 2;
        posYBall = WIN_HEIGHT / 2;
        dirBall.x = -fabs(dirBall.x);
        dirBall.y *= -1;
        setText(text, to_string(scoreP1) + " | " + to_string(scoreP2));
    }

    if(posYBall > WIN_HEIGHT || posYBall < 0){
        dirBall.y *= -1;
    }
}

void autoPaddleRight(){
    posYPaddleRight = posYBall;
}