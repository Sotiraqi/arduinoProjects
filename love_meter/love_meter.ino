const int sensorPin = A0;
const float baselineTemp = 0;

void setup() {
  Serial.begin(9600);
  for(int pin = 6; pin <=11; pin++)
  {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW); //turn off all LEDs
  }

  
}

void loop() {
  int sensorValue = analogRead(sensorPin);
  Serial.print("Sensor value: ");
  Serial.println(sensorValue);

  //converting ADC to voltage
  float voltage = sensorValue * 5000 / 1024;

  Serial.print("Volts: ");
  Serial.println(voltage);

  //convert voltage to temperature
  float temperature = (voltage - 500) / 10;
  Serial.print("Temperature: ");
  Serial.print(temperature);

  if(temperature <= baselineTemp + 2)
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);    
  }
  else if (temperature > baselineTemp + 2 && temperature <= baselineTemp + 4)
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  }
  else if (temperature > baselineTemp + 4 && temperature <= baselineTemp + 6)
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  }
  else if (temperature > baselineTemp + 6 && temperature <= baselineTemp + 8)
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  }
  else if (temperature > baselineTemp + 8 && temperature <= baselineTemp + 10)
  {
    digitalWrite(11, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(6, LOW);
  }
  else 
  {
    for(int pin = 6; pin <=11; pin++)
    {
      digitalWrite(pin, HIGH); //turn on all LEDs
    }
  }


  

}
