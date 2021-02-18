#include <LiquidCrystal.h>
z
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
byte count = 0;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
    Serial.begin(9600);  
    pinMode(inPin1, INPUT);
    pinMode(inPin2, INPUT);
    lcd.begin(16, 2);
}
    
void loop() {
    changeTicker();
    getPrices(); 
    chooseTicker();
}
void changeTicker(){
    if (digitalRead(inPin1)){
        count++;
        if(count == 9)
            count =0;
        Serial.write('N');
    } else if (digitalRead(inPin2)){
        count--;
        if (count == -1)
            count = 8;
        Serial.write('B');
    }
}
void chooseTicker(){
    switch(count){
        case 0: standardPrint("GME");
        case 1: standardPrint("AMC");
        case 2: standardPrint("BBBY");
        case 3: standardPrint("NOK");
        case 4: standardPrint("BB");
        case 5: standardPrint("TSLA");
        case 6: standardPrint("AAPL");
        case 7: standardPrint("DIS");
        case 8: standardPrint("NVDA");
    }
}
void getPrices(){
    if (Serial.available()>3){
      price = Serial.read();
      priceDecimal = Serial.read();
      price += priceDecimal/100.0;
      closePrice = Serial.read();
      closeDecimal = Serial.read();
      closePrice += closeDecimal/100.0;
    }
}
double calcChange(){
    return (price-closePrice);
}
double calcChangePercent(){
    return ((price/closePrice)-1);
}
void standardPrint(String ticker){
     lcd.setCursor(0,0);
     lcd.print(ticker);
     lcd.print(" ");
     lcd.print(calcChange());
     lcd.print(" ");
     if(calcChangePercent() < 0){
        lcd.print("-");
     } else{
        lcd.print("+");
     }
     lcd.print(calcChangePercent());
     lcd.setCursor(0, 1);
     lcd.print(price);
     delay(50);
     lcd.clear();
}
