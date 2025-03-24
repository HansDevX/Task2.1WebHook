#include <WiFiNINA.h>
#include <DHT.h>
#include <ThingSpeak.h>

//WiFi ssid and password
char ssid[] = "KavinduiPhone";   
char pass[] = "Kavindu1234";   

//DHT Sensor Setup
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//ThingSpeak channel number and API key
unsigned long myChannelNumber = 2885003;  
const char * myWriteAPIKey = "HPQ2YKPWE8O88H3S";

WiFiClient client;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("!");
  }
  Serial.println("Connected to WiFi!!");
  
  ThingSpeak.begin(client);
  dht.begin();
}

void loop() {

  //Temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("The DHT sensor could not be read!!");
    return;
  }

  // Print the values to the serial monitor
  Serial.print("Temperature:- ");
  Serial.print(temperature);
  Serial.print("C - Humidity:- ");
  Serial.print(humidity);
  Serial.println("%");

  // Send data to ThingSpeak
  ThingSpeak.setField(1, temperature); 
  ThingSpeak.setField(2, humidity);   
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  
  // Wait 60 seconds
  delay(60000);  
}
