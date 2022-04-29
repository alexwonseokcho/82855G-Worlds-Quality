#include "main.h"
#include "devices.hpp"

using namespace pros;

Controller master(E_CONTROLLER_MASTER);

Motor LF(6, MOTOR_GEARSET_6);
Motor LB(9, MOTOR_GEARSET_6, true);
Motor LT(10, MOTOR_GEARSET_6);

Motor RF(5, MOTOR_GEARSET_6, true);
Motor RB(3, MOTOR_GEARSET_6);//
Motor RT(1, MOTOR_GEARSET_6, true);

Motor lift(21, MOTOR_GEARSET_18, true);
Motor conveyor(20, MOTOR_GEARSET_6, true);


// ADIPotentiometer clampPos('A');

ADIDigitalOut frontClip('H');
ADIDigitalOut backClip1('A');
ADIDigitalOut backClip2('B');

//Gps gps1(10, -1.5, -1.14);
//gps_status_s_t gpsData;

/* Optical Sensor Declaration
Optical opticalFlyWheel(5);
*/

// Distance Sensor Declaration
Distance distanceMogoApproach(11);


/// Inertial Sensor Declaration
Imu inertial(15);
Imu inertialLeft(20);


/* Tracking Wheels for 3-wire splitter
// ADIEncoder leftEnc({13, 'C', 'D'}, true);
// ADIEncoder rightEnc({13, 'A', 'B'}, false);
// ADIEncoder backEnc({13, 'E', 'F'}, true);
*/

//Tracking Wheels
ADIEncoder vertEnc('C', 'D', true);
ADIEncoder horiEnc('E', 'F', true);


/* Line Sensor
ADILineSensor linetrackerTowerApproach('A');
*/
