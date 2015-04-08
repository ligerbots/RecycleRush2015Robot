// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "DriveDistance.h"

#include <algorithm>
#include "../Subsystems/Parameters.h"

DriveDistance::DriveDistance(double distL, double distR) : _distL(distL) , _distR(distR) {
	Requires(Robot::driveSubsystem);
	driveSubsystem = Robot::driveSubsystem;
	printf("DriveDistance constructed for left: %1.2f, right: %1.2f inches, inches per tick %1.6f.\n",
			_distL, _distR, RobotMap::inchesPerTick);
}

// Called just before this Command runs the first time
void DriveDistance::Initialize() {
	// reset the encoders to 0
	//RobotMap::driveBackLeft->SetPosition(0);
	encoderStartL = driveSubsystem->GetLeftEncoderPosition();
	distanceTravelledL = 0.0;
	rateLeft = initialRate;

	//RobotMap::driveBackRight->SetPosition(0);
	encoderStartR = driveSubsystem->GetRightEncoderPosition();
	distanceTravelledR = 0.0;
	rateRight =initialRate;
	timeTicks = 0;
	remainingDistance = 0.0;
	// Disable the voltage ramp rate
	RobotMap::driveBackLeft->SetVoltageRampRate(0.0);
	RobotMap::driveBackRight->SetVoltageRampRate(0.0);
	printf("DriveDistanceCommand initialized: %1.2f, right: %1.2f inches, inches per tick %1.6f.\n",
			_distL, _distR, RobotMap::inchesPerTick);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistance::Execute() {
	// If we're farther away than five inches then speed up to max
	distanceTravelledL = RobotMap::inchesPerTick * (driveSubsystem->GetLeftEncoderPosition() - encoderStartL);
	distanceTravelledR = RobotMap::inchesPerTick * (driveSubsystem->GetRightEncoderPosition() - encoderStartR);
	// Left will be the opposite sign of right.
	// When going forward, we expect left to be negative and right to be positive.
	remainingDistance = _distL >= 0 ? std::max(_distL + distanceTravelledL, 0.0) : std::min(_distL - distanceTravelledL, 0.0);

	// Compute how far we would go if we started decelerating at the max rate
	// It turns out timeToStop = velocity/acceleration and
	// distanceToStop = currentSpeed * timeToStop / 2
	timeToStop = rateLeft/rateStep * 0.02;
	double speed = driveSubsystem->GetLeftSpeed();

	maxDecelDistance = fabs(speed) * timeToStop / 2.0;

	// arbitrarily add 5.0 to our Decel Distance, based on testing
	if (remainingDistance > (maxDecelDistance + 2.0))
	{
		rateLeft = std::min(rateLeft + rateStep, maxRate);
	}
	else
	{
		// There's no point in going faster than our stall speed.
		// If we ramp down too fast the robot essentially halts short
		// of the goal and never gets there.
		rateLeft = std::max(rateLeft - rateStep, initialRate);
	}
	// Now let's check to see how far each side has traveled
	// and scale the right side accordingly
	// The right side goes in the opposite direction, so to get a difference
	// we add.
	double distanceError = distanceTravelledL + distanceTravelledR;

	//voltageRight = voltageLeft + distanceError * voltageScale;
	// For test bot use '-'
	rateRight = rateLeft - distanceError * rateScale;

	driveSubsystem->robotDrive->TankDrive(-rateLeft, -rateRight, true);


	if (timeTicks++%10==0)
	{
		//printf("speed=%1.2f (inches per second), timeToStop = %1.4f, maxDecelDistance = %1.4f\n", speed, timeToStop, maxDecelDistance);
		printf("distanceError = %1.2f, distanceLeft = %1.2f, distanceRight = %1.2f, remainingDistance = %1.2f, rateLeft = %1.2f, rateRight = %1.2f\n",
				distanceError, distanceTravelledL, distanceTravelledR, remainingDistance, rateLeft, rateRight);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistance::IsFinished() {
	isCommandDone = remainingDistance < 1.0 || -distanceTravelledL > _distL;
	return isCommandDone;
}

// Called once after isFinished returns true
void DriveDistance::End() {
	driveSubsystem->robotDrive->ArcadeDrive(0, 0, true);
	printf("distanceLeft = %f, distanceRight = %f\n",distanceTravelledL, distanceTravelledR);

	// Set the voltage ramp rate for both drive motors
	RobotMap::driveBackLeft->SetVoltageRampRate(Parameters::driveRampRate);
	RobotMap::driveBackRight->SetVoltageRampRate(Parameters::driveRampRate);

	// Can't do this!
	//((DriveCommand *)Robot::driveCommand)->Start();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistance::Interrupted() {

}
