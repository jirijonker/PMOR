#include <wiringPi.h>
 #include <iostream>
using namespace std;


#define Servo1 23
#define Servo2 26
#define Open 15
#define Close 16
#define LatchClossed1 4 
#define LatchClossed2 5
#define Solenoid1 21
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
	bool Latch1 = false;
	bool Latch2 = false;
	
	while (true)
	{
		if (digitalRead(Open) == 1)
		{
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
			cout << "Solenoid1 aan" << endl;
			digitalWrite(Solenoid2, 1);
			cout << "Solenoid2 aan" << endl;
			
			while (Latch1 == false || Latch2 == false)
			{
				if(Latch1 == false)
				{
					digitalWrite(Servo1, 1);
					delay(1.5);
					digitalWrite(Servo1, 0);
					delay(18.5);
					if (digitalRead(LatchClossed1) == 1)
					{
						cout << "Luikje1 dicht" << endl;
						digitalWrite(Solenoid1, 0);
						cout << "Solenoid1 uit" << endl;
						cout << "Servo1 uit" << endl;
						Latch1 = true;
						delay(500);
					}
				}
				if(Latch2 == false)
				{
					digitalWrite(Servo2, 1);
					delay(1);
					digitalWrite(Servo2, 0);
					delay(18);
					if (digitalRead(LatchClossed2) == 1)
					{
						cout << "Luikje2 dicht" << endl;
						digitalWrite(Solenoid2, 0);
						cout << "Solenoid2 uit" << endl;
						cout << "Servo2 uit" << endl;
						Latch2 = true;
						delay(500);
					}
				}				

			}
			cout << "Beide luikjes zijn dicht" << endl;
			
		}
	}
	return 0;
}
