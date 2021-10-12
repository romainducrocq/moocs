#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include "../include/input.h"

using namespace std;

#define LOG(x) cout << x << endl

static const int WIN_WIDTH = 800;
static const int WIN_HEIGHT = 576;
static const int SPRITE_SIZE = 32;
static const int MOVE_SPEED = 4;
static const string RES_DIR = "../../res/";

void checkButton(); 
void animPlayer();

#endif