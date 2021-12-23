#include <MQTT.h>
#include <PubSubClient.h>
#include <WifiESP.h>
#include <WiFi.h>


WiFiClient espClient;
PubSubClient client(espClient);

long lastReconnectAttempt = 0;

      
void setup_mqtt() {
     
client.setServer(MQTT_SERVER_IP, 1883);
client.setCallback(callback);
  
}
/*      
boolean reconnect() {
  Serial.println("Hi");
  if (!client.connected()) {
    Serial.println("INFO: Attempting MQTT connection...");
    // Attempt to connect
    String clientId;
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) { //MQTT_USER, MQTT_PASSWORD
      Serial.println("INFO: connected");
      // Once connected, publish an announcement...
      // ... and resubscribe


      //client.subscribe(MQTT_BIN1_RT);
    } else {
      Serial.print("ERROR: failed, rc=");
      Serial.print(client.state());
    }
  }
  return client.connected();
 }*/
 void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp32/output");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/*void test_conn(){
  if (!client.connected()) {
     long nownow = millis();
     if (nownow - lastReconnectAttempt > 5000) {
       lastReconnectAttempt = nownow;
       // Attempt to reconnect
       if (reconnect()) {
        lastReconnectAttempt = 0;
       }}}else{
     client.loop();
       }
}*/



void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off". 
  // Changes the output state according to the message
  if (String(topic) == "esp32/output") {
    Serial.print("Changing output to ");
    if(messageTemp == "on"){
      Serial.println("on");

    }
    else if(messageTemp == "off"){
      Serial.println("off");
    }
  }
}




void floatMsg_out(String TopicToSend, float data){
char value[10];
char merged[100];
dtostrf(data, 8, 4, value); //Float to Char
String mergedTopic = TopicToSend;
mergedTopic.toCharArray(merged,mergedTopic.length()+1);
client.publish(merged, value);
Serial.println(value);

}

void charMsg_out(String TopicToSend, char* data){
  char merged[100];
  String mergedTopic = TopicToSend;
  mergedTopic.toCharArray(merged,mergedTopic.length()+1);
  client.publish(merged, data);
}

String merge(String Input, char* line){
  String mergedTopic = String(line) +  "/" + Input;
  Serial.println(mergedTopic);
  return mergedTopic;
}