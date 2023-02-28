/*******************************************************************

Toxic Test Stuff

*******************************************************************/
 
#include <ESP8266WiFi.h>
#include <IRCClient.h>

#define ZAPPER D1 // Trigger in NodeMCU at pin GPIO16 (D1).



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

const String deviceName = "Stream_Gun";

// const char* deviceName = "ToxTestArduino";


IPAddress ip(10,76,210,86);
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
 


const long SHORT_interval = 5000;  // pause for two seconds
const long LONG_interval = 30000;  // pause for two seconds
const long COOLDOWN_interval = 2000;  // pause for two seconds




// put your setup code here, to run once:
void setup() {

  pinMode(ZAPPER, OUTPUT);

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
  //WiFi.config()
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
}
 
void loop() {
 

  // Try to connect to chat. If it loses connection try again
  if (!client.connected()) {
    Serial.println("Attempting to connect to " + ircChannel );
    // Attempt to connect
    // Second param is not needed by Twtich
    if (client.connect(TWITCH_BOT_NAME, "", TWITCH_OAUTH_TOKEN)) {
      client.sendRaw("JOIN " + ircChannel);
      Serial.println("connected and ready to rock");
      sendTwitchMessage("Thingy Connected to TWITCH");
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





if (ircMessage.text.indexOf("ZAP-Short") > -1 && ircMessage.nick == "XSTARWAKE")
      { 
      Serial.println("Toxic Circuit Testing");
     sendTwitchMessage("Short Test.");  

      digitalWrite(ZAPPER, HIGH); // turn on relay with voltage HIGH
      delay(SHORT_interval);              // pause
      digitalWrite(ZAPPER, LOW);  // turn off relay with voltage LOW
      delay(COOLDOWN_interval);              // pause

    
    }

if (ircMessage.text.indexOf("ZAP-Long") > -1 && ircMessage.nick == "XSTARWAKE")
      {
     
  Serial.println("Toxic Circuit Testing");

        sendTwitchMessage("Long Test.");

        digitalWrite(ZAPPER, HIGH); // turn on relay with voltage HIGH
        delay(LONG_interval);              // pause
        digitalWrite(ZAPPER, LOW);  // turn off relay with voltage LOW
        delay(COOLDOWN_interval);              // pause



    }

    




 
    return;




  }

}

