/*
Sprite sheets available at:
- Universal LPC Sprite Sheet
- OpenGameArt.org
- itch.io
*/

#include "../include/main.h"

RenderWindow window;
Input input;

Texture playerTexture;
Sprite playerSprite;

enum AnimPlayer{ Down, Right, Up, Left, DownAtk, RightAtk, UpAtk, LeftAtk };
Vector2i animPlayerSprite(0, Down);
Clock animPlayerClock;
bool animPlayerIdle = true;
bool animPlayerReset = false;

RectangleShape cube(Vector2f(SPRITE_SIZE, SPRITE_SIZE));
FloatRect cubeHitbox;
FloatRect playerHitbox;

uint nbCollisions = 0;

int main(){
    window.create(VideoMode(WIN_WIDTH,WIN_HEIGHT,32), "MY SFML GAME", Style::Default);
    window.setVerticalSyncEnabled(true);

    if(!playerTexture.loadFromFile(RES_DIR + "sprite/player_sprite_sheet.png")){
        LOG("[ERROR] Failed lod texture ...");
    }
    playerSprite.setTexture(playerTexture);

    cube.setFillColor(Color(255,0,0,100));
    cube.setPosition((WIN_WIDTH - SPRITE_SIZE) / 2, (WIN_HEIGHT - SPRITE_SIZE) / 2);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            input.inputHandler(event, window);
        }
        checkButton();
        animPlayer();
        simpleCheckCollisions();

        window.clear(Color::Black);
        
        window.draw(playerSprite);
        window.draw(cube);

        window.display();
    }

    return 0;
}

void checkButton(){
    if(!animPlayerReset){
        if(input.getButton().down == true){
            animPlayerSprite.y = Down; 
            playerSprite.move(0, MOVE_SPEED);
            animPlayerIdle = false;
        }else if(input.getButton().right == true){
            animPlayerSprite.y = Right; 
            playerSprite.move(MOVE_SPEED, 0);
            animPlayerIdle = false;
        }else if(input.getButton().up == true){
            animPlayerSprite.y = Up; 
            playerSprite.move(0, -MOVE_SPEED);
            animPlayerIdle = false;
        }else if(input.getButton().left == true){
            animPlayerSprite.y = Left; 
            playerSprite.move(-MOVE_SPEED, 0);
            animPlayerIdle = false;
        }else{
            animPlayerIdle = true;
        }
        if(input.getButton().attack == true){
            animPlayerReset = true;
            animPlayerSprite.x = 0;
            animPlayerSprite.y += 4;
        }
    }
    if(input.getButton().escape == true){
        window.close();
    }
}

void animPlayer(){
    playerSprite.setTextureRect(IntRect(animPlayerSprite.x * SPRITE_SIZE, animPlayerSprite.y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE));
    if(animPlayerClock.getElapsedTime().asSeconds() > 0.1f){
        if(animPlayerSprite.x * SPRITE_SIZE >= (int)playerTexture.getSize().x - SPRITE_SIZE){      
            animPlayerSprite.x = 0;
            if(animPlayerReset){
                animPlayerReset = false;
                animPlayerSprite.y -= 4;
            }
        }else if(!animPlayerIdle || animPlayerReset){
            animPlayerSprite.x++;
        }
        animPlayerClock.restart();
    }
}

void simpleCheckCollisions(){
    cubeHitbox = cube.getGlobalBounds();
    playerHitbox = playerSprite.getGlobalBounds();
    
    if(playerHitbox.intersects(cubeHitbox)){
        nbCollisions++;
        LOG("COLLISION " << nbCollisions);
        cube.setPosition(rand() % WIN_WIDTH - SPRITE_SIZE, rand() % WIN_HEIGHT - SPRITE_SIZE); 
    }
}