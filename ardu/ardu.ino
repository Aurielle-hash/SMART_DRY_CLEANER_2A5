#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2 );//include LCD library (standard library)
#include <Keypad.h> //include keypad library - first you must install library (library link in the video description)

#define redLED 12 //define the LED pins
#define greenLED 11

char* password ="1234"; //create a password

int pos = 0; //keypad position

const byte rows = 4; //number of the keypad's rows and columns
const byte cols = 4;

char keyMap [rows] [cols] = { //define the cymbols on the buttons of the keypad

  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins [rows] = {9, 8, 7, 6}; //pins of the keypad
byte colPins [cols] = {5, 4, 3, 2};

Keypad myKeypad = Keypad( makeKeymap(keyMap), rowPins, colPins, rows, cols);



void setup(){
lcd.init();
lcd.init();
lcd.backlight();
Serial.begin(9600);
  lcd.begin(16, 2);
  
   
  pinMode(redLED, OUTPUT);  //set the LED as an output
  pinMode(greenLED, OUTPUT);
  digitalWrite(11,LOW);
    digitalWrite(12,LOW);
  
  setLocked (true); //state of the password
}

void loop(){

  char whichKey = myKeypad.getKey(); //define which key is pressed with getKey 
   char pasfault= myKeypad.getKey(); 

  lcd.setCursor(0, 0);
  lcd.print(" Welcome__");
  lcd.setCursor(0, 1);
  lcd.print(" Enter Password");

   /* if(pasfault!=password [pos])
  {
    pos=0;
     setLocked (true);
        lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" password invalid!");
    delay(1000);
    lcd.clear();
  }*/

  if(whichKey == '*' || whichKey == '#' || whichKey == 'A' ||       //define invalid keys
  whichKey == 'B' || whichKey == 'C' || whichKey == 'D'){

    pos=0;
    setLocked (true);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" touche invalid!");
    delay(1000);
    lcd.clear();
  }

  
  if(whichKey == password [pos]){

    pos ++;
  }
  if(pos == 4){
    setLocked (false);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("*Acces autorise***");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Bienvenue");
    lcd.setCursor(0, 1);
    lcd.print("Dry_Cleaner");
    delay(7000);
    lcd.clear();
  }
  delay(100);
}

void setLocked(int locked){
  if(locked){
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    }
    else{
      digitalWrite(redLED, LOW);
      digitalWrite(greenLED, HIGH);
    }
  }
