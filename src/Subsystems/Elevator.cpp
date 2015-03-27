// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Elevator.h"
#include "../RobotMap.h"
#include "../Robot.h"
#include "Parameters.h"

Elevator::Elevator() : Subsystem("Elevator") {
	printf("Elevator constructor\n");

	elevatorIndex = 0;		// assume for now, set properly later
	zeroed = false;

	elevatorMotor1 = RobotMap::elevatorMotor1;
	elevatorMotor2 = RobotMap::elevatorMotor2;

	if (RobotMap::testBot) encoderPos = -70.0;	// simulated encoder

	wheelDiameter = 1.895; 				// starting guess

	ticksPerRotation = 1024.0;
	inchesPerTote = 12.1;
	inchesPerRotation = wheelDiameter * 3.14159;
	ticksPerInch = ticksPerRotation / inchesPerRotation;
	ticksPerTote = ticksPerInch * inchesPerTote;

	inchesPerCanOffset = 21.0;
	//ticksPerCanOffset = ticksPerInch * inchesPerCanOffset;

	//Define elevator heights for lifting totes
	printf("Elevator heights ----------------------------------------------------\n");
	elevatorHeightsTotes[0] = 0.0;
	elevatorHeightsTotes[1] = round(ticksPerInch * 7.0);
	printf("   elevatorHeightsTotes[0] = %1.2f\n   elevatorHeightsTotes[1] = %1.2f\n",
			elevatorHeightsTotes[0], elevatorHeightsTotes[1]);

	for(int i=2; i!=LENGTH(elevatorHeightsTotes); i++) {
		elevatorHeightsTotes[i] = round((i - 1) * ticksPerTote + elevatorHeightsTotes[1]);
		printf("   elevatorHeightsTotes[%d] = %1.2f\n", i, elevatorHeightsTotes[i]);
	}
	elevatorHeightsTotes[LENGTH(elevatorHeightsTotes)-1] = 7840.0;
	// last debug out
	//  elevatorHeightsTotes[0] = 0.00
	//  elevatorHeightsTotes[1] = 1204.00
	//  elevatorHeightsTotes[2] = 3285.00
	//  elevatorHeightsTotes[3] = 5367.00
	//  elevatorHeightsTotes[4] = 7448.00
	//   elevatorHeightsTotes[5] = 9529.00 -- will be bashed to 7840

	//Define elevator heights for lifting cans

	elevatorHeightsCans[0] = 0.0;
	elevatorHeightsCans[1] = round(ticksPerInch * (4.0 + inchesPerCanOffset));
	printf("   elevatorHeightsCans[0] = %1.2f\n   elevatorHeightsCans[1] = %1.2f\n",
			elevatorHeightsCans[0], elevatorHeightsCans[1]);

	for(int i = 2; i != LENGTH(elevatorHeightsCans); i++) {
		elevatorHeightsCans[i] = round((i - 1) * ticksPerTote + elevatorHeightsCans[1] /*+ ticksPerCanOffset*/);
		printf("   elevatorHeightsCans[%d] = %1.2f\n", i, elevatorHeightsCans[i]);
	}
	elevatorHeightsCans[LENGTH(elevatorHeightsCans)-1] = 7840.0;
	// last debug output:
	//   elevatorHeightsCans[0] = 0.00
	//   elevatorHeightsCans[1] = 4300.00
	//   elevatorHeightsCans[2] = 6381.00
	//   elevatorHeightsCans[3] = 8463.00 -- will be bashed to 7840


	// This is for testBot only:
	// Simulate movement so a full tote's height takes about 0.5 seconds
	ticksPerCycle = ((ticksPerInch * inchesPerTote) / 25);
}
    
void Elevator::SetHeight(double height)
{
	targetHeight = height;

	if (!RobotMap::testBot) {
		Robot::parameters->UpdateElevatorPIDParams();
		elevatorMotor1->SetVoltageRampRate(30.0);
		elevatorMotor1->SetPID(Parameters::elevatorP,Parameters::elevatorI,Parameters::elevatorD,Parameters::elevatorF);
		elevatorMotor1->ClearIaccum();

		printf("PID Elevator params distance=%1.2f, elevatorP=%1.3f, elevatorI=%1.3f, elevatorD=%1.3f, elevatorF=%1.3f.\n",
				height, Parameters::elevatorP, Parameters::elevatorI, Parameters::elevatorD, Parameters::elevatorF);

		elevatorMotor1->Set(targetHeight);
	}
	else {
		printf("Elevator simulator - move to %1.0f\n", targetHeight);
	}
}

