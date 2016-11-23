# IOT_Sketches
Special methods to use

// get GROVE temperature sensor value
float getTemp(int a) {
  int B = 3975;                //B value of the thermistor
  float resistance = (float)(1023 - a) * 10000 / a;
  float temperature = 1 / (log(resistance / 10000) / 3975 + 1 / 298.15) - 273.15;
  return  temperature;
}
    
        
/**
  *
   Float to String
   arg1 : float value
   arg2 : precision ( number of digits after point
   returns String valueOf Float
  *
  */
String float2String(float f, int precision) {
  char ta[20];
  sprintf(ta, "%f", f);
  String s = "";
  String result = "";
  s += ta;
  int pos = s.indexOf('.');
  for (int i = 0; i < pos + 1 + precision ; i++) {
    result += ta[i];
  }
  return result;

}


/**
   Convert IPv4 adress to String
  Arg :IPAddress address
*/
String DisplayAddress(IPAddress address)
{
  return String(address[0]) + "." +
         String(address[1]) + "." +
         String(address[2]) + "." +
         String(address[3]);
}
