// C++ code
//

int redLED = 8;
int yellowLED = 9;
int greenLED = 10;
int pushbutton = 2;
int previousState;
int state = 0;
int counter = 0;


void setup()
{  
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(pushbutton, INPUT);  
  attachInterrupt(digitalPinToInterrupt(pushbutton), myISR, FALLING);
  Serial.begin(9600);
}

void myISR()
{
  state = !state;
}


void loop()
{  
  if(previousState != state)
  {
    counter++;
  }

  Serial.println("Prev");
  Serial.println(previousState);
  Serial.println("STATE");
  Serial.println(state);
  Serial.println("COUNTER");
  Serial.println(counter);  
  if(counter == 0)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
  }
  else if(counter == 1)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, HIGH);
    delay(100);
    digitalWrite(yellowLED, LOW);
    delay(100);
    digitalWrite(greenLED, LOW);    
  }
  else if(counter == 2)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);    
  }
  else
  {
    counter = 0;
  }
  
  previousState = state;
  delay(500);
  
  
 
}
