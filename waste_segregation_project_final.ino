#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,9,10,11,12);//RS,EN,D4,D5,D6,D7
int moisturePin = A0;    // moisture sensor pin
int irSensorPin = A1;    // IR sensor pin
int servoPin = 6;        // servo motor pin
int wetThreshold = 800;  // moisture level threshold for wet waste
int irThreshold = 500;   // IR sensor threshold for dry waste
int trigPin1 = 1 ; ///right
int echoPin1 = 2;
int trigPin2 = 3 ; //// front
int echoPin2 = 4;

Servo myServo;

void setup() {
   Serial.begin(9600);

  myServo.attach(servoPin);
  
  pinMode(moisturePin, INPUT);
  pinMode(irSensorPin, INPUT);
  
 lcd.begin(16,2); //initializing LCD
 lcd.setCursor(0,0); 
 lcd.print("Automatic WASTE");
 lcd.setCursor(0,1); 
 lcd.print("Segregation sys");
delay(3000); 
lcd.clear();

   
}

void loop() {
  int moistureValue = analogRead(moisturePin);  // read moisture sensor value
  int irValue = analogRead(irSensorPin);  // read IR sensor value
  Serial.println(moistureValue);

  
  if (moistureValue < wetThreshold && irThreshold >irValue ) {  // if the waste is wet
    lcd.setCursor(0,0); 
    lcd.print(" WET  GARBAGE");
    Serial.println("wet");
    myServo.write(0);                 // rotate servo to one side for wet waste
    delay(5000);                      // wait for 5 seconds
    lcd.clear();
} 

 else if (irThreshold >irValue) {  // if the waste is dry
  delay(2000);
    lcd.setCursor(0,0); 
    lcd.print(" DRY  GARBAGE");
    Serial.println("Dry");
     myServo.write(180);                // rotate servo to the other side for dry waste
    delay(2000);                     // wait for 5 seconds
    lcd.clear();
    
  } else{
    Serial.print("no waste");
     myServo.write(90);                // rotate servo to the other side for dry waste
    delay(1000);
    lcd.clear(); 
    } 
}
