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
//TODO #includes
#include "../Robot.h"
/**
*
*
* @author ExampleAuthor
*/
class AutonomousCommand1Can: public CommandGroup {
public:
AutonomousCommand1Can();
private:
Command* PickUpTote();
Command* GoDownTote();
Command* MoveHalfForward();
};
