#include <Time.h>
#include <TimeLib.h>

#include <RCSwitch.h>
#include <dht.h>

#define DHT11_PIN 7

RCSwitch mySwitch = RCSwitch();

dht DHT;

void setup() {

  Serial.begin(9600);

  mySwitch.enableTransmit(10);  // Transmitter on pin 10

  mySwitch.setPulseLength(161); // Pulse length for ELEKCITY ZAP 1L IS 161us

  pinMode(13,OUTPUT);

  Serial.println("CLEARDATA");
  Serial.println("LABEL,Time,Timer (<24hrs), Temperature (C), Humidity (%RH)");
}

void loop() {
// Read and print humidity and temperature
  int chk = DHT.read11(DHT11_PIN);
  time_t t = now();
  
  Serial.print("DATA,TIME,");
  Serial.print(hour(t));
  Serial.print(":");
  Serial.print(minute(t));
  Serial.print(":");
  Serial.print(second(t));
  Serial.print(",");
  Serial.print(DHT.temperature);
  Serial.print(",");
  Serial.println(DHT.humidity);

if(second(t) == 50)
{
  Serial.println("CLEARDATA");
  time_t t = now();
}

  //time_t t = now();
  //Serial.print("Second = ");
  //Serial.println(second(t));
  //Serial.print("Minute = ");
  //Serial.println(minute(t));
 
  if ( DHT.temperature > 30 )
  {
    mySwitch.send("010101000101010100111100"); // Switch OFF code
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
  }
  delay(10000);
}
