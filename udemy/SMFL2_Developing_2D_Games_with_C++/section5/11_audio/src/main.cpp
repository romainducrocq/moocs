/*
Sprite sheets available at:
- Universal LPC Sprite Sheet
- OpenGameArt.org
- itch.io
*/

/*
Audio 8-bit available at:
- OpenGameArt.org
- freesound.org
*/

#include "../include/main.h"

RenderWindow window;
Input input;

//Sprite playerSprite;
Texture playerTexture;
enum AnimPlayer{ Down, Right, Up, Left, DownAtk, RightAtk, UpAtk, LeftAtk };
Vector2i animPlayerSprite(0, Down);
Clock animPlayerClock;
bool animPlayerIdle = true;
bool animPlayerReset = false;
int playerPosX, playerPosY;

Sprite mobSlimeSprite;
Texture mobSlimeTexture;
Vector2i animMobSlimeSprite(0, 0);
Clock animMobSlimeClock;
float mobSlimeSpeed = 0.6f;
bool isMobSlimeAlive = true;

Sprite attackArrowSprite;
Texture attackArrowTexture;
bool isAttackArrow = false; 
int dirAttackArrow = 0;
Clock attackArrowClock;

Sprite lifeHeartSprite[LIFE_N] = {};
Texture lifeHeartTexture;
int life = LIFE_N;
bool isInvincible = false;
Clock invincibleClock;

Sprite npcSprite;
Texture npcTexture;
bool npcReward = false;

Sprite textBoxSprite;
Texture textBoxTexture;
bool textBoxTy = false;

int levelTiles[MAP_COL * MAP_ROW];
int levelCollisions[MAP_COL * MAP_ROW];
RectangleShape debugCollisions[MAP_COL * MAP_ROW];

Font font;
Text text;

SoundBuffer attackSoundBuffer;
Sound attackSound;

Music music;


int main(){
    window.create(VideoMode(WIN_WIDTH,WIN_HEIGHT,32), "MY SFML GAME", Style::Default);
    window.setVerticalSyncEnabled(true);

    setup();

    while(window.isOpen()){
        Event event;
        while(window.pollEvent(event)){
            input.inputHandler(event, window);
        }

        loop();
    }

    return 0;
}

