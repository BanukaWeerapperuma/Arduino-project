//com _05
#include <Wire.h>




// Define the analog pin connected to the MQ-2 sensor
const int gasSensorPin = A0; // Use GPIO 34 or another analog pin
// Define the pin connected to the buzzer
const int buzzerPin = 13;
// Define the window pin for the IR sensor
const int windowSensorPin = 12;     
bool windowDetected = false;

const int passWindowPin = 3 ;
const int passGasPin = 4;

void setup() {
  Serial.begin(9600); // Initialize serial communication
   
  pinMode(gasSensorPin , INPUT); // Set the gas sensor pin as an input
  pinMode(buzzerPin , OUTPUT);
  pinMode(passWindowPin , OUTPUT);
  pinMode(passGasPin , OUTPUT);
  
   pinMode(windowSensorPin, INPUT);
}

void loop() {
  
  windowDetected = digitalRead(windowSensorPin);
  int gasValue = analogRead(gasSensorPin); // Read the analog value from the sensor

  //window
  if (windowDetected) {
    Serial.println("window open");

       digitalWrite(buzzerPin, HIGH);
       digitalWrite(passWindowPin, HIGH);
      delay(3000); // Wait for 1 second (1000 milliseconds)
      digitalWrite(passWindowPin, LOW);
      
  // Turn the buzzer off
      digitalWrite(buzzerPin, LOW);
      delay(1000); // Wait for 1 second (1000 milliseconds)
      
  } else {
    Serial.println("window close");
  }


  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue); // Display the raw analog value

  if (gasValue>120){
       digitalWrite(buzzerPin, HIGH);
       digitalWrite(passGasPin, HIGH);
      delay(3000); // Wait for 1 second (1000 milliseconds)
      digitalWrite(passGasPin, LOW);

  // Turn the buzzer off
      digitalWrite(buzzerPin, LOW);
      delay(1000); // Wait for 1 second (1000 milliseconds) 
    }

  delay(1000); // Wait for a second before the next reading
}
