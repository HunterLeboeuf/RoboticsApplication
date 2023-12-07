#include <AFMotor.h>


AF_DCMotor MotorL(3);  // Motor for drive Left on M3
AF_DCMotor MotorR(4);  // Motor for drive Right on M4

//ultrasonic setup:
const int trigPin = A0; // trig pin connected to Arduino's pin A0
const int echoPin = A1; // echo pin connected to Arduino's pin A1
// Switch set up 
const int switchPin = A2;
// State flags for testing 
const int state_1 = 0;

int state_3 = 0;
int distance = 10;
long duration;
int distanceCm = 0;

void setup() {
  // Ran before everything else 
  Serial.begin(115200);
  Serial.println("Hunter Leboeuf and Arthor Upfield Soda bringer");
  pinMode(trigPin, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input
  pinMode(switchPin,INPUT_PULLUP);





}

// main program loop
void loop() {
  // turn on motor


  // constantly get distance to make sure we dont over shoot target location
  distanceCm=getDistance(); 
  // get the reading from the switch
  int swt = digitalRead(switchPin);

  // Set to low too lazy to change wires around :/
  // Low == soda on 
  // High  == Soda off 
  // if we have soda and are in range we wait until someone takes soda 
  if(swt == LOW && distanceCm <= distance){
    Serial.println("Switch status: " + swt);
    // do nothing but wait as we are in range and have a soda 
    MotorL.setSpeed(0);
    MotorR.setSpeed(0);  
    MotorL.run(RELEASE);
    MotorR.run(RELEASE);
  }
  // if we are not in range we go forward until we are in range 
  else if(distanceCm >= distance)
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
    MotorL.setSpeed(255);
    MotorR.setSpeed(255);
    Serial.println("Moving!!");
    MotorL.run(FORWARD);
    MotorR.run(FORWARD);

}
// turn function to be called when robot needs to complete a 180
int turn()
{
    Serial.println("turning!!");
    //--------------------------------
    MotorL.setSpeed(255);
    MotorR.setSpeed(255);
    // delayed so we know we are completing the turn 
    MotorL.run(FORWARD);
    MotorR.run(BACKWARD);
    // delay for 2 seconds
    delayMicroseconds(2000);

    state_3 = 0;
    // ---------------------------------
}