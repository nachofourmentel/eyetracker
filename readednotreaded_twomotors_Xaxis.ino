//ARRAY
#include <avr/pgmspace.h>
const PROGMEM uint16_t pixelX_Izq[] = {  1000, 800, 700, 600, 500, 800, 200, 500, 300};
const PROGMEM uint16_t pixelX_Der[] = {  1000, 1950, 7000, 650, 1550, 1500, 5000, 2000, 6000};
long arraySize = 9;                                                                                 //726; //cantidad de fijaciones
long n = 1;
long m = 0;
//HAY QUE MODIFICAR ESTO
const int minX_Izq = 0;
const int maxX_Izq = 2000;
const int minX_Der = 0;
const int maxX_Der = 2000;
float f = 7;                                                                                    // RECALCULAR con guias lineales 13.5
long posX_Izq = 0;                                                                              //Pasos convertidos a partir de la variable en X
long posX_Der = 0;                                                                              //Pasos convertidos a partir de la variable en X
long counterX_Izq = 0;
long counterX_Der = 0;
// MOTOR DERECHA
const int reset_Der = 2;
const int steps_Der = 0;
const int dir_Der = 1;
// MOTOR IZQUIERDA
const int reset_Izq = 7;
const int steps_Izq = 4;
const int dir_Izq = 3;
// MOTOR Z IZQUIERDA
const int reset_Z_Izquierda = 10;
const int steps_Z_Izquierda = 9;
const int dir_Z_Izquierda =  8;
// MOTOR Z DERECHA
const int reset_Z_Derecha =  13;
const int steps_Z_Derecha =  12;
const int dir_Z_Derecha =    11;
// STEPS
const unsigned long stepsMotorErase = 800;                                                      // Pasos de borrado
const unsigned long stepsZ = 1000;                                                              //Pasos del movimiento en Z
// THRS, TIMERS & SPEEDS
const int velocity =  650;
const int velocity_Izquierda =  300;                                                            //para evitar ruido al buscar cero
const int velocityErase = 1200;                                                                // velocity particular para el Erase (mas lento)
const int velocityZ = 650;                                                                     //velocity del pivot
const int timer = 100;                                                                           // timer uso general
const int threshold =   8;
// Fines de carrera
int sensorValueA0;
int sensorValueA1;
int sensorValueA2;
int sensorValueA3;
int valEndIzquierda;
int valEndDerecha;
//FLAGS TRIGGERS
int flag = LOW;
int FLAG   = 0;
int FLAG_2 = 0;
int FLAG_3;
int FLAG_4;
int flagFindZero = HIGH;                        //si pongo LOW evita buscar el cero
int flagEndX_1 = LOW;
int flagEndX_2 = LOW;
// Leds usos multiples
//const int LED_1 = A4;
//const int LED_2 = A5;
//const int LED_3 = 12;
//const int LED_4 = 13;

// SETTINGS
void setup() {
  //pinModes
  pinMode(reset_Izq, OUTPUT);
  pinMode(steps_Izq, OUTPUT);
  pinMode(dir_Izq, OUTPUT);
  pinMode(reset_Der, OUTPUT);
  pinMode(steps_Der, OUTPUT);
  pinMode(dir_Der, OUTPUT);
  pinMode(reset_Z_Izquierda, OUTPUT);
  pinMode(steps_Z_Izquierda, OUTPUT);
  pinMode(dir_Z_Izquierda, OUTPUT);
  pinMode(reset_Z_Derecha, OUTPUT);
  pinMode(steps_Z_Derecha, OUTPUT);
  pinMode(dir_Z_Derecha, OUTPUT);
  // LEDS
  //pinMode(LED_1, OUTPUT);
  //pinMode(LED_2, OUTPUT);
  //pinMode(LED_3, OUTPUT);
  //pinMode(LED_4, OUTPUT);
  //digitalWrite(LED_1, LOW);
  //digitalWrite(LED_2, LOW);
  //digitalWrite(LED_3, LOW);
  //digitalWrite(LED_4, LOW);
}

void loop() {

  if (flagFindZero == HIGH) {
    findZero();
  }
  borrar();
}


void findZero() {
  sensorValueA0 = analogRead(A0);   //PUENTE          - IZQ a DER     [IZQ A DER]
 // sensorValueA1 = analogRead(A1);   //PUENTE          - DER a IZQ     [DER A IZQ]
  sensorValueA2 = analogRead(A2);   //Fin de carrera  - IZQ a DER     [EXTREMO IZQUIERDO]
 // sensorValueA3 = analogRead(A3);   //Fin de carrera  - DER a IZQ     [EXTREMO DERECHO]

  //No quedan frenados y funciona trabado.
  //FIN DE CARRERA EJE X. IZQUIERDA
  if (sensorValueA0 >  threshold)     {
    flagEndX_1 = LOW;
    turnOn();
    left();
  }
  if (sensorValueA0 <  threshold)     {
    flagEndX_1  = HIGH;
    turnOff();
  }
  //FIN DE CARRERA EJE X. DERECHA
  if (sensorValueA2 >  threshold)   {
    flagEndX_2 = LOW;
    turnOn_2();
    left_2();
  }
  if (sensorValueA2 <  threshold)   {
    flagEndX_2 = HIGH;
    turnOff_2();
  }
//IF BOTH ARE ON X= 0
//  if (flagEndX_1   == HIGH)   {
//    digitalWrite(LED_1, HIGH);
//  }   else {
//    digitalWrite(LED_1, LOW);
//  }
//  if (flagEndX_2 == HIGH)   {
//    digitalWrite(LED_2, HIGH);
//  } else {
//    digitalWrite(LED_2, LOW);
//  }
  if ((flagEndX_1 == HIGH) && (flagEndX_2 == HIGH))  {
    flagFindZero = LOW;
//    delay(timer);                                        //JUEGO DE LEDS DE FINDZERO
//    digitalWrite(LED_1, LOW);
//    delay(timer);
//    digitalWrite(LED_1, HIGH);
//    delay(timer);
//    digitalWrite(LED_2, LOW);
//    delay(timer);
//    digitalWrite(LED_2, HIGH);
//    delay(timer);
}
}
void borrar() {
  if (flagFindZero == LOW) {
    if (flag == LOW) {
      arrayRead();
      //secuencia de encendido()
      digitalWrite(reset_Izq, HIGH);
      digitalWrite(reset_Der, HIGH);
      flag = HIGH;
    }
    //movimiento de motores en X Y x2
    if (flag == HIGH) {
      if (posX_Izq > 0) {//hacia la izquierda
        digitalWrite(dir_Izq, LOW);
        if (counterX_Izq < posX_Izq) {
          moveMotor(steps_Izq, velocity);           //Move
          counterX_Izq++;
        }
      }
      else if (posX_Izq < 0) {
        digitalWrite(dir_Izq, HIGH);
        if (counterX_Izq < (-posX_Izq)) {
          moveMotor(steps_Izq, velocity);
          counterX_Izq++;
        }
      }

      //      if (posX_Der > 0) {                         //hacia abajo
      //        digitalWrite(dir_Der, LOW);
      //        if (counterX_Der < posX_Der) {
      //          moveMotor(steps_Der, velocity);
      //          counterX_Der++;
      //        }
      //      }
      //      else if (posX_Der < 0) {                       //hacia arriba
      //        valEndDerecha = analogRead(A2);             //LÍMITES MECÁNICOS. leo el sensor
      //          if (valEndDerecha < threshold) {          //si llega al sensor
      //           posX_Der = 0;                            // cree que llegó al punto
      //           counterX_Der = posX_Der;
      //          }
      //        digitalWrite(dir_Der, HIGH);
      //        if (counterX_Der < (-posX_Der)) {
      //          moveMotor(steps_Der, velocity);
      //          counterX_Der++;
      //        }
      //      }
    }
    if (counterX_Izq == abs(posX_Izq)) {
     delay(500);
     eraserZDown(steps_Z_Izquierda, dir_Z_Izquierda, reset_Z_Izquierda);
     for (int i = 0; i < 2; i++) { eraseMovement(dir_Izq, steps_Z_Izquierda, dir_Z_Izquierda ); }     
     eraserZUp(steps_Z_Izquierda, dir_Z_Izquierda, reset_Z_Izquierda);
     counterX_Izq = 0;
     counterX_Der = 0;
     m = n;
     n++;                                                // avanzo una posición en el array
     if (n == arraySize - 1) {                           // tiene que ir -1
     n = 1;
     m = 0;
     flagEndX_1 = LOW;
     flagEndX_2 = LOW;
     flagFindZero = HIGH;  
     flag = LOW;                           
     findZero();
}
     arrayRead();                                       //  nueva lectura        
}
}
}

