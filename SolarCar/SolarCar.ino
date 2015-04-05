#include <Servo.h> 

#define DIR 2
#define PWM 3
#define STEERINGMOTOR 5

Servo Steering;
byte received;
byte Angle;
byte Speed;
byte oldAngle;

int Speeds[] = { 254, 220, 180, 150, 100, 70, 35, 0, 35, 70, 100, 150, 180, 220, 254};
int Angles[] = { -35, -30, -25, -20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30, 35};

void setup() 
{
  Steering.attach(STEERINGMOTOR);
  Serial.begin(9600);
}

void loop() 
{	
  if (Serial.available() > 0) 
  {
    received = Serial.read();
    Speed = received & 0x0F;
    oldAngle = Angle;
    Angle = received >> 4;
    if(Speed < 6)
      digitalWrite(DIR,LOW);
    else
      digitalWrite(DIR,HIGH);
    if(Angle != oldAngle)
      Steering.write(Angles[Angle]);
    Serial.write(received);
  }
  analogWrite(PWM,Speeds[Speed]);
}
