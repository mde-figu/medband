#include <RH_ASK.h>
#include <SPI.h> // Not actualy used but needed to compile

RH_ASK driver;

// Digital 11 reservado para recepção, DATA do RF-5V

char buf[12];
char ch;
int Contrast=15;
// initialize the library with the numbers of the interface pins


void setup() 
{
  Serial.begin(9600);
  Serial.println("Iniciado");
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
  Serial.print((char*)buf);


}
