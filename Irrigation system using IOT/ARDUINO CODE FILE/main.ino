#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <ArduinoJson.h>

char auth[] = "x08Aj6TQyEOCWhCWb9xy-FfI2ZNAOzFo";
char ssid[] = "POCO M3";
char pass[] = "12312312";

const int soilMoisturePin = A0;
const int pumpControlPin = D1;

BlynkTimer timer;

void sendSensorData()
{
  int soilMoisture = analogRead(soilMoisturePin);
  Blynk.virtualWrite(V0, soilMoisture);
}

BLYNK_WRITE(V1) // Triggered when Button widget is pressed
{
  int pumpStatus = param.asInt();
  
  if (pumpStatus == 1) // If the button is pressed
  {
    digitalWrite(pumpControlPin, HIGH); // Turn on the water pump
  }
  else
  {
    digitalWrite(pumpControlPin, LOW); // Turn off the water pump
  }
}

void setup()
{
  pinMode(pumpControlPin, OUTPUT);
  digitalWrite(pumpControlPin, LOW);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendSensorData);
}

void loop()
{
  Blynk.run();
  timer.run();
}