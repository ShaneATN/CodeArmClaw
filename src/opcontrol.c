/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * PROS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request. 
 * changes!!
 */

#include "main.h"
Ultrasonic leftSonar;
Ultrasonic rightSonar;



/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */
int power, turn;
void operatorControl() {
	int distanceToObjectLeft = ultrasonicGet(leftSonar);
	int distanceToObjectRight = ultrasonicGet(rightSonar);
	leftSonar = ultrasonicInit(3,4);
	rightSonar = ultrasonicInit(1,2);
	printf("starting \n");
	while (1) {
		distanceToObjectLeft = ultrasonicGet(leftSonar);
		distanceToObjectRight = ultrasonicGet(rightSonar);
		printf("Distance left: %d \n", distanceToObjectLeft);
		printf("Distance right: %d \n", distanceToObjectRight);
		power = 0;
		turn = 0;
		/*power = joystickGetAnalog(1,2);//vertical axis on right joystick
		turn = joystickGetAnalog(1,4); //horizontal axis on right joystick
		motorSet(2, -turn); // middle wheel
		motorSet(3, power + turn); //back right wheel
		motorSet(4, power + turn); //front right wheel
		motorSet(5, power - turn); // front left wheel
		motorSet(6, power - turn); // back left wheel */
		if(10 < leftSonar < 20 || 10 < rightSonar < 20){
			power = 100;
		}
		else if(10> leftSonar || 10 > leftSonar){
			power = -100;
		}

		if(leftSonar < rightSonar){
			turn = 25;
		}
		else if(rightSonar < leftSonar){
			turn = -25;
		}
		else{
			turn = 0;
		}
		motorSet(2, -turn); // middle wheel
		motorSet(3, power /*+ turn*/); //back right wheel
		motorSet(4, power /*+ turn*/); //front right wheel
		motorSet(5, power /*- turn*/); // front left wheel
		motorSet(6, power /*- turn*/); // back left wheel
		//printf("The distance to object on left is %f", distanceToObjectLeft);
		//printf("The distance to object on right is %f", distanceToObjectRight);
		//delay(20);
		delay(50);
	}
}
