#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};

byte rowPins[ROWS] = {12, 11, 10, 9}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8,7,6}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


boolean butt_flag = 0;
boolean butt;
boolean butt2;
boolean led_flag = 0;
unsigned long last_press;
byte led = 4;
void setup() {
  pinMode(3, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);

  pinMode(A2,OUTPUT);

  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(A1, OUTPUT);
  digitalWrite(4, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, HIGH);
}

void loop() {
  butt = !digitalRead(3); // считать текущее положение кнопки
  butt2 = !digitalRead(2);
  if (butt2 == 1 && butt == 1 && butt_flag == 0 && millis() - last_press > 100) {
    butt_flag = 1;
    digitalWrite(A2,1);
    Serial.println("Button pressed");
    digitalWrite(4, 0);
    last_press = millis();
    timer();
  }
  if (butt2 == 0 && butt == 0 && butt_flag == 1) {
    digitalWrite(4,1);
    butt_flag = 0;
    Serial.println("Button released");
  }
}


void timer() {
 while (millis()- last_press < 4000) {
  butt = !digitalRead(3); 
  butt2 = !digitalRead(2);
  if (butt == 1 && butt2 ==1 )
  digitalWrite(A1,1);
  else break;
  
 }
 digitalWrite(A1,0);
 digitalWrite(4,1);
 digitalWrite(A2, LOW);
}