void Elevator::MoveByTote(int commandDirection) {
	// for better or worse, negative is up on our elevator
	printf("MoveTote from %1.2f to %1.2f\n", elevatorIndex, elevatorIndex+commandDirection);
	// avoid truncation problems
	if (commandDirection > 0) elevatorIndex = trunc(elevatorIndex + ((double)commandDirection + 0.001));
	else elevatorIndex = ceil(elevatorIndex + ((double)commandDirection - 0.001));
	if (elevatorIndex < 0) elevatorIndex = 0;
	if (elevatorIndex >= (int)LENGTH(elevatorHeightsTotes)) elevatorIndex = LENGTH(elevatorHeightsTotes)-1;
	SetHeight(-elevatorHeightsTotes[(int)elevatorIndex]);
}

void Elevator::MoveCan(int commandDirection) {
	// for better or worse, negative is up on our elevator
	printf("MoveCan from %1.2f to %1.2f\n", elevatorIndex, elevatorIndex+commandDirection);
	// avoid truncation problems
	if (commandDirection > 0) elevatorIndex = trunc(elevatorIndex + ((double)commandDirection + 0.01));
	else elevatorIndex = ceil(elevatorIndex + ((double)commandDirection - 0.01));
	if (elevatorIndex < 0) elevatorIndex = 0;
	if (elevatorIndex >= (int)LENGTH(elevatorHeightsCans)) elevatorIndex = LENGTH(elevatorHeightsCans)-1;
	SetHeight(-elevatorHeightsCans[(int)elevatorIndex]);
}

// For use in handling the transition between manual control and autonomous.
// Set the current elevator index to be where the elevator actually is
int Elevator::UpdateElevatorIndex() {
	double curPos = GetEncPosition();
	// We start at 1 because we can't be under the zero position
	for (int i = 1; i!=LENGTH(elevatorHeightsTotes); i++) {
		if (-curPos < elevatorHeightsTotes[i]) {
			// we're at position i, but also compute the fraction of the "floor" we're at
			double frac = (-curPos - elevatorHeightsTotes[i-1]) /
					 (elevatorHeightsTotes[i] - elevatorHeightsTotes[i-1]);
			elevatorIndex = (i-1) + frac;
			/*printf("Elevator::UpdateElevatorIndex curPos=%1.f, i=%d, frac=%1.2f elevatorHeightsTotes[i]=%1.2f, elevatorHeightsTotes[i-1]=%1.2f\n",
					 curPos, i, frac,
					 elevatorHeightsTotes[i],  elevatorHeightsTotes[i-1] );*/
			break;
		}
	}
	// it's possible to manually move a little further than the highest official index position..
	if (-curPos > elevatorHeightsTotes[LENGTH(elevatorHeightsTotes)-1]) elevatorIndex = LENGTH(elevatorHeightsTotes)-1;
	//printf("Elevator::UpdateElevatorIndex curPos = %1.2f, index set to %1.2f.\n", curPos, elevatorIndex);
	return elevatorIndex;
}

// Only valid on the test bot. On the real elevator, we actually move
void Elevator::Move(double ticksToMove) {
	// On the production bot, nothing's here. The Talon's PID loop is doing all the work!
	if (RobotMap::testBot) {
		// printf("encoderPos = %1.2f  ", encoderPos);
		if (encoderPos <= 0) {
			// mimic the negative is up orientation of the real elevator
			encoderPos += ticksToMove;
			// printf("--- new encoderPos = %1.2f\n", encoderPos);
			if (encoderPos > 0) encoderPos = 0;
		}
	}
}

void Elevator::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// presume Elevator starts at position zero. We need to actually
	// ensure this elsewhere
	/*   Nah, we don't want this anymore
	 * if (!RobotMap::testBot) {
		SetDefaultCommand(Robot::holdElevatorCommand);
	}
	*/
}

double Elevator::GetPosition() {
	if (RobotMap::testBot) return encoderPos;
	return elevatorMotor1->GetPosition();
}

double Elevator::GetEncPosition() {
	if (RobotMap::testBot) return encoderPos;
	return elevatorMotor1->GetEncPosition();
}

bool Elevator::IsAtTop() {
	if (!RobotMap::testBot) {
		if (!elevatorMotor1->GetReverseLimitOK()) printf("Elevator HIT TOP!\n");
		return !elevatorMotor1->GetReverseLimitOK();
	}
	else return false;
}

bool Elevator::IsAtBottom() {
	if (!RobotMap::testBot)	{
		if (!elevatorMotor1->GetForwardLimitOK()) {
			printf("Elevator zeroed at bottom.\n");
			zeroed = true;
			elevatorMotor1->SetPosition(0.0);
		}
		return !elevatorMotor1->GetForwardLimitOK();
	}
	else{
		if (encoderPos==0) {
			zeroed = true;
			printf("Elevator zeroed at bottom.\n");
		}
		return (encoderPos==0);
	}
}

double Elevator::GetPositionInInches() {
	return -(GetEncPosition()/ticksPerInch) + 8.25;
}

bool Elevator::WasZeroed() {
	return zeroed;
}

