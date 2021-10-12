#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <utility>
#include <cstdlib>
#include <cmath>
#include "input.h"
#include "map.h"
#include "portal.h"

using namespace std;
using namespace sf;

#define LOG(x) cout << x << endl

static const bool DEBUG = false;
static const string RES_DIR = "../../res/";

static const int WIN_WIDTH = 800;
static const int WIN_HEIGHT = 576;
static const int SPRITE_SIZE = 32;
static const int MOVE_SPEED = 4;
static const int MAP_COL = 25;
static const int MAP_ROW = 18;
static const int MAP_N = 3;

void checkButton(); 
void animPlayer();

void loadArrLevel2D(int* arrLevel, const string& path, int n);
void loadArrLevel1D(int* arrLevel, const string& path, int n);

vector<string> explode(const string& s, char delim);

#endif