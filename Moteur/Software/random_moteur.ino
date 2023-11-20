#include <Wire.h>

// Include Adafruit PCA9685 Servo Library
#include <Adafruit_PWMServoDriver.h>

// Creat object to represent PCA9685 at default I2C address
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver(0x40);

// Define maximum and minimum number of "ticks" for the servo motors
// Range from 0 to 4095
// This determines the pulse width

#define SDA 26
#define SCL 27 

//Valeur 0° 90° 180° moteur vertical
#define SERVOMIN_1  100  // Minimum value
#define SERVOMAX_1  520  // Maximum value
#define SERVOMID_1  310  // Middle value

//Valeur 0° 90° 180° moteur horizontal
#define SERVOMIN_2  125  // Minimum value
#define SERVOMAX_2  455  // Maximum value
#define SERVOMID_2  280  // Middle value

// Define servo motor connections (expand as required)
#define SER0  0   //Servo Motor 0 on connector 0
#define SER1  1  //Servo Motor 1 on connector 12
const int DEGRE_TO_TICK = (SERVOMAX_1 - SERVOMIN_1) / 180 ;

// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;

void setup() {
  // Serial monitor setup
  Wire.begin(SDA , SCL);
  Serial.begin(115200);

  // Print to monitor
  Serial.println("PCA9685 Servo Test");

  // Initialize PCA9685
  pca9685.begin();

  // Set PWM Frequency to 50Hz
  pca9685.setPWMFreq(50);

}

void loop() {
  long rand;
  rand = random(0, 180);
  int PulseValue = SERVOMIN_1 + rand* DEGRE_TO_TICK;

  Serial.printf("Valeur en degré = %ld  \n", rand);
  Serial.printf("Valeur en tick = %d \n", PulseValue);
  pca9685.setPWM(SER0, 0, PulseValue );
  pca9685.setPWM(SER1, 0, PulseValue );
  delay(500);
  //MIN Moteur vertical

 
}
