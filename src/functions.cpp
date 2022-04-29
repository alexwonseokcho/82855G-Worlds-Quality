#include "main.h"
#include "devices.hpp"
#include "functions.hpp"

int sgn(int i){
	return (i < 0) ? -1 : ((i > 0) ? 1 : 0);
}

void brake(){
  LF.move_velocity(0);
  LT.move_velocity(0);
  LB.move_velocity(0);
  RF.move_velocity(0);
  RT.move_velocity(0);
  RB.move_velocity(0);
  LF.set_brake_mode(MOTOR_BRAKE_HOLD);
  LT.set_brake_mode(MOTOR_BRAKE_HOLD);
  LB.set_brake_mode(MOTOR_BRAKE_HOLD);
  RF.set_brake_mode(MOTOR_BRAKE_HOLD);
  RT.set_brake_mode(MOTOR_BRAKE_HOLD);
  RB.set_brake_mode(MOTOR_BRAKE_HOLD);
}
void move(int forwardPower, int turnPower){
	LF.move(forwardPower + turnPower);
	LT.move(forwardPower + turnPower);
	LB.move(forwardPower + turnPower);
	RF.move(forwardPower - turnPower);
	RT.move(forwardPower - turnPower);
	RB.move(forwardPower - turnPower);
}
void move_velocity(int forwardPower, int turnPower){
	LF.move_velocity(forwardPower + turnPower);
	LT.move_velocity(forwardPower + turnPower);
	LB.move_velocity(forwardPower + turnPower);
	RF.move_velocity(forwardPower - turnPower);
	RT.move_velocity(forwardPower - turnPower);
	RB.move_velocity(forwardPower - turnPower);
}
void moveLR(int leftPower, int rightPower){
	LF.move(leftPower);
	LB.move(leftPower);
	LT.move(leftPower);
	RF.move(rightPower);
	RB.move(rightPower);
	RT.move(rightPower);
}

//
// float angleAway(){
// 	float errorAngle = targetAngle_async - globalAngle;
// 	if(errorAngle < -180)
// 		errorAngle = errorAngle + 360;
// 	else if(errorAngle > 180)
// 		errorAngle = errorAngle - 360;
//
// 	return fabs(errorAngle);
// }
// float distanceAway(){
// 	return sqrt(pow((target_x_async*12) - global_x, 2) + pow((target_y_async*12) - global_y, 2));
// }
//
// void driveTo(float x_target, float y_target, float angleTarget){
// 	target_x_async = x_target;
// 	target_y_async = y_target;
// 	targetAngle_async = angleTarget;
// }
