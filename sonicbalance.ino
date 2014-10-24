#include <Ultrasonic.h>

Ultrasonic ultrasonic(12,13);

#include <Servo.h>
Servo myservo1;
Servo myservo2;

//Variables
unsigned int Ptime = 0;                                      
int Drive = 0;                                               
int Error[5];                                       
int P = 0;                                                   // proportional term
int I = 0;                                                   // integral term
int D = 0;                                                   // derivative term

byte Count = 0;                                              
int Period = 0;                                              
int Lwheel = 0;                                              // left wheel variable
int Rwheel = 0;                                              // right wheel variable
                                          
//Ping PID constants
#define Kp 2                                                
#define Ki 3                                                
#define Kd 4                                                

//Meaningful names for error array index:
#define Current 0
#define Sum 1
#define Last 2
#define SecondToLast 3
#define Delta 4

#define Lservo  9 // digital pin 4
#define Rservo 8  // digital pin 5

int accuracy = 1;
// max accuracy for ultrasonic  = 1 
int SetPoint = 365;                                            // perfect balance point value

void setup()
{
  Serial.begin(19200);
  
  //set balance point to be start position
  
  SetPoint = ultrasonic.Timing() / accuracy;
  
  myservo1.attach(9);
  myservo2.attach(8);
}

int PID() {
  Error[Current] = SetPoint - Ptime;
  
  P = Error[Current] * Kp;
  Error[Sum] = Error[Current] + Error[Last] + Error[SecondToLast];
  I = Error[Sum] * Ki;
  Error[Delta] = Error[Current] - Error[Last];
  D = Error[Delta] * Kd;
  Drive = P + I + D;
  Error[SecondToLast] = Error[Last];
  Error[Last] = Error[Current];
  Drive = Drive / 50 ;          //50         
 
  return Drive;
}

int inbyte;

void loop()
{
  
  Ptime = ultrasonic.Timing() / accuracy;
  
  PID();
  
  myservo1.write(90 - Drive); 
  myservo2.write(96 + Drive);
  
 delay(5); 
}





