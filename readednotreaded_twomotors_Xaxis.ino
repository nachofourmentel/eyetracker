// MOTOR 2 
const int reset_2 = 7;
const int steps_2 = 8;
const int dir_2 = 9;
// MOTOR 1
const int reset = 2;
const int steps = 3;
const int dir = 4;
// STEPS
const unsigned long stepsMotor = 3000;          // 160000;    //220000 to 2 meters aprox.
const unsigned long stepsErase = 3;            //
const unsigned long stepsMotorErase = 800;    // Pasos de borraado  
// THRS, TIMERS & SPEEDS 
const int velocity = 650;                    //maxima 650
//const int velocityErase = 650;             // velocity particular para el Erase
const int timer = 10;                        // timer
const int threshold = 5;                     // thrs fin de carrera
// Fines de carrera
int sensorValueA0;
int sensorValueA1;
int sensorValueA2;
int sensorValueA3;
//flags
int FLAG   = 0;
int FLAG_2 = 0;
int FLAG_3;
int FLAG_4;
// Leds usos multiples
const int LED = 11;
const int LED_2 = 10;

// SETTINGS
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
//encendido 
 turnOn();
 turnOn_2();
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
  
  sensorValueA0 = analogRead(A0);   //Fin de carrera  - IZQ a DER     [CENTRO] 
  sensorValueA1 = analogRead(A1);   //Fin de carrera  - DER a IZQ     [CENTRO]
  sensorValueA2 = analogRead(A2);   //Fin de carrera  - IZQ a DER [EXTREMO IZQUIERDO]
  sensorValueA3 = analogRead(A3);   //Fin de carrera  - DER a IZQ [EXTREMO DERECHO]
  
  if (sensorValueA0 < threshold) {FLAG = 1;}   else {FLAG   = 0;}
  if (sensorValueA1 < threshold) {FLAG_2 = 1;} else {FLAG_2 = 0;}
  if (sensorValueA2 < threshold) {FLAG_3 = 1;} else {FLAG_3 = 0;}
  if (sensorValueA3 < threshold) {FLAG_4 = 1;} else {FLAG_4 = 0;}

//  ARRANQUE.
  if (FLAG == 0 && FLAG_2 == 0) {
    right();
    erase();
    }  
//  // Fin de carrera DERECHO. 
//  if (FLAG_4 == 1) {
//    turnOff();
//    turnOff_2();
//  }
//  // Fin de carrera IZQUIERDO. 
//  if (FLAG_3 == 1){
//    turnOff();
//    turnOff_2();
//  }
//  // Si llega al centro . IZQ - DER // OK
//  if (FLAG == 1 && FLAG_2 == 0)  {
//    turnOff();
//    turnOn_2();
//    right_2();
//  }
//  // Si llega al centro . DER - IZQ // OK
//  if (FLAG_2 == 1 && FLAG == 0) {
//    turnOff_2();
//    turnOn();
//    left();    
//    } 
}

void right() {
  digitalWrite(dir, HIGH);
  for (unsigned long i = 0; i < stepsMotor; i++) {functionMove();}
}
void borrar_right() {
  digitalWrite(dir, HIGH);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {functionMove();}
}
void borrar_left() {
  digitalWrite(dir, LOW);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {functionMove();}
}
void right_2() {
  digitalWrite(dir_2, HIGH);
  for (unsigned long i = 0; i < stepsMotor; i++) {functionMove_2();}
}
void left() {
  digitalWrite(dir, LOW);
  for (unsigned long i = 0; i < stepsMotor; i++) {functionMove();}
}
void left_2() {
  digitalWrite(dir_2, LOW);
  for (unsigned long i = 0; i < stepsMotor; i++) {functionMove_2();}
}
void functionMove_2() {
  digitalWrite(steps_2, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps_2, LOW);
  delayMicroseconds(velocity);
}
void erase() {
  for (int i = 0; i < stepsErase; i++) {
    borrar_left();
    delayMicroseconds(500);
    borrar_right();    
    delayMicroseconds(500);
  }
  }
void turnOff()  {digitalWrite(reset, LOW)   ;} 
void turnOff_2(){digitalWrite(reset_2,LOW)  ;}
void turnOn()   {digitalWrite(reset, HIGH)  ;} 
void turnOn_2() {digitalWrite(reset_2, HIGH);}     
    
