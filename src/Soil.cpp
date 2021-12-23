#include <Soil.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

DHT dht(DHTPIN, DHTTYPE);

float measureSoil(int Sensor){
    int total = 0;
    for(int i = 0; i<samples; i++){
    int reading = analogRead(Sensor);
    total = total + reading;
    }
    float mean = total/samples;
    float  value = map(mean, ADC_MIN, ADC_MAX, 100,0);
    return value;
}

void measureAir(float & hum, float & temp){

float h = dht.readHumidity();
float t = dht.readTemperature();

if (isnan(h) || isnan(t)) {
Serial.println(F("Failed to read from DHT sensor!"));
return;

}
hum = h;
temp = t;

    }

void setup_dht(void){
    dht.begin();
}