

/*******************************************************************

Toxic Test Stuff

*******************************************************************/
 
#include <ESP8266WiFi.h>
#include <IRCClient.h>
#include <Servo.h>
#include <Stepper.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const int stepsPerRevolution = 256;  // change this to fit the number of steps per revolution
Stepper myStepper(stepsPerRevolution, 5, 4, 14, 12);
Servo servo; 

int counter =0;

//define your default values here, if there are different values in config.json, they are overwritten.
#define secret_ssid "BOTTY" 
#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667
 
//------- info compte! ------
//char ssid[] = "Collins_Net";       // your network SSID (name)
//char password[] = "PrestonNet";  // your network key

char ssid[] = "Toxic_Streamer";       // your network SSID (name)
char password[] = "WakeCrew4Life";  // your network key

const String twitchChannelName = "xstarwake"; //this is case sensitive!

const String deviceName = "SprayMachine";

// const char* deviceName = "ToxTestArduino";


IPAddress ip(10,76,210,201);
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
 
// put your setup code here, to run once:
void setup() {


    servo.attach(2); //D4
    servo.write(90);

  
 
  myStepper.setSpeed(60);

  delay(2000);
  Serial.begin(115200);
  Serial.println();
 
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
 
  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.hostname(deviceName); // DHCP Hostname
  
  
  WiFi.config(ip, dns, gateway, subnet);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);
 
  ircChannel = "#" + twitchChannelName;
 
  client.setCallback(callback);

  //ArduinoOTA.setPort(8266);

  ArduinoOTA.setHostname("SprayMachine");

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
      sendTwitchMessage("Tox Con...");
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



    if (ircMessage.text.indexOf("SPRAY") > -1 && ircMessage.nick == "TOXIC__SALT")
      {
     
      Serial.println("Toxic Servo Testing");
      myStepper.step(stepsPerRevolution);
      servo.write(0);
      delay(1050);
      servo.write(90);
        sendTwitchMessage("OHHHH Poor Tox");
   
    }

    if (ircMessage.text.indexOf("REPORT") > -1 && ircMessage.nick == "TOXIC__SALT")
      {
     
    Serial.println("Toxic Servo Testing");
        sendTwitchMessage("Toxic Sprayer Reporting for Duty!");
   
    }

    if (ircMessage.text.indexOf("Tox Guess What...") > -1 && ircMessage.nick == "BORIS___BOT")
      {
     
      Serial.println("Toxic Servo Testing");
      myStepper.step(stepsPerRevolution);
      servo.write(0);
      delay(1050);
      servo.write(90);
        //sendTwitchMessage("Tox 1");
   
    }

    if (ircMessage.text.indexOf("Tox They Claimed The Big Load...") > -1 && ircMessage.nick == "BORIS___BOT")
      {
     
      Serial.println("Toxic Servo Testing");
  
      for(counter = 0;counter <= 9;counter++) {
        myStepper.step(stepsPerRevolution);
        servo.write(0);
        delay(850);
        servo.write(90);
        //sendTwitchMessage("Tox 1");
   
      }
    }
  
    if (ircMessage.text.indexOf("Tox Guess What...") > -1 && ircMessage.nick == "INSTRUCTBOT")
      {
     
  Serial.println("Toxic Servo Testing");
  myStepper.step(stepsPerRevolution);
      servo.write(0);
      delay(1050);
      servo.write(90);
      //  sendTwitchMessage("Tox 1");
   
    }

    if (ircMessage.text.indexOf("Tox They Claimed The Big Load...") > -1 && ircMessage.nick == "INSTRUCTBOT")
      {
     
     
  Serial.println("Toxic Servo Testing");
  
  for(counter = 0;counter <= 9;counter++) {
    myStepper.step(stepsPerRevolution);
      servo.write(0);
      delay(850);
      servo.write(90);
        //sendTwitchMessage("Tox 1");
   
      }
    }

  return;

  }

}

