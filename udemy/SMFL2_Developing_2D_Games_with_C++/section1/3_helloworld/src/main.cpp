#include "../include/main.h"

RenderWindow window;
Input input;
Font font;
Text txt;

int posX = WIN_WIDTH / 2, posY = WIN_HEIGHT / 2;

int main(){
    ContextSettings options;
    options.antialiasingLevel = 8;

    window.create(VideoMode(WIN_WIDTH,WIN_HEIGHT,32), "Hello World !", Style::Default, options);
    window.setVerticalSyncEnabled(true);

    loadFont();
    setText("Hello World !");

    CircleShape circleShape(75.f);
    circleShape.setFillColor(Color(100, 175, 80, 150));
    circleShape.setOutlineColor(Color::Red);
    circleShape.setOutlineThickness(5);

    RectangleShape rectangleShape(Vector2f(120.f, 50.f));
    rectangleShape.setFillColor(Color(141, 95, 43, 100));
    rectangleShape.setOutlineColor(Color::Blue);
    rectangleShape.setOutlineThickness(2);
    rectangleShape.setPosition(200, 300);
    rectangleShape.setSize(Vector2f(150, 300));

    CircleShape triangle(80.f, 3);
    triangle.setFillColor(Color::Green);
    triangle.setOutlineColor(Color::Black);
    triangle.setOutlineThickness(1);
    triangle.setPosition(400, 400);

    ConvexShape convex;
    convex.setPointCount(5);
    convex.setPoint(0, Vector2f(0.f, 0.f));
    convex.setPoint(1, Vector2f(150.f, 10.f));
    convex.setPoint(2, Vector2f(120.f, 90.f));
    convex.setPoint(3, Vector2f(30.f, 100.f));
    convex.setPoint(4, Vector2f(0.f, 50.f));
    convex.setFillColor(Color::White);
    convex.setOutlineColor(Color::Black);
    convex.setOutlineThickness(1);
    convex.setPosition(10, 400);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            input.inputHandler(event, window);
        }
        checkButton();
        circleShape.setPosition(posX, posY);

        window.clear(Color::Black);
        
        window.draw(txt);
        window.draw(rectangleShape);
        window.draw(triangle);
        window.draw(convex);
        window.draw(circleShape);
        
        window.display();
    }

    return 0;
}

void loadFont(){
    if(!font.loadFromFile(FONT_DIR + "ubuntu/Ubuntu-Regular.ttf")){
        cout << "[ERROR] Failed to load font ..." << endl;
    }
}

void setText(const string str){
    txt.setFont(font);
    txt.setString(str);
    txt.setCharacterSize(32);
    txt.setFillColor(Color::White);
    txt.setStyle(Text::Bold | Text::Underlined);
}

void checkButton(){
    string str = "Hello World !";
    if(input.getButton().up == true){
        str = "Up";
        if(posY > 0){ posY -= 1; }
    }
    if(input.getButton().down == true){
        str = "Down";
        if(posY < WIN_HEIGHT){ posY += 1; }
    }
    if(input.getButton().left == true){
        str = "Left";
        if(posX > 0){ posX -= 1; }
    }
    if(input.getButton().right == true){
        str = "Right";
        if(posX < WIN_WIDTH){ posX += 1; }
    }
    if(input.getButton().escape == true){
        str = "Escape";
    }
    if(input.getButton().attack == true){
        str = "Attack";
    }

    str += "\n(X: " + 
            to_string(posX) +
            ", Y: " +
            to_string(posY) +
            ")";

    setText(str);
}