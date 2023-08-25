// C++ code
//

int redLED = 7;
int yellowLED = 8;
int greenLED = 9;
int piezo = 2;

int counter = 0;
int toneCounter = 0;

void setup()
{  
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(piezo, OUTPUT);
}

void loop()
{
  //maximum delay 10 ms, every value should be divided by 10. Ex: 3 s = 3000 ms = 300 units (for the counter)
  counter++;
  
  if(counter <= 300)
  {
    tone(piezo, 5000);
    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);
  }
  else if(counter>300 && counter <= 500)
  {
    toneCounter++;
    if(toneCounter<=30)
    {
      tone(piezo, 20000);      
    }
    else if(toneCounter>30 && toneCounter <50)
    {
      noTone(piezo);      
    }
    else
    {
      toneCounter = 0;
    }
    delay(10);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  else if(counter>500 && counter <= 1000)
  {
    tone(piezo, 15000);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);
  }
  else if(counter>1000 && counter <= 1400)
  {
    toneCounter++;
    if(toneCounter<=30)
    {
      tone(piezo, 20000);      
    }
    else if(toneCounter>30 && toneCounter <50)
    {
      noTone(piezo);      
    }
    else
    {
      toneCounter = 0;
    }
    delay(10);
    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);
  }
  else
  {
    counter = 0;
  }
  delay(10);
}
