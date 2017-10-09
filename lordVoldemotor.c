#pragma config(Motor,  port1,           frontLeft,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           backLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           frontRight,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           backRight,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           armLeft,       tmotorVex393_MC29, openLoop, encoderPort, None)
#pragma config(Motor,  port6,           armRight,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           clawMotor,     tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/* 
 * Enhanced shared RobotC templates from the community to fit the design and needs of our Robot!  
 * Thanks to the VEX Robotics community for all the help in bootstraping our team!
 * -Team: 18181A
 */

#pragma platform(VEX)


#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)


#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!

#define DRIVESPEED 0.50 //ranges between 0 to 1
#define ARCADE true //controls whether the drive is tank style (0) or arcade style (1)

int filter (int input){
	if (input > 20){
		return input;
	}
	if (input < -20){
		return input;
	}
	return 0;
}

task drive{
	while (true){

/* -- unused code?
		if (!ARCADE){
			motor[frontLeft] = DRIVESPEED*((float) filter(vexRT[Ch2]));
			motor[backLeft] = DRIVESPEED*((float) filter(vexRT[Ch2]));
			motor[frontRight] = DRIVESPEED*((float) filter(vexRT[Ch2]));
			motor[backRight] = DRIVESPEED*((float) filter(vexRT[Ch2]));
		}
		else {
 */
			float forward = (float) filter(vexRT[Ch2]);
			float turn = (float) filter(vexRT[Ch4]);
			motor[frontLeft] = DRIVESPEED*(forward + turn);
			motor[backLeft] = DRIVESPEED*(forward + turn);

			motor[frontRight] = DRIVESPEED*(forward - turn);
			motor[backRight] = DRIVESPEED*(forward - turn);
//		} -- unused code?
	}
}

task arm{
	while (true){
		if (vexRT[Btn6U] == 1){
			while (vexRT[Btn6U] == 1){
				motor[armLeft] = 127;
				motor[armRight] = 127;
			}
			motor[armLeft] = 0;
			motor[armRight] = 0;
		}
		else if (vexRT[Btn6D] == 1){
			while (vexRT[Btn6D] == 1){
				motor[armLeft] = -127;
				motor[armRight] = -127;
			}
			motor[armLeft] = 0;
			motor[armRight] = 0;
		}

		wait1Msec(100);
	}
}

task claw{
	while (true){
		if (vexRT[Btn5U] == 1){
			while (vexRT[Btn5U] == 1){
				motor[clawMotor] = 127;
			}
			motor[clawMotor] = 10;
		}
		else if (vexRT[Btn5D] == 1){
			while (vexRT[Btn5D] == 1){
				motor[clawMotor] = -127;
			}
			motor[clawMotor] = 0;
		}
		wait1Msec(100);
	}
}

void assignArmMotor(int power){
	motor[armLeft] = power;
	motor[armRight] = power;
}

void assignClawMotor(int power){
	motor[clawMotor] = power;

}

void assignDriveMotors(int leftPower, int rightPower){
	motor[frontLeft] = leftPower;
	motor[backLeft] = leftPower;
	motor[frontRight] = rightPower;
    motor[backRight] = rightPower;
}

void pre_auton(){

}

task autonomous(){
	assignDriveMotors(127, 127);
	wait1Msec(2000);
    assignDriveMotors(0,0);
}

task usercontrol()
{
	startTask(drive);
	startTask(arm);
	startTask(claw);
	while(true){
	 wait1Msec(15);
	}

}
