#include <iostream>
//#include <wiringPi.h>

using namespace std;


//wiringPi uses its own GPIO numbering!!!!

// digitalWrite(pin, value)
//digitalRead(pin)
int main()
{
	wiringPiSetup();
	int Direction1 = pinMode(7, OUTPUT);
	int Direction2 = pinMode(7, OUTPUT);

	bool Servo1 = pinMode(8, OUTPUT);
	bool Servo2 = pinMode(9, OUTPUT);

	bool Open = pinMode(15, INPUT);
	bool Close = pinMode(16, INPUT);

	int LatchClossed1 = pinMode(4, INPUT);
	int LatchClossed2 = pinMode(5, INPUT);

	int Solenoid1 = pinMode(0, OUTPUT);
	int Solenoid2 = pinMode(2, OUTPUT);
	
	while (true)
	{
		if (digitalRead(Open) == true) 
		{
			digitalWrite(Solenoid1, true);
			digitalWrite(Solenoid2, true);
			delay(500); //Delay is in ms
			digitalWrite(Direction1, 1);
			digitalWrite(Direction2, -1);
			digitalWrite(Servo1, true);
			digitalWrite(Servo2, true);
		}
		else if (digitalRead(Close) == true)
		{
			digitalWrite(Direction1, -1);
			digitalWrite(Direction2, 1);
			digitalWrite(Servo1, true);
			digitalWrite(Servo2, true);
			while (digitalRead(LatchClossed1) == false || digitalRead(LatchClossed2) == false)
			{
				if (digitalRead(LatchClossed1) == true)
				{
					digitalWrite(Solenoid1, false);
				}
				if (digitalRead(LatchClossed2) == true)
				{
					digitalWrite(Solenoid2, false);
				}
			}
		}
	}
	return 0;
}