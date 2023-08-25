#include <LiquidCrystal.h>
#include <String.h>

#define ROWS 2
#define COLS 16

LiquidCrystal lcd(4, 5, 10, 11, 12, 13);



String firstMessage = "Salut";
String secondMessage = "Sotiraq";
String last1, last2 = " ";

int delayCounter = 0;
int posCounterToLeft = 16 - secondMessage.length();
int posCounterToRight = 0;

void setup() {
  lcd.begin(COLS, ROWS); 
  Serial.begin(9600);
   
}

void loop()
{
  if(delayCounter == 0)
  {
    if(posCounterToLeft > 0 && posCounterToRight < COLS - secondMessage.length() + 1)
    {
      lcd.clear();
      lcd.setCursor(posCounterToLeft, 1);
      lcd.print(secondMessage);  
      lcd.setCursor(posCounterToRight, 0);
      lcd.print(firstMessage);   
      
    }
    else
    {
      last2 = secondMessage.substring(-posCounterToLeft); 
      last1 = firstMessage.substring(COLS - posCounterToRight);
              
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(last2);     
      lcd.setCursor(16 + posCounterToLeft, 1); 
      lcd.print(secondMessage);
      lcd.setCursor(0, 0);
      lcd.print(last1);
      lcd.setCursor(posCounterToRight, 0);
      lcd.print(firstMessage);
      
               
    }
    posCounterToLeft--;
    posCounterToRight++;
    if(posCounterToLeft == -1 - secondMessage.length() && posCounterToRight > 15 )
    {
      posCounterToLeft = 16 - secondMessage.length();
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
  
