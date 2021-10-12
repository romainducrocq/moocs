#ifndef _MAIN_H
#define _MAIN_H

#include <iostream>
#include <string>
#include "../include/input.h"

using namespace std;

static const int WIN_WIDTH = 800;
static const int WIN_HEIGHT = 600;
static const string FONT_DIR = "../../res/font/";

void loadFont();
void setText(const string str);
void checkButton();

#endif