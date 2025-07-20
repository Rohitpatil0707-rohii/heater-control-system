#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimerOne.h>  

// Pin definitions
#define DHTPIN        2
#define DHTTYPE       DHT22
#define HEATER_PIN    3
#define BUZZER_PIN    4

// Thresholds
#define TARGET_TEMP       28.0
#define OVERHEAT_TEMP     37.0

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

volatile float currentTemp = 0;   // temp variable
String lastState = "";           // To avoid repeated beeps

// Timer ISR to read temperature
void readTempISR() {
  float temp = dht.readTemperature();
  if (!isnan(temp)) {
    currentTemp = temp;
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
  lcd.backlight();

  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Heater System");
  delay(1000);
  lcd.clear();

  //   Timer1 to trigger ISR every 1 second
  Timer1.initialize(1000000);         // 1 sec = 1,000,000 µs
  Timer1.attachInterrupt(readTempISR);
}

void loop() {
  float temp = currentTemp;

  if (isnan(temp) || temp == 0.0) {  // Check if temp is invalid
    Serial.println("Sensor error");
    lcd.setCursor(0, 0);
    lcd.print("Sensor Error   ");
    delay(2000);
    return;
  }

  String state = " ";

  // ----- STATE LOGIC -----
  if (temp >= OVERHEAT_TEMP) { //if temp overheat 
    digitalWrite(HEATER_PIN, LOW);
    tone(BUZZER_PIN, 1000);  // Continuous warning tone
    state = "OVERHEAT";
  }
    else if (temp > TARGET_TEMP + 2 && temp <= OVERHEAT_TEMP) { //if temp is more then target(too Hot)
    digitalWrite(HEATER_PIN, LOW);
    noTone(BUZZER_PIN);
    tone(BUZZER_PIN, 1000);
      delay(300);
      noTone(BUZZER_PIN);
    state = "TOO_HOT";
  }
  else if (temp >= TARGET_TEMP && temp <= TARGET_TEMP + 2) {/// Target_reached
    digitalWrite(HEATER_PIN, LOW);
    if (lastState != "TARGET_REACHED") {
      tone(BUZZER_PIN, 1000);
      delay(500);
      noTone(BUZZER_PIN);
    }
    state = "TARGET_REACHED";
  }
  else if (temp >= TARGET_TEMP - 1 && temp < TARGET_TEMP) {//target not reached or STABILIZING
    digitalWrite(HEATER_PIN, HIGH);
    noTone(BUZZER_PIN);
    state = "STABILIZING";
  }
  else if (temp < TARGET_TEMP - 1) { //Heating
    digitalWrite(HEATER_PIN, HIGH);
    noTone(BUZZER_PIN);
    state = "HEATING";
  }
  else {                       // IDLE
    digitalWrite(HEATER_PIN, LOW); 
    noTone(BUZZER_PIN);
    state = "IDLE";
  }

  // ----- LCD DISPLAY -----
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);
  lcd.print(" C   ");

  lcd.setCursor(0, 1);
  lcd.print("State: ");
  lcd.print(state);
  lcd.print("     ");

  // ----- Serial Display -----
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print(" C | State: ");
  Serial.println(state);

  lastState = state;
  delay(1000);
}
