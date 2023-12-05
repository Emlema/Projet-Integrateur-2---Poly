
#include <Servo.h>
#include <SoftwareSerial.h> 
#include <ArduinoBlue.h> 

const unsigned long BAUD_RATE = 9600;

const int depot1 = 2; 
const int depot2 = 3; 
const int leftForward = 4; 
const int leftBackward = 5; 
const int rightForward = 10; 
const int rightBackward = 11;


const int MINIMUM_MOTOR_SPEED = 65;


const int BLUETOOTH_TX = 8;
const int BLUETOOTH_RX = 7;

Servo myservo;

int pos = 0;
int button = -1;

SoftwareSerial softSerial(BLUETOOTH_TX, BLUETOOTH_RX);
ArduinoBlue phone(softSerial);

void depot(){
  digitalWrite(depot1 , HIGH);
  digitalWrite(depot2 , LOW);
}

void stopdepot(){
  digitalWrite(depot1 , LOW);
  digitalWrite(depot2 , LOW);
}

void stopRobot() {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , LOW);
}

void moveBackward() {
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);
}

void moveForward() {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
}

void turnLeft() {
  digitalWrite(leftForward , HIGH);
  digitalWrite(leftBackward , LOW);
  digitalWrite(rightForward , HIGH);
  digitalWrite(rightBackward , LOW);
}

void turnRight() {
  digitalWrite(leftForward , LOW);
  digitalWrite(leftBackward , HIGH);
  digitalWrite(rightForward , LOW);
  digitalWrite(rightBackward , HIGH);
}

void controlDrive() {
	int throttle = phone.getThrottle() - 49;
	int steering = phone.getSteering() - 49;

	if (throttle == 0 and steering == 0 ) {
		stopRobot();
		return;
	}

	if (throttle > 0) {
		moveForward();
	}
	if (throttle < 0) {
		moveBackward();
	}

  if (steering > 0) {
		turnLeft();
	}
	if (steering < 0) {
		turnRight();
	}
}



void setup() {
	delay(500);
	softSerial.begin(BAUD_RATE);
  myservo.attach(6);
  
  pinMode(depot1, OUTPUT);
  pinMode(depot2, OUTPUT);
	Serial.begin(BAUD_RATE);

	Serial.println("SETUP COMPLETE");
}


bool isServoActive = false;

void loop() {
  button = phone.getButton();
  Serial.println(button);




  if (button == 1) {
  myservo.attach(9);
  myservo.write(104);
  delay(300);
  myservo.attach(6);
  }else if (button == 0) {
    myservo.attach(9);
     myservo.write(81);
     delay(300);
     myservo.attach(6);
  }else if (button == 2) {
   myservo.attach(6);
  }
  
 if (button == 3){
 depot();
 delay(500);
 stopdepot();
  }

   
 controlDrive();

  }
