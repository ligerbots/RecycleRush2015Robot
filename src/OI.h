// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#pragma once

#include "WPILib.h"

class OI {
private:
	JoystickButton *joystick1Buttons[12];	// we don't use zero!

	// helper function for binding joystick buttons
	void Joystick1WhenPressed(Command *command, int buttonNum);

public:
	Joystick *joystick2;
	Joystick *joystick1;

	Command *driveDistanceCommand;	// don't have time to debug this?
	Command *driveCommand;
	Command *toggleArmFlap;
	Command *armsUp;	// open, widen
	Command *armsDown;	// close, narrow
	Command *toteUp;
	Command *toteDown;
	Command *canUp;
	Command *canDown;
	Command *drivePID;
	Command *toggleCompressor;
	Command *pushTote;
	Command *switchCamera;

	OI();
 
	Joystick *getJoystick1();
	Joystick *getJoystick2();

};

