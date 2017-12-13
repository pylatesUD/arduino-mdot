#include <Arduino.h>

#include <ubidotsMdot.h>
#include <math.h>

const int Rc = 10000; //valor de la resistencia
const int Vcc = 5;
const int SensorPIN = A0;
const int SensorPIN1 = A2;


float A = 1.11492089e-3;
float B = 2.372075385e-4;
float C = 6.954079529e-8;

float K = 2.5; //factor de disipacion en mW/C
//Definiciones de codigo AT
#define SSID "Conduit_LoRa_Network_Name"
#define PASS "Conduit_LoRa_Network_Password"
#define SUB_BAND "1" // Number of your sub band of LoRa 1-8
#define TEMPERATURA 0  // Depends of the number it'll be send a setted name

char const * SSID_NAME = "48170f5e533ca8f6"; // Put here your LoRa SSID
char const * SSID_PASS = "630c843393c1876e4c701eff0c7dd3f0"; // Put here your LoRa Network password

Ubidots client(SSID_NAME, SSID_PASS, 0);

void setup()
{
  Serial.begin(115200);
  //digitalWrite(13,HIGH);

  //  client.loraVerify(SSID, PASS, SUB_BAND);
}
void loop()
{
  float raw = analogRead(SensorPIN);
  float V =  raw / 1024 * Vcc;

  float R = (Rc * V ) / (Vcc - V);


  float logR  = log(R);
  float R_th = 1.0 / (A + B * logR + C * logR * logR * logR );

  float kelvin = R_th - V*V/(K * R)*1000;
  float celsius = kelvin - 273.15;

//  Serial.print("T = ");
  //Serial.print(celsius);
//  Serial.print("C\n");

//  float value = analogRead(A0);
  client.add(TEMPERATURA,1);
  client.add(celsius, 4);

  client.sendAll();

  delay(5000);
}
