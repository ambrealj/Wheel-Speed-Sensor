#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int sensorPin = 9;
int tickcount = 0;
const int timespan=60;
int minutes=0;
int currentTimestamp;
const int button= 5;
double rpm = 0;
//const int sda = A4;
//const int scl = A5;
unsigned long starttime=0;

void setup() {
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("S: ");
  lcd.setCursor(8,0);
  lcd.print("M: ");
  lcd.setCursor(0,1);
  lcd.print("T: ");
  lcd.setCursor(8,1);
  lcd.print("RPM: ");
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(sensorPin, INPUT);
  pinMode(button, INPUT);
  //pinMode(sda, OUTPUT);
  //pinMode(scl, OUTPUT);
  starttime=millis();

}

void loop() {
  // put your main code here, to run repeatedly:
  int switchstate = digitalRead(button);
  
  if (switchstate == LOW) {
    
    //delay(1000);
    int reading = digitalRead(sensorPin);
    //Serial.println(reading);
    tickcount+=reading;
    unsigned long currentTimestamp = millis();
    Serial.println(tickcount);
    
    if(currentTimestamp-starttime>= (60000)){
      //Serial.println("tickcount: " + tickcount);
      minutes++;
      //currentTimestamp =0;
      //currentTimestamp = millis();
      rpm = tickcount/16;
      
      starttime=currentTimestamp;
      tickcount =0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("S: ");
      lcd.setCursor(8,0);
      lcd.print("M: ");
      lcd.setCursor(0,1);
      lcd.print("T: ");
      lcd.setCursor(8,1);
      lcd.print("RPM: ");
      lcd.setCursor(3,0);
      lcd.print((currentTimestamp-starttime)/1000); 
      //lcd.print(currentTimestamp/1000);   
      lcd.setCursor(11,0);
      lcd.print(minutes);
      lcd.setCursor(3,1);
      lcd.print(tickcount);
      lcd.setCursor(12,1);
      lcd.print(rpm);
      
      
      
      //currentTimestamp=0;
    }
    lcd.setCursor(3,0);
    lcd.print((currentTimestamp-starttime)/1000); 
    //lcd.print(currentTimestamp/1000);   
    lcd.setCursor(11,0);
    lcd.print(minutes);
    lcd.setCursor(3,1);
    lcd.print(tickcount);
    lcd.setCursor(12,1);
    lcd.print(rpm);
    
    //Serial.println(rpm);
    //Serial.println(tickcount);
    //Serial.println(reading);
    //Serial.println(tickcount);
    delay(500);
    
  }
}
//take input from digital read add together over 60 seconds divide by 16(nujmber of ticks)