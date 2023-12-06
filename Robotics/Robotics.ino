#include <AFMotor.h>

AF_DCMotor MotorL(1);  // Motor for drive Left on M1
AF_DCMotor MotorR(2);  // Motor for drive Right on M2

//ultrasonic setup:
const int trigPin = A0; // trig pin connected to Arduino's pin A0
const int echoPin = A1; // echo pin connected to Arduino's pin A1
// Switch set up 
const int switchPin = A2;

int distance = 10;

long duration;
int distanceCm = 0;

void setup() {
  // Ran before everything else 
  Serial.begin(115200);
  Serial.println("Hunter Leboeuf and Aurthor Upfield Soda bringer");
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(switchPin,INPUT_PULLUP);
  MotorL.setSpeed(255);
  MotorR.setSpeed(255);
  
  // turn on motor
  MotorL.run(RELEASE);
  MotorR.run(RELEASE);



}

// main program loop
void loop() {


  // constantly get distance to make sure we dont over shoot target location
  distanceCm=getDistance(); 
  // get the reading from the switch
  int swt = digitalRead(switchPin);
  Serial.println(distanceCm);
  // Set to low too lazy to change wires around :/
  // Low == soda on 
  // High  == Soda off 
  // if we have soda and are in range we wait until someone takes soda 
  if(swt == LOW && distanceCm <= distance){
    Serial.println("Switch status: " + swt);
    // do nothing but wait as we are in range and have a soda 

  }
  // if we have a soda but are not in range we go forward until we are in range 
  else if(swt == LOW && distanceCm >= distance)
  {
    move();
  }
  // if we dont have a soda and are in range we turn 
  else if(swt == HIGH && distanceCm <= distance)
  {
    turn();
  }
}



//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
int getDistance() {
  int echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  int calcualtedDistance;         //variable to store the distance calculated from the echo time
  
  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calcualtedDistance = echoTime / 58.26;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)
  return calcualtedDistance;              //send back the distance that was calculated
}
// move function to be called to move robot forward 
int move()
{
    MotorL.run(FORWARD);
    MotorR.run(FORWARD);

}
// turn function to be called when robot needs to complete a 180
int turn()
{
    // delayed so we know we are completing the turn 
    MotorL.run(FORWARD);
    MotorR.run(BACKWARD);
    delay(1000);

}