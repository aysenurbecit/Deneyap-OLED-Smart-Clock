#include <Deneyap_OLED.h>
#include <NTPClient.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <deneyap.h>

#define UTC_OFFSET_IN_SECONDS 3600   

const char* ssid = "WiFi Adi"; //bagli oldugunuz WiFi adi
const char* password = "WiFi Sifresi*";

OLED oled;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", UTC_OFFSET_IN_SECONDS);

void GulenYuz(); 
void yuz();

void setup() {
  Serial.begin(115200); 
  oled.begin(0x7A);
  oled.clearDisplay();

  if (!oled.begin(0x7A)) {                        // begin(slaveAdress) fonksiyonu ile cihazların haberleşmesi başlatılması
    delay(3000);
    Serial.println("I2C bağlantısı başarısız ");  // I2C bağlantısı başarısız olursa seri terminale yazdırılması
  }
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
  oled.clearDisplay(); //ilk ekran
  delay(500);
  GulenYuz();
  Serial.println("Current Time: ");
  Serial.println(timeClient.getHours());
  Serial.println(":");
  Serial.println(timeClient.getMinutes());
  Serial.println(":");
  Serial.println(timeClient.getSeconds());
 // Serial.println(timeClient.getFormattedTime());
 
  oled.clearDisplay();
  oled.setHorizontalScrollProperties(Scroll_Right, 0, 7, Scroll_4Frames);
  oled.activateScroll();//ekran 2
  oled.setTextXY(3, 2);
  oled.putString("Current Time ");
  oled.setTextXY(4, 2);
  oled.putString("Deneyap Kart ");
  oled.setTextXY(5, 2);
  oled.putString("Akıllı Saat");
  delay(1500);
  oled.clearDisplay(); 
  oled.deactivateScroll();

  int hours = (timeClient.getHours() + 2) % 24; // GMT+3 icin +1,+2 veya +3 ekliyoruz cunku NTP ile alinan saatin, bulundugumuz Turkiye
  int minutes = timeClient.getMinutes();        // saatiyle arasındaki farki bilmiyoruz. Bunu tek seferde satir 28'deki kismi acararak da
  int seconds = timeClient.getSeconds();        // yapabilirsiniz. Ardindan mod 24 yaparak 24 saatlik formata sigdiriyoruz.
  
  oled.setTextXY(2, 1);  oled.putString("  ----------    ");
  oled.setTextXY(3, 4);
  oled.putString(String(hours) + ":" + String(minutes) + ":" + String(seconds)); //saat ekrani
  oled.setTextXY(4, 1); oled.putString("  ----------    ");
  yuz();
  delay(3000);

}
void GulenYuz() {

    oled.setTextXY(2, 0);
    oled.putString("    O      O    ");
    oled.setTextXY(4, 0);
    oled.putString("       -        ");
    oled.setTextXY(6, 0);
    oled.putString("  -__________-  ");
    delay(450);
    oled.setTextXY(2, 0);
    oled.putString("    O     _    ");
    oled.setTextXY(4, 0);
    oled.putString("       -        ");
    oled.setTextXY(6, 0);
    oled.putString("  -__________-  ");
    delay(350);
    oled.setTextXY(2, 0);
    oled.putString("    O      O    ");
    oled.setTextXY(4, 0);
    oled.putString("       -        ");
    oled.setTextXY(6, 0);
    oled.putString("  -__________-  ");
    delay(450);
}
void yuz() {

    oled.setTextXY(6, 2);
    oled.putString("    O O         ");
    oled.setTextXY(7, 2);
    oled.putString("   -___-        "); 
delay(400);
    oled.setTextXY(6, 2);
    oled.putString("    > <         ");
    oled.setTextXY(7, 2);
    oled.putString("   -___-        "); 
delay(400);
    oled.setTextXY(6, 2);
    oled.putString("    O O         ");
    oled.setTextXY(7, 2);
    oled.putString("   -___-        "); 

}

/*
OLED EKRAN CIKTISI ASAGIDAKI FORMATTA OLACAKTIR
 ________________
|                |
|                | 
|     O    _     | //animasyon ekrani
|                |
|        -       |
|  -__________-  |
|________________|
 ________________
|                |
|  Current Time  |
|  Deneyap Kart  | //kaydirma ekrani
|  Akıllı Saat   |
|                |
|                |
|________________|
 ________________
|                |
|   ----------   |
|    hh:mm:ss    | //aniamsyon ve saat bilgisi ekrani
|   ----------   |
|       O <      |
|      -___-     |
|________________|

*/