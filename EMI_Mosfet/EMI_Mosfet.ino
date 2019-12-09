  int microswitch = A1;
  int ontkoppelknop = A0;
  int LED = 7;
  int Speaker = 6;
  int solenoid1 = 2;
  bool startup = 0;
  int Ontkoppelen = 0;
  int InPositie = 0;
  
void setup() {
  // put your setup code here, to run once:
  pinMode(microswitch, INPUT);
  pinMode(ontkoppelknop, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(Speaker, OUTPUT);
  pinMode(solenoid1, OUTPUT);
Serial.begin(9600);
  //Retract solenoids
    digitalWrite(solenoid1, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true)
  {
    Ontkoppelen = analogRead(ontkoppelknop);
    InPositie = analogRead(microswitch);
    bool temp1 = 0;
    bool temp2 = 0;
    if (Ontkoppelen >= 700)
    {
      temp1 = 1;  
    }
    if (Ontkoppelen <= 700)
    {
      temp1 = 0;
    }
    if (InPositie >= 700)
    {
      temp2 = 1;  
    }
    if (InPositie <= 700)
    {
      temp2 = 0;
    }
    
    if (temp1 == 1 && temp2 == 1) 
    {
      digitalWrite(solenoid1, HIGH);
      digitalWrite(LED, LOW);
      digitalWrite(Speaker, LOW);
    }
    
    if (temp1 == 0 && temp2 == 1 && startup == 0) // EMI in elkaar geschoven eerste keer
    {
      digitalWrite(solenoid1, LOW);
      digitalWrite(LED, HIGH);
      digitalWrite(Speaker, HIGH);
      delay(1000);
      digitalWrite(Speaker, LOW);
      startup = 1;
    }
    if (temp1 == 0 && temp2 == 1 && startup == 1)
    {
      digitalWrite(LED, HIGH);
      digitalWrite(solenoid1, LOW);
      digitalWrite(Speaker, LOW);
    }
    if (temp1 == 0 && temp2 == 0) 
    {
      digitalWrite(solenoid1, HIGH);
      digitalWrite(LED, LOW);
      digitalWrite(Speaker, LOW);
      startup = 0;
    }
    
    Serial.println(startup);
  }
}
