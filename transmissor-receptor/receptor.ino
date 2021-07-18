#include <LiquidCrystal.h>
#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;


char buf[12];
char ch;
int Contrast=15;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 10, 5, 4, 3, 2);

void setup() 
{
  Serial.begin(9600);
  Serial.println("LCD test with PWM contrast adjustment");
  pinMode(13,OUTPUT);
  analogWrite(6,Contrast);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("LCD test!!");
//two lines receiver
   if (!driver.init())
         Serial.println("init failed");

}

void loop() 
{


  
uint8_t buf[12];
    uint8_t buflen = sizeof(buf);
    if (driver.recv(buf, &buflen)) // Non-blocking
    {
      int i;
      // Message with a good checksum received, dump it.
      Serial.print("Message: ");
      Serial.println((char*)buf);         
    }



   digitalWrite(13,LOW);
   delay(1000);
   digitalWrite(13,HIGH);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print((char*)buf);









}

void serialEvent()
{
     if (Serial.available())
  {
    ch= Serial.read();
    if(ch=='A' && Contrast<255)
    {
      Contrast=Contrast+1;
    }
    if(ch=='B' && Contrast>0)
    {
      Contrast=Contrast-1;
    }
        if(ch=='N')
    {
      analogWrite(9,28836);
    }
       if(ch=='F')
    {
      analogWrite(9,0);
    }
    analogWrite(6,Contrast);
    Serial.println("Current contrast");
    Serial.println(Contrast);
  }
}
