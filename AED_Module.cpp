#include <wiringPi.h>
 #include <iostream>
using namespace std;


#define Servo1 23
#define Servo2 26
#define Open 15
#define Close 16
#define LatchClossed1 4 
#define LatchClossed2 5
#define Solenoid1 22
#define Solenoid2 30

	
int main()
{
	wiringPiSetup();
	pinMode(Servo1, OUTPUT);
	pinMode(Servo2, OUTPUT);
	pinMode(Open, INPUT);
	pinMode(Close, INPUT);
	pinMode(LatchClossed1, INPUT);
	pinMode(LatchClossed2, INPUT);
	pinMode(Solenoid1, OUTPUT);
	pinMode(Solenoid2, OUTPUT);
	
	while (true)
	{
		if (digitalRead(Open) == 1)
		{
			//Latch1 = false;
			//Latch2 = false;
					//ontgrendel
			digitalWrite(Solenoid1, 1);
			cout << "Solenoid1 open" << endl;
			digitalWrite(Solenoid2, 1);
			cout << "Solenoid2 open" << endl;
			delay(500);
					//openen
			for(int i = 0; i < 1; ++i)
			{
				digitalWrite(Servo1, 1);
				delay(2);
				digitalWrite(Servo1, 0);
				delay(18);
			}
			for(int i = 0; i < 1; ++i)
			{
				digitalWrite(Servo2, 1);
				delay(1.5);
				digitalWrite(Servo2, 0);
				delay(18.5);
			}			
			delay(2000);
					//einde open
			digitalWrite(Solenoid1, 0);
			cout << "Solenoid1 dicht" << endl;
			digitalWrite(Solenoid2, 0);
			cout << "Solenoid2 dicht" << endl;

		}
		else if (digitalRead(Close) == 1)
		{
			//sluiten
			digitalWrite(Solenoid1, 1);
			cout << "Solenoid1 open" << endl;
			digitalWrite(Solenoid2, 1);
			cout << "Solenoid2 open" << endl;
			for(int i = 0; i < 1; ++i)
			{
				digitalWrite(Servo1, 1);
				delay(1.5);
				digitalWrite(Servo1, 0);
				delay(18.5);
			}		
			while (digitalRead(LatchClossed1) == 0)
			{
				digitalWrite(Solenoid1, 1);
			}
			digitalWrite(Solenoid1, 0);
			cout << "Luikje1 dicht" << endl;
			cout << "Solenoid1 uit" << endl;
			for(int i = 0; i < 1; ++i)
			{
				digitalWrite(Servo2, 1);
				delay(2);
				digitalWrite(Servo2, 0);
				delay(18);
			}
			while (digitalRead(LatchClossed2) == 0)
			{
				digitalWrite(Solenoid2, 1);
			}
			digitalWrite(Solenoid2, 0);
			cout << "Solenoid2 uit" << endl;
			cout << "Luikje2 dicht" << endl;
		cout << "Beide luikjes zijn dicht" << endl;
		}
	}
	return 0;
}
