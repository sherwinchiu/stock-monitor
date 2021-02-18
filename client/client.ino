#include <LiquidCrystal.h>

#define     rs      12
#define     en      11
#define     d4      5
#define     d5      4
#define     d6      3
#define     d7      2
#define     inPin1  6
#define     inPin2  7

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

double price;
int priceDecimal;
byte count = 1;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
    Serial.begin(9600);  
    pinMode(inPin1, INPUT);
    pinMode(inPin2, INPUT);
    lcd.begin(16, 2);
    lcd.print("hello, world!");
}
    
void loop() {
    lcd.setCursor(0, 0);
    if (digitalRead(inPin1)){
        count++;
        if(count == 10)
            count =1;
        Serial.write('N');
    } else if (digitalRead(inPin2)){
        count--;
        if (count == 0)
            count = 9;
        Serial.write('B');
    }
    getPrice();
    switch(count){
        case 1: printGME();
        case 2: printAMC();
        case 3: printBBBY();
        case 4: printNOK();
        case 5: printBB();
        case 6: printTSLA();
        case 7: printAAPL();
        case 8: printDIS();
        case 9: printNVDA();
    }
}
void getPrice(){
    if (Serial.available()>1){
      price = Serial.read();
      priceDecimal = Serial.read();
      price += priceDecimal/100.0;
    }
}
int calcChange(){
    
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
void printAMC(){
    
}
void printBBBY(){
    
}
void printNOK(){
    
}
void printBB(){
    
}
void printTSLA(){
    
}
void printAAPL(){
    
}
void printDIS(){
    
}
void printNVDA(){
    
}
