#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
double price;
int priceDecimal;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
    Serial.begin(9600);  
    lcd.begin(16, 2);
    lcd.print("hello, world!");
}
    
void loop() {
    lcd.setCursor(0, 0);
    if (Serial.available()>3){
      price = Serial.read();
      priceDecimal = Serial.read();
      price += priceDecimal/100.0;
    }
    printGME();
    
}
void printGME(){
    lcd.setCursor(0,0);
    lcd.print("GME ");
    lcd.setCursor(0,1);
    lcd.print(price);
    lcd.print(" ");
    delay(100);
    lcd.clear();
}
