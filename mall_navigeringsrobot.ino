/******************************

Setup

******************************/

//Motor pins
int ML_Ctrl = 4; 
int ML_PWM = 5;   
int MR_Ctrl = 2;    
int MR_PWM = 9;  

//Servo pin
int headPin = 10;

//Sonar Pins
int trigPin = 12;    // Sonar Trigger
int echoPin = 13;    // Sonar Echo

//Display Pins
int SCL_Pin = A5;  //Set clock pin to A5
int SDA_Pin = A4;  //Set data pin to A4

//Display Patterns (16*8)
//http://dotmatrixtool.com/

unsigned char face[] = {0x00, 0x00, 0x04, 0x0a, 0x04, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x04, 0x0a, 0x04, 0x00, 0x00};

void setup() {

  //Motor setup
  pinMode(ML_Ctrl, OUTPUT);
  pinMode(ML_PWM, OUTPUT);
  pinMode(MR_Ctrl, OUTPUT);
  pinMode(MR_PWM, OUTPUT);

  //Sonar setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Display setup
  pinMode(SCL_Pin,OUTPUT);
  pinMode(SDA_Pin,OUTPUT);

  Serial.begin (9600);
}





/******************************

Code

Example:

void loop() {
  showDisplay(face); //Ritar ut mönstret "face" till display
  
  goForward(500); //Kör frammåt i 500ms, fortsätter köra om inget annat kommando ges
  goBackward(500);  //Kör bakåt i 500ms, fortsätter köra om inget annat kommando ges
  goLeft(500);  //Svänger vänster i 500ms, fortsätter köra om inget annat kommando ges
  goRight(500);  //Svänger höger i 500ms, fortsätter köra om inget annat kommando ges
  goStop(500);  //Står stilla i 500ms, fortsätter köra om inget annat kommando ges
  
  turnHead(50); //Vänder huvudet till 50 grader
  
  int distance = lookAhead(); //Läser av avståndet till närmsta hinder
  Serial.println(distance); //Skriver ut till USB så att det går att se via Verktyg -> Seriell Monitor (Tools -> Serial Monitor)
}
  
******************************/


void loop() {
  showDisplay(face); //Ritar ut mönstret "face" till display
  
  goForward(500); //Kör frammåt i 500ms, fortsätter köra om inget annat kommando ges
  goBackward(500);  //Kör bakåt i 500ms, fortsätter köra om inget annat kommando ges
  goLeft(500);  //Svänger vänster i 500ms, fortsätter köra om inget annat kommando ges
  goRight(500);  //Svänger höger i 500ms, fortsätter köra om inget annat kommando ges
  goStop(500);  //Står stilla i 500ms, fortsätter köra om inget annat kommando ges
  
  turnHead(50); //Vänder huvudet till 50 grader
  
  int distance = lookAhead(); //Läser av avståndet till närmsta hinder
  Serial.println(distance); //Skriver ut till USB så att det går att se via Verktyg -> Seriell Monitor (Tools -> Serial Monitor)
}









/******************************

Functions

******************************/

void goStop(int time) {
  analogWrite(ML_PWM,0);
  analogWrite(MR_PWM,0);
  delay(time);
}

void goForward(int time) {
  digitalWrite(ML_Ctrl,HIGH);//set the direction control pin of B motor to HIGH
  analogWrite(ML_PWM,200);//set the PWM control speed of B motor to 200
  digitalWrite(MR_Ctrl,HIGH);//set the direction control pin of A motor to HIGH
  analogWrite(MR_PWM,200);//set the PWM control speed of A motor to 200
  delay(time);
}

void goBackward(int time) {
  digitalWrite(ML_Ctrl,LOW);//set the direction control pin of B motor to LOW
  analogWrite(ML_PWM,200);//set the PWM control speed of B motor to 200  
  digitalWrite(MR_Ctrl,LOW);//set the direction control pin of A motor to LOW
  analogWrite(MR_PWM,200);//set the PWM control speed of A motor to 200
  delay(time);
}

void goRight(int time){
  digitalWrite(ML_Ctrl,HIGH);
  analogWrite(ML_PWM,200);
  digitalWrite(MR_Ctrl,LOW);
  analogWrite(MR_PWM,200);
  delay(time);
}

void goLeft(int time){
  digitalWrite(ML_Ctrl,LOW);
  analogWrite(ML_PWM,200);
  digitalWrite(MR_Ctrl,HIGH);
  analogWrite(MR_PWM,200);
  delay(time);
}


void turnHead(int angle){
  int pulsewidth;
  pulsewidth = angle * 11 + 500;  //calculate the value of pulse width
  digitalWrite(headPin,HIGH);
  delayMicroseconds(pulsewidth);   //The duration of high level is pulse width
  digitalWrite(headPin,LOW);
  delay((20 - pulsewidth / 1000));  // the cycle is 20ms, the low level last for the rest of time
}

int lookAhead(){
  int duration, cm;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
   // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);
   // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343

  return cm;
}


void showDisplay(unsigned char matrix_value[])
{
  IIC_start();  //the function to call the data transmission
  IIC_send(0xc0);  //Select address
  
  for(int i = 0;i < 16;i++) //Pattern data has 16 bytes
  {
     IIC_send(matrix_value[i]); //data to convey patterns
  }
  IIC_end();   //end the transmission of patterns data
  IIC_start();
  IIC_send(0x8A);  //display control, set pulse width to 4/16
  IIC_end();
}
//  the condition that data transmission starts
void IIC_start()
{
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
}
// transmit data
void IIC_send(unsigned char send_data)
{
  for(char i = 0;i < 8;i++)  //Every character has 8 bits
  {
      digitalWrite(SCL_Pin,LOW);  //pull down the SCL_Pin to change the signal of SDA
      delayMicroseconds(3);
      if(send_data & 0x01)  //1 or 0 of byte  is used to set high and low level of SDA_Pin
      {
        digitalWrite(SDA_Pin,HIGH);
      }
      else
      {
        digitalWrite(SDA_Pin,LOW);
      }
      delayMicroseconds(3);
      digitalWrite(SCL_Pin,HIGH); //Pull up SCL_Pin to stop data transmission
      delayMicroseconds(3);
      send_data = send_data >> 1;  //Detect bit by bit, so move the data right by one bit
  }
}
//the sign that data transmission ends 
void IIC_end()
{
  digitalWrite(SCL_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,LOW);
  delayMicroseconds(3);
  digitalWrite(SCL_Pin,HIGH);
  delayMicroseconds(3);
  digitalWrite(SDA_Pin,HIGH);
  delayMicroseconds(3);
}//****************************************************************************************
