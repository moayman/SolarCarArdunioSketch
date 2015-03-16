byte incomingByte;
byte steeringAngle;
bool RightLeft; // right = 1 left  = 0
bool forward;
bool backward;

void setup() 
{
	Serial.begin(38400);
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
		Serial.print(incomingByte);
    }    
}