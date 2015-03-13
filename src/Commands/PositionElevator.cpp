// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "PositionElevator.h"

int PositionElevator::targetIndex = 0;

PositionElevator::PositionElevator(int commandDirection, bool trashcan) {
	Requires(Robot::elevator);
	elevator = Robot::elevator;
	this->commandDirection = commandDirection;	// +1 for up, -1 for down, 0 to hold
	this->trashcan = trashcan;			// true if we're move trash cans, false for totes
	printf("PositionElevator constructed for commandDirection=%d, %s version, elevatorPIDDistance=%1.2f\n",
			commandDirection, trashcan ? "Trash Can" : "Tote", elevator->GetPosition());
}

// Called just before this Command runs the first time
void PositionElevator::Initialize() {
	double curPos;
	SetInterruptible(true);
	Robot::parameters->UpdateElevatorPIDParams();
	if (!RobotMap::testBot) {
		RobotMap::elevatorMotor1->SetControlMode(CANSpeedController::kPosition);
	}
	// Max says this is wrong, I think it'll work for now:
	curPos =  RobotMap::elevatorMotor1->GetEncPosition();
	printf("PositionElevator initialized for commandDirection=%d, %s version moving from %1.2f\n",
			commandDirection, trashcan ? "Trash Can" : "Tote", curPos);
	// always make sure we're back in position control mode.
	if (commandDirection == 0) {
		// if curPos is not accurate, stupid things happen here
		elevator->SetHeight(curPos);	// hold mode
	}
	else {
		if (!trashcan) {
			elevator->MoveByTote(commandDirection);
		}
		else {
			elevator->MoveCan(commandDirection);
		}
	}
}

// Called repeatedly when this Command is scheduled to run
void PositionElevator::Execute() {
	if (RobotMap::testBot && commandDirection!=0) {
		// calculate how much we should move per clock cycle (every 1/50 second)
		// to move a tote's distance in two seconds
		// only continue moving if we're more than two cycles away from our goal
		if (fabs(elevator->GetPosition() - elevator->targetHeight) > 2*elevator->ticksPerCycle) {
			double direction = elevator->targetHeight < elevator->GetPosition() ? -1.0 : 1.0;
			double movement = direction*elevator->ticksPerCycle;
			/* printf("PositionElevator: is at %1.0f, moving to moving %1.0f, by %1.0f\n",
				elevator->GetPosition(),
				elevator->targetHeight,
				movement); */
			elevator->Move(movement);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool PositionElevator::IsFinished() {
	// End PID control if the joystick throttles are pressed
	// Test bot is different. Simulated elevator ends when it reaches set point
	if (RobotMap::testBot && commandDirection!=0)
		return (fabs(elevator->GetPosition() - elevator->targetHeight) < 2*elevator->ticksPerCycle);
	// Otherwise, the PID directional move commands end immediately -- the PID loop
	// will do the rest. Except the default command -- holdElevator, that maintains
	// position.
	if (!RobotMap::testBot) {
		if (commandDirection==0) return false;	// holdCommand never finishes
		return true;
	}
	// on testBot, we only end when if we've reached the target
	return true;
}

// Called once after isFinished returns true
void PositionElevator::End() {
	printf("PositionElevator ended for commandDirection=%d, %s version\n",
			commandDirection, trashcan ? "Trash Can" : "Tote");
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void PositionElevator::Interrupted() {
}
