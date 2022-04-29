#include "main.h"

#ifndef DEVICES_HPP
#define DEVICES_HPP

extern pros::Controller master;

extern pros::Motor LF;
extern pros::Motor LB;
extern pros::Motor LT;
extern pros::Motor RF;
extern pros::Motor RB;
extern pros::Motor RT;

extern pros::Motor conveyor;
extern pros::Motor lift;

//extern pros::Gps gps1;
//extern pros::gps_status_s_t gpsData;

extern pros::ADIDigitalOut frontClip;
extern pros::ADIDigitalOut backClip1;
extern pros::ADIDigitalOut backClip2;

extern pros::Imu inertialRight;
extern pros::Imu inertialLeft;

extern pros::Distance distanceMogoApproach;

// extern pros::ADIPotentiometer clampPos;

#endif
