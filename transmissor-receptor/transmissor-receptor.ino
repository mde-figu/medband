#include <RH_ASK.h>
#include <SPI.h> // Not actually used but needed to compile
RH_ASK driver;
int pfe=18;
char msg[10];


 
int led = 13;                // the pin that the LED is atteched to
int sensor = 3;// the pin that the sensor is atteched to
int sensor2 = 5;
int state = LOW;             // by default, no motion detected
int state2 = LOW; 
int val = 0;                 // variable to store the sensor status (value)
int val2 = 0;
int countpos=0;// counter for sensor1
int countneg=0; //counter for sensor two 
int countres=0; // result : what we are really after here. later on, this result will be sent by the RF transmitter

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  pinMode(sensor, INPUT);    // initialize sensor as an input
  pinMode(sensor2, INPUT);
  Serial.begin(9600);        // initialize serial
 if (!driver.init())
         Serial.println("init failed");

}

void loop(){
  val = digitalRead(sensor);   // read sensor value
  if (val == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    countpos=countpos+1;
    Serial.print("countpos="); 
    Serial.println(countpos);
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
    }

    // SECOD SENSOR 
    val2 = digitalRead(sensor2);   // read sensor value
  if (val2 == HIGH) {           // check if the sensor is HIGH
    digitalWrite(led, HIGH);   // turn LED ON
    delay(100);                // delay 100 milliseconds 
    
    if (state2 == LOW) {
      Serial.println("Motion detected!"); 
      state2 = HIGH;       // update variable state to HIGH
    countneg=countneg+1;
        Serial.print("countneg"); 
Serial.println(countneg);
    }
  } 
  else {
      digitalWrite(led, LOW); // turn LED OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state2 == HIGH){
        Serial.println("Motion stopped!");
        state2 = LOW;       // update variable state to LOW
    }
    }
    countres=countpos-countneg;
          delay(2000);             // delay 200 milliseconds 

        Serial.println("countres=");

    Serial.println(countres);
   

   // CODE EMETTEUR
const char *msg = "Hello World!";
    itoa(countres, msg, 10);  
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    delay(1000);
   
}
