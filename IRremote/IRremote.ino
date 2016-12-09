#include <IRremote.h>
int RECV_PIN = 6;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {                
  // initialize the digital pin as an output.
  pinMode(RECV_PIN, INPUT);  
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
}
void loop() {
 while (irrecv.decode(&results)  )
 {

  String s = String(results.value,HEX);
  if ( s!="ffffffff")
  Serial.println(s);
  irrecv.resume();
 }
}
