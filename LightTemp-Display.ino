#include <LiquidCrystal_I2C.h>
#include <BH1750.h>
#include <Wire.h>

// voor de temperatuur sensor
const int temperatuurPin = 34;
float sensorValue;
float voltageOut;
float temperatuurC;


BH1750 lightMeter;
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  //serial begin
  Serial.begin(9600);

  // Temperatuursensor opstarten

  pinMode(temperatuurPin, INPUT);

  // lcd opstarten
  lcd.init();
  lcd.backlight();

  // lichtsensor opstarten
  Wire.begin(D2, D1);
  lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE, 0x23);  // 0x23 of 0x5C
  Serial.println(F("BH1750 Test begin"));
}

void loop() {
  // Lees de lichtsensor uit

  float lux = lightMeter.readLightLevel();

  // bereken de temperatuur voor de LM335
  sensorValue = analogRead(temperatuurPin);
  voltageOut = (sensorValue * 5000) / 4095;
  temperatuurC = (voltageOut / 10) - 273;

  //  Print op LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Licht: " + String(lux));
  lcd.setCursor(0, 1);
  lcd.print("Temp: " + String(temperatuurC));

  //serial print
  Serial.println("Light: " + String(lux));
  Serial.println("Temperatuur: " + String(temperatuurC) + " | " + "Voltage uit (mV): " + String(voltageOut));


  delay(1000);
}