void arrayRead() {   //FALTA LECTURA X_2
  /*
     chequear antes de moverme si se puede ir o no a ese punto, segun límites de ancho de hoja
     si está fuera de los límites paso al siguiente punto (sin actualizar el punto anterior)
     tengo que saber mi posición actual Y hacer el calculo Y ver si está dentro de mi hoja
     si no está dentro de mi hoja n++
  */
  posX_Izq = pgm_read_word_near(pixelX_Izq + n);                            //leo nueva cordenada en X
  while ( posX_Izq < minX_Izq || posX_Izq > maxX_Izq) {                    //si posX se sale de lo límites
    n++;                                                                  //avanzo una posición
    posX_Izq = pgm_read_word_near(pixelX_Izq + n);
}
  //leo nueva posición en X
  posX_Izq = (posX_Izq - pgm_read_word_near(pixelX_Izq + m)) * f;           //posX = cantidad de pasos de motor en "x" que debe efectuar para ir a destino
}
void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}


void eraseMovement(int pinDirX, int pinStepsZ, int pinDirZ) {  
  digitalWrite(pinDirX, HIGH);
  delay(10);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase(steps_Izq, velocityErase);
  }
  digitalWrite(pinDirX, LOW);
  delay(10);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase(steps_Izq, velocityErase);
  }
  //digitalWrite(pinDirX, HIGH);
}


void eraserZDown (int pinStepsZ, int pinDirZ, int pinResetZ) {
  digitalWrite(pinResetZ, HIGH);
  digitalWrite(pinDirZ, LOW);
  for (int i = 0; i < stepsZ; i++) {
    moveMotor(pinStepsZ, velocityZ);
  }

}
void eraserZUp (int pinStepsZ, int pinDirZ, int pinResetZ) {
  digitalWrite(pinResetZ, HIGH);
  digitalWrite(pinDirZ, HIGH);
  for (int i = 0; i < stepsZ; i++) {
    moveMotor(pinStepsZ, velocityZ);
  }
}


void right() {
  digitalWrite(dir_Izq, HIGH);
  moveMotor(steps_Izq, velocity);
}
void right_2() {
  digitalWrite(dir_Der, HIGH);
  moveMotor(steps_Der, velocity);
}
void left() {
  digitalWrite(dir_Izq, LOW);
  moveMotor(steps_Izq, velocity_Izquierda);
}
void left_2() {
  digitalWrite(dir_Der, LOW);
  moveMotor(steps_Der, velocity);
}
void functionMoveErase(int pinSteps, int velocidad) {
  digitalWrite(pinSteps, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinSteps, LOW);
  delayMicroseconds(velocidad);
}
void functionMove(int pinSteps, int velocidad ) {
  digitalWrite(pinSteps, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinSteps, LOW);
  delayMicroseconds(velocidad);
}
void turnOff()  {
  digitalWrite(reset_Izq, LOW);
}
void turnOff_2() {
  digitalWrite(reset_Der, LOW);
}
void turnOn()   {
  digitalWrite(reset_Izq, HIGH);
}
void turnOn_2() {
  digitalWrite(reset_Der, HIGH);
}
