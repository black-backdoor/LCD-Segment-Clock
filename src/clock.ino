#include <LiquidCrystal_I2C.h>

// ---------- SETTINGS ----------
const bool DOTS = true;


// ---------- Custom Characters ----------
// the 8 arrays that form each segment of the custom numbers
const byte bar1[8] = {0b11100,0b11110,0b11110,0b11110,0b11110,0b11110,0b11110,0b11100};
const byte bar2[8] = {0b00111,0b01111,0b01111,0b01111,0b01111,0b01111,0b01111,0b00111};
const byte bar3[8] = {0b11111,0b11111,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111};
const byte bar4[8] = {0b11110,0b11100,0b00000,0b00000,0b00000,0b00000,0b11000,0b11100};
const byte bar5[8] = {0b01111,0b00111,0b00000,0b00000,0b00000,0b00000,0b00011,0b00111};
const byte bar6[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b11111,0b11111};
const byte bar7[8] = {0b00000,0b00000,0b00000,0b00000,0b00000,0b00000,0b00111,0b01111};
const byte bar8[8] = {0b11111,0b11111,0b00000,0b00000,0b00000,0b00000,0b00000,0b00000};


// ------ SETUP -----
LiquidCrystal_I2C lcd(0x27, 16, 2);

int seconds, minutes, hours;

unsigned long last_millis;
bool dots_on;




void setup()
{
    lcd.init(); // LCD Display init
    lcd.backlight(); // LCD Display activate backlight

    // Create custom characters once during setup
    lcd.createChar(1, bar1);
    lcd.createChar(2, bar2);
    lcd.createChar(3, bar3);
    lcd.createChar(4, bar4);
    lcd.createChar(5, bar5);
    lcd.createChar(6, bar6);
    lcd.createChar(7, bar7);
    lcd.createChar(8, bar8);

    seconds = 0;
    minutes = 0;
    hours = 0;

    Serial.begin(9600);

    Serial.println(F("enter hour"));
    while (!Serial.available()){
        delay(1);
    }

    String temp = "";
    temp = Serial.readString();
    hours = temp.toInt();
  
    Serial.println(F("enter minutes"));
    while (!Serial.available()){
        delay(1);
    }
    temp = Serial.readString();
    minutes = temp.toInt();
  
    Serial.println(F("enter seconds"));
    while (!Serial.available()){
        delay(1);
    }
    temp = Serial.readString();
    seconds = temp.toInt();


    Serial.print(F("TIME SET TO "));
    Serial.print(hours);
    Serial.print(F(":"));
    Serial.print(minutes);
    Serial.print(F(":"));
    Serial.print(seconds);
    Serial.println();

    last_millis = millis();
}

void custom0(int col) {
    // uses segments to build the number 0
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(8); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(2);  
    lcd.write(6);  
    lcd.write(1);
}

void custom1(int col) {
    lcd.setCursor(col,0);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
    lcd.setCursor(col,1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
}

void custom2(int col) {
    lcd.setCursor(col,0);
    lcd.write(5);
    lcd.write(3);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(2);
    lcd.write(6);
    lcd.write(6);
}

void custom3(int col) {
    lcd.setCursor(col,0);
    lcd.write(5);
    lcd.write(3);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(7);
    lcd.write(6);
    lcd.write(1); 
}

void custom4(int col) {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(6);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
}

void custom5(int col) {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(col, 1);
    lcd.write(7);
    lcd.write(6);
    lcd.write(1);
}

void custom6(int col) {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(3);
    lcd.write(4);
    lcd.setCursor(col, 1);
    lcd.write(2);
    lcd.write(6);
    lcd.write(1);
}

void custom7(int col) {
    lcd.setCursor(col,0);
    lcd.write(2);
    lcd.write(8);
    lcd.write(1);
    lcd.setCursor(col, 1);
    lcd.write(32);
    lcd.write(32);
    lcd.write(1);
}

void custom8(int col) {
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(3); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(2);  
    lcd.write(6);  
    lcd.write(1);
}

void custom9(int col) {
    lcd.setCursor(col, 0); 
    lcd.write(2);  
    lcd.write(3); 
    lcd.write(1);
    lcd.setCursor(col, 1); 
    lcd.write(7);  
    lcd.write(6);  
    lcd.write(1);
}

void printNumber(int value, int col) {
    switch (value) {
        case 0: custom0(col); break;
        case 1: custom1(col); break;
        case 2: custom2(col); break;
        case 3: custom3(col); break;
        case 4: custom4(col); break;
        case 5: custom5(col); break;
        case 6: custom6(col); break;
        case 7: custom7(col); break;
        case 8: custom8(col); break;
        case 9: custom9(col); break;
    }
} 



void loop() {
    // update time
    if(seconds > 59){
        seconds = 0;
        minutes++;

        if(minutes>59){
            minutes=0;
            hours++;

            if(hours>11){
                hours=0;
            } 
        }

        Serial.print(F("CURRENT TIME "));
        Serial.print(hours);
        Serial.print(F(":"));
        Serial.print(minutes);
        Serial.print(F(":"));
        Serial.print(seconds);
        Serial.println();
    }

    int d;

    d=hours%10;
    printNumber(d, 3);

    d=hours/10;
    printNumber(d, 0);

    d=minutes%10;
    printNumber(d, 10);

    d=minutes/10;
    printNumber(d, 7);

    if((millis() - last_millis) >= 1000){
        last_millis += 1000;
        seconds++;
    }


    if (DOTS) {
        if (millis() % 1000 < 500) {
            lcd.setCursor(6, 0);
            lcd.print(".");
            lcd.setCursor(6, 1);
            lcd.print(".");
        } else {
            lcd.setCursor(6, 0);
            lcd.print(" ");
            lcd.setCursor(6, 1);
            lcd.print(" ");
        }
    }
}
