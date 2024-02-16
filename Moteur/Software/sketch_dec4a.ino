#include <Wire.h>
#include "FrelonKiller.h"
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

#define SIZE_X_SCREEN 320
#define SIZE_Y_SCREEN 240


//Rotation limite des moteurs
#define MAX_DEGRE_X  180
#define MIN_DEGRE_X  0

#define MAX_DEGRE_Y  180
#define MIN_DEGRE_Y  0

const long POS_X_TO_DEGRE =  360 / SIZE_X_SCREEN ;
const long DEGRE_TO_TICK_X = (SERVOMAX_X - SERVOMIN_X) / 180 ;

const long POS_Y_TO_DEGRE =  360 / SIZE_X_SCREEN ;
const long DEGRE_TO_TICK_Y = (SERVOMAX_Y - SERVOMIN_Y) / 180 ;



// Variables for Servo Motor positions (expand as required)
int pwm0;
int pwm1;

int Current_Camera_Angle_X; //En degré
int Current_Camera_Angle_Y; //En degré

char State;



void setup() {
  // Serial monitor setup
  State = DetectHornet;
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
  EdgeImpulseAnswer MyEdgeImpulseAnswerObj;


  while(true)
  {
    switch (State)
    {

      case INIT: 
        Motor_Initialization();
      break;

      case DETECT_HORNET:

        DetectMotion(&MyEdgeImpulseAnswerObj);
         if (MyEdgeImpulseAnswerObj.ShouldWeKill == "true")
         { 
            State = AIM_HORNET;
         } 

      break;
      case :AIM_HORNET:
           AimTarget(MyEdgeImpulseAnswerObj);
           State = VERIFY_HOVERING;

      break;

      case VERIFY_HOVERING:
           bool Result = IsTargetNotMoving(&MyEdgeImpulseAnswerObj);
           if (Result == true)
           {
             State = SHOOT;
           }
           else
           {
            State = INIT;
           }
      break;

      case SHOOT:
        Shoot(MyEdgeImpulseAnswerObj);
        State = INIT;

      break;
    }
  }
}

FunctionResult DetectMotion(EdgeImpulseAnswer* MyEdgeImpulseAnswerObj)
{
  //METTRE LA MAGNIFQIUE FONCTION DE AYOUB ICI 
  *MyEdgeImpulseAnswerObj = EdgeImpulse();
  FunctionResult myResult;

  if (MyEdgeImpulseAnswerObj->Name != "NullAnswer")
  {
    myResult.Result = true;
  }
  else
  {
    myResult.Result = false;
  }
  //AFFICHAGE 
  //If (  MyEdgeImpulseAnswerObj.Name == "hornet") 
  //{
  
  //x = MyEdgeImpulseAnswerObj.x;
  //y = MyEdgeImpulseAnswerObj.y;
  //width = MyEdgeImpulseAnswerObj.width;
  //height = MyEdgeImpulseAnswerObj.height;
  //test.Result = true;
  //}
  //else
  //{
  //test.Result = false;
  //}
  return myResult;
} 

FunctionResult AimTarget(EdgeImpulseAnswer MyEdgeImpulseAnswerObj)
{
    //Center coordinates of Frelon
    int pos_x = MyEdgeImpulseAnswerObj.x + (MyEdgeImpulseAnswerObj.size_x)/2;
    int pos_y = MyEdgeImpulseAnswerObj.y + (MyEdgeImpulseAnswerObj.size_y)/2;


  //TODO Calcul par rapport à la position actuelle (camera etant sur le viseur)
    long degre_X = pos_x * POS_X_TO_DEGRE;
    long degre_Y = pos_y * POS_Y_TO_DEGRE;

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

    int PulseValueX = SERVOMIN_X + (long) degre_X* DEGRE_TO_TICK_X;
    int PulseValueY = SERVOMIN_Y + (long) degre_Y* DEGRE_TO_TICK_Y;
    Serial.printf("Valeur en degré pour X = %ld  \n", degre_X);
    Serial.printf("Valeur en tick pour X = %d \n", PulseValueX);
    pca9685.setPWM(SERX, 0, PulseValueX );
    pca9685.setPWM(SERY, 0, PulseValueY );
    delay(5000);
}

FunctionResult IsTargetNotMoving(EdgeImpulseAnswer* LastEdgeImpulseAnswerObj)
{
  FunctionResult MyResult; 
  int old_pos_x;
  int old_pos_y;
  int pos_x;
  int pos_y;

  EndOfLoap = false;
  while(EndOfLoap == false;)
  {
    old_pos_x = LastEdgeImpulseAnswerObj.x + (LastEdgeImpulseAnswerObj.size_x)/2;
    old_pos_y = LastEdgeImpulseAnswerObj.y + (LastEdgeImpulseAnswerObj.size_y)/2;

    EdgeImpulseAnswer MyCurrentEdgeImpulseAnswerObj = EdgeImpulse();

    pos_x = MyCurrentEdgeImpulseAnswerObj.x + (MyCurrentEdgeImpulseAnswerObj.size_x)/2;
    pos_y = MyCurrentEdgeImpulseAnswerObj.y + (MyCurrentEdgeImpulseAnswerObj.size_y)/2;
  }

  //Si aucun frelon détecté
  if (MyCurrentEdgeImpulseAnswerObj.Name != "hornet")
  {
    //Return false
    MyResult.Result = false;
    return MyResult
  }
  else
  {
    //Si on détecte toujours un frelon, on regarde si il a bougé
    //Si la différente est seulement de quelques pixels, on repositionne la caméra
    //#TODO
  }
  return MyResult;
}

FunctionResult Shoot(EdgeImpulseAnswer LastEdgeImpulseAnswerObj)
{
  FunctionResult myResult;
  myResult.Result = false;
  return myResult;
}

void Motor_Initialization()
{
  //Positionne les moteurs à 90 degrés.
  //Permet de synchro la pos des moteurs avec celle enregistré dans le uc
  //Il y a un risque de desynchronisation ( écart de position entre commande et réponse)
  //Cette fonction sera dans le futur remplaçé par un régulateur de position

  //90° en ticks
  int PulseValueX = SERVOMID_X;
  int PulseValueY = SERVOMID_Y;
  pca9685.setPWM(SERX, 0, PulseValueX);
  pca9685.setPWM(SERY, 0, PulseValueY);

  delay(5000);
  Current_Camera_Angle_X = 90;
  Current_Camera_Angle_Y = 90;



}
