#include <Servo.h>
int
left_motor_forward=4,
left_motor_backward=8,
right_motor_forward=2,
right_motor_backward=12,
left_motor_pwm=10,
right_motor_pwm=6;

#define trigPin 5
#define echoPin 3

int dangerThresh = 5; //threshold for obstacles (in cm)
int leftDistance, rightDistance; //distances on either side

Servo panMotor;


void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(left_motor_forward,OUTPUT);
  pinMode(left_motor_backward,OUTPUT);
  pinMode(right_motor_forward,OUTPUT);
  pinMode(right_motor_backward,OUTPUT);
  panMotor.attach(9); //attach motors to proper pins
  panMotor.write(90); //set PING))) pan to center
  delay(1000);
}
void loop()
{
  int distanceFwd = distance_calculation();
  if (distanceFwd>dangerThresh) //if path is clear
    {
     forward(); 
    }
  else //if path is blocked
  {
    Stop();
    panMotor.write(0); 
    delay(500);
    rightDistance = distance_calculation(); //scan to the right
    delay(500);
    panMotor.write(180);
    delay(500);
    leftDistance = distance_calculation(); //scan to the left
    delay(500);
    panMotor.write(90); //return to center
    delay(100);
    compareDistance();
  }

}
void forward()
{
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,150);
  analogWrite(right_motor_pwm,150);
  delay(1000);
  Stop();
}
void backward()
{
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,1);
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,0);
  analogWrite(left_motor_pwm,150);
  analogWrite(right_motor_pwm,150);
  delay(1000);
  Stop();
}
void right_turn()  //hard right turn
{
  digitalWrite(left_motor_forward,1);
  digitalWrite(right_motor_forward,0);
  digitalWrite(left_motor_backward,0);
  digitalWrite(right_motor_backward,1);
  analogWrite(left_motor_pwm,200);   
  analogWrite(right_motor_pwm,100);
  delay(500);
  Stop();
}
void left_turn()    //hard left turn
{
  digitalWrite(left_motor_forward,0);
  digitalWrite(right_motor_forward,1);
  digitalWrite(left_motor_backward,1);
  digitalWrite(right_motor_backward,0);
  analogWrite(left_motor_pwm,100);
  analogWrite(right_motor_pwm,200);
  delay(500);
  Stop();
}
void Stop()
{
  analogWrite(left_motor_pwm,0);
  analogWrite(right_motor_pwm,0);
}

long distance_calculation()
{
  long duration, distance;
  digitalWrite(trigPin, LOW);  
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void compareDistance()
{
  if (leftDistance>rightDistance) //if left is less obstructed 
  {
    left_turn();
    delay(500); 
  }
  else //if right is less obstructed
  {
    right_turn();
    delay(500);
  }
}

  
