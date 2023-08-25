#include <LiquidCrystal.h>
#include <String.h>

#define ROWS 2
#define COLS 16

#define SENSORPIN A0

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);

byte grad[8] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};

String firstMessage = "Temp:";
String secondMessage = "Max:";
String thirdMessage = "Min:";

float sensorValue;
int temp;
static int maxTemp = 0;
static int minTemp = 100;
static int previousTemp;

void setup() {
  pinMode(SENSORPIN, INPUT);
  lcd.begin(COLS, ROWS); 
  lcd.createChar(0, grad);
  Serial.begin(9600);
   
}

void loop()
{
  
  sensorValue = analogRead(SENSORPIN);
  temp = (((sensorValue * 5.0) / 1024) - 0.5) * 100;
  Serial.println(temp);
    
  if(temp >= maxTemp)
  {
    maxTemp = temp;
  }
  
  
  if(temp < minTemp)
  {
    minTemp = temp;
    
  }
  Serial.println("MIN");
  Serial.println(minTemp);
  
  
  String temperature = String(firstMessage+temp);
  String maxTemperature = String(secondMessage+maxTemp);
  String minTemperature = String(thirdMessage+minTemp);
  
  //first line
  lcd.setCursor(2, 0);
  lcd.print(temperature);
  lcd.write(byte(0));
  lcd.print("C");

  //second line
  lcd.setCursor(0, 1);
  lcd.print(maxTemperature);
  lcd.write(byte(0));
  lcd.print("C");

  lcd.setCursor(8, 1);
  lcd.print(minTemperature);
  lcd.write(byte(0));
  lcd.print("C");
     

  delay(100);  
  
}
