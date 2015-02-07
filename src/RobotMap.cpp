// RobotBuilder Version: 1.5
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"


// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
SpeedController* RobotMap::driveSubsystemfrontLeftMotor = NULL;
SpeedController* RobotMap::driveSubsystemfrontRightMotor = NULL;
RobotDrive* RobotMap::driveSubsystemRobotDrive = NULL;
SpeedController* RobotMap::driveSubsystembackLeftMotor = NULL;
SpeedController* RobotMap::driveSubsystembackRightMotor = NULL;
Encoder* RobotMap::driveSubsystemlEncoder = NULL;
Encoder* RobotMap::driveSubsystemrEncoder = NULL;
SpeedController* RobotMap::pickupSubsystempickupMotor1 = NULL;
SpeedController* RobotMap::pickupSubsystempickupMotor2 = NULL;
Encoder* RobotMap::pickupSubsystempickupEncoder = NULL;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION

void RobotMap::init() {

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();

	driveSubsystemfrontLeftMotor = new TalonSRX(1);
	lw->AddActuator("DriveSubsystem", "frontLeftMotor", (TalonSRX*) driveSubsystemfrontLeftMotor);
	
	driveSubsystemfrontRightMotor = new TalonSRX(3);
	lw->AddActuator("DriveSubsystem", "frontRightMotor", (TalonSRX*) driveSubsystemfrontRightMotor);
	
	driveSubsystemRobotDrive = new RobotDrive(driveSubsystemfrontLeftMotor, driveSubsystemfrontRightMotor);
	
	driveSubsystemRobotDrive->SetSafetyEnabled(false);
        driveSubsystemRobotDrive->SetExpiration(0.1);
        driveSubsystemRobotDrive->SetSensitivity(0.5);
        driveSubsystemRobotDrive->SetMaxOutput(1.0);

        driveSubsystemRobotDrive->SetInvertedMotor(RobotDrive::kRearRightMotor, true);        

	driveSubsystembackLeftMotor = new TalonSRX(2);
	lw->AddActuator("DriveSubsystem", "backLeftMotor", (TalonSRX*) driveSubsystembackLeftMotor);
	
	driveSubsystembackRightMotor = new TalonSRX(4);
	lw->AddActuator("DriveSubsystem", "backRightMotor", (TalonSRX*) driveSubsystembackRightMotor);
	
	driveSubsystemlEncoder = new Encoder(0, 1, false, Encoder::k4X);
	lw->AddSensor("DriveSubsystem", "lEncoder", driveSubsystemlEncoder);
	driveSubsystemlEncoder->SetDistancePerPulse(1.0);
        driveSubsystemlEncoder->SetPIDSourceParameter(Encoder::kRate);
	driveSubsystemrEncoder = new Encoder(2, 3, false, Encoder::k4X);
	lw->AddSensor("DriveSubsystem", "rEncoder", driveSubsystemrEncoder);
	driveSubsystemrEncoder->SetDistancePerPulse(1.0);
        driveSubsystemrEncoder->SetPIDSourceParameter(Encoder::kRate);
	pickupSubsystempickupMotor1 = new Talon(0);
	lw->AddActuator("PickupSubsystem", "pickupMotor1", (Talon*) pickupSubsystempickupMotor1);
	
	pickupSubsystempickupMotor2 = new Talon(5);
	lw->AddActuator("PickupSubsystem", "pickupMotor2", (Talon*) pickupSubsystempickupMotor2);
	
	pickupSubsystempickupEncoder = new Encoder(4, 5, false, Encoder::k4X);
	lw->AddSensor("PickupSubsystem", "pickupEncoder", pickupSubsystempickupEncoder);
	pickupSubsystempickupEncoder->SetDistancePerPulse(1.0);
        pickupSubsystempickupEncoder->SetPIDSourceParameter(Encoder::kRate);


    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	Ct = new CANTalons();

	driveSubsystemfrontLeftMotor = Ct->Init(3, (char *)"FrontLeft");
	//lw->AddActuator("DriveSubsystem", "motorControllerFrontLeft", (CANTalon*) driveSubsystemmotorControllerFrontLeft);
	driveSubsystemfrontRightMotor =  Ct->Init(1, (char *)"FrontRight");
	//lw->AddActuator("DriveSubsystem", "motorControlleFrontRight", (CANTalon*) driveSubsystemmotorControlleFrontRight);
	driveSubsystembackLeftMotor  =  Ct->Init(4, (char *)"BackLeft");
	//lw->AddActuator("DriveSubsystem", "motorControllerBackLeft", (CANTalon*) driveSubsystemmotorControllerBackLeft);
	driveSubsystembackRightMotor =  Ct->Init(2, (char *)"BackRight");
	//lw->AddActuator("DriveSubsystem", "motorControllerBackRight", (CANTalon*) driveSubsystemmotorControllerBackRight);

    driveSubsystemfrontLeftMotor->SetControlMode(CANSpeedController::kPercentVbus);
    driveSubsystemfrontRightMotor->SetControlMode(CANSpeedController::kPercentVbus);
    // Set the back talons to follow the front talons
    driveSubsystembackLeftMotor->SetControlMode(CANSpeedController::kFollower);
    driveSubsystembackLeftMotor->Set(3);
    driveSubsystembackLeftMotor->EnableControl();
    driveSubsystembackRightMotor->SetControlMode(CANSpeedController::kFollower);
    driveSubsystembackRightMotor->Set(1);
    driveSubsystembackRightMotor->EnableControl();
}
