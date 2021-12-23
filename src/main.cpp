#include <Arduino.h>

#include <MQTT.h>
#include <WifiESP.h>
#include <Soil.h>



#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */

RTC_DATA_ATTR int bootCount = 0;

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    case ESP_SLEEP_WAKEUP_TOUCHPAD : Serial.println("Wakeup caused by touchpad"); break;
    case ESP_SLEEP_WAKEUP_ULP : Serial.println("Wakeup caused by ULP program"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

unsigned long now = millis();
unsigned long lastMeasure = millis();
long interval = 2000;

void setup() {
Serial.begin(115200);
delay(1000);
print_wakeup_reason();

  /*
  First we configure the wake up source
  We set our ESP32 to wake up every 5 seconds
  */
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");

setup_wifi();
setup_mqtt();
setup_dht();
reconnect();
float aja = measureSoil(35);
Serial.print(aja); 
Serial.print("\t"); 
float hum,temp;
measureAir(hum, temp);
Serial.print(hum); 
Serial.print("\t");
Serial.println(temp); 

floatMsg_out(MQTT_HUM_SOIL_TOPIC, aja);
floatMsg_out(MQTT_HUM_AIR_TOPIC, hum);
floatMsg_out(MQTT_TEMP_AIR_TOPIC, temp);

  Serial.println("Going to sleep now");
  delay(1000);
  Serial.flush(); 
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
}

void loop() {
/*test_conn();
for (int deg = 0; deg < 360; deg = deg + 1){
    dacWrite(25, int(128 + 127 * (sin(deg*PI/180))));
  }
now = millis();
if(now - lastMeasure > interval){  
float aja = measureSoil(35);
Serial.print(aja); 
Serial.print("\t"); 
float hum,temp;
measureAir(hum, temp);
Serial.print(hum); 
Serial.print("\t");
Serial.println(temp); 
lastMeasure = now;

floatMsg_out(MQTT_HUM_SOIL_TOPIC, aja);
floatMsg_out(MQTT_HUM_AIR_TOPIC, hum);
floatMsg_out(MQTT_TEMP_AIR_TOPIC, temp);
}
*/
}




