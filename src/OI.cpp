// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"

#include "Commands/DriveCommand.h"
#include "Commands/ToggleFlapsCommand.h"
#include "Commands/DrivePID.h"
#include "Commands/PositionElevator.h"
#include "Commands/ToggleCompressor.h"
#include "Commands/PushTote.h"
#include "Commands/ZeroElevator.h"
#include "Commands/SwitchCamera.h"
#include "Commands/AutonomousCommand1Can1Tote.h"
#include "Commands/DriveD2.h"
#include "Commands/DriveD2.h"
#include "Commands/DriveDistance.h"
#include "Commands/ToggleOverlay.h"
#include "Commands/SlideLeft.h"
#include "Commands/SlideRight.h"
#include "Commands/Turn.h"
#include "RobotMap.h"

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
	joystick1 = new Joystick(0);
	joystick2 = new Joystick(1);

	//applyBreakCommand = new ApplyBreakCommand();
	driveDistanceCommand = new DriveDistance(10.0, 10.0); 	// new DriveDistance(10.0, 10.0);
	zeroElevator= new ZeroElevator();
	driveCommand = new DriveCommand();
	drive100 = new DriveDistance(100.0, 100.0);
	drive10 = new DrivePID(10.0, 10.0, false);
	driveDistance25 = new DriveDistance(25.0, 25.0);
	toggleArmFlap = new ToggleFlapsCommand(0);
	armsUp = new ToggleFlapsCommand(-1);
	armsDown = new ToggleFlapsCommand(1);
	toggleCompressor = new ToggleCompressor();
	pushTote = new PushTote();
	switchCamera = new SwitchCamera();
	toggleCameras = new SwitchCamera(true);
	turnLeft = new Turn(-RobotMap::ninetyDegreeTurn, RobotMap::ninetyDegreeTurn);
	turnRight = new Turn(RobotMap::ninetyDegreeTurn, -RobotMap::ninetyDegreeTurn);

	//turnLeft = new DrivePID(-ninetyDegreeTurn, ninetyDegreeTurn, false);
	//turnRight = new DrivePID(ninetyDegreeTurn, -ninetyDegreeTurn, false);
	toggleOverlay = new ToggleOverlay();

	toteUp = new PositionElevator(1, false);				// Tote Up
	toteDown = new PositionElevator(-1, false);				// Tote Down
	canUp = new PositionElevator(1, true);					// Can Up
	canDown = new PositionElevator(-1, true);				// Can Down

	// Slide left or right
	double inchesToSlide = 1.0;
	slideLeft = new SlideLeft(inchesToSlide);
	slideRight = new SlideRight(inchesToSlide);

	//Joystick1WhenPressed(toteUp, 6);			// Right bumper
	//Joystick1WhenPressed(toteDown, 5);			// Left bumper
	//Joystick1WhenPressed(canUp, 4);				// Y button
	Joystick1WhenPressed(zeroElevator, 4);
	// Joystick1WhenPressed(canDown, XXX);			// B button (open, widen arms)

	Joystick1WhenPressed(armsUp, 1);			// A button
	Joystick1WhenPressed(armsDown, 3);			// X button (close, narrow arms)
	Joystick1WhenPressed(armsDown, 2);			// B button (close, narrow arms)
	Joystick1WhenPressed(toggleCompressor, 7);	// tiny back button (old XBox)
	Joystick1WhenPressed(pushTote, 8);			// tiny start button

	// We won't have two cameras, so use the switching button to toggle the overlay
	//Joystick1WhenPressed(switchCamera, 10);		// Right joystick press
	Joystick1WhenPressed(toggleOverlay, 10);
	Joystick1WhenPressed(toggleCameras, 9);		// Left joystick press

	Joystick1WhenPressed(slideLeft, 5);
	Joystick1WhenPressed(slideRight, 6);




	printf("Joystick2 button count: %d.\n", joystick2->GetButtonCount());
	if (joystick2->GetButtonCount() > 0) {
	// these next two commands are only for testing
		Joystick2WhenPressed(slideRight, 11);			// upper right button on Logitech Attack 3
		Joystick2WhenPressed(slideLeft, 10);		// middle right button?

		Joystick2WhenPressed(toteUp, 1);			// trigger
		Joystick2WhenPressed(toteDown, 2);			// behind trigger


		Joystick2WhenPressed(driveDistance25, 5);
		Joystick2WhenPressed(drive100, 6);			    // upper left button on Logitech Attack 3
		Joystick2WhenPressed(drive10, 7);
		Joystick2WhenPressed(turnLeft, 8);
		Joystick2WhenPressed(turnRight, 9);
	}
}

void OI::Joystick1WhenPressed(Command *command, int buttonNum) {
	// Truthfully, we don't really need to remember these pointers.
	// Once we assigned WhenPressed, we could throw them away
	joystick1Buttons[buttonNum] = new JoystickButton(joystick1, buttonNum);
	joystick1Buttons[buttonNum]->WhenPressed(command);
}

void OI::Joystick2WhenPressed(Command *command, int buttonNum) {
	joystick2Buttons[buttonNum] = new JoystickButton(joystick2, buttonNum);
	joystick2Buttons[buttonNum]->WhenPressed(command);
}

Joystick* OI::getJoystick2() {
	return joystick2;
}

Joystick* OI::getJoystick1() {
	return joystick1;
}
