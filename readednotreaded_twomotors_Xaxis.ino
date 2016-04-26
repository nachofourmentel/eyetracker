//ARRAY
#include <avr/pgmspace.h>
const PROGMEM uint16_t pixelX_Izq[]   = {  5000, 10000, 7000, 5000, 2000, 1500, 1200, 1000, 6000};
const PROGMEM uint16_t pixelX_Der[] = {  1000, 1950, 7000, 650, 1550, 1500, 5000, 2000, 6000};
long arraySize = 9;                 //726; //cantidad de fijaciones
long n = 1;
long m = 0;
//configurar estas variables según dimensiones de hoja a usar
const int minX_Izq = 0;
const int maxX_Izq = 1000;
const int minX_Der = 0;
const int maxX_Der = 1000;
float f = 7;//con guias lineales 13.5
long posX_Izq = 0; //Pasos convertidos a partir de la variable en X
long posX_Der = 0; //Pasos convertidos a partir de la variable en X
long counterX_Izq = 0;
long counterX_Der = 0;
// MOTOR 2
const int reset_Der = 2;
const int steps_Der = 0;
const int dir_Der = 1;
// MOTOR 1
const int reset_Izq = 7;
const int steps_Izq = 4;
const int dir_Izq = 3;
// STEPS
const unsigned long stepsMotor = 1000;          // 160000;    //220000 to 2 meters aprox.   //1000 pasos @ 650 de velocity equivalen a ->
const unsigned long stepsMotorErase = 800;      // Pasos de borrado
// THRS, TIMERS & SPEEDS
const int velocity =  650;                      //maxima 650
const int velocityErase = 1000;                 // velocity particular para el Erase (mas lento)
const int timer = 100;                          // timer
const int threshold =   8;
// Fines de carrera
int sensorValueA0;
int sensorValueA1;
int sensorValueA2;
int sensorValueA3;
int valEndIzquierda;
int valEndDerecha;
//FLAGS TRIGGERS
int flag;
int FLAG   = 0;
int FLAG_2 = 0;
int FLAG_3;
int FLAG_4;
int flagFindZero = HIGH;                        //si pongo LOW evita buscar el cero
int flagEndX_1 = LOW;
int flagEndX_2 = LOW;
// Leds usos multiples
const int LED_1 = 10;
const int LED_2 = 11;
const int LED_3 = 12;
const int LED_4 = 13;

// SETTINGS
void setup() {
  //pinModes
  pinMode(reset_Izq, OUTPUT);
  pinMode(steps_Izq, OUTPUT);
  pinMode(dir_Izq, OUTPUT);
  pinMode(reset_Der, OUTPUT);
  pinMode(steps_Der, OUTPUT);
  pinMode(dir_Der, OUTPUT);
  // LEDS
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
  digitalWrite(LED_4, LOW);
}

void loop() {
  if (flagFindZero == HIGH) {
    findZero();
  }
  borrar();
}


void findZero() {
  sensorValueA0 = analogRead(A0);   //PUENTE          - IZQ a DER     [IZQ A DER]
  sensorValueA1 = analogRead(A1);   //PUENTE          - DER a IZQ     [DER A IZQ]
  sensorValueA2 = analogRead(A2);   //Fin de carrera  - IZQ a DER     [EXTREMO IZQUIERDO]
  sensorValueA3 = analogRead(A3);   //Fin de carrera  - DER a IZQ     [EXTREMO DERECHO]
 
  //No quedan frenados y funciona trabado.
  //FIN DE CARRERA EJE X. IZQUIERDA
  if (sensorValueA0 >  threshold)     {
    turnOn();
    left();
  }
  if (sensorValueA0 <  threshold)     {
    flagEndX_1  = HIGH;
    turnOff();
  }
  //FIN DE CARRERA EJE X. DERECHA
  if (sensorValueA2 >  threshold)   {
    turnOn_2();
    left_2();
  }
  if (sensorValueA2 <  threshold)   {
    flagEndX_2 = HIGH;
    turnOff_2();
  }
  //IF BOTH ARE ON X= 0
  if (flagEndX_1   == HIGH)   {
    digitalWrite(LED_1, HIGH);
  }   else {
    digitalWrite(LED_1, LOW);
  }
  if (flagEndX_2 == HIGH)   {
    digitalWrite(LED_2, HIGH);
  } else {
    digitalWrite(LED_2, LOW);
  }
  if ((flagEndX_1 == HIGH) && (flagEndX_2 == HIGH))  {
    flagFindZero = LOW;
    delay(2000);
    digitalWrite(LED_1, LOW);
    delay(timer);
    digitalWrite(LED_1, HIGH);
    delay(timer);
    digitalWrite(LED_2, LOW);
    delay(timer);
    digitalWrite(LED_2, HIGH);
    delay(timer);
  }
}
void borrar() {
  if (flagFindZero == LOW) {
     arrayRead();
    //secuencia de encendido()
    digitalWrite(reset_Izq, HIGH);
    digitalWrite(reset_Der, HIGH);
    flag = HIGH;
    //movimiento de motores en X Y x2
    if (flag == HIGH) {
      if (posX_Izq > 0) {//hacia la izquierda
         valEndIzquierda = analogRead(A0);      //LÍMITES MECÁNICOS. leo el sensor
          if (valEndIzquierda < threshold) {    //si llega al sensor
          posX_Izq = 0;                             // cree que llegó al punto
          counterX_Izq= posX_Izq;
          } 
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

      if (posX_Der > 0) {                         //hacia abajo
        digitalWrite(dir_Der, LOW);
        if (counterX_Der < posX_Der) {
          moveMotor(steps_Der, velocity);
          counterX_Der++;
        }
      }
      else if (posX_Der < 0) {                         //hacia arriba
        valEndDerecha = analogRead(A2);             //LÍMITES MECÁNICOS. leo el sensor
          if (valEndDerecha < threshold) {          //si llega al sensor
           posX_Der = 0;                              // cree que llegó al punto
           counterX_Der = posX_Der;
          }  
        digitalWrite(dir_Der, HIGH);
        if (counterX_Der < (-posX_Der)) {
          moveMotor(steps_Der, velocity);
          counterX_Der++;
        }
      }
    }
    if (counterX_Izq == abs(posX_Izq) && counterX_Der == abs(posX_Der)) {
      eraseMovement();                                 //marco la fijacion
      counterX_Izq = 0;
      counterX_Der = 0;
      m = n;
      n++;                                            //avanzo una posición en el array
      if (n == arraySize - 1) {
        for (int i = 0; i < 3; i++) {                 //probando que llegó
          eraseMovement();
        }
        n = 1;
        m = 0;
        flagFindZero = HIGH;                          //faltaba agregar esto :)
        flagEndX_1 = LOW;
        flagEndX_2 = LOW;
        findZero();
      }
      arrayRead();                                    //busca una nueva posición
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
    while ( posX_Izq < minX_Izq || posX_Izq > maxX_Izq) {                             //si posX se sale de lo límites
    n++;                                                            //avanzo una posición
    posX_Izq = pgm_read_word_near(pixelX_Izq + n);
    digitalWrite(LED_1, HIGH);
    delay(200);
    digitalWrite(LED_1, LOW);
  }
  
  posX_Izq = pgm_read_word_near(pixelX_Izq + n);                             //leo nueva posición en X
  posX_Izq = (posX_Izq - pgm_read_word_near(pixelX_Izq + m)) * f;                //posX = cantidad de pasos de motor en "x" que debe efectuar para ir a destino
}
void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}
void eraseMovement() {  ///HAY QUE HACER UNO PARA MOTOR DERECHO
  digitalWrite(dir_Izq, HIGH);
  delay(1000);
  eraserZDown();
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase();
  }
  digitalWrite(dir_Izq, LOW);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase();
  }
  digitalWrite(dir_Izq, HIGH);
  eraserZUp();
}
void eraserZDown(){/*MOVIMIENTO EN Z DEL ERASER*/}
void eraserZUp(){/*MOVIMIENTO EN Z DEL ERASER*/}
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
  moveMotor(steps_Izq, velocity);
}
void left_2() {
  digitalWrite(dir_Der, LOW);
  moveMotor(steps_Der, velocity);
}
void functionMoveErase() {
  digitalWrite(steps_Izq, HIGH);
  delayMicroseconds(velocityErase);
  digitalWrite(steps_Izq, LOW);
  delayMicroseconds(velocityErase);
}
void functionMove() {
  digitalWrite(steps_Izq, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps_Izq, LOW);
  delayMicroseconds(velocity);
}
void functionMove_2() {
  digitalWrite(steps_Der, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps_Der, LOW);
  delayMicroseconds(velocity);
}
void turnOff()  {
  digitalWrite(reset_Izq, LOW)   ;
}
void turnOff_2() {
  digitalWrite(reset_Der, LOW)  ;
}
void turnOn()   {
  digitalWrite(reset_Izq, HIGH)  ;
}
void turnOn_2() {
  digitalWrite(reset_Der, HIGH);
}
