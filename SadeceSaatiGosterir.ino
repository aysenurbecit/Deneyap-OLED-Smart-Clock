// animasyon icermeyen versiyon. sadece anlik zamani ekrana yazar.
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <deneyap.h>
#include <Deneyap_OLED.h> 

#define UTC_OFFSET_IN_SECONDS 3600   

const char* ssid = "WiFi Adi"; //bagli oldugunuz WiFi adi
const char* password = "WiFi Sifresi";   //bagli oldugunuz WiFi sifresi

OLED o; // OLED EKRAN icin class tanimlamasi
// Zamani almak icin NTP Client'i tanimlayin
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

void setup(){
  o.begin(0x7A);
  o.clearDisplay(); 
  Serial.begin(115200); // veya bunu kullanabilirsiniz: 19200
 
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.println ( "." );
  }
 // timeClient.setTimeOffset(-10800);
  timeClient.begin();
  timeClient.update();
}

void loop() {

  Serial.println("Current Time: ");
 // Serial.print(", ");
  Serial.println(timeClient.getHours());
  Serial.println(":");
  Serial.println(timeClient.getMinutes());
  Serial.println(":");
  Serial.println(timeClient.getSeconds());
 // Serial.println(timeClient.getFormattedTime());
  o.setTextXY(0, 2);
  o.putString("Current Time ");

  int hours = (timeClient.getHours() + 2) % 24; // GMT+3 icin +1,+2 veya +3 ekliyoruz cunku NTP ile alinan saatin, bulundugumuz Turkiye
  int minutes = timeClient.getMinutes();        // saatiyle arasındaki farki bilmiyoruz. Bunu tek seferde satir 28'deki kismi acararak da
  int seconds = timeClient.getSeconds();        // yapabilirsiniz. Ardindan mod 24 yaparak 24 saatlik formata sigdiriyoruz.
 
  o.setTextXY(3, 4);
  o.putString(String(hours) + ":" + String(minutes) + ":" + String(seconds));
  delay(3000);
  o.clearDisplay();
}
/*
OLED EKRAN CIKTISI ASAGIDAKI FORMATTA OLACAKTIR
 _______________
| Current Time  |
|               |
|               |
|   hh:mm:ss    |
|               |
|               |
|_______________|

*/