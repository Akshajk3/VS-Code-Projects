#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS][COLD] = 
{
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

byte rowPins[ROWS] = {13, 12, 11, 10};
byte colPins[COLS] = {9, 8, 7, 6};

Keypad myKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

bool presentValue = false;
bool next = false;
bool final = false;

String num1, num2;
int answer;
char op;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Techtronic Harsh");
  lcd.setCursor(0,1);
  lcd.print("   Calculator");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    Like And");
  lcd.setCursor(0,1);
  lcd.print("  Subscribe Us"    );
  delay(3000);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  char key = myKeypad.getKey();

  if(key != NO_KEY && (key == '1' || key == '2' || key == '3' || key == '4' || key == '5' || ))
}
