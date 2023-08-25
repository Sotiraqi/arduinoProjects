const int gLED = 9;
const int rLED = 10;
const int bLED = 11;

const int rSensor = A0;
const int gSensor = A1;
const int bSensor = A2;

int rVal = 0;
int gVal = 0;
int bVal = 0;

int rSensVal = 0;
int gSensVal = 0;
int bSensVal = 0;

void setup() {
  Serial.begin(9600);
  pinMode(gLED, OUTPUT);
  pinMode(rLED, OUTPUT);
  pinMode(bLED, OUTPUT);

}

void loop() {
  rSensVal = analogRead(rSensor);
  delay(5);
  gSensVal = analogRead(gSensor);
  delay(5);
  bSensVal = analogRead(bSensor);
  delay(5);

  Serial.println("Raw Sensor Value");
  Serial.print("RED: ");
  Serial.println(rSensVal);
  Serial.print("GREEN: ");
  Serial.println(gSensVal);
  Serial.print("BLUE: ");
  Serial.println(bSensVal);

  rVal = rSensVal/4;
  gVal = gSensVal/4;
  bVal = bSensVal/4;

  Serial.println("Mapped sensor values");
  Serial.print("RED: ");
  Serial.println(rVal);
  Serial.print("GREEN: ");
  Serial.println(gVal);
  Serial.print("BLUE: ");
  Serial.println(bVal);

  analogWrite(rLED, rVal);
  analogWrite(gLED, gVal);
  analogWrite(bLED, bVal);
  

}
