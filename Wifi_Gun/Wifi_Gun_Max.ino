#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <IRCClient.h>

#ifndef STASSID
#define STASSID "XStarWake-WiFi"
#define STAPSK "wittystar718"
#endif

//define your default values here, if there are different values in config.json, they are overwritten.
#define secret_ssid "BOTTY" 
#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667

#define TRIGGER D1

//OAuth Key 
// https://twitchapps.com/tmi/
#define TWITCH_BOT_NAME "BORIS___BOT"  // to change to the actual bot name
#define TWITCH_OAUTH_TOKEN "oauth:6c91x6yiuapswpttdl9ur8tuxu1yac" //to chage to the one your bot has
//------------------------------

String ircChannel = "";

const String twitchChannelName = "xstarwake"; //this is case sensitive!

const char* ssid = STASSID;
const char* password = STAPSK;
const String deviceName = "Max_Gun";

IPAddress ip(192,168,1,69);
IPAddress dns(4,2,2,2);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);

const long GUN_interval = 2000;  // pause for two seconds
const long COOLDOWN_interval = 2000;  // pause for two seconds

void setup() {
  pinMode(TRIGGER, OUTPUT);
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
  
  ircChannel = "#" + twitchChannelName;
  client.setCallback(callback);

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  ArduinoOTA.setHostname("max-gun");

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
}

void loop() {
  ArduinoOTA.handle();
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

    //prints chat to serial
    Serial.println(message);

  if (ircMessage.text.indexOf("REPORT") > -1 && ircMessage.nick == "TOXIC__SALT")
      { 
     sendTwitchMessage("SECRET TOX THING REPORTING FOR DUTY.");  
    }

  if (ircMessage.text.indexOf("REPORT") > -1 && ircMessage.nick == "XSTARWAKE")
      { 
     sendTwitchMessage("SECRET XSTAR MAX THING REPORTING FOR DUTY.");  
    }

  if (ircMessage.text.indexOf("SHOOT") > -1 && ircMessage.nick == "XSTARWAKE")
      { 
      sendTwitchMessage("Blast Max in the Face!");  

      digitalWrite(TRIGGER, HIGH); // turn on relay with voltage HIGH
      delay(GUN_interval);              // pause
      digitalWrite(TRIGGER, LOW);  // turn off relay with voltage LOW
      delay(COOLDOWN_interval);              // pause
    
    }
 
  if (ircMessage.text.indexOf("Max Bang") > -1 && ircMessage.nick == "INSTRUCTBOT")
      { 
      //sendTwitchMessage("Blast Max in the Face!");  

      digitalWrite(TRIGGER, HIGH); // turn on relay with voltage HIGH
      delay(GUN_interval);              // pause
      digitalWrite(TRIGGER, LOW);  // turn off relay with voltage LOW
      delay(COOLDOWN_interval);              // pause
    
    }

  if (ircMessage.text.indexOf("Max Bang") > -1 && ircMessage.nick == "BORIS___BOT")
      { 
      //sendTwitchMessage("Blast Max in the Face!");  

      digitalWrite(TRIGGER, HIGH); // turn on relay with voltage HIGH
      delay(GUN_interval);              // pause
      digitalWrite(TRIGGER, LOW);  // turn off relay with voltage LOW
      delay(COOLDOWN_interval);              // pause
    
    }

    return;

  }

}
