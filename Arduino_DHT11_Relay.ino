// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

#include <DHT.h>

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Connect pin 1 (on the left) of the sensor to +5V
// NOTE: If using a board with 3.3V logic like an Arduino Due connect pin 1
// to 3.3V instead of 5V!
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND
// Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor

// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(DHTPIN, DHTTYPE);

int relay_pin = 10;   // 定義數位引腳 10 為 ledPin

void setup() {
  Serial.begin(115200);
  Serial.println("DHT11 measuring...");

  dht.begin();

  pinMode(relay_pin, OUTPUT);  // 定義引腳介面為輸出
  digitalWrite(relay_pin, HIGH);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2*1000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C / ");
//  Serial.print(f);
//  Serial.print(" °F");

  if( t >= 26 ) {
     digitalWrite(relay_pin, LOW);   // 馬達 轉
     Serial.println(" Ralay(L) Trigger --> Motor Run");
     }
  else {
     digitalWrite(relay_pin, HIGH);    // 馬達 停
     Serial.println(" Realy(H) Relex --> Motor Off");
  }
}
