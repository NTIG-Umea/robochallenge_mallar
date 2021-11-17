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



//End Patterns

void setup() {

  //Display setup
  pinMode(SCL_Pin,OUTPUT);
  pinMode(SDA_Pin,OUTPUT);
}





/******************************

Code

Example:

void loop() {
  showDisplay(face); //Ritar ut mönstret "face" till display
}
  
******************************/


void loop() {
  showDisplay(face); //Ritar ut mönstret "face" till display
 
}









/******************************

Functions

******************************/

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
