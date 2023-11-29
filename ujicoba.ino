#define BLYNK_PRINT Serial
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 25200;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "id.pool.ntp.org", utcOffsetInSeconds);

long previousMillis = 0;
long currentMillis = 0;
long interval = 1000;
int data=0;
int vtombol;
int status = 0;
int x = 0;



char auth[] = "qay8C6EjMCJEmSVG83PmBCxlf4cJc8qH";

char ssid[] = "OPPO A57";
char pass[] = "98765321";

void setup()
{

  SPI.begin();
  Serial.begin(9600);
  //Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8080);
  pinMode(D3,OUTPUT);
  digitalWrite(D3, HIGH);
  pinMode(D5, INPUT);
   digitalWrite(D3, HIGH);
   timeClient.begin();
   Serial.println("LABEL, Hari, Waktu awal, Waktu Respons");

  
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
}

BLYNK_WRITE(V1) //mendapatkan data dari V1 (tombol virtual blynk)
{
  vtombol=param.asInt(); //mendapatkan status dari tombol virtual
  
}


void loop()
{
  Blynk.run();
  lampu();
}

void lampu()
{
   int tombol = digitalRead(D5);
   timeClient.update();
   String currentSecond = timeClient.getFormattedTime();
    if(tombol == 1 || vtombol==1)
    {   
       Serial.print("DATA, DATE, TIME, ");
       Serial.println(currentSecond);
        status = !status;
        digitalWrite(D3,status);
        delay(500);
        
    }

 
}