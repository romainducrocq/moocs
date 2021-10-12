#ifndef _PROTAL_H
#define _PORTAL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"

using namespace std;
using namespace sf;

Sprite playerSprite;

Map tilemap;
int currentMap = 1;

FloatRect playerHitbox;
RectangleShape gotoTilemap2(Vector2f(32, 32));
FloatRect gotoTilemap2Hitbox;
RectangleShape gotoTilemap1(Vector2f(32, 32));
FloatRect gotoTilemap1Hitbox;

void updateTilemap();

void simpleCollisions(){
    gotoTilemap2Hitbox = gotoTilemap2.getGlobalBounds();
    gotoTilemap1Hitbox = gotoTilemap1.getGlobalBounds();
    playerHitbox = playerSprite.getGlobalBounds();
    if(playerHitbox.intersects(gotoTilemap2Hitbox) && currentMap == 1){
        currentMap = 2;
        updateTilemap();
        playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y + (15 * 32));
    }else if(playerHitbox.intersects(gotoTilemap1Hitbox) && currentMap == 2){
        currentMap = 1;
        updateTilemap();
        playerSprite.setPosition(playerSprite.getPosition().x, playerSprite.getPosition().y - (15 * 32));
    }

}

#endif