#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal.h>
#include "configs.h"

//liquid crystal
const int rs = 3, en = 2, d4 = 16, d5 = 17, d6 = 18, d7 = 19;

//Functions
void emergency_alert();
int calculateWaterLevel(int analogValue);
int calculateMotorSpeed(int analogValue);
int calculateLightIntensity(int analogValue);

SoftwareSerial ser(6, 7);//Serial
MFRC522 cardReader = new MFRC522(SS_PIN, RST_PIN); //Card reader
Servo lock; //servo motor (lock)
Adafruit_BMP280 bmp; //temperature sensor
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); //lcd

//Analog values
int analogWater = 0;
int analogPhotoresistor = 0;
int analogPotentio = 0;

//default values
int waterLevel = 0;
float temperature = 0;
int motorPower = 0;
int lighting = 0;
int pressure;
int altitude;

//LCD strings
String firstMessage = "Temp:";
String secondMessage = "Press:";
String thirdMessage = "Alt:";

byte grad[8] = {
  B00010,
  B00101,
  B00010,
  B00000,
  B00000,
  B00000,
  B00000,
};

void setup() {

  //lcd
  lcd.begin(16, 2);
  lcd.createChar(0, grad);
  //Serial
  Serial.begin(9600);
  ser.begin(9600);
    
  //Card reader
  SPI.begin();
  cardReader.PCD_Init();
  Serial.println("Approximate card: ");
  Serial.println();

  //Lock
  lock.attach(SERVO_PIN);
  lock.write(0);
  

  //Piezo
  pinMode(PIEZO_PIN, OUTPUT);

  //Sensors
  pinMode(WATER_SENSOR, INPUT);
  pinMode(POTENTIOMETER, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  

  bmp.begin();
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    

  
}  
  
  
void loop() {
  Serial.println("Looping");
    
  /*/************************************** ANALOG READING SECTION ****************************************/
  analogWater = analogRead(WATER_SENSOR);
  analogPotentio = analogRead(POTENTIOMETER);
  temperature = bmp.readTemperature(); 
  pressure = bmp.readPressure()/100;;
  altitude = bmp.readAltitude();
  
  //Debug
  Serial.print("water: ");
  Serial.println(analogWater);
  Serial.print("photores: ");
  Serial.println(analogPhotoresistor);
  Serial.print("potentio: ");
  Serial.println(analogPotentio);
  
  waterLevel = calculateWaterLevel(analogWater);
  motorPower = calculateMotorSpeed(analogPotentio);
  lighting = calculateLightIntensity(analogPhotoresistor);  

  //Debug
  //Serial.print("water: ");
  //Serial.println(waterLevel);
  Serial.print("lighting: ");
  Serial.println(lighting);
  //Serial.print("potentio: ");
  //Serial.println(motorPower);

  /*************************************MOTOR********************************************************/
  
  motorPower= 1024-analogPotentio;         

  digitalWrite(MOTOR_PIN, HIGH); 

  delayMicroseconds(motorPower);   

  digitalWrite(MOTOR_PIN, LOW);  

  delayMicroseconds(analogPotentio);  

  /************************************** LCD ********************************************************/
  String temperatureString = String(firstMessage+temperature);
  String pressureString = String(secondMessage+pressure);
  String altitudeString = String(thirdMessage+altitude);

  //first line
  lcd.setCursor(2, 0);
  lcd.print(temperature);
  lcd.write(byte(0));
  lcd.print("C");

  //second line
  lcd.setCursor(0, 1);
  lcd.print(pressure);
  lcd.print("hPa");

  lcd.setCursor(8, 1);
  lcd.print(altitude);
  lcd.print("M");
  
  /************************************** EMERGENCY SECTION ***********************************/
  if(waterLevel > 3 || temperature > 45)
  {
    ser.write(ALERT);
    emergency_alert();      
    lcd.clear();
    lcd.setCursor(0, 4);
    lcd.print("Alert!!!");
    lcd.setCursor(1,1);
    lcd.print("Check pipes or temp");
    delay(500);           
  }   
  
  /************************************** RFID SECTION ****************************************/
  // Look for new cards
  if(!cardReader.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if(!cardReader.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < cardReader.uid.size; i++) 
  {
     Serial.print(cardReader.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(cardReader.uid.uidByte[i], HEX);
     content.concat(String(cardReader.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(cardReader.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "7B 9A D1 22") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    Serial.println();
    lock.write(180);
    ser.write(GREEN); //green led
    tone(PIEZO_PIN, 10000, 500);
    Serial.println("Sending value");    
    delay(3000);
    lock.write(0);
  } 
  else  
  {
    Serial.println("Access denied");
    ser.write(RED); //red led
    tone(PIEZO_PIN, 5000, 500);
    delay(3000);
  }  
    
}

//Functions
void emergency_alert()
{
  tone(PIEZO_PIN, 5000, 1000);
	delay(500);
	noTone(PIEZO_PIN);
	delay(1000);	
}

int calculateWaterLevel(int analogValue)
{
  int waterLevel = map(analogValue, 0, 521, 0, 5);
  return waterLevel;
}

int calculateMotorSpeed(int analogValue)
{
  int motorSpeed = map(analogValue, 0, 1023, 0, 255);
  return motorSpeed;
}

int calculateLightIntensity(int analogValue)
{
  int lighting = map(analogValue, 0, 1023, 0, 255);
  return 255 - lighting;
}
