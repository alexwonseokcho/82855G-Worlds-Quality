#include "main.h"
#include "devices.hpp"
#include "functions.hpp"

using namespace pros;

#define powerFactor 1
#define turnSens 1

void initialize() {
	pros::lcd::initialize();

	master.set_text(0, 0, "  SPLIT ARCADE :D  ");
}

void disabled() {}void competition_initialize() {}

int exponentialDrive(int power){
	return (pow(abs(power), powerFactor) / (pow(127, powerFactor - 1)) * sgn(power));
}

void autonomous() {
	frontClip.set_value(LOW);
	moveLR(127, 127);
	while(distanceMogoApproach.get() > 150){
		pros::delay(5);
	}
	frontClip.set_value(HIGH);
	lift.move_velocity(0);
	lift.set_brake_mode(MOTOR_BRAKE_HOLD);
	moveLR(-127, -127);
	pros::delay(800);
	// lift.move(0);
	brake();

}


void opcontrol() {
	int left, right;

	enum driveMode{split_arcade, arcade, tank} driveMode;
	driveMode = split_arcade;
	int counter = 0, countee = 0;
	bool backClamp = false;
	bool frontClamp = false;



	while (true) {

		if(master.get_digital_new_press(DIGITAL_X)){
			if(driveMode == split_arcade){
				driveMode = arcade;
				master.set_text(0, 0, "  ARCADE L Bozo :<   ");
			}
			else if(driveMode == arcade){
				driveMode = tank;
				master.set_text(0, 0, "  TANK LMFAO L :<    ");
			}
			else{
				driveMode = split_arcade;
				master.set_text(0, 0, "  SPLIT ARCADE :D  ");
			}
			counter = 1;
		}
		if(counter > 0){
			counter++;
			if(counter > 7){
				master.rumble(".");
				counter = 0;
			}
		}

		if(driveMode == split_arcade){
			left = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_RIGHT_X)*turnSens;
			right = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_RIGHT_X)*turnSens;

		}
		else if(driveMode == arcade){
			left = master.get_analog(ANALOG_LEFT_Y) + master.get_analog(ANALOG_LEFT_X)*turnSens;
			right = master.get_analog(ANALOG_LEFT_Y) - master.get_analog(ANALOG_LEFT_X)*turnSens;
		}
		else{
			left = master.get_analog(ANALOG_LEFT_Y);
			right = master.get_analog(ANALOG_RIGHT_Y);
		}

		left = exponentialDrive(left);
		right = exponentialDrive(right);

		moveLR(left, right);

		int L = master.get_analog(ANALOG_LEFT_Y);
		int R = master.get_analog(ANALOG_RIGHT_Y);
		//
		// LF.move(L);
		// LB.move(L);
		// LT.move(L);
		// RF.move(R);
		// RB.move(R);
		// RT.move(R);

		// RT.move(0);
		// RF.move(127);
		// pros::delay(1000);
		// RB.move(127);
		// RF.move(0);
		// pros::delay(1000);
		// RB.move(0);
		// RT.move(127);
		// pros::delay(1000);

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


		if(master.get_digital(DIGITAL_L1)){
			if(master.get_digital(DIGITAL_DOWN)){
				lift.move_velocity(60);
			}
			else{
				lift.move_velocity(200);
			}
			countee = -1;
		}
		else if(master.get_digital(DIGITAL_L2)){
			if(master.get_digital(DIGITAL_DOWN)){
				lift.move_velocity(-60);
			}
			else{
				lift.move_velocity(-200);
			}
			countee = -1;
		}
		else{
			if(countee < 0){
				countee--;
				if(countee < -3)
					countee = 1;
				lift.move_velocity(0);
				lift.set_brake_mode(MOTOR_BRAKE_COAST);
			}
			else{
				lift.move_velocity(0);
				lift.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}

		if(master.get_digital(DIGITAL_R1)) conveyor.move_velocity(600);
		else if(master.get_digital(DIGITAL_R2)) conveyor.move_velocity(-600);
		else conveyor.move(0);

		if(master.get_digital_new_press(DIGITAL_Y))
			frontClamp = !frontClamp;

		if(frontClamp) frontClip.set_value(HIGH);
		else frontClip.set_value(LOW);

		pros::delay(20);
	}
}



/*
void opcontrol() {

	bool backClamp = false;

	while (true) {

		int forwardPower = master.get_analog(ANALOG_LEFT_Y);
		int turnPower = master.get_analog(ANALOG_RIGHT_X);

		LF.move(forwardPower);
		LB.move(forwardPower);
		LT.move(forwardPower);


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

		pros::lcd::print(0, "%d", backClamp);
		pros::delay(20);
	}
}
*/
