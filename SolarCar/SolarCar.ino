#define CH1DIR 2
#define CH1PWM 3
#define CH2DIR 4
#define CH2PWM 5

byte received;
byte right;
byte left;
bool backward;

int Speeds[] = { 0, 35, 70, 100, 150, 180, 220, 254};

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{	
  if (Serial.available() > 0) 
  {
    received = Serial.read();
    backward = (received >> 7) & 1;
    right = received & 0x07;
    left = (received & 0x38) >> 3;
    digitalWrite(CH1DIR,!backward);
    digitalWrite(CH2DIR,!backward);
    Serial.write(received);
  }
  analogWrite(CH1PWM,Speeds[right]);
  analogWrite(CH2PWM,Speeds[left]);
}
