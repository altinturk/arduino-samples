#include <TinyGPS++.h>
#include <SoftwareSerial.h>
/*
   Based on TinyGPS++ (TinyGPSPlus) sample code.
   GPS device hooked up on pins 4(rx) and 3(tx).
*/
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup()
{
  Serial.begin(115200);
  ss.begin(GPSBaud);
  Serial.print(F("TinyGPS++ library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
}

void loop()
{
  Serial.print("SATS:");
  printInt(gps.satellites.value(), gps.satellites.isValid(), 3);
  Serial.print("ERR:");
  printInt(gps.hdop.value(), gps.hdop.isValid(), 5);
  
  Serial.print("LAT:");
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  Serial.print("LON:");
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.print("CLK:");
  printDateTime(gps.time);
  Serial.print("ALT:");
  printFloat(gps.altitude.meters(), gps.altitude.isValid(), 7, 2);
  Serial.print("DIR:");
  printFloat(gps.course.deg(), gps.course.isValid(), 7, 2);
  Serial.print("RCV:");
  printInt(gps.charsProcessed(), true, 6);
  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSTime &t)
{
  if (t.isValid())
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
