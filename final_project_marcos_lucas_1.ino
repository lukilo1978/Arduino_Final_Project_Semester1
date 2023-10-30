// C++ code
//
// include the library code:
#include <LiquidCrystal.h>
// include Servo library code
#include <Servo.h>

const int rs = 12, en = 11, d4 = 6, d5 = 5, d6 = 4, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int RGBRedPin = 8;    //The red RGB LED is connected pin 9 of the Arduino. 
int RGBGreenPin = 9; //The green RGB LED is connected pin 10 of the Arduino. 
int RGBBluePin = 10; //The blue RGB LED is connected pin 10 of the Arduino. 


int baselineTemp = 0;
int celsius = 0;
int fahrenheit = 0;


int whiteLED = 13;
int photosensor = A1;
int data = 0;

int distance_v = 0;

Servo servo_3;

long readUltrasonicDistance(int triggerPin, int echoPin)
  
{
  pinMode(triggerPin, OUTPUT);  // Clear the trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  return pulseIn(echoPin, HIGH);
}

void setup()
{
  servo_3.attach(3, 500, 2500);
  lcd.begin(16, 2);
  
 
  pinMode(RGBRedPin, OUTPUT);    //Setup red RGB LED pin as an output pin. 
  pinMode(RGBGreenPin, OUTPUT);  //Setup green RGB LED pin as an output pin. 
  pinMode(RGBBluePin, OUTPUT);   //Setup blue RGB LED pin as an output pin. 
  
  //temp sensor
  pinMode(A0, INPUT);
  
  pinMode(A1,INPUT_PULLUP);
  pinMode(whiteLED,OUTPUT);

  
  Serial.begin(9600);
}

void loop()
{
  
  celsius = map(((analogRead(A0) - 20) * 3.04), 0, 1023, -40, 125);
  
  fahrenheit = ((celsius * 9) / 5 + 32);
  Serial.print(celsius);
  Serial.print(" C, ");
  Serial.print(fahrenheit);
  Serial.println(" F");
  
    if (celsius < baselineTemp) {
    lcd.setCursor(0, 1);
    lcd.print("Freezing");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
    lcd.setCursor(13, 1);
    lcd.print("C");  
  }
  if (celsius >= baselineTemp && celsius < baselineTemp + 20) {
    
    lcd.setCursor(0, 1);
    lcd.print("Cold");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
    lcd.setCursor(13, 1);
    lcd.print("C");  
  }
  if (celsius >= baselineTemp + 20 && celsius < baselineTemp + 30) {
    
    lcd.setCursor(0, 1);
    lcd.print("Warm");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
    lcd.setCursor(13, 1);
    lcd.print("C");  
  }
  if (celsius >= baselineTemp + 30 && celsius < baselineTemp + 40) {
    
    lcd.setCursor(0, 1);
    lcd.print("Hot");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
    lcd.setCursor(13, 1);
    lcd.print("C");  
  }
  if (celsius >= baselineTemp + 40) {
    
    lcd.setCursor(0, 1);
    lcd.print("Boiling");
    lcd.setCursor(10, 1);
    lcd.print(celsius);
    lcd.setCursor(13, 1);
    lcd.print("C");  
    
  }
  delay(1000); 
  
  
  servo_3.write(0);
  distance_v = 0.01723 * readUltrasonicDistance(7, 7);
  
  if (distance_v < 100) {
    
    servo_3.write(180);
    lcd.setCursor(0, 0);
    lcd.print("Open door");
    delay(1000);
    lcd.clear();
    digitalWrite(RGBRedPin,LOW);
    digitalWrite(RGBGreenPin,HIGH);
    digitalWrite(RGBBluePin,LOW);
    
  } else {
    
    servo_3.write(0);
    lcd.setCursor(0, 0);
    lcd.print("Close door");
    delay(1000);
    lcd.clear();
    digitalWrite(RGBRedPin,HIGH);
    digitalWrite(RGBGreenPin,LOW);
    digitalWrite(RGBBluePin,LOW);
  }
  
  ligthControl();

  delay(10); // Delay a little bit to improve simulation performance
  
}

void ligthControl(){
  
  data = analogRead(photosensor);
  
  Serial.print("Photosensor Data = ");
  Serial.println(data);
  
  if (data < 169){
  digitalWrite(whiteLED, HIGH);
  }
   if(data>169&&data<339){
  digitalWrite(whiteLED, 127);
   }
  
   if (data>339&&data<609){
  digitalWrite(whiteLED, 69);
  }
  if(data > 609){
    digitalWrite (whiteLED, LOW);
    
    delay(100);
}
}
  