#include "main.h"
#include "devices.hpp"
#include "functions.hpp"

using namespace pros;

int sgn(int i){
	return (i < 0) ? -1 : ((i > 0) ? 1 : 0);
}

/**
 * @brief 
 * add macros and preset heights & PID-ish 
 * ability to reset the initial height 
 * L2 = low height preset for scoring on platform 
 * L1 = high height preset 
 * RIGHT = drop down all the way
 * R1 = manual height increase
 * R2 = manual height decrease
 * Y = front clamp toggle
 * A = back clamp toggle
 * DOWN = slow mode (for lift and intake)
 * ??? B = precision base control mode (for balancing)
 */
void liftTask(void*){

	int counter = 0;

	while (true){

		if(master.get_digital(DIGITAL_L1)){
			if(master.get_digital(DIGITAL_DOWN))
				lift.move_velocity(60);
			else
				lift.move_velocity(200);
			counter = -1;
		}
		else if(master.get_digital(DIGITAL_L2)){
			if(master.get_digital(DIGITAL_DOWN))
				lift.move_velocity(-60);
			else
				lift.move_velocity(-200);
			counter = -1;
		}
		else{
			if(counter < 0){
				counter--;
				if(counter < -3)
					counter = 1;
				lift.move_velocity(0);
				lift.set_brake_mode(MOTOR_BRAKE_COAST);
			}
			else{
				lift.move_velocity(0);
				lift.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}

		delay(20);
	}
}

/**
 * @brief 
 * Add ability to detect jams
 * Try reversing and auto-correcting for faults
 * Auto start/stop with ring sensors?
 */
void intakeTask(void*){

	while (true){
		if(master.get_digital(DIGITAL_DOWN)){
			if(master.get_digital(DIGITAL_R1)) conveyor.move_velocity(200);
			else if(master.get_digital(DIGITAL_R2)) conveyor.move_velocity(-200);
			else conveyor.move(0);
		}
		else{
			if(master.get_digital(DIGITAL_R1)) conveyor.move_velocity(600);
			else if(master.get_digital(DIGITAL_R2)) conveyor.move_velocity(-600);
			else conveyor.move(0);
		}
		
		delay(20);
	}
}

void clampTask(void*){

	
	bool backClamp = false;
	bool frontClamp = false;

	while (true){

		if(master.get_digital_new_press(DIGITAL_A))
			backClamp = !backClamp;

		if(backClamp){
			backClip1.set_value(HIGH);
			backClip2.set_value(HIGH);
		}
		else{
			backClip1.set_value(LOW);
			backClip2.set_value(LOW);
		}		

		if(master.get_digital_new_press(DIGITAL_Y))
			frontClamp = !frontClamp;

		if(frontClamp) frontClip.set_value(HIGH);
		else frontClip.set_value(LOW);

		delay(20);
	}
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
