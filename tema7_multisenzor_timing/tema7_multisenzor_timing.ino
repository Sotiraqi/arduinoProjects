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

int moistureValue = 0;
int temperatureValue = 0;
int lightValue = 0;

int no = 3;
int interval = 1500;
int val_timp = 0;
int d = interval/no;

void loop() {
 
    lightValue += analogRead(LIGHT_SENS);
    moistureValue += analogRead(PTM);
    temperatureValue += analogRead(TEMP_SENS);

    if(val_timp >= interval)
    {
        
      int moistureSensorValue = map(moistureValue, 0, 1023, 300, 900);
      int moisture = moistureSensorValue / no;
      int temperature = (((temperatureValue * 5.0 / 1024) - 0.5) * 100)/no;
      int light = lightValue / no;
          
    
      if(light <= (20*100.0/942)/no)
      {
        digitalWrite(LED, HIGH);
      }
      else
      {
        digitalWrite(LED, LOW);
      }
    
      if(moisture >= (70*600.0/100)/no && temperature <= 20/no)
      {
        tone(PIEZO, 5000);    
      }
      else
      {
        noTone(PIEZO);
      }    

      moistureValue = 0;
      temperatureValue = 0;
      lightValue = 0;
    }
    val_timp += d;
    delay(d);  

}