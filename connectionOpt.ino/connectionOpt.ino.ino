#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;

// Enter a MAC address for your controller below.
// Newer Ethernet shields have a MAC address printed on a sticker on the shield
byte mac[] = {  0x98, 0x4F, 0xEE, 0x05, 0x34, 0x85};

IPAddress staticIP(172, 16, 222, 199); // adress
IPAddress server(192, 168, 43, 70); // adresse serveur
//192.168.3.78

Servo groveServo;

EthernetClient client;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  delay(1000);
  groveServo.attach(9);
  pinMode(13, OUTPUT);
  Serial.println("connecting ...");

  if (Ethernet.begin(mac) == 0) {
    Serial.println("DHCP not connected");
    Serial.println("getting static IP");
    Ethernet.begin(mac, staticIP);
  }
  else {
    Serial.println("DHCP OK");
  }

  Serial.println(Ethernet.localIP());
  system("ifup eth0");

  delay(1000);
  Serial.println("connecting to remote server...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /iot/yesno.php");
  }
  else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }



  //LCD init
  lcd.begin(16, 2);
  lcd.setRGB(255, 205, 205);
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print("hello");

}

void loop()
{

  // if there are incoming bytes available
  // from the server, read them and print them:
  String in = "";
  while (client.available()) {
    char c = client.read();
    in += c;
  }
  String in1 = in;
  String in2 = in;

  Serial.println(in);

  //Serial.print("my message is ");
  //Serial.println( in.substring( in.indexOf(',')+1 , in2.lastIndexOf(',')  )  );

  int m = 0;
  int p = in.indexOf(',');
  String smot  = in.substring(0, p);
  m = smot.toInt();
  groveServo.write(m);
  String message = in.substring(p + 1);
  lcd.clear();
  lcd.print(message);
  lcd.setCursor(0, 1);


  Serial.println(smot);
  Serial.println(message);

  if ( digitalRead(4) == HIGH) {
    float t = getTemp(analogRead(A0));
    String ip = DisplayAddress(Ethernet.localIP());
    String req = "GET /iot/insert.php?ip=";
    req += ip;
    req += "&temp=";
    req += float2String(t,5);
    Serial.println(req);
    sendRequest(req);

  }



  sendRequest( "GET /iot/getEtat.php");
  delay(2000);
}
void sendRequest(String url ) {
  client.stop();
  if ( client.connect(server, 80)) {
    client.println(url);
  }
}

float getTemp(int a) {

  int B = 3975;                //B value of the thermistor

  float resistance = (float)(1023 - a) * 10000 / a;
  float temperature = 1 / (log(resistance / 10000) / 3975 + 1 / 298.15) - 273.15;
  return  temperature;
}

/**
 * Float to String 
 * arg1 : float value
 * arg2 : precision ( number of digits after point
 * returns String valueOf Float
 */
String float2String(float f, int precision) {
  char ta[20];
  sprintf(ta, "%f", f);
  String s="";
  String result="";
  s+=ta;
  
  int pos = s.indexOf('.');
  for (int i=0;i< pos+1+precision ;i++){
    result+=ta[i];
  }
return result;

}
/**
 * Convert IPv4 adress to String
 *Arg :IPAddress address
 */
String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}

/*

    string 1234567895
 ************   substring(2) == "23456789") {
   find string in string
   stringOne.indexOf("5"); return 5
   mystring.lastIndexOf("5");  returns 10

*/


