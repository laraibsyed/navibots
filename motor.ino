#include <Servo.h>
char t;
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
String in_chars = "";
int pos = 0;    // variable to store the servo position
// defines variables
long duration;
int distance;
int RPWM=5;
int LPWM=6;
// timer 0
int L_EN=7;
int R_EN=8;
int data;
int ledState = LOW;

// defines pins numbers
const int trigPin = 12;
const int echoPin = 2;

void setup() {
   //put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  for(int i=5;i<9;i++){
   pinMode(i,OUTPUT);
  }
   for(int i=5;i<9;i++){
   digitalWrite(i,LOW);
  }
   delay(1000);
    Serial.begin(9600);
    myservo.attach(9);
  }
  void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println("EN High");
 digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.println(distance);
  if(distance<20){
     myservo.write(90);
//    delay(1000);
    digitalWrite(R_EN,HIGH);
 digitalWrite(L_EN,HIGH);
 analogWrite(RPWM,0); 
 analogWrite(LPWM,25);
 delay(500);
 digitalWrite(R_EN,LOW);
  digitalWrite(L_EN,LOW);
  analogWrite(RPWM,0);
  analogWrite(LPWM,0);
  }else{
    while(Serial.available())
  {
    digitalWrite(R_EN,HIGH);
 digitalWrite(L_EN,HIGH);
 analogWrite(RPWM,25); 
// analogWrite(LPWM,25);
 delay(500);
 analogWrite(RPWM,0); 
 digitalWrite(R_EN,HIGH);
 digitalWrite(L_EN,HIGH);
 analogWrite(LPWM,25); 
 delay(500);
 digitalWrite(R_EN,LOW);
  digitalWrite(L_EN,LOW);
  analogWrite(LPWM,0);
//    digitalWrite(R_EN,HIGH);
//  digitalWrite(L_EN,HIGH);
//  analogWrite(RPWM,35);
    data = Serial.read();
  }
  }

if (data == '0')
  {
//    ledState = HIGH;
    myservo.write(120);
//    delay(1000);
////    digitalWrite(R_EN,HIGH);
////  digitalWrite(L_EN,HIGH);
////  analogWrite(RPWM,150);
  }
  else if (data == '1')
  {
//    ledState = LOW;
    myservo.write(60);
//    delay(1000);
  }else if (data == '2')
  {
//    ledState = LOW;
    myservo.write(90);
//    delay(1000);
    digitalWrite(R_EN,LOW);
 digitalWrite(L_EN,LOW);
 analogWrite(RPWM,0); 
// analogWrite(LPWM,25);
 delay(50);
 digitalWrite(R_EN,HIGH);
 digitalWrite(L_EN,HIGH);
 analogWrite(LPWM,25); 
 delay(500);
 digitalWrite(R_EN,LOW);
  digitalWrite(L_EN,LOW);
  analogWrite(LPWM,0);
 
  }
}
