#include <SoftwareSerial.h>



float bxpos=30;
float bypos=30;
int cspeed=50;

int ultrasonicdis=0;

int maxthres=35;

SoftwareSerial mySerial(7, 8);

// defines pins numbers
int trigPin = 9;
int echoPin = 10;
// defines variables
long duration;
float distance;


void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600); 
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
 delay(100);

}

void loop() {
  // put your main code here, to run repeatedly:

  //float distravel=cspeed*0.277778*5;
  //bxpos=bxpos+distravel;

  //measure ultrasonic distance
  
  digitalWrite(trigPin, LOW);                      // setting trigpin to low and wait for 2microsec of delay
  delayMicroseconds(2);
   
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);                        // again setting pin to high for trigpin and adding delay of 10microsec
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);                           //setting trigpin to low 
  
   // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);                   
  
  // Calculating the distance
  distance= duration*0.034/2;
  ultrasonicdis=distance;

  if ((ultrasonicdis<=0) || (ultrasonicdis>=maxthres))
  {
      // no need to send value  
  }
  else
  {
     Serial.print(duration);
     Serial.print(",");
     Serial.print(distance);
     Serial.print(",");
     Serial.print(ultrasonicdis);
     Serial.print(","); 
         
  }
  
  delay(1500);
     
}
