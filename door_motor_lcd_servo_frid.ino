#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

#include <Servo.h>

int servoPin = 8;
int DoorIRSensor = 7;
bool objectDetected;

Servo servo;
int angle = 0;  // servo position in degrees


// Define pins for RFID
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Define I2C LCD (0x27 is the default I2C address; it might vary)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// UID of the authorized card
byte authorizedUID[] = {0x63, 0xF3, 0xE0, 0x0F}; 

void setup() {

  servo.attach(servoPin);
  
  // Initialize serial communication
  Serial.begin(9600);
  // Initialize SPI bus and RFID reader
  SPI.begin();
  mfrc522.PCD_Init();
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Scan your card1");


  

   pinMode(DoorIRSensor, INPUT); // AI_IR Sensor pin INPUT

  
}

void loop() {
 
 
  // Check if a new RFID card is present
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Display the UID in serial monitor for debugging
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  

  // Check if the detected UID matches the authorized UID
  if (checkUID(mfrc522.uid.uidByte) || objectDetected == LOW ) {

      
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Open the door");

    for(angle = 0; angle < 180; angle++) {
        servo.write(angle);
        delay(15);
    }

    delay(10000);

     lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("close the door");

    // now scan back from 180 to 0 degrees
    for(angle = 180; angle > 0; angle--) {
        servo.write(angle);
        delay(15);
    }


    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scan your card2");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Access Denied");
    delay(2000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Scan your card3");

    objectDetected = digitalRead(DoorIRSensor); // Read the sensor value


    
  }
  
  // Halt PICC
  mfrc522.PICC_HaltA();
}

// Function to check if UID matches the authorized UID
bool checkUID(byte *uid) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != authorizedUID[i]) {
      return false;
    }
  }
  return true;
}
