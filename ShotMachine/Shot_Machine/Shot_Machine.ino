/*******************************************************************
http://www.heroshot.ca
AUOMATIC COCKTAIL MAKER
twitch awesomeness v3.1
par patrick groleau
1(873)200-3676
*******************************************************************/
 
#include <ESP8266WiFi.h>
#include <IRCClient.h>
#include <Servo.h>
#include <Stepper.h>



int PUMP1 = 13;
int PUMP2 = 12;
int PUMP3 = 14;
int PUMP4 = 16;








 


//define your default values here, if there are different values in config.json, they are overwritten.
#define secret_ssid "BOTTY" 
#define IRC_SERVER   "irc.chat.twitch.tv"
#define IRC_PORT     6667
 
//------- info compte! ------
char ssid[] = "XStarWake-WiFi";       // your network SSID (name)
char password[] = "wittystar718";  // your network key
const String twitchChannelName = "xstarwake"; //this is case sensitive!
#define TWITCH_BOT_NAME "BORIS___BOT"  // to change to the actual bot name

//OAuth Key 
// https://twitchapps.com/tmi/
#define TWITCH_OAUTH_TOKEN "oauth:1z6sj2eja0p8vzu70aaq7pwyct976e" //to chage to the one your bot has
//------------------------------

String ircChannel = "";
 
WiFiClient wiFiClient;
IRCClient client(IRC_SERVER, IRC_PORT, wiFiClient);
 
// put your setup code here, to run once:
void setup() {


  // Relay board
digitalWrite(5, LOW);   
digitalWrite(4, LOW);   
digitalWrite(0, LOW);   
digitalWrite(15, LOW);   
digitalWrite(13, LOW);   
digitalWrite(12, LOW);   
digitalWrite(14, LOW);   
digitalWrite(16, LOW);   

  
  // Relay board
  pinMode(5, OUTPUT); 
  pinMode(4, OUTPUT); 
  pinMode(0, OUTPUT); 
  pinMode(15, OUTPUT); 
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT); 
  pinMode(14, OUTPUT); 
  pinMode(16, OUTPUT); 



 
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
      //sendTwitchMessage("COCKTAIL MAKER V3.1 CONNECTED ! ");
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



//EMPLACEMENT DES ACTIONS RECETTES 


// PUMP1
if (ircMessage.text.indexOf("Lets Celebrate") > -1 && ircMessage.nick == "InstructBot")
      { 
     digitalWrite(PUMP1, HIGH);   
  delay(9000);            
  digitalWrite(PUMP1, LOW); 
    }

    // PUMP2
if (ircMessage.text.indexOf("Shot Time") > -1 && ircMessage.nick == "InstructBot")
      { 
    digitalWrite(PUMP2, HIGH);   
  delay(9000);            
  digitalWrite(PUMP2, LOW);  
    }

    // PUMP3
if (ircMessage.text.indexOf("Someone Say Shot") > -1 && ircMessage.nick == "InstructBot")
      { 
   digitalWrite(PUMP3, HIGH);   
  delay(9000);            
  digitalWrite(PUMP3, LOW);   
    }

    // PUMP4
if (ircMessage.text.indexOf("Cheers") > -1 && ircMessage.nick == "InstructBot")
      { 
  digitalWrite(PUMP4, HIGH);   
  delay(9000);            
  digitalWrite(PUMP4, LOW); 
   
    }

// PUMP1
if (ircMessage.text.indexOf("Lets Celebrate") > -1 && ircMessage.nick == "INSTRUCTBOT")
      { 
     digitalWrite(PUMP1, HIGH);   
  delay(9000);            
  digitalWrite(PUMP1, LOW); 
    }

    // PUMP2
if (ircMessage.text.indexOf("Shot Time") > -1 && ircMessage.nick == "INSTRUCTBOT")
      { 
    digitalWrite(PUMP2, HIGH);   
  delay(9000);            
  digitalWrite(PUMP2, LOW);  
    }

    // PUMP3
if (ircMessage.text.indexOf("Someone Say Shot") > -1 && ircMessage.nick == "INSTRUCTBOT")
      { 
   digitalWrite(PUMP3, HIGH);   
  delay(9000);            
  digitalWrite(PUMP3, LOW);   
    }

    // PUMP4
if (ircMessage.text.indexOf("Cheers") > -1 && ircMessage.nick == "INSTRUCTBOT")
      { 
  digitalWrite(PUMP4, HIGH);   
  delay(9000);            
  digitalWrite(PUMP4, LOW); 
   
    }


    // PUMP1
if (ircMessage.text.indexOf("BOURBON1") > -1 && ircMessage.nick == "BORIS___BOT")
      { 
     digitalWrite(PUMP1, HIGH);   
  delay(9000);            
  digitalWrite(PUMP1, LOW); 
    }

    // PUMP2
if (ircMessage.text.indexOf("BOURBON2") > -1 && ircMessage.nick == "BORIS___BOT")
      { 
    digitalWrite(PUMP2, HIGH);   
  delay(9000);            
  digitalWrite(PUMP2, LOW);  
    }

    // PUMP3
if (ircMessage.text.indexOf("BOURBON3") > -1 && ircMessage.nick == "BORIS___BOT")
      { 
   digitalWrite(PUMP3, HIGH);   
  delay(9000);            
  digitalWrite(PUMP3, LOW);   
    }

    // PUMP4
if (ircMessage.text.indexOf("BOURBON4") > -1 && ircMessage.nick == "BORIS___BOT")
      { 

  digitalWrite(PUMP4, HIGH);   
  delay(9000);            
  digitalWrite(PUMP4, LOW); 
   
    }

    // PUMP1
if (ircMessage.text.indexOf("BOURBON1") > -1 && ircMessage.nick == "Boris___Bot")
      { 
     digitalWrite(PUMP1, HIGH);   
  delay(9000);            
  digitalWrite(PUMP1, LOW); 
    }

    // PUMP2
if (ircMessage.text.indexOf("BOURBON2") > -1 && ircMessage.nick == "Boris___Bot")
      { 
    digitalWrite(PUMP2, HIGH);   
  delay(9000);            
  digitalWrite(PUMP2, LOW);  
    }

    // PUMP3
if (ircMessage.text.indexOf("BOURBON3") > -1 && ircMessage.nick == "Boris___Bot")
      { 
   digitalWrite(PUMP3, HIGH);   
  delay(9000);            
  digitalWrite(PUMP3, LOW);   
    }

    // PUMP4
if (ircMessage.text.indexOf("BOURBON4") > -1 && ircMessage.nick == "Boris___Bot")
      { 

  digitalWrite(PUMP4, HIGH);   
  delay(9000);            
  digitalWrite(PUMP4, LOW); 
   
    }
  }

}