#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <IRCClient.h>

#ifndef STASSID
#define STASSID "Toxic_Streamer"
#define STAPSK "WakeCrew4Life"
#endif

#define ZAPPER D1 // Trigger in NodeMCU at pin GPIO16 (D1).

//define your default values here, if there are different values in config.json, they are overwritten.
#define secret_ssid "BOTTY" 
#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667

const String twitchChannelName = "xstarwake"; //this is case sensitive!

const char* ssid = STASSID;
const char* password = STAPSK;

const String deviceName = "Zapper";

IPAddress ip(10,76,210,203);
IPAddress dns(4,2,2,2);
IPAddress gateway(10,76,210,1);
IPAddress subnet(255,255,255,0);


#define TWITCH_BOT_NAME "BORIS___BOT"  // to change to the actual bot name

//OAuth Key 
// https://twitchapps.com/tmi/
#define TWITCH_OAUTH_TOKEN "oauth:6c91x6yiuapswpttdl9ur8tuxu1yac" //to chage to the one your bot has
//------------------------------

String ircChannel = "";

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

const long ZAP_interval = 15000;  // pause for two seconds
const long COOLDOWN_interval = 2000;  // pause for two seconds



void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.hostname(deviceName); // DHCP Hostname
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("zapper");

  // No authentication by default
  ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  pinMode(ZAPPER, OUTPUT);

  ircChannel = "#" + twitchChannelName;
  client.setCallback(callback);

}

void loop() {

  ArduinoOTA.handle();

  // Try to connect to chat. If it loses connection try again
  if (!client.connected()) {
    Serial.println("Attempting to connect to " + ircChannel );
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN)) {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");
      sendTwitchMessage("Z Con");
    } else {
      Serial.println("failed... try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
    return;

    
  }
  client.loop();

}

void sendTwitchMessage(String message) {
  client.sendMessage(ircChannel, message);
}


void callback(IRCMessage ircMessage) {
  //Serial.println("In CallBack");
 
  if (ircMessage.command == "PRIVMSG" && ircMessage.text[0] != '\001') {
    //Serial.println("Passed private message.");
   
    ircMessage.nick.toUpperCase();
 
    String message("<" + ircMessage.nick + "> " + ircMessage.text);
 
    //prints chat to serial
    Serial.println(message);





if (ircMessage.text.indexOf("2") > -1 && ircMessage.nick == "TOXIC__SALT")
      { 
     sendTwitchMessage("Tox 2.");  

      digitalWrite(ZAPPER, HIGH); // turn on relay with voltage HIGH
      delay(ZAP_interval);              // pause
      digitalWrite(ZAPPER, LOW);  // turn off relay with voltage LOW
      delay(COOLDOWN_interval);              // pause

    
    }
 
    return;




  }

}



