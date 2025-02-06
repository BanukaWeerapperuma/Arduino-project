//com_12/18
//Connect the RTC module (like DS3231) to the ESP32 via I2C (SDA to GPIO 21, SCL to GPIO 22).
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <DHT.h>
#include <RTClib.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define WIFI_SSID "abc"                 // WiFi SSID
#define WIFI_PASSWORD "12340000"         // WiFi Password
#define DHTPIN 15                             // Pin connected to the DHT11 data pin
#define DHTTYPE DHT11                         // DHT11 sensor type
#define LED_PIN 4                           // Pin connected to the LED

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Create objects for Firebase configuration and authentication
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData firebaseData;

DHT dht(DHTPIN, DHTTYPE);
RTC_DS3231 rtc;


int FromHour = 18;  //time
int ToHour = 6;
const int RTCledPin = 5; // LED  RTC LED (4:00 PM to 5:00 PM)

const int DoorPassPin = 26;
bool door = false;

const int WindowPassPin = 2;
bool window = false;

const int GasPassPin = 23;
bool gas = false;


void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  pinMode(RTCledPin, OUTPUT);
 
  
  dht.begin();
    pinMode(WindowPassPin, INPUT);
    pinMode(DoorPassPin , INPUT);
     pinMode(GasPassPin , INPUT);



  // Initialize the RTC module
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
  

   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    while (true);
  }

  // Check if the RTC lost power and if so, set the time
  if (rtc.lostPower()) {
    // Set the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }


  

  // Connect to WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Set up Firebase configuration
  config.host = "fir-iot-------------rtdb.firebaseio.com";  // Your Firebase URL
  config.api_key = "AIzaSyBf------------9dfumUP9mLcY";                   // Replace with your Firebase API Key

  // Optional: Set Firebase Authentication
 auth.user.email = "Email";  // Optional: Replace with your Firebase email
  auth.user.password = "Email_password";        // Optional: Replace with your Firebase password

  // Initialize Firebase
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {
    door = digitalRead(DoorPassPin);
    window = digitalRead(WindowPassPin);
    gas = digitalRead(GasPassPin);

  //RTC Time SET/SHOW
  DateTime now = rtc.now(); // Get current time

  int hour = now.hour();
  int minute = now.minute();
  int second = now.second();
  
  // Read temperature and humidity from DHT11
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

    

   Serial.print("Gas Sensor Value: ");
  Serial.println(gas); 

  Serial.print("door Sensor Value: ");
  Serial.println(door);

Serial.print("window Sensor Value: ");
  Serial.println(window); 
  

  // Update Firebase with sensor data
  if (Firebase.ready()) {
    Firebase.setFloat(firebaseData, "/sensors/temperature", temperature);
    Firebase.setFloat(firebaseData, "/sensors/humidity", humidity);
    Firebase.setFloat(firebaseData, "/sensors/door", door);
    Firebase.setFloat(firebaseData, "/sensors/window", window); 
    Firebase.setFloat(firebaseData, "/sensors/lpg", gas);
    
    // Read LED state from Firebase
    if (Firebase.getBool(firebaseData, "/controls/led")) {
      bool ledState = firebaseData.boolData();
      digitalWrite(LED_PIN, ledState ? HIGH : LOW);
    }


      //clock from hour
     if (Firebase.getInt(firebaseData, "/time/FromHour")) {
      FromHour = firebaseData.intData();
      Serial.print("from hour  :");
      Serial.println(FromHour);
      
       Serial2.print(FromHour);
    } else {
    Serial.println("Failed to get startHour");
    Serial.println(firebaseData.errorReason());
   }


     //clock to hour
     if (Firebase.getInt(firebaseData, "/time/ToHour")) {
      ToHour = firebaseData.intData();
      Serial2.println(ToHour);
       Serial.print("to hour  :");
      Serial.println(ToHour);
    } else {
    Serial.println("Failed to get endHour");
    Serial.println(firebaseData.errorReason());
  }
        
  }


  // LED RTC: 4:00 PM to 5:00 PM (16:00 to 17:00)
  if (hour >= FromHour && hour < ToHour) {
    delay(2000);
    digitalWrite(RTCledPin, HIGH); // Turn RTC LED ON
  } else {
    digitalWrite(RTCledPin, LOW);  // Turn RTC LED OFF
  }


  // SHOW time and date in serial print

  // Print current time with hours, minutes, and seconds
  //Serial.print("Current time: ");
  //Serial.print(hour);
  //Serial.print(":");
  //Serial.print(minute);
  //Serial.print(":");
  //Serial.println(second);  // Print seconds as well

  //delay(1000); // Wait for 1 second before updating the time again
  
  
  //oled

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("homesecuritysystem");

  display.setCursor(0, 20);  // Move to the second row
  display.print(temperature);
  display.write(248);                 // ASCII code for the degree symbol
  display.print("C humi:");
  
  display.print(humidity);
  display.println("%");

  
  display.setCursor(0, 30);  // Move to the second row
  display.print("gas leak : ");
  display.println(gas);

  display.setCursor(0, 40);  // Move to the second row
  display.print("LED ON: ");
  display.print(FromHour );
  display.print(" - ");
  display.println(ToHour );

  display.setCursor(0, 50);  // Move to the second row
  display.print("door :");
  display.print(door);
  display.print("  win :");
  display.println(window);
  


   

  display.display();


  

 // delay(500); // Delay between readings
}
