/*
 M1 = Red tape - opens and closes the "arm"
 M2 = Beige tape - opens and closes the "elbow" 
 M3 = Yellow tape - rotates "wrist", its the left motor if looking from the front
 M4 = Green tape - rotates "wrist", the right motor when looking from the front
 M5 = Blue tape - opens and shuts "hand"
 M6 = Broun tape - rotation of entire "arm"

 shift register 1 = M3 & M4
 shift register 2 = M5 & M6
 shift register 3 = M1 & M2
*/

// ------- joystick -------

const int SW_pin = A2; // digital pin connected to switch output
const int X_pin = A0; // analog pin connected to X output
const int Y_pin = A1; // analog pin connected to Y output 

// --------- shift regiser 1 ---------

//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

// --------- shift regiser 2 ---------

//Pin connected to ST_CP of 74HC595
int latchPin2 = 2;
////Pin connected to DS of 74HC595
int dataPin2 = 3;

// --------- shift regiser 2 ---------

//Pin connected to ST_CP of 74HC595
int latchPin3 = 4;
////Pin connected to DS of 74HC595
int dataPin3 = 7;

// speed
const int milDel = 30;

void setup() {
  
  // ------ Joy Stick ------
  
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);

  // ------ Shift Register 1 ------

  pinMode(clockPin, OUTPUT);

  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT); 

  // ------ Shift Register 2 ------
  
  pinMode(latchPin2, OUTPUT);
  pinMode(dataPin2, OUTPUT);

  // ------ Shift Register 3 ------
  
  pinMode(latchPin3, OUTPUT);
  pinMode(dataPin3, OUTPUT);
}

void loop() {

  // ----- joystick serial -----
  
  Serial.print("Switch:  ");
  Serial.print(digitalRead(SW_pin));
  Serial.print("\n");
  Serial.print("X-axis: ");
  Serial.print(analogRead(X_pin));
  Serial.print("\n");
  Serial.print("Y-axis: ");
  Serial.println(analogRead(Y_pin));
  Serial.print("\n\n");
  delay(500);

  /*

 while(analogRead(X_pin) < 300){
  
  Serial.print("x<");
  openM1();
 }
 
 while(analogRead(X_pin) > 700){
  Serial.print("x>");
  closeM1();
 }
 
 while(analogRead(Y_pin) < 300){
  Serial.print("y<");
  openM2();
 }
 
 while(analogRead(Y_pin) > 700){
  Serial.print("y>");
  closeM2();
 }
*/

 while(analogRead(X_pin) < 300){
  
  Serial.print("x<");
  openM3();
  //closeM1RotM2();
 }
 
 while(analogRead(X_pin) > 700){
  Serial.print("x>");
  closeM3();
  //RotM1closeM2();
 }
 
 while(analogRead(Y_pin) < 300){
  Serial.print("y<");
  //antiM3clockM4();
  //antiM5clockM6();
  openM4();
 }
 
 while(analogRead(Y_pin) > 700){
  Serial.print("y>");
  //clockM3antiM4();
  //clockM5antiM6();
  closeM4();
 }
 
 /*
 // ----- M5 and M6 joystick ------
 while(analogRead(X_pin) < 300){
  
  Serial.print("x<");
  openM5();
  //closeM1RotM2();
 }
 
 while(analogRead(X_pin) > 700){
  Serial.print("x>");
  closeM5();
  //RotM1closeM2();
 }
 
 while(analogRead(Y_pin) < 300){
  Serial.print("y<");
  //antiM3clockM4();
  //antiM5clockM6();
  openM6();
 }
 
 while(analogRead(Y_pin) > 700){
  Serial.print("y>");
  //clockM3antiM4();
  //clockM5antiM6();
  closeM6();
 }
*/
}

// ----- Shift Register 1 -----
// ----- M3 -----

// M3 = Yellow tape - rotates wrist, its the left motor if looking from the front
void openM3(){
  
  for (int numberToDisplay = 1; numberToDisplay <= 8; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}
void closeM3(){
  
  for (int numberToDisplay = 8; numberToDisplay >= 1; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}

// ----- M4 -----

// M4 = Green tape - rotates wrist, the right motor when looking from the front
void openM4(){
  
  for (int numberToDisplay = 16; numberToDisplay <= 128; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}
void closeM4(){
  
  for (int numberToDisplay = 128; numberToDisplay >= 16; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}

void antiM3clockM4(){
  int j = 128;
  for (int numberToDisplay = 8; numberToDisplay >= 1; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay + j);  
    j = j / 2;
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}

void clockM3antiM4(){
  int j = 16;
  for (int numberToDisplay = 1; numberToDisplay <= 8; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, MSBFIRST, numberToDisplay + j);  
    j = j * 2;
    digitalWrite(latchPin, HIGH);
    delay(milDel);
  }
}

// ------ Shift Register 2 ------
// ----- M5 -----

// M5 = opens and shuts "hand"
void openM5(){
  
  for (int numberToDisplay = 1; numberToDisplay <= 8; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}
void closeM5(){
  
  for (int numberToDisplay = 8; numberToDisplay >= 1; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}

// ----- M6 -----

// M6 = rotation of entire "arm"
void openM6(){
  
  for (int numberToDisplay = 16; numberToDisplay <= 128; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}
void closeM6(){
  
  for (int numberToDisplay = 128; numberToDisplay >= 16; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}

// uses sift egister to ...
void antiM5clockM6(){
  
  int j = 128;
  for (int numberToDisplay = 8; numberToDisplay >= 1; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay + j);  
    j = j / 2;
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}

void clockM5antiM6(){
  int j = 16;
  for (int numberToDisplay = 1; numberToDisplay <= 8; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin2, LOW);
    shiftOut(dataPin2, clockPin, MSBFIRST, numberToDisplay + j);  
    j = j * 2;
    digitalWrite(latchPin2, HIGH);
    delay(milDel);
  }
}

// ----- Shift Register 3 -----
// ----- M1 -----

// M1 = Red tape - opens and closes the "arm"
void openM1(){
  
  for (int numberToDisplay = 1; numberToDisplay <= 8; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin3, HIGH);
    delay(milDel);
  }
}
void closeM1(){
  
  for (int numberToDisplay = 8; numberToDisplay >= 1; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin3, HIGH);
    delay(milDel);
  }
}

// ----- M2 -----

// M2 = beige tape - opens and closes the "elbow" 
void openM2(){
  
  for (int numberToDisplay = 16; numberToDisplay <= 128; numberToDisplay = numberToDisplay * 2) {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin, MSBFIRST, numberToDisplay);  
    digitalWrite(latchPin3, HIGH);
    delay(milDel);
  }
}
void closeM2(){
  
  for (int numberToDisplay = 128; numberToDisplay >= 16; numberToDisplay = numberToDisplay / 2) {
    digitalWrite(latchPin3, LOW);
    shiftOut(dataPin3, clockPin, MSBFIRST, numberToDisplay);
    digitalWrite(latchPin3, HIGH);
    delay(milDel);
  }
}

void oneStep(int output, int t){
  digitalWrite(output,HIGH);
  delay(t);
  digitalWrite(output,LOW);
  delay(t);
}
