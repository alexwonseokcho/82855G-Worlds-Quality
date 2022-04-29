#include "main.h"
#include "devices.hpp"

#ifndef FUNCTIONS_HPP
#define FUCTIONS_HPP

int sgn(int v);
void move_velocity(int forwardPower, int turnPower);
void move(int forwardPower, int turnPower);
void brake();
void moveLR(int leftPower, int rightPower);

#endif
//
