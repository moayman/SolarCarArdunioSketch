#define CH1DIR 2
#define CH1PWM 3
#define CH2DIR 4
#define CH2PWM 5

byte received;
byte right;
byte left;
bool backward;

int Speeds[] = { 0, 100, 150, 255};

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{	
  if (Serial.available() > 0) 
  {
    received = Serial.read();
    backward = (received >> 4) & 1;
    right = received & 0x03;
    left = (received & 0x0C) >> 2;
    digitalWrite(CH1DIR,!backward);
    digitalWrite(CH2DIR,!backward);
    Serial.write(received);
  }
  analogWrite(CH1PWM,Speeds[right]);
  analogWrite(CH2PWM,Speeds[left]);
}
