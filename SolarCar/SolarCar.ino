byte incomingByte;
byte steeringAngle;
bool RightLeft;
bool forward;
bool backward;

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{	
  if (Serial.available() > 0) 
  {
    incomingByte = Serial.read();
    RightLeft = (incomingByte >> 4) & 1;
    steeringAngle = (incomingByte & 0x0C) >> 2;
    forward = incomingByte & 1;
    backward = (incomingByte >> 1) & 1;
    Serial.write(incomingByte);
  }    
}
