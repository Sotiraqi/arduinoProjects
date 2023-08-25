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

String firstMessage = "Temp: ";
String secondMessage = "Max temp: ";
String last1, last2 = " ";

float sensorValue;
int temp;
static int maxTemp = 0;

int delayCounter = 0;
int posCounterToLeft = 16 - secondMessage.length();
int posCounterToRight = 0;

void setup() {
  pinMode(SENSORPIN, INPUT);
  lcd.begin(COLS, ROWS); 
  lcd.createChar(0, grad);
  Serial.begin(9600);
   
}

void loop()
{
  if(delayCounter == 0)
  {
    sensorValue = analogRead(SENSORPIN);
    temp = (((sensorValue * 5.0) / 1024) - 0.5) * 100;
    Serial.println(temp);
    String temperature = String(firstMessage+temp);

    
    if(temp >= maxTemp)
    {
      maxTemp = temp;
    }
    

    String maxTemperature = String(secondMessage+maxTemp);
    
    if(posCounterToLeft > 0 && posCounterToRight < COLS - temperature.length() + 1)
    {
      lcd.clear();
      lcd.setCursor(posCounterToLeft, 1);
      lcd.print(maxTemperature);
      lcd.write(byte(0));
      lcd.setCursor(posCounterToRight, 0);
      lcd.print(temperature);   
      lcd.write(byte(0));
      
    }
    else
    {
      last2 = maxTemperature.substring(-posCounterToLeft); 
      last1 = temperature.substring(COLS - posCounterToRight);
              
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(last2);   
      lcd.write(byte(0));  
      lcd.setCursor(16 + posCounterToLeft, 1); 
      lcd.print(maxTemperature);
      lcd.write(byte(0));
      lcd.setCursor(0, 0);
      lcd.print(last1);
      lcd.write(byte(0));
      lcd.setCursor(posCounterToRight, 0);
      lcd.print(temperature);
      lcd.write(byte(0));
      
               
    }
    posCounterToLeft--;
    posCounterToRight++;
    if(posCounterToLeft == -1 - maxTemperature.length() && posCounterToRight > 15 )
    {
      posCounterToLeft = 16 - maxTemperature.length();
      posCounterToRight = 0 ;
      last1 = " ";
      
    }
  }
  delayCounter++;

  if(delayCounter>=4)
  {
    delayCounter = 0;
  }

  delay(50);  
  
}
