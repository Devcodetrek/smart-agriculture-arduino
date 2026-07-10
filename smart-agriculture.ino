#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Stepper.h>

// === DHT11 Tanımları ===
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// === HC-SR04 Tanımları ===
#define TRIGPIN 6
#define ECHOPIN 7

// === Step Motor Tanımları ===
const int adimSayisi = 2048;
Stepper motor(adimSayisi, 8, 10, 9, 11); // IN1=8, IN3=10, IN2=9, IN4=11

// === LCD Tanımı ===
LiquidCrystal_I2C lcd(0x27, 16, 2);

// === Joystick Tanımları ===
#define JOY_Y A1
#define JOY_SW 3
const int yukariEsik = 800;
const int asagiEsik = 200;

// === Nem Eşiği ===
const float nemEsik = 40.0;
bool motorCalisti = false;

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();
  motor.setSpeed(10);

  pinMode(TRIGPIN, OUTPUT);
  pinMode(ECHOPIN, INPUT);

  pinMode(JOY_SW, INPUT_PULLUP); // Joystick butonu
}

void loop() {
  // --- DHT11 Verileri ---
  float sicaklik = dht.readTemperature();
  float nem = dht.readHumidity();

  // --- Mesafe Ölçümü ---
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
  long sure = pulseIn(ECHOPIN, HIGH);
  float mesafe = sure * 0.034 / 2;

  // --- LCD Güncelle ---
  lcd.setCursor(0, 0);
  lcd.print("S:");
  lcd.print(sicaklik);
  lcd.print("C N:");
  lcd.print(nem);
  lcd.print("%   ");

  lcd.setCursor(0, 1);
  lcd.print("Mesafe:");
  lcd.print(mesafe);
  lcd.print("cm ");

  // --- Nem ile Otomatik Kontrol ---
  if (nem < nemEsik && !motorCalisti) {
    Serial.println(">> NEM DUSUK – KAPAK ACILIYOR...");
    motor.step(adimSayisi); // 1 tur ileri
    motorCalisti = true;
  }
  if (nem >= nemEsik) {
    motorCalisti = false;
  }

  // --- Joystick Manuel Kontrol ---
  int joyY = analogRead(JOY_Y);
  if (joyY > yukariEsik) {
    Serial.println(">> JOYSTICK YUKARI – MOTOR ILERI");
    motor.step(512); // 1/4 tur ileri
  } else if (joyY < asagiEsik) {
    Serial.println(">> JOYSTICK ASAGI – MOTOR GERI");
    motor.step(-512); // 1/4 tur geri
  }

  if (digitalRead(JOY_SW) == LOW) {
    Serial.println(">> JOYSTICK BASILI – SISTEM BEKLIYOR");
    delay(1000); // güvenlik beklemesi
  }

  delay(1000);
}
