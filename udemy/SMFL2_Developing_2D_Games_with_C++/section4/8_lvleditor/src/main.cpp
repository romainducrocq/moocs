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

enum AnimPlayer{ Down, Right, Up, Left, DownAtk, RightAtk, UpAtk, LeftAtk };
Vector2i animPlayerSprite(0, Down);
Clock animPlayerClock;
bool animPlayerIdle = true;
bool animPlayerReset = false;

int levelTiles[MAP_COL * MAP_ROW];
int levelCollisions[MAP_COL * MAP_ROW];
RectangleShape debugCollisions[MAP_COL * MAP_ROW];

int main(){
    window.create(VideoMode(WIN_WIDTH,WIN_HEIGHT,32), "MY SFML GAME", Style::Default);
    window.setVerticalSyncEnabled(true);

    if(!playerTexture.loadFromFile(RES_DIR + "sprite/player_sprite_sheet.png")){
        LOG("[ERROR] Failed load texture ...");
    }
    playerSprite.setTexture(playerTexture);

    updateTilemap();

    gotoTilemap2.setFillColor(Color(255, 0, 0, 100));
    gotoTilemap2.setPosition(SPRITE_SIZE * 6, 0);

    gotoTilemap1.setFillColor(Color(255, 0, 0, 100));
    gotoTilemap1.setPosition(SPRITE_SIZE * 6, SPRITE_SIZE * 17);

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            input.inputHandler(event, window);
        }
        checkButton();
        animPlayer();

        window.clear(Color::Black);

        window.draw(tilemap);
        window.draw(playerSprite);
        window.draw(gotoTilemap1);
        window.draw(gotoTilemap2);

        if(DEBUG){
            for(unsigned int i = 0; i < MAP_ROW; i++){
                for(unsigned int j = 0; j < MAP_COL; j++){
                    if(levelCollisions[j + i * MAP_COL]){
                        debugCollisions[j + i * MAP_COL].setPosition(Vector2f(j * SPRITE_SIZE, i * SPRITE_SIZE));
                        debugCollisions[j + i * MAP_COL].setSize(Vector2f(SPRITE_SIZE, SPRITE_SIZE));
                        debugCollisions[j + i * MAP_COL].setFillColor(Color(255, 0, 0, 100));
                        window.draw(debugCollisions[j + i * MAP_COL]);
                    }
                }
            }
        }

        simpleCollisions();

        window.display();
    }

    return 0;
}

void checkButton(){
    int playerPosX = round(playerSprite.getPosition().x / SPRITE_SIZE);
    int playerPosY = round(playerSprite.getPosition().y / SPRITE_SIZE);

    if(!animPlayerReset){
        if(input.getButton().down == true){
            animPlayerSprite.y = Down;
            playerPosY = round((playerSprite.getPosition().y  + MOVE_SPEED + 1) / SPRITE_SIZE);
            if(levelCollisions[playerPosX + playerPosY * MAP_COL] == 0 && playerPosY < MAP_ROW){
                playerSprite.move(0, MOVE_SPEED);
            }
            animPlayerIdle = false;
        }else if(input.getButton().right == true){
            animPlayerSprite.y = Right; 
            playerPosX = round((playerSprite.getPosition().x  + MOVE_SPEED + 1) / SPRITE_SIZE);
            if(levelCollisions[playerPosX + playerPosY * MAP_COL] == 0 && playerPosX < MAP_COL){
                playerSprite.move(MOVE_SPEED, 0);
            }
            animPlayerIdle = false;
        }else if(input.getButton().up == true){
            animPlayerSprite.y = Up; 
            playerPosY = round((playerSprite.getPosition().y  - MOVE_SPEED - 1) / SPRITE_SIZE);
            if(levelCollisions[playerPosX + playerPosY * MAP_COL] == 0 && playerPosY >= 0){
                playerSprite.move(0, -MOVE_SPEED);            
            }
            animPlayerIdle = false;
        }else if(input.getButton().left == true){
            animPlayerSprite.y = Left; 
            playerPosX = round((playerSprite.getPosition().x  - MOVE_SPEED - 1) / SPRITE_SIZE);
            if(levelCollisions[playerPosX + playerPosY * MAP_COL] == 0 && playerPosX >= 0){
                playerSprite.move(-MOVE_SPEED, 0);
            }
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

vector<string> explode(const string& s, char delim){
    vector<string> result;
    istringstream iss(s);

    for(string token; getline(iss, token, delim); ){
        result.push_back(move(token));
    }

    return result;
}

void loadArrLevel2D(int* arrLevel, const string& path, int n){
    string str;
    ifstream ifs(RES_DIR + path + "/" + path + to_string(n) + ".txt");
    for(int i = 0; i < MAP_ROW; i++){
        if(!getline(ifs, str)) { break; }
        vector<string> vstr = explode(str, ' ');
        for(int j = 0; j < MAP_COL; j++){
            arrLevel[j + i * MAP_COL] = stoi(vstr[j]);
        }
    }
}

void loadArrLevel1D(int* arrLevel, const string& path, int n){
    ifstream ifs(RES_DIR + path + "/" + path + to_string(n) + ".txt");
    string str((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));
    vector<string> vstr = explode(str, ' ');
    for (int i = 0; i < MAP_ROW * MAP_COL; i++){
        arrLevel[i] = stoi(vstr[i]);
    }
}

void updateTilemap(){
    loadArrLevel1D(levelTiles, "tilemap", currentMap + 2);
    loadArrLevel1D(levelCollisions, "collmap", currentMap + 2);

    if(!tilemap.load(RES_DIR + "tileset/tileset2.png", Vector2u(SPRITE_SIZE, SPRITE_SIZE), levelTiles, MAP_COL, MAP_ROW)){
        LOG("[ERROR] Failed load tilemap ...");
    }
}