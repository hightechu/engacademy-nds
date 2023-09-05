const int trigPin = 9; // The pin connected to the Trig pin on ultrasonic sensor
const int echoPin = 10; // The pin connected to the Echo pin on ultrasonic sensor
#include <SoftwareSerial.h> //import the serial library
int fsrPin = 0;     // the FSR and 10K pulldown are connected to a0
int fsrPin2 = 1;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrReading2;     // the analog reading from the FSR resistor divider
const int PIN_RED   = 5;
const int PIN_GREEN = 4;
const int PIN_BLUE  = 3;


SoftwareSerial btSerial(6, 7); // set serial RX & TX to pins 10 & 11 respectively

String bt_rx; //set up recieved string variable


// Here is where our program starts. This code will run when the
// Arduino Uno is initially plugged in to power or when you upload your code. 
// The code inside setup() will only run once!
void setup()
{
  // We tell the board we want to use certain pins for our LED and
  // ultrasonic sensor. We do that using the pinMode() function. 

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);

  // If you want to know the exact distance between the object and the ultrasonic sensor,
  // you can print the value to the serial monitor. You can access the serial monitor by
  // clicking the magnifying glass icon in the top right.
  Serial.begin(9600);
  btSerial.begin(9600);
}

// Once the code in setup() is finished, the code in loop() will
// continuously run until the Arduino is disconnected from power
void loop()
{

   // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Calculating the distance by reading the echoPin, which
  // returns the sound wave travel time in microseconds
  int distance = (pulseIn(echoPin, HIGH) * 0.034) / 2;
  
  // Prints the distance to the Serial Monitor
  if(distance < 14) {
      analogWrite(PIN_RED, 255);
      analogWrite(PIN_BLUE, 0);
      analogWrite(PIN_GREEN, 0);
  } else if(distance < 55 && distance >= 14) {
      analogWrite(PIN_RED, 254);
      analogWrite(PIN_BLUE, 0);
      analogWrite(PIN_GREEN, 218);
  } else {
      analogWrite(PIN_RED, 0);
      analogWrite(PIN_BLUE, 0);
      analogWrite(PIN_GREEN, 255);
  }
  btSerial.print("Distance from nearest object: ");
  btSerial.println(distance);

fsrReading = analogRead(fsrPin);  
 
  btSerial.print("Boat side reading = ");
  btSerial.print(fsrReading);     // print the raw analog reading
 
  if (fsrReading < 10) {
    btSerial.println(" - Nothing on right side");
  } else if (fsrReading < 200) {
    btSerial.println(" - Light touch on right side");
  } else {
    btSerial.println(" - Hit on right side");
  }
  delay(1000);

  fsrReading2 = analogRead(fsrPin2);  
  btSerial.print("Boat side reading = ");
  btSerial.print(fsrReading2);     // print the raw analog reading
 
  if (fsrReading2 < 10) {
    btSerial.println(" - Nothing on left side");
  } else if (fsrReading2 < 200) {
    btSerial.println(" - Light touch on left side");
  } else {
    btSerial.println(" - Hit on left side");
  }
  delay(1000);
}
