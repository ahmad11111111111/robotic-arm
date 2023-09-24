#include <RoboticArm.h>
iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii
// Define your servos
Servo BAS_SERVO;
Servo SHL_SERVO;
Servo ELB_SERVO;
Servo WRI_SERVO;
Servo GRI_SERVO;

RoboticArm arm(BAS_SERVO, SHL_SERVO, ELB_SERVO, WRI_SERVO, GRI_SERVO);

void setup() {
    // Initialize your servos and set initial positions
    arm.initializeServos();

    // Set some initial positions
    arm.moveServo(BAS_SERVO, 1500, 1600);
    arm.moveServo(SHL_SERVO, 1500, 1400);
    arm.moveServo(ELB_SERVO, 1500, 1400);
    arm.moveServo(WRI_SERVO, 1500, 1600);
}

void loop() {
    // Move the arm smoothly
    arm.smooth(100, -50, -50, 100);
    delay(1000);

    // Move the arm smoothly back to initial position
    arm.smooth(-100, 50, 50, -100);
    delay(1000);
}
