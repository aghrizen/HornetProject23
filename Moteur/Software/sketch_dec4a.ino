#include <Wire.h>
#include "EdgeImpulse.h"

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
//LIMITE MOTEUR
#define SERVOMIN_Y  100  // Minimum value
#define SERVOMAX_Y  520  // Maximum value
#define SERVOMID_Y  310  // Middle value

//Valeur 0° 90° 180° moteur horizontal
//LIMITE MOTEUR
#define SERVOMIN_X  125  // Minimum value
#define SERVOMAX_X  455  // Maximum value
#define SERVOMID_X  280  // Middle value

// Define servo motor connections (expand as required)
#define SERX  0   //Servo Motor 0 on connector 0
#define SERY  1  //Servo Motor 1 on connector 12


const long POS_X_TO_DEGRE =  360 / SIZE_X_SCREEN ;
const long DEGRE_TO_TICK = (SERVOMAX_1 - SERVOMIN_1) / 180 ;

// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;

int Current_Camera_Angle_X: //En degré
int Current_Camera_Angle_Y: //En degré

const MAX_DEGRE_X = 180;
const MIN_DEGRE_X = 0;

const MAX_DEGRE_Y = 180;
const MIN_DEGRE_Y = 0;


struct FunctionResult 
{ 
    bool Result;
    String NameFunction;
    String CodeError;
    String ErrorDescription;
};

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

void loop() 
{
  int X_coordinate;
  int Y_coordinate;
  int picture_width;
  int picture_height;

  Motor_Initialization();

  while(true)
  {
      DetectMotion(&X_coordinate , &Y_coordinate, &picture_width, &picture_height);
      AimTarget(X_coordinate , Y_coordinate, picture_width, picture_height);
      TakePictureToConfirm();
      AimTarget();
      Shoot();
  }
 
}

FunctionResult DetectMotion(int* x, int* y, int *width, int *height)
{
  //METTRE LA MAGNIFQIUE FONCTION DE AYOUB ICI 
  test = EdgeImpuslse();

  
  //If (   = "hornet") 
  //{
  test.Result = true;
  x = 
  y = 
  width =
  height =
  //}
  //else
  //{
  test.Result = false;
  //}
  return test;
} 

FunctionResult AimTarget(int pos_x, int pos_y, int size_x, int size_y)
{

  //TODO Calcul par rapport à la position actuelle (camera etant sur le viseur)
    long degre_X = x * POS_X_TO_DEGRE;
    long degre_Y = y * POS_Y_TO_DEGRE;

    degre_X = degre_X + Current_Camera_Angle_X;
    degre_Y = degre_Y + Current_Camera_Angle_Y;

    if (degre_X > MAX_DEGRE_X)
    {
      degre_X = MAX_DEGRE_X;
    }
    else if (degre_X < MIN_DEGRE_X)
    {
        degre_X = MIN_DEGRE_X;
    }

      if (degre_Y > MAX_DEGRE_Y)
    {
      degre_Y = MAX_DEGRE_Y;
    }
    else if (degre_Y < MIN_DEGRE_Y)
    {
        degre_Y = MIN_DEGRE_Y;
    }
    Current_Camera_Angle_X = degre_X;
    Current_Camera_Angle_Y = degre_Y;

    PulseValueX = SERVOMIN_X + (long) degre_X* DEGRE_TO_TICK;
    PulseValueY = SERVOMIN_Y + (long) degre_Y* DEGRE_TO_TICK;
    Serial.printf("Valeur en degré = %ld  \n", rand);
    Serial.printf("Valeur en tick = %d \n", PulseValue);
    pca9685.setPWM(SERX, 0, PulseValueX );
    pca9685.setPWM(SERY, 0, PulseValueY );
    delay(5000);
}

FunctionResult TakePictureToConfirm()
{

}

FunctionResult Shoot()
{

}
