#include <Wire.h>
#include <VL53L0X.h>
#include <VL53L1X.h>

#include <ArduinoBLE.h>
#define RED 22
#define GREEN 23
#define BLUE 24

VL53L0X sensor;
VL53L0X sensor2;
VL53L1X sensor3;

// Motor 1
int pwmA = 2; //PWM Out
int in1A = 3; //For Forward
int in2A = 4; //For Back
int MotorSpeedA = 0; // Motor Speed

// Motor 2
int pwmB = 5; //PWM Out
int in1B = 6; //For Forward
int in2B = 7; //For Back
int MotorSpeedB = 0; // Motor Speed

void setup()
{

  pinMode(9, OUTPUT); //For Sensor XShut
  pinMode(10, OUTPUT); //For Sensor2 XShut
  pinMode(11, OUTPUT); //For Sensor3 XShut
 
  digitalWrite(9, LOW); //Shutting sensor down
  digitalWrite(10, LOW); //Shutting sensor2 down
  digitalWrite(11, LOW); //Shutting sensor3 down
 
  delay(500);
  Wire.begin(); //Start SDA
  Wire.setClock(400000); //Setting I2C to 400KHz

  Serial.begin (19200); //Setting rate


  //SENSOR
  //This is used to initiate one of the Vl53L0X and then re-address it so it can be singlely addressed. 
  pinMode(9, INPUT);
  delay(150);
  sensor.init(true);
  delay(100);
  sensor.setAddress((uint8_t)22); //gives address 16

  //SENSOR 2
  pinMode(10, INPUT);
  delay(150);
  sensor2.init(true);
  delay(100);
  sensor2.setAddress((uint8_t)25); //gives address of 19
  
  //SENSOR 3
  pinMode(11, INPUT);
  delay(150);
  sensor3.init(true);
  delay(100);
  sensor3.setAddress((uint8_t)28); //gives address of 22
  sensor3.setDistanceMode(VL53L1X::Medium);

  Serial.println("");
  Serial.println("addresses set");
  Serial.println("");
  Serial.println("");

//Sets the maximum time to wait for data from the sensors. 
  sensor.setTimeout(500);
  sensor2.setTimeout(500);

//Setting Pins for MOTORA
  pinMode(pwmA, OUTPUT);
  pinMode(in1A, OUTPUT);
  pinMode(in2A, OUTPUT);
  
//Setting Pins for MOTORB
  pinMode(pwmB, OUTPUT);
  pinMode(in1B, OUTPUT);
  pinMode(in2B, OUTPUT);
}

void loop()
{
  long DISTANCE_L = (sensor.readRangeSingleMillimeters());
  long DISTANCE_R = (sensor2.readRangeSingleMillimeters());
  long DISTANCE_F = (sensor3.readRangeSingleMillimeters());
	
	if DISTANCE_F < 1000 {
		digitalWrite(BLUE, LOW);
		delay(200);
		digitalWrite(BLUE, HIGH);
		delay(200);
	}
	if DISTANCE_L < 1000 {
		digitalWrite(GREEN, LOW);
		delay(200);
		digitalWrite(GREEN, HIGH);
		delay(200);
	}
	if DISTANCE_R < 1000 {
		digitalWrite(RED, LOW);
		delay(200);
		digitalWrite(RED, HIGH);
		delay(200);
	}
 // Read potentiometer and convert to range of 0-255
  MotorSpeedA = 100;
  MotorSpeedB = 100;

 // Set Motor A forward
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  
 // Set Motor B forward
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, LOW);  
  
  delay(500)
  
   // Set Motor A forward
  digitalWrite(in1A, HIGH);
  digitalWrite(in2A, LOW);
  delay(200);
  
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  delay(200);
  
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, HIGH);
  delay(200);
  
  digitalWrite(in1A, LOW);
  digitalWrite(in2A, LOW);
  delay(200);
  
  digitalWrite(in1B, HIGH);
  digitalWrite(in2B, LOW);  
  delay(200)
  
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, LOW);  
  delay(200)
  
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, HIGH);  
  delay(200)
  
  digitalWrite(in1B, LOW);
  digitalWrite(in2B, LOW);  
  delay(200)
  
  for(int i = 0; i<5; i++){
	  	digitalWrite(BLUE, LOW);
		delay(50);
		digitalWrite(BLUE, HIGH);
		delay(50);
	  
  }

	
}