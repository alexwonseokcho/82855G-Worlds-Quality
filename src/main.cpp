#include "main.h"
#include "devices.hpp"
#include "functions.hpp"

using namespace pros;

#define powerFactor 1
#define turnSens 1

void initialize() {
	lcd::initialize();

	master.set_text(0, 0, "  SPLIT ARCADE :D  ");

	
}

void disabled() {}void competition_initialize() {}

int exponentialDrive(int power){
	return (pow(abs(power), powerFactor) / (pow(127, powerFactor - 1)) * sgn(power));
}

void autonomous() {

frontClip.set_value(LOW);
	// moveLR(127, 127);
	// while(distanceMogoApproach.get() > 150){
	// 	pros::delay(5);
	// }
	// frontClip.set_value(HIGH);
	// lift.move_velocity(0);
	// lift.set_brake_mode(MOTOR_BRAKE_HOLD);
	// moveLR(-127, -127);
	// pros::delay(800);
	// // lift.move(0);
	// brake();

	frontClip.set_value(LOW);
	moveLR(127, 127);
	while(distanceMogoApproach.get() > 360){
		move(distanceMogoApproach.get() * 0.3, 0);
		pros::delay(5);
	}
	while(distanceMogoApproach.get() > 200){
		move(distanceMogoApproach.get() * 0.3, 0);
		pros::delay(20);
	}
	move(0, 0);
	frontClip.set_value(HIGH);
	
	lift.move_velocity(0);
	lift.set_brake_mode(MOTOR_BRAKE_HOLD);
	while(distanceMogoApproach.get() > 50){
		move((distanceMogoApproach.get() - 50) * 0.5, 0);
		pros::delay(20);
	}
	int counter = 40;
	while(counter < 127){
		move(-counter, 0);
		counter++;
		pros::delay(1.2);
	}
	
	pros::delay(600);
	brake();
}

/*
 * CONTROL MAPPING:
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

void opcontrol() {

	pros::Task intakeT (intakeTask, (void *) "PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	pros::Task liftT (liftTask, (void *) "PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	pros::Task clampT (clampTask, (void *) "PROS", TASK_PRIORITY_DEFAULT, TASK_STACK_DEPTH_DEFAULT);
	int left, right;
	enum driveMode{split_arcade, arcade, tank} driveMode;
	driveMode = split_arcade;
	int counter = 0;

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

		pros::lcd::print(0, "LF: %d LB: %d LT: %d", int(LF.get_temperature()), int(LB.get_temperature()), int(LT.get_temperature()));
		pros::lcd::print(1, "RF: %d RB: %d RT: %d", int(RF.get_temperature()), int(RB.get_temperature()), int(RT.get_temperature()));
		pros::lcd::print(2, "Int: %d Lift: %d", int(conveyor.get_temperature()), int(lift.get_temperature()));
		pros::lcd::print(3, "RPM intake: %d", int(conveyor.get_actual_velocity()));

		delay(20);
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
