#ifndef SOIL_H
    #define SOIL_H

    #include <Arduino.h>
    

    #define samples 15
    #define ADC_MIN 1000
    #define ADC_MAX 3000

    #define DHTPIN 13
    #define DHTTYPE DHT11

    float measureSoil(int Sensor);
    void measureAir(float & hum, float & temp);

    void setup_dht(void);

    
#endif


