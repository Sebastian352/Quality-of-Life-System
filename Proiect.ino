#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include "dht11.h"
#include <IRremote.h>

const int RECV_PIN = 12;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define DHT11PIN 8
dht11 DHT11;

LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)


#define dht22 5 // DHT22 temperature and humidity sensor
const int trigPin = 9;
const int echoPin = 10;
const int ldrPin = A0;
const int stateButton = 11;

long duration;
int distanceCm, distanceInch;
int state = 1;
int button;
int qualityPoints = 10;

void setup() {
  lcd.begin(16,2);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldrPin, INPUT);
  pinMode(stateButton,INPUT);

  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  lcd.clear();
  //Distance Sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * 0.034 / 2;

  lcd.setCursor(0, 0); // Sets the location at which subsequent text written to the LCD will be displayed

  
  int chk = DHT11.read(DHT11PIN);

  //Light Sensor
  int lightValue = analogRead(ldrPin);


  button = digitalRead(stateButton);
  //if(distanceCm < 100){
      if(button == HIGH){
        state++;
        delay(250);
        if(state > 4) 
          state = 1;
      }
      lcd.print("State: ");
      if(state == 1){
        lcd.print(" WORK ");
      }else if(state == 2){
        lcd.print(" WORKOUT ");
      }else if(state == 3){
        lcd.print(" SLEEP ");
      }

    lcd.setCursor(0, 1);
    qualityPoints = 10; // initialise quality points
    
    if(state == 1){
    //Quality Points of Lights
      if(lightValue > 600 && lightValue < 900){
        qualityPoints += 30;
      }else if(lightValue > 400 && lightValue < 599){
        qualityPoints += 20;
      }else if((lightValue > 200 && lightValue < 399) ||(lightValue > 900 && lightValue < 1000)){
        qualityPoints += 10;
      }
      
      //Quality Points of Temperature
      if((float)DHT11.temperature >= 22 && (float)DHT11.temperature <= 24){
        qualityPoints += 30;
      }else if(((float)DHT11.temperature >= 20 && (float)DHT11.temperature <= 21) || ((float)DHT11.temperature >= 25 && (float)DHT11.temperature <= 26)){
        qualityPoints += 20;
      }else if(((float)DHT11.temperature >= 18 && (float)DHT11.temperature <= 19) || ((float)DHT11.temperature >= 27 && (float)DHT11.temperature <= 28)){
        qualityPoints += 10;
      }

      //Quality Points of Humidity
      if((float)DHT11.humidity >= 20 && (float)DHT11.humidity <= 30){
        qualityPoints += 30;
      }else if(((float)DHT11.humidity >= 30 && (float)DHT11.humidity <= 40) || ((float)DHT11.humidity >= 10 && (float)DHT11.humidity <= 20)){
        qualityPoints += 20;
      }else if(((float)DHT11.humidity >= 40 && (float)DHT11.humidity <= 50) || ((float)DHT11.humidity >= 5 && (float)DHT11.humidity <= 10)){
        qualityPoints += 10;
      }
    }else if(state == 3){
      //Quality Points of Lights
      if(lightValue > 0 && lightValue < 200){
        qualityPoints += 30;
      }else if((lightValue > 200 && lightValue < 400)){
        qualityPoints += 20;
      }else if((lightValue > 400 && lightValue < 600)){
        qualityPoints += 10;
      }

      //Quality Points of Temperature
      if((float)DHT11.temperature >= 19 && (float)DHT11.temperature <= 21){
        qualityPoints += 30;
      }else if(((float)DHT11.temperature >= 17 && (float)DHT11.temperature <= 18) || ((float)DHT11.temperature >= 22 && (float)DHT11.temperature <= 23)){
        qualityPoints += 20;
      }else if(((float)DHT11.temperature >= 15 && (float)DHT11.temperature <= 16) || ((float)DHT11.temperature >= 24 && (float)DHT11.temperature <= 25)){
        qualityPoints += 10;
      }

      //Quality Points of Humidity
      if((float)DHT11.humidity >= 40 && (float)DHT11.humidity <= 50){
        qualityPoints += 30;
      }else if(((float)DHT11.humidity >= 25 && (float)DHT11.humidity <= 39) ){
        qualityPoints += 20;
      }else if(((float)DHT11.humidity >= 10 && (float)DHT11.humidity <= 24) || ((float)DHT11.humidity >= 40 && (float)DHT11.humidity <= 60)){
        qualityPoints += 10;
      }
    }else if(state == 2){
      //Quality Points of Lights
      if(lightValue > 500 && lightValue < 700){
        qualityPoints += 30;
      }else if((lightValue > 300 && lightValue < 499) || (lightValue > 700 && lightValue < 800)){
        qualityPoints += 20;
      }else if((lightValue > 200 && lightValue < 300) ||(lightValue > 800 && lightValue < 900)){
        qualityPoints += 10;
      }

      //Quality Points of Temperature
      if((float)DHT11.temperature >= 19 && (float)DHT11.temperature <= 21){
        qualityPoints += 30;
      }else if(((float)DHT11.temperature >= 17 && (float)DHT11.temperature <= 18) || ((float)DHT11.temperature >= 22 && (float)DHT11.temperature <= 23)){
        qualityPoints += 20;
      }else if(((float)DHT11.temperature >= 15 && (float)DHT11.temperature <= 16) || ((float)DHT11.temperature >= 24 && (float)DHT11.temperature <= 25)){
        qualityPoints += 10;
      }

      //Quality Points of Humidity
      if((float)DHT11.humidity >= 20 && (float)DHT11.humidity <= 30){
        qualityPoints += 30;
      }else if(((float)DHT11.humidity >= 30 && (float)DHT11.humidity <= 40) || ((float)DHT11.humidity >= 10 && (float)DHT11.humidity <= 20)){
        qualityPoints += 20;
      }else if(((float)DHT11.humidity >= 40 && (float)DHT11.humidity <= 50) || ((float)DHT11.humidity >= 5 && (float)DHT11.humidity <= 10)){
        qualityPoints += 10;
      }
    }

    if(state == 4){
      //Distance Meter
      lcd.setCursor(0, 0);
      lcd.print("Distance: "); // Prints string "Distance" on the LCD
      lcd.print(distanceCm); // Prints the distance value from the sensor
      lcd.print(" cm");

      //Light Meter
      lcd.setCursor(0, 1);
      lcd.print("Light: ");
      lcd.println(lightValue);
      
      delay(2000);
      lcd.clear();

      //Temperature and Humidity Sensor
      lcd.setCursor(0, 0);
      lcd.print("Humidity (%): ");
      lcd.println((float)DHT11.humidity, 2);
      lcd.setCursor(0, 1);
      lcd.print("Tmp (C): ");
      lcd.println((float)DHT11.temperature, 2);

      delay(2000);
      lcd.clear();
    }

    int stars = qualityPoints / 20;
    if(stars == 0)     
      lcd.print("Room unsuitable");
    else if(stars == 1)
      lcd.print("Room Qlt: *");
    else if(stars == 2)
      lcd.print("Room Qlt: **");
    else if(stars == 3)
      lcd.print("Room Qlt: ***");
    else if(stars == 4)
      lcd.print("Room Qlt: ****");
    else if(stars == 5)
      lcd.print("Room Qlt: *****");
 // }
  
  delay(1000);
  //if(state == 1) // WORK STATE (STARTING STATE)

}