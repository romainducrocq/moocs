#ifndef _MAIN_H
#define _MAIN_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "input.h"

using namespace std;
using namespace sf;

static const string RES_DIR = "../../res/";

static const int WIN_WIDTH = 800;
static const int WIN_HEIGHT = 600;

void setText(Text& txt, string str);
void checkButton();

void updateBall();
void autoPaddleRight();

#endif