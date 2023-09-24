#include "RoboticArm.h"
#include <Servo.h>

class RoboticArm {
public:
    // Constructor
    RoboticArm(Servo bas, Servo shl, Servo elb, Servo wri, Servo gri) {
        BAS_SERVO = bas;
        SHL_SERVO = shl;
        ELB_SERVO = elb;
        WRI_SERVO = wri;
        GRI_SERVO = gri;
    }

    void initializeServos() {
        
#define ROBOT_GEEK_9G_GRIPPER 1
#define ROBOT_GEEK_PARALLEL_GRIPPER 2

//The 9G gripper is the gripper with the small blue 9g servo
//The Parralle gripper has a full robotgeek servo and paralle rails
//Uncomment one of the following lines depending on which gripper you are using.
//#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER
#define GRIPPER_TYPE ROBOT_GEEK_PARALLEL_GRIPPER

#ifndef GRIPPER_TYPE
   #error YOU HAVE TO SELECT THE GRIPPER YOU ARE USING! Uncomment the correct line above for your gripper
#endif

#define DELAY_TIME 2 //milliseconds to wait between

//define analog pins that will be connected to the joystick pins
#define BASE      0  //connected to Rotation Knob / Potentiometer # 1
#define SHOULDER  1  //connected to Vertical Axis on Joystick # 1 forward+
#define ELBOW     2  //connected to Vertical Axis on Joystick # 2
#define WRIST     3  //connected to Vertical Axis on Joystick # 3
#define GRIPPER   4  //connected to Rotation Knob / Potentiometer # 2

// Servo position limitations - limits in microseconds
#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  1800
#define ELBOW_MIN     1200
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 

//mins and maxes depending on gripper type
#if GRIPPER_TYPE == ROBOT_GEEK_9G_GRIPPER
  #define GRIPPER_MIN   900   //full counterclockwise for 9g servo
  #define GRIPPER_MAX   2100  //full clockwise for 9g servo
#elif GRIPPER_TYPE == ROBOT_GEEK_PARALLEL_GRIPPER
  #define GRIPPER_MIN   750   //fully closed
  #define GRIPPER_MAX   2400  //fully open
#endif

#define CENTERED      1500

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 462 //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 562  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

// Declare servo objects
Servo BAS_SERVO;  //base servo - RobotGeek Servo
Servo SHL_SERVO;  //shoulder servo - RobotGeek Servo 
Servo ELB_SERVO;  //elbow servo - RobotGee
#define ROBOT_GEEK_9G_GRIPPER 1
#define ROBOT_GEEK_PARALLEL_GRIPPER 2

//The 9G gripper is the gripper with the small blue 9g servo
//The Parralle gripper has a full robotgeek servo and paralle rails
//Uncomment one of the following lines depending on which gripper you are using.
//#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER
#define GRIPPER_TYPE ROBOT_GEEK_PARALLEL_GRIPPER

#ifndef GRIPPER_TYPE
   #error YOU HAVE TO SELECT THE GRIPPER YOU ARE USING! Uncomment the correct line above for your gripper
#endif

#define DELAY_TIME 2 //milliseconds to wait between

//define analog pins that will be connected to the joystick pins
#define BASE      0  //connected to Rotation Knob / Potentiometer # 1
#define SHOULDER  1  //connected to Vertical Axis on Joystick # 1 forward+
#define ELBOW     2  //connected to Vertical Axis on Joystick # 2
#define WRIST     3  //connected to Vertical Axis on Joystick # 3
#define GRIPPER   4  //connected to Rotation Knob / Potentiometer # 2

// Servo position limitations - limits in microseconds
#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  1800
#define ELBOW_MIN     1200
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 

//mins and maxes depending on gripper type
#if GRIPPER_TYPE == ROBOT_GEEK_9G_GRIPPER
  #define GRIPPER_MIN   900   //full counterclockwise for 9g servo
  #define GRIPPER_MAX   2100  //full clockwise for 9g servo
#elif GRIPPER_TYPE == ROBOT_GEEK_PARALLEL_GRIPPER
  #define GRIPPER_MIN   750   //fully closed
  #define GRIPPER_MAX   2400  //fully open
#endif

#define CENTERED      1500

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 462 //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 562  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

// Declare servo objects
Servo BAS_SERVO;  //base servo - RobotGeek Servo
Servo SHL_SERVO;  //shoulder servo - RobotGeek Servo 
Servo ELB_SERVO;  //elbow servo - RobotGeek Servo 
Servo WRI_SERVO;  //wrist servo - RobotGeek Servo
Servo WRO_SERVO;  //wrist rotate servo - RobotGeek Servo (unused for snapper arm)        
Servo GRI_SERVO;  //gripper servo - 9g servo

//present positions of the servos 
int Base     =1500;  //holds the present position of the Base servo, starts at 1500 (centered)
int Shoulder =1500;  //holds the present position of the Shoulder servo, starts at 1500 (centered)
int Elbow    =1500;  //holds the present position of the Elbow servo, starts at 1500 (centered)
int Wrist    =1500;  //holds the present position of the wrist servo, starts at 1500 (centered)
int Gripper  =2100;  //holds the present position of the gripper servo, starts at 1500 (centered)

//last read values of analog sensors (Native values, 0-1023)
int joyBaseVal = 0;     //present value of the base rotation knob (analog 0)
int joyShoulderVal = 0; //present value of the shoulder joystick (analog 1)
int joyElbowVal = 0;    //present value of the elbow joystick (analog 2)
int joyWristVal = 0;    //present value of the wrist joystick (analog 3)
int joyGripperVal = 0;  //present value of the gripper rotation knob (analog 4)

//last calculated values of analog sensors (Mapped values)
//knob values (base and gripper) will be mapped directly to the servo limits
//joystick values (shoulder, elbow and wrist) will be mapped from -speed to speed, to faciliate incremental control
int joyBaseMapped = 0;      //base knob value, mapped from 1-1023 to BASE_MIN-BASE_MAX
int joyShoulderMapped = 0;  //shoulder joystick value, mapped from 1-1023 to -speed to speed
int joyElbowMapped = 0;     //elbow joystick value, mapped from 1-1023 to -speed to speed
int joyWristMapped = 0;     //wrist joystick value, mapped from 1-1023 to -speed to speed
int joyGripperMapped = 0;   //gripper knob  value, mapped from 1-1023 to GRIPPER_MIN-GRIPPER_MAX
int als[8];k Servo 
Servo WRI_SERVO;  //wrist servo - RobotGeek Servo
Servo WRO_SERVO;  //wrist rotate servo - RobotGeek Servo (unused for snapper arm)        
Servo GRI_SERVO;  //gripper servo - 9g servo

//present positions of the servos 
int Base     =1500;  //holds the present position of the Base servo, starts at 1500 (centered)
int Shoulder =1500;  //holds the present position of the Shoulder servo, starts at 1500 (centered)
int Elbow    =1500;  //holds the present position of the Elbow servo, starts at 1500 (centered)
int Wrist    =1500;  //holds the present position of the wrist servo, starts at 1500 (centered)
int Gripper  =2100;  //holds the present position of the gripper servo, starts at 1500 (centered)

//last read values of analog sensors (Native values, 0-1023)
int joyBaseVal = 0;     //present value of the base rotation knob (analog 0)
int joyShoulderVal = 0; //present value of the shoulder joystick (analog 1)
int joyElbowVal = 0;    //present value of the elbow joystick (analog 2)
int joyWristVal = 0;    //present value of the wrist joystick (analog 3)
int joyGripperVal = 0;  //present value of the gripper rotation knob (analog 4)

//last calculated values of analog sensors (Mapped values)
//knob values (base and gripper) will be mapped directly to the servo limits
//joystick values (shoulder, elbow and wrist) will be mapped from -speed to speed, to faciliate incremental control
int joyBaseMapped = 0;      //base knob value, mapped from 1-1023 to BASE_MIN-BASE_MAX
int joyShoulderMapped = 0;  //shoulder joystick value, mapped from 1-1023 to -speed to speed
int joyElbowMapped = 0;     //elbow joystick value, mapped from 1-1023 to -speed to speed
int joyWristMapped = 0;     //wrist joystick value, mapped from 1-1023 to -speed to speed
int joyGripperMapped = 0;   //gripper knob  value, mapped from 1-1023 to GRIPPER_MIN-GRIPPER_MAX
int als[8];
        
        Serial.begin(9600);

    // Attach servo and set limits
        BAS_SERVO.attach(3, BASE_MIN, BASE_MAX);
        SHL_SERVO.attach(5, SHOULDER_MIN, SHOULDER_MAX);
        ELB_SERVO.attach(6, ELBOW_MIN, ELBOW_MAX);
        WRI_SERVO.attach(9, WRIST_MIN, WRIST_MAX);
        GRI_SERVO.attach(10, GRIPPER_MIN, GRIPPER_MAX);
    }

    void moveServo(Servo servo, int initialPosition, int finalPosition) {
        for (int i = initialPosition; i < finalPosition; i++) {
            servo.writeMicroseconds(i);
            delay(DELAY_TIME);
        }

        for (int i = initialPosition; i > finalPosition; i--) {
            servo.writeMicroseconds(i);
            delay(DELAY_TIME);
        }
    }

    void smooth(double base, double shoulder, double elbow, double wrist) {
        // Assuming direct proportional movement to the specified base, shoulder, elbow, wrist values
        moveServo(BAS_SERVO, BAS_SERVO.readMicroseconds(), BAS_SERVO.readMicroseconds() + base);
        moveServo(SHL_SERVO, SHL_SERVO.readMicroseconds(), SHL_SERVO.readMicroseconds() + shoulder);
        moveServo(ELB_SERVO, ELB_SERVO.readMicroseconds(), ELB_SERVO.readMicroseconds() + elbow);
        moveServo(WRI_SERVO, WRI_SERVO.readMicroseconds(), WRI_SERVO.readMicroseconds() + wrist);
    }

    void smoothc(double base, double shoulder, double elbow, double wrist) {
        // Assuming direct proportional movement to the specified base, shoulder, elbow, wrist values
        int pos_base = BAS_SERVO.readMicroseconds();
        int pos_shoulder = SHL_SERVO.readMicroseconds();
        int pos_elbow = ELB_SERVO.readMicroseconds();
        int pos_wrist = WRI_SERVO.readMicroseconds();

        double inc_base = base / 10;
        double inc_shoulder = shoulder / 10;
        double inc_elbow = elbow / 10;
        double inc_wrist = wrist / 10;

        for (int i = 0; i < 10; i++) {
            pos_base += inc_base;
            pos_shoulder += inc_shoulder;
            pos_elbow += inc_elbow;
            pos_wrist += inc_wrist;

            moveServo(BAS_SERVO, BAS_SERVO.readMicroseconds(), pos_base);
            moveServo(SHL_SERVO, SHL_SERVO.readMicroseconds(), pos_shoulder);
            moveServo(ELB_SERVO, ELB_SERVO.readMicroseconds(), pos_elbow);
            moveServo(WRI_SERVO, WRI_SERVO.readMicroseconds(), pos_wrist);
        }
    }

    void setServo() {
        delay(1000);
        BAS_SERVO.writeMicroseconds(Base);
        delay(1000);
        WRI_SERVO.writeMicroseconds(Wrist);
        delay(1000);
        SHL_SERVO.writeMicroseconds(Shoulder);
        delay(1000);
        ELB_SERVO.writeMicroseconds(Elbow);
        delay(1000);
        GRI_SERVO.writeMicroseconds(Gripper);
        delay(1000);
    }

    void moveArm(int* vals, int numVals) {
        for (int i = 0; i < numVals; i += 4) {
            int basd = vals[i] - baso;
#define ROBOT_GEEK_9G_GRIPPER 1
#define ROBOT_GEEK_PARALLEL_GRIPPER 2

//The 9G gripper is the gripper with the small blue 9g servo
//The Parralle gripper has a full robotgeek servo and paralle rails
//Uncomment one of the following lines depending on which gripper you are using.
//#define GRIPPER_TYPE ROBOT_GEEK_9G_GRIPPER
#define GRIPPER_TYPE ROBOT_GEEK_PARALLEL_GRIPPER

#ifndef GRIPPER_TYPE
   #error YOU HAVE TO SELECT THE GRIPPER YOU ARE USING! Uncomment the correct line above for your gripper
#endif

#define DELAY_TIME 2 //milliseconds to wait between

//define analog pins that will be connected to the joystick pins
#define BASE      0  //connected to Rotation Knob / Potentiometer # 1
#define SHOULDER  1  //connected to Vertical Axis on Joystick # 1 forward+
#define ELBOW     2  //connected to Vertical Axis on Joystick # 2
#define WRIST     3  //connected to Vertical Axis on Joystick # 3
#define GRIPPER   4  //connected to Rotation Knob / Potentiometer # 2

// Servo position limitations - limits in microseconds
#define BASE_MIN      600     //full counterclockwise for RobotGeek 180 degree servo
#define BASE_MAX      2400    //full clockwise for RobotGeek 180 degree servo
#define SHOULDER_MIN  600
#define SHOULDER_MAX  1800
#define ELBOW_MIN     1200
#define ELBOW_MAX     2400
#define WRIST_MIN     600
#define WRIST_MAX     2400 

//mins and maxes depending on gripper type
#if GRIPPER_TYPE == ROBOT_GEEK_9G_GRIPPER
  #define GRIPPER_MIN   900   //full counterclockwise for 9g servo
  #define GRIPPER_MAX   2100  //full clockwise for 9g servo
#elif GRIPPER_TYPE == ROBOT_GEEK_PARALLEL_GRIPPER
  #define GRIPPER_MIN   750   //fully closed
  #define GRIPPER_MAX   2400  //fully open
#endif

#define CENTERED      1500

//generic deadband limits - not all joystics will center at 512, so these limits remove 'drift' from joysticks that are off-center.
#define DEADBANDLOW 462 //decrease this value if drift occurs, increase it to increase sensitivity around the center position
#define DEADBANDHIGH 562  //increase this value if drift occurs, decrease it to increase sensitivity around the center position

// Declare servo objects
Servo BAS_SERVO;  //base servo - RobotGeek Servo
Servo SHL_SERVO;  //shoulder servo - RobotGeek Servo 
Servo ELB_SERVO;  //elbow servo - RobotGeek Servo 
Servo WRI_SERVO;  //wrist servo - RobotGeek Servo
Servo WRO_SERVO;  //wrist rotate servo - RobotGeek Servo (unused for snapper arm)        
Servo GRI_SERVO;  //gripper servo - 9g servo

//present positions of the servos 
int Base     =1500;  //holds the present position of the Base servo, starts at 1500 (centered)
int Shoulder =1500;  //holds the present position of the Shoulder servo, starts at 1500 (centered)
int Elbow    =1500;  //holds the present position of the Elbow servo, starts at 1500 (centered)
int Wrist    =1500;  //holds the present position of the wrist servo, starts at 1500 (centered)
int Gripper  =2100;  //holds the present position of the gripper servo, starts at 1500 (centered)

//last read values of analog sensors (Native values, 0-1023)
int joyBaseVal = 0;     //present value of the base rotation knob (analog 0)
int joyShoulderVal = 0; //present value of the shoulder joystick (analog 1)
int joyElbowVal = 0;    //present value of the elbow joystick (analog 2)
int joyWristVal = 0;    //present value of the wrist joystick (analog 3)
int joyGripperVal = 0;  //present value of the gripper rotation knob (analog 4)

//last calculated values of analog sensors (Mapped values)
//knob values (base and gripper) will be mapped directly to the servo limits
//joystick values (shoulder, elbow and wrist) will be mapped from -speed to speed, to faciliate incremental control
int joyBaseMapped = 0;      //base knob value, mapped from 1-1023 to BASE_MIN-BASE_MAX
int joyShoulderMapped = 0;  //shoulder joystick value, mapped from 1-1023 to -speed to speed
int joyElbowMapped = 0;     //elbow joystick value, mapped from 1-1023 to -speed to speed
int joyWristMapped = 0;     //wrist joystick value, mapped from 1-1023 to -speed to speed
int joyGripperMapped = 0;   //gripper knob  value, mapped from 1-1023 to GRIPPER_MIN-GRIPPER_MAX
int als[8];
            int shod = vals[i + 1] - shoo;
            int elbd = vals[i + 2] - elbo;
            int wrid = vals[i + 3] - wrio;

            smoothc(basd, shod, elbd, wrid);

            baso = vals[i];
            shoo = vals[i + 1];
            elbo = vals[i + 2];
            wrio = vals[i + 3];
        }

        BAS_SERVO.writeMicroseconds(Base);
        WRI_SERVO.writeMicroseconds(Wrist);
        SHL_SERVO.writeMicroseconds(Shoulder);
        ELB_SERVO.writeMicroseconds(Elbow);
    }

private:
    Servo BAS_SERVO;
    Servo SHL_SERVO;
    Servo ELB_SERVO;
    Servo WRI_SERVO;
    Servo GRI_SERVO;
    const int DELAY_TIME = 15;

    int baso = 0;
    int shoo = 0;
    int elbo = 0;
    int wrio = 0;
    int gripper = 0;
    int Base = 0;
    int Shoulder = 0;
    int Elbow = 0;
    int Wrist = 0;
};
