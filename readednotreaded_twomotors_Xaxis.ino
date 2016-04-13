// MOTOR 2 
const int reset_2 = 7;
const int steps_2 = 8;
const int dir_2 = 9;
//MOTOR 1
const int reset = 2;
const int steps = 3;
const int dir = 4;
//STEPS
const unsigned long stepsMotor = 10;    // 160000;     //220000 to 2 meters aprox.
//THRS, TIMERS & SPEEDS
const int velocity = 650;   //maxima 650
const int timer = 100;      // timer
const int threshold = 5;   // thrs fin de carrera
// Fines de carrera
int sensorValueA0;
int sensorValueA1;
//flags
int FLAG = 0;
int FLAG_2;
// Leds usos multiples
const int LED = 11;
const int LED_2 = 10;
//settings
void setup() {
  // Check sensors.
  //Serial.begin(9600);
  //pinModes  
  pinMode(reset, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(reset_2, OUTPUT);
  pinMode(steps_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
 
  digitalWrite(reset, HIGH);
  digitalWrite(reset_2, HIGH);
  
  //Leds
  pinMode(LED, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(LED_2, LOW);
}

void loop() {
  //Sensor Reading
  //Serial.print(sensorValueA0 = analogRead(0));
  //Serial.print("   ;   ");
  //Serial.println(sensorValueA1 = analogRead(1));
  
  sensorValueA0 = analogRead(A0);   //Fin de carrera  - IZQ a DER
  sensorValueA1 = analogRead(A1);   //Fin de carrera  - DER a IZQ
  
  if (sensorValueA0 < threshold) {FLAG = 1;} else {FLAG = 0;}
  if (sensorValueA1 < threshold) {FLAG_2 = 1;} else {FLAG_2 = 0;}

  if (FLAG == 0 && FLAG_2 == 0) {
    right();
    delayMicroseconds(velocity);
    stopMovement_2();
}
  if (FLAG == 1) {
    stopMovement();
    delayMicroseconds(velocity);
    right_2();
  }
  if (FLAG_2 == 1) {
    stopMovement();
    delayMicroseconds(velocity);
    left_2();
  }
}

void right() {
  stopMovement_2();
  digitalWrite(dir, HIGH);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove();
  }
}

void right_2() {
  stopMovement();
  digitalWrite(dir_2, HIGH);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove_2();
  }
}
void left() {
  stopMovement_2();
  digitalWrite(dir, LOW);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove();
  }
}

void left_2() {
  stopMovement();
  digitalWrite(dir_2, LOW);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove_2();
  }
}
void functionMove() {
  digitalWrite(steps, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps, LOW);
  delayMicroseconds(velocity);
}
void functionMove_2() {
  digitalWrite(steps_2, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps_2, LOW);
  delayMicroseconds(velocity);
}
void stopMovement(){
   digitalWrite(steps, LOW);  
  }

void stopMovement_2(){
   digitalWrite(steps_2, LOW);  
  }  
