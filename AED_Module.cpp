#include <wiringPi.h>
#include <iostream>
#include <softPwm.h>
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
		bool Latch1 = false;
		bool Latch2 = false;
		if (digitalRead(Open) == 1)
		{
					//ontgrendel
			digitalWrite(Solenoid1, 1);
			cout << "Solenoid1 open" << endl;
			digitalWrite(Solenoid2, 1);
			cout << "Solenoid2 open" << endl;
			delay(500);
					//openen
			digitalWrite(Servo1, LOW);
			softPwmCreate(Servo1, 0, 200);
			softPwmWrite(Servo1, 25);
			delay(420);
			softPwmWrite(Servo1, 14);
		
			digitalWrite(Servo2, LOW);
			softPwmCreate(Servo2, 0, 200);
			softPwmWrite(Servo2, 4);
			delay(420);
			softPwmWrite(Servo2, 14);
			
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
			while (Latch1 == false || Latch2 == false)
			{
				while (digitalRead(LatchClossed1) == false && Latch1 == false)
				{
					digitalWrite(Servo1, LOW);
					softPwmCreate(Servo1, 0, 200);
					softPwmWrite(Servo1, 4);
					delay(420);
					softPwmWrite(Servo1, 14); 
					digitalWrite(Solenoid1, 1);
				}  
				digitalWrite(Solenoid1, 0);
				Latch1	= true;	
				softPwmStop(Servo1);
				while (digitalRead(LatchClossed2) == 0 && Latch2 == false)
				{
					digitalWrite(Servo2, LOW);
					softPwmCreate(Servo2, 0, 200);
					softPwmWrite(Servo2, 25);
					delay(420);
					softPwmWrite(Servo2, 14);
					digitalWrite(Solenoid2, 1);
				}
				digitalWrite(Solenoid2, 0);
				Latch2 = true;
				softPwmStop(Servo2);

			}
		cout << "Solenoid2 uit" << endl;
		cout << "Luikje2 dicht" << endl;
		cout << "Beide luikjes zijn dicht" << endl;
		}
	}
			
	/*while(digitalRead(Open) == false)
	{
		digitalWrite(Servo1, LOW);
		softPwmCreate(Servo1, 0, 200);
		softPwmWrite(Servo1, 10);
		delay(1000);
	} 
	*/
	return 0;
}

