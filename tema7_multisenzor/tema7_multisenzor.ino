#define PIEZO 8
#define LED 6
#define TEMP_SENS A0
#define LIGHT_SENS A1
#define PTM A2

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(PIEZO, OUTPUT);
  pinMode(TEMP_SENS, INPUT);
  pinMode(LIGHT_SENS, INPUT);
  pinMode(PTM, INPUT);
  Serial.begin(9600);
}

void loop() {
 
    int lightSensorValue = analogRead(LIGHT_SENS);
    Serial.println("Light: ");
    Serial.println(lightSensorValue);
    int potentioValue = analogRead(PTM);
    int temperatureSensorValue = analogRead(TEMP_SENS);
    Serial.println("temperature in volts: ");
    Serial.println(temperatureSensorValue);
  
    int moistureSensorValue = map(potentioValue, 0, 1023, 300, 900);
    Serial.println("moisture: ");
    Serial.println(moistureSensorValue);
    int temperature = ((temperatureSensorValue * 5.0 / 1024) - 0.5) * 100;
    Serial.println("temperature in volts: ");
    Serial.println(temperature);
    
  
    if(lightSensorValue <= (20*100.0/942))
    {
      digitalWrite(LED, HIGH);
    }
    else
    {
      digitalWrite(LED, LOW);
    }
  
    if(moistureSensorValue >= 70*600.0/100 && temperature <= 20)
    {
      tone(PIEZO, 5000);    
    }
    else
    {
      noTone(PIEZO);
    }    
  
    delay(1000);
  

}
