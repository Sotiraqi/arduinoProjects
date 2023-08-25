#include <LiquidCrystal.h>
#include <String.h>

#define ROWS 2
#define COLS 16

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);



String message = "Salut";
String last = " ";

int delayCounter = 0;
int posCounter = 16 - message.length();

void setup() {
  lcd.begin(COLS, ROWS); 
  Serial.begin(9600);
   
}

void loop()
{
  if(delayCounter == 0)
  {
    if(posCounter >= COLS - message.length())
    {
      last = message.substring(COLS + posCounter);
      lcd.print(last);
      Serial.print("Poscounter first if: ");
      Serial.println(posCounter);
      lcd.clear();
      lcd.setCursor(posCounter, 0);
      lcd.print(message);      
      
    }
    else
    {
      
      
      lcd.clear();
      lcd.setCursor(posCounter, 0);
      lcd.print(message);      
      Serial.print("Poscounter else: ");
      Serial.println(posCounter);         
    }
    posCounter--;
    if(posCounter < 0)
    {
      posCounter = 16;
    }
  }
  delayCounter++;

  if(delayCounter>=4)
  {
    delayCounter = 0;
  }

  delay(200);  
  
}
  
