/*
@Author Alp
Let's read a thermistor and make a digital thermometer.
Some of the sample code I used here can be found at: http://playground.arduino.cc/ComponentLib/Thermistor2
*/

#include <math.h>

int thermistorPin = A0; //analog pin 0
double tSaved = 0;
double tMax = 0;
double tMin = 100;

double Thermistor(int RawADC) {
 double Temp;
 Temp = log(10000.0*((1024.0/RawADC-1))); 
//         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
 Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp ))* Temp );
 Temp = Temp - 273.15;            // Convert Kelvin to Celcius
 //Temp = (Temp * 9.0)/ 5.0 + 32.0; // Convert Celcius to Fahrenheit
 return Temp;
}

void setup(){
  Serial.begin(9600);
}

void loop(){
  int thermistorReading = analogRead(thermistorPin); 
  double tCurrent = Thermistor(thermistorReading);
  
  if(tSaved != tCurrent){
    if(tCurrent>tMax) tMax = tCurrent;
    if(tCurrent<tMin) tMin = tCurrent;
    tSaved = tCurrent;
    Serial.print("Temp: ");
    Serial.print(tCurrent);
    Serial.print(", TMax: ");
    Serial.print(tMax);
    Serial.print(", TMin: ");
    Serial.print(tMin);
    Serial.print(", RAW: ");
    Serial.println(thermistorReading);
  }
  
  delay(300); //just here to slow down the output for easier reading
}
