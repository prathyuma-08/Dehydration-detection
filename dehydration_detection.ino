#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include <LiquidCrystal.h>
const int PulseWire = 0;
int Threshold = 550;
PulseSensorPlayground pulseSensor;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  pinMode(A2,INPUT);
  pinMode(A1,INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pulseSensor.analogInput(PulseWire);
  pulseSensor.setThreshold(Threshold);
  if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");
  }
}
void loop() {
  int sensorValue = analogRead(A2);
  int tempValue = analogRead(A1);
  int myBPM = pulseSensor.getBeatsPerMinute();
  int ph = sensorValue * (14.0 / 1023.0); // To convert analogReadings to pH 
  int temp = tempValue * 0.4882812;
  Serial.print(temp);
  Serial.print(",");
  Serial.print(37);
  Serial.print(",");
  Serial.print(ph);
  Serial.print(",");
  Serial.print(5.9);
  Serial.print(",");
  Serial.print(myBPM);
  Serial.print(",");
  Serial.println(100);
  if (temp > 37 and myBPM > 100 and ph >= 5.9) {
        lcd.clear();
        lcd.print("DEHYDRATED!!");
        lcd.setCursor(0, 1);
        lcd.print("Go drink water!");
        //Serial.println("Go drink water");
  }
  else {
    lcd.clear();
    lcd.print("YOU'RE HYDRATED");
    lcd.setCursor(0, 1);
    lcd.print("Keep going!!");
  }
  delay(1000);
}
