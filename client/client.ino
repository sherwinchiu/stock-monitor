#include <LiquidCrystal.h>
#include <Servo.h>

#define     rs      12
#define     en      11
#define     d4      5
#define     d5      4
#define     d6      3
#define     d7      2
#define     inPin1  6
#define     inPin2  7
#define     servo   9

double price;
int priceDecimal;
double closePrice;
int closeDecimal;
int count = 0;
int debounceDelay = 1000;
int lastDebounceTime = millis();
Servo servo1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
    Serial.begin(9600);  
    pinMode(inPin1, INPUT);
    pinMode(inPin2, INPUT);
    servo1.attach(servo);
    lcd.begin(16, 2);
}
    
void loop() {
    changeTicker();  //Checks if user wants to change the ticker symbol
    getPrices();     // Gets the price of ticker symbol
    chooseTicker();  // If user does want to change ticker symbol, update display
}
void changeTicker(){
    if(millis() - lastDebounceTime > debounceDelay){
      if (digitalRead(inPin1)){
          count++;
          if(count >= 9)
              count =0;
          Serial.write(0);
          lastDebounceTime = millis();
          delay(500);
      } else if (digitalRead(inPin2)){
          count--;
          if (count <= -1)
              count = 8;
          Serial.write(1);
          delay(500);  
          lastDebounceTime = millis();
      }
    }
}
void chooseTicker(){
    if(count ==0){
        standardPrint("GME");
    } else if (count == 1){
        standardPrint("AMC");
    } else if (count == 2){
        standardPrint("BBBY");
    } else if (count == 3){
        standardPrint("NOK");
    } else if (count == 4){
        standardPrint("BB");
    } else if (count == 5){
        standardPrint("FOOD");
    } else if (count == 6){
        standardPrint("AAPL");
    } else if (count == 7){
        standardPrint("DIS");
    } else if (count == 8){
        standardPrint("NVDA");
    }
}
void getPrices(){
    if (Serial.available()>5){
      price = Serial.read()<<8;
      price += Serial.read();
      priceDecimal = Serial.read();
      price += priceDecimal/100.0;
      closePrice = Serial.read()<<8;
      closePrice += Serial.read();
      closeDecimal = Serial.read();
      closePrice += closeDecimal/100.0;
      if(calcChange() < 0)
        servo1.write(60);
      else if (calcChange() > 0)
        servo1.write(180);
    }
    
}
double calcChange(){
    return (price-closePrice);
}
double calcChangePercent(){
    return ((price/closePrice)-1)*100.0 ;
}
void standardPrint(String ticker){
     lcd.setCursor(0,0);
     lcd.print(ticker);
     lcd.print("   ");
     lcd.print("%");
     lcd.print(calcChangePercent());
     lcd.setCursor(0, 1);
     lcd.print(price);
     lcd.print("   ");
     lcd.print(calcChange());
     delay(25);
    // lcd.clear();
}
