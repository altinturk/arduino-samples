/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;

const int flexpin = 0;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);     
    Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  
  
  int flexposition;    // Input value from the analog pin.
    int servoposition;   // Output value to the servo.


  // Read the position of the flex sensor (0 to 1023):

  flexposition = analogRead(flexpin);

  servoposition = map(flexposition, 100, 500, 0, 180);
  servoposition = constrain(servoposition, 0, 180);

  Serial.print("sensor: ");
  Serial.print(flexposition);
  Serial.print("  servo: ");
  Serial.println(servoposition);

  if(servoposition>60)
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  else
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
// wait for a second
 delay(200);
}
