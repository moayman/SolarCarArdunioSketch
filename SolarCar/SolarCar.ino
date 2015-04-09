#include <Servo.h> 

#define CH1DIR 2
#define CH1PWM 3
#define CH2DIR 4
#define CH2PWM 5
#define STEERINGMOTOR 6

Servo Steering;
byte received;
byte Angle = 7;
byte Speed = 7;
byte oldAngle;

int Speeds[] = { 254, 220, 180, 150, 100, 70, 35, 0, 35, 70, 100, 150, 180, 220, 254};
int Angles[] = { -35, -30, -25, -20, -15, -10, -5, 0, 5, 10, 15, 20, 25, 30, 35};
int Offset=70;

void setup() 
{
  Steering.attach(STEERINGMOTOR);
  MoveServo(Angles[Angle]+Offset);
  Serial.begin(9600);
}
void MoveServo(int Target)
{
    int cpos=Steering.read();
    int dir=Target>cpos?1:-1;
    for(cpos;cpos!=Target;cpos+=dir)
    {
        Steering.write(cpos);
        delay(2);
    }
    Steering.write(cpos);
    delay(2);
}
void loop() 
{	
  if (Serial.available() > 0) 
  {
    received = Serial.read();
    Speed = received & 0x0F;
    oldAngle = Angle;
    Angle = received >> 4;
    if(Speed < 7)
    {
      digitalWrite(CH1DIR,LOW);
      digitalWrite(CH2DIR,LOW);
    }
    else
    {
      digitalWrite(CH1DIR,HIGH);
      digitalWrite(CH2DIR,HIGH);
    }
    MoveServo(Angles[Angle]+Offset);
    Serial.write(received);
  }
  analogWrite(CH1PWM,Speeds[Speed]); 
  analogWrite(CH2PWM,Speeds[Speed]);
}
