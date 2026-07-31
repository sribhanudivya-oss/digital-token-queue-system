#include <LiquidCrystal.h>
#include <EEPROM.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Pins
const int tokenButton = 7;
const int resetButton = 6;
const int nowServingButton = A1;
const int buzzerPin = 8;

const int limitLedPin = 13;     // 🔴 Token limit LED
const int greenLedPin = 10;     // 🟢 Token issued LED
const int redLedPin = 9;        // 🔴 Now serving LED

int tokenNumber;
int lastTokenState = HIGH;
int lastResetState = HIGH;
int lastServeState = HIGH;

const int tokenLimit = 10;

// LCD Auto-off
unsigned long lastActionTime = 0;
bool lcdOff = false;

void showHomeScreen() {
  lcd.display();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Push a button");
  lcd.setCursor(0, 1);
  lcd.print("for token...");
  lcdOff = false;
}

void setup() {
  pinMode(tokenButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(nowServingButton, INPUT_PULLUP);

  pinMode(buzzerPin, OUTPUT);
  pinMode(limitLedPin, OUTPUT);
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);

  lcd.begin(16, 2);

  tokenNumber = EEPROM.read(0);
  if (tokenNumber < 1 || tokenNumber > 250) tokenNumber = 0;

  digitalWrite(limitLedPin, (tokenNumber >= tokenLimit) ? HIGH : LOW);

  lastTokenState = digitalRead(tokenButton);
  lastResetState = digitalRead(resetButton);
  lastServeState = digitalRead(nowServingButton);

  showHomeScreen();
  lastActionTime = millis();
}

void loop() {
  int tokenState = digitalRead(tokenButton);
  int resetState = digitalRead(resetButton);
  int serveState = digitalRead(nowServingButton);
  unsigned long currentMillis = millis();

  // 🔋 LCD auto-off after 30 sec
  if ((currentMillis - lastActionTime > 10000) && !lcdOff) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Screen Off");
    lcd.setCursor(0, 1);
    lcd.print("Saving Power...");
    delay(2000);
    lcd.noDisplay();
    lcdOff = true;
  }

  // 🔘 Token button pressed
  if (lastTokenState == HIGH && tokenState == LOW) {
    lastActionTime = currentMillis;
    lcd.display();
    showHomeScreen();

    if (tokenNumber < tokenLimit) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Processing...");
      lcd.setCursor(0, 1);
      lcd.print("Please wait...");
      delay(500);  // 3 sec delay

      int displayToken = tokenNumber + 1;

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Token#");
      lcd.print(displayToken);
      lcd.print(" 26-06-25");

      lcd.setCursor(0, 1);
      lcd.print("Time:10:30AM");

      digitalWrite(greenLedPin, HIGH);
      tone(buzzerPin, 1000, 150);
      delay(250);
      digitalWrite(greenLedPin, LOW);

      delay(500);
      showHomeScreen(); 

      tokenNumber = displayToken;
      EEPROM.write(0, tokenNumber);

      if (tokenNumber >= tokenLimit) {
        digitalWrite(limitLedPin, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Token Limit!");
        lcd.setCursor(0, 1);
        lcd.print("No more tokens");
        tone(buzzerPin, 2000, 300);
        delay(500);
        
      }
    }
  }

  // 🔁 Reset button
  if (lastResetState == HIGH && resetState == LOW) {
    lastActionTime = currentMillis;
    lcd.display();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Resetting...");
    delay(500);

    tokenNumber = 0;
    EEPROM.write(0, tokenNumber);
    digitalWrite(limitLedPin, LOW);
    tone(buzzerPin, 500, 400);
    delay(500);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Token Reset!");
    lcd.setCursor(0, 1);
    lcd.print("Token: 0");
    delay(500);

    showHomeScreen();
  }

  // 🔔 Now Serving button
  if (lastServeState == HIGH && serveState == LOW) {
    lastActionTime = currentMillis;
    lcd.display();

    digitalWrite(redLedPin, HIGH);
    tone(buzzerPin, 1500, 100);
    delay(1000);
    digitalWrite(redLedPin, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Now Serving...");
    lcd.setCursor(0, 1);
    lcd.print("Please enter");
    delay(2000);

    showHomeScreen();
  }

  // Save button states
  lastTokenState = tokenState;
  lastResetState = resetState;
  lastServeState = serveState;
}
