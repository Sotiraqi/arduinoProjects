#include <SoftwareSerial.h>
#include <Arduino.h>

//Serial
SoftwareSerial ser(D7, D6);//RX, TX

//Lights 0-Red Alert, 1-Light sensor, 2-blue, 3-red, 4 yellow, 5-green
#define ALERT D2
#define BLUE D1
#define RED D3
#define YELLOW D4
#define GREEN D5

const int leds[5] = {ALERT, BLUE, RED, YELLOW, GREEN};

void setup() {

  for(int i = 0; i < sizeof(leds)/sizeof(int); i++)
  {
    pinMode(leds[i], OUTPUT);
  }
  
  // put your setup code here, to run once:
  ser.begin(9600);
  Serial.begin(9600); 

}

void loop() {
  // put your main code here, to run repeatedly:
  if(ser.available()>0)
  {
    int led = ser.read();
    Serial.println("Recieving value");
    Serial.println(led);
    switch(led)
    {
      case 1:
      digitalWrite(leds[0], HIGH);
      delay(500);
      break;
      case 2:
      digitalWrite(leds[1], HIGH);
      delay(500);
      break;
      case 3:
      digitalWrite(leds[2], HIGH);
      delay(500);
      break;
      case 4:
      digitalWrite(leds[3], HIGH);
      delay(500);
      break;
      case 5:
      digitalWrite(leds[4], HIGH);
      delay(500);
      break;      
    }

    //turn off all leds
    for(int i = 0; i < sizeof(leds)/sizeof(int); i++)
    {
      digitalWrite(leds[i], LOW);
    }

  }

}