void setup(){
    if(!playerTexture.loadFromFile(RES_DIR + "sprite/player_sprite_sheet.png")){
        LOG("[ERROR] Failed load texture ...");
    }
    playerSprite.setTexture(playerTexture);

    if(!mobSlimeTexture.loadFromFile(RES_DIR + "sprite/mob_slime_sprite.png")){
        LOG("[ERROR] Failed load texture ...");
    }
    mobSlimeSprite.setTexture(mobSlimeTexture);
    mobSlimeSprite.setTextureRect(IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    mobSlimeSprite.setPosition(5 * SPRITE_SIZE, 5 * SPRITE_SIZE);
    mobSlimeSprite.setScale(0.6f, 0.6f);

    if(!attackArrowTexture.loadFromFile(RES_DIR + "sprite/attack_arrow_sprite.png")){
        LOG("[ERROR] Failed load texture ...");
    }
    attackArrowSprite.setTexture(attackArrowTexture);

    updateTilemap();

    gotoTilemap2.setFillColor(Color(255, 0, 0, 100));
    gotoTilemap2.setPosition(SPRITE_SIZE * 6, 0);

    gotoTilemap1.setFillColor(Color(255, 0, 0, 100));
    gotoTilemap1.setPosition(SPRITE_SIZE * 6, SPRITE_SIZE * 17);

    loadFont();

    lifeHeartTexture.loadFromFile(RES_DIR + "sprite/heart_sprite.png");
    for(int i = 0; i < life; i++){
        lifeHeartSprite[i].setTexture(lifeHeartTexture);
        lifeHeartSprite[i].setColor(Color(255,255,255,200));
        lifeHeartSprite[i].setPosition(5 + (i * 35), WIN_HEIGHT - SPRITE_SIZE - 5);
    }

    npcTexture.loadFromFile(RES_DIR + "sprite/npc_sprite_sheet.png");
    npcSprite.setTexture(npcTexture);
    npcSprite.setTextureRect(IntRect(0, 0, SPRITE_SIZE, SPRITE_SIZE));
    npcSprite.setPosition(10 * SPRITE_SIZE, 10 * SPRITE_SIZE);
    npcSprite.setScale(0.75f, 0.75f);

    attackSoundBuffer.loadFromFile(RES_DIR + "audio/attack_sound.wav");
    attackSound.setBuffer(attackSoundBuffer);
    attackSound.setPitch(1.5f);

    music.openFromFile(RES_DIR + "audio/music.ogg");
    music.play();
    music.setVolume(50);
    music.setLoop(true);

}

void loop(){
    checkButton();
    animPlayer();
    animMobSlime();

    window.clear(Color::Black);

    window.draw(tilemap);
    window.draw(playerSprite);
    if(currentMap == 2){
        window.draw(gotoTilemap1);
    }else if(currentMap == 1){
        window.draw(gotoTilemap2);
        window.draw(mobSlimeSprite);
        window.draw(npcSprite);
    }
    for(int i = 0; i < life; i++){
        window.draw(lifeHeartSprite[i]);
    }

    animAttackArrow();
    simpleCollisions();
    npcText();

    debug();

    window.display();
}

void debug(){
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
}

void checkButton(){
    playerPosX = round(playerSprite.getPosition().x / SPRITE_SIZE);
    playerPosY = round(playerSprite.getPosition().y / SPRITE_SIZE);

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

        }else if(input.getButton().magic == true){
            animPlayerReset = true;
            animPlayerSprite.x = 0;
            animPlayerSprite.y += 4;

            if(!isAttackArrow){
                attackSound.play();

                isAttackArrow = true;
                attackArrowSprite.setPosition(playerSprite.getPosition().x + SPRITE_SIZE/2, playerSprite.getPosition().y + SPRITE_SIZE/2);
                attackArrowSprite.setScale(0.75f, 0.75f);
                attackArrowSprite.setOrigin(SPRITE_SIZE/2, SPRITE_SIZE/2);
                dirAttackArrow = animPlayerSprite.y;
                attackArrowClock.restart();
            }
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

void animAttackArrow(){
    if(isAttackArrow){
        switch(dirAttackArrow){
        case DownAtk:
            attackArrowSprite.setRotation(270);
            attackArrowSprite.move(0, ATTACK_ARROW_SPEED);
            break;
        case UpAtk:
            attackArrowSprite.setRotation(90);
            attackArrowSprite.move(0, -ATTACK_ARROW_SPEED);
            break;
        case LeftAtk:
            attackArrowSprite.setRotation(0);
            attackArrowSprite.move(-ATTACK_ARROW_SPEED, 0);
            break;
        case RightAtk:
            attackArrowSprite.setRotation(180);
            attackArrowSprite.move(ATTACK_ARROW_SPEED, 0);
            break;
        default:
            break;
        }

        window.draw(attackArrowSprite);

        if(attackArrowClock.getElapsedTime().asSeconds() > 1.0f){
            isAttackArrow = false;
        }

        FloatRect attackArrowHitbox = attackArrowSprite.getGlobalBounds();
        FloatRect mobSlimeHitBox = mobSlimeSprite.getGlobalBounds();
        if(attackArrowHitbox.intersects(mobSlimeHitBox)){
            isMobSlimeAlive = false;
            isAttackArrow = false;
            mobSlimeSprite.setPosition(10000, 10000);
        }
    }
}

void animMobSlime(){
    if(isMobSlimeAlive){
        mobSlimeSprite.move(mobSlimeSpeed, 0);
        if(mobSlimeSprite.getPosition().x > 600 || mobSlimeSprite.getPosition().x < 100){
            mobSlimeSpeed *= -1;
        }

        mobSlimeSprite.setTextureRect(IntRect(animMobSlimeSprite.x * SPRITE_SIZE, animMobSlimeSprite.y * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE));
        if(animMobSlimeClock.getElapsedTime().asSeconds() > 0.2f){
            if(animMobSlimeSprite.x * SPRITE_SIZE >= (int)mobSlimeTexture.getSize().x - SPRITE_SIZE){
                animMobSlimeSprite.x = 0;
            }else{
                animMobSlimeSprite.x++;
            }
            animMobSlimeClock.restart();
        }

        FloatRect playerHitbox = playerSprite.getGlobalBounds();
        FloatRect mobSlimeHitbox = mobSlimeSprite.getGlobalBounds();
        if(playerHitbox.intersects(mobSlimeHitbox) && !isInvincible){
            life--;
            isInvincible = true;
            invincibleClock.restart();
        }
        if(invincibleClock.getElapsedTime().asSeconds() > 2 && isInvincible){
            isInvincible = false;
        }
    }
}

void loadFont(){
    if(!font.loadFromFile(RES_DIR + "font/poppins.ttf")){
        LOG("[ERROR] Failed load font ...");
    }
}

void setText(Text& text, const string& str){
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
    text.setPosition(55, 470);

    if(!textBoxTexture.loadFromFile(RES_DIR + "sprite/text_box_sprite.png")){
        LOG("[ERROR] Failed load sprite ...");
    }
    textBoxSprite.setTexture(textBoxTexture);
    textBoxSprite.setPosition(20, 450);
    textBoxSprite.setScale(1.9f, 0.75f);
    if(str != ""){
        window.draw(textBoxSprite);
        window.draw(text);
    }
}

void npcText(){
    if(playerPosX == 10 && playerPosY == 11){
        if(isMobSlimeAlive){
            setText(text, "KILL THY BLOB IN THE NORTH THREATENING OUR WIFES !");
        }else if(!textBoxTy){
            setText(text, "THANKS PJ, HERE ARE 5 DOGECOINS AND A SNICKERS !");
            npcReward = true;
        }else{
            setText(text, "YOU SAVED US ALL FROM ETERNAL DAMNATION IN HELL!");
        }
    }else{
        setText(text, "");
        if(npcReward){
            textBoxTy = true;
        }
    }
}