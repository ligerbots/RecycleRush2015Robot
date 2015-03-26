// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef _ROBOT_H
#define _ROBOT_H
#define inchesBetweenWheels 25.5
#define ninetyDegreeTurn (inchesBetweenWheels*(3.14159/4))

#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/CommandGroup.h"
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
#include <limits.h>

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Subsystems/DriveSubsystem.h"
#include "Subsystems/ArmFlaps.h"
#include "Subsystems/TotePusher.h"
#include "Commands/DriveCommand.h"
#include "Commands/DriveElevator.h"
#include "OI.h"
#include "Subsystems/Elevator.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Commands/DrivePID.h"
#include "Subsystems/Parameters.h"

class Robot : public IterativeRobot {
private:

public:
	CommandGroup *autonomousCommand;
	SendableChooser *chooser;

	static int Ticks;
	static PowerDistributionPanel* pdp;
	static Parameters *parameters;
	static Command *driveCommand;
	static Command *driveElevatorCommand;
	static Command *holdElevatorCommand;
	static Command *zeroElevator;
	CommandGroup *autoCommandDoNothing;
	CommandGroup *autoCommand1Tote;
	CommandGroup *autoCommand1Can;
	CommandGroup *autoCommandMoveToZone;
	CommandGroup *autoCommand1Can1Tote;
// moved to OI for testing	CommandGroup *autoCommand1Can1Tote;

	static OI *oi;
	LiveWindow *lw;
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	static DriveSubsystem* driveSubsystem;
	static Elevator* elevator;
	static ArmFlaps* armFlaps;
	static TotePusher* totePusher;
	static CompressorSubsystem* compressorSubsystem;
	int rumbleTicks = INT_MAX;
	int autoPeriodicCount = 0;

//	static double drivePIDDistance;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	virtual void RobotInit();
	virtual void DisabledInit();
	virtual void DisabledPeriodic();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestPeriodic();
	void UpdateDashboardPeriodic();
	void DisplaySensorData();
	int CameraCount();
	void CameraStart(int i);
	void CameraFeed(int i);
	void CameraStop(int i);
};
#endif
