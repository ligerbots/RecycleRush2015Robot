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
#include "ctre/CanTalonSRX.h"
#define LENGTH(x) (sizeof(x)/sizeof(x[0]))

/**
 *
 *
 * @author ExampleAuthor
 */
class Elevator: public Subsystem {
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	CANTalon *elevatorMotor1;
	Encoder *pickupEncoder;
	double encoderPos;		// this is only used for the test Bot simulation!

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS

	// Need to use CanTalonSRX for pickupMotor2 so we can invert the following Talon
	// See Software Reference Manual 21.15
	CanTalonSRX* elevatorMotor2;

	Elevator();
	void InitDefaultCommand();
	void ArmFlapUp();
	void ArmFlapDown();
	double GetEncPosition();
	double GetPosition();
	void MoveByTote(int commandDirection);
	void MoveCan(int commandDirection);
	int UpdateElevatorIndex();

	void SetHeight(double height);
	void Move(double n);
	bool IsAtTop();
	bool IsAtBottom();
	bool WasZeroed();
	double GetPositionInInches();

	double elevatorIndex;
	bool zeroed;
	double targetHeight;

	double elevatorHeightsTotes[6];
	double elevatorHeightsCans[4];

	double ticksPerRotation;
	double m_startPos;
	double m_targetPos;

	double inchesPerTote;
	double inchesPerCanOffset;

	double wheelDiameter;
	double inchesPerRotation;
	double ticksPerInch;

	double ticksPerTote;
	double ticksPerCanOffset;

	double ticksPerCycle;	// testBot only

};


