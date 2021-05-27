long count;
int mins, secs, tenths;
String str;

void setup() {
  Serial.begin(9600);
}

String printMe(int n) {
  if (n < 10)
    return "0"+String(n);
  else
    return String(n);
}

String version1(long c) {
  mins = floor(c/60000);
  secs = floor(c%60000/1000);
  tenths = c%10;
  str = String(printMe(mins)) + ":" + String(printMe(secs) + "." + String(tenths));
  return str;
}

String version2(long c) {
  mins = floor(c/60000);
  secs = int(c/1000 - mins*60);
  tenths = c - floor(c/10)*10;
  str = String(printMe(mins)) + ":" + String(printMe(secs) + "." + String(tenths));
  return str;
}

void loop() {
  count = millis();
  Serial.print(version1(count));
  Serial.print("\t");
  Serial.println(version2(count));
  delay(200);
}
