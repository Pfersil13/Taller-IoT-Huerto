#ifndef MQTT_H
    #define MQTT_H

    #include <Arduino.h>
    
    #define MQTT_VERSION MQTT_VERSION_3_1_1
    
    #define MQTT_SERVER_IP  "192.168.1.117" 
    #define MQTT_USER  "mqttUSERNAME"
    #define MQTT_PASSWORD  "mqttPASSWORD"


    // MQTT: topics                        
    #define MQTT_HUM_SOIL_TOPIC  "node0/hum/soil"
    #define MQTT_HUM_AIR_TOPIC  "node0/hum/air"
    #define MQTT_TEMP_AIR_TOPIC  "node0/temp/air"
    
    

    void reconnect();
    //boolean reconnect();
    //void test_conn();
    void callback(char* p_topic, byte* p_payload, unsigned int p_length);
    void setup_mqtt();
    void floatMsg_out(String TopicToSend, float data);
    void charMsg_out(String TopicToSend, char* data);   
    String merge(String Input, char* line);

    
#endif


