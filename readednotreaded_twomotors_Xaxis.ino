//ARRAY
#include <avr/pgmspace.h>
const PROGMEM uint16_t pixelX[]   = {  5000, 10000, 7000, 5000, 2000, 1500, 1200, 1000, 6000};
const PROGMEM uint16_t pixelX_2[] = {  1000, 1950, 7000, 650, 1550, 1500, 5000, 2000, 6000};
long arraySize = 9;                 //726; //cantidad de fijaciones
long n = 1;
long m = 0;
//configurar estas variables según dimensiones de hoja a usar
const int minX = 0;
const int maxX = 1000;
const int minX_2 = 0;
const int maxX_2 = 1000;
float f = 7;//con guias lineales 13.5
long posX = 0; //Pasos convertidos a partir de la variable en X
long posX_2 = 0; //Pasos convertidos a partir de la variable en X
long counterX = 0;
long counterX_2 = 0;
// MOTOR 2
const int reset_2 = 7;
const int steps_2 = 8;
const int dir_2 = 9;
// MOTOR 1
const int reset = 2;
const int steps = 3;
const int dir = 4;
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
  // Check sensors.
  //Serial.begin(9600);
  //pinModes
  pinMode(reset, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
  pinMode(reset_2, OUTPUT);
  pinMode(steps_2, OUTPUT);
  pinMode(dir_2, OUTPUT);
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
    digitalWrite(reset, HIGH);
    digitalWrite(reset_2, HIGH);
    flag = HIGH;
    //movimiento de motores en X Y x2
    if (flag == HIGH) {
      if (posX > 0) {//hacia la izquierda
         valEndIzquierda = analogRead(A0);      //LÍMITES MECÁNICOS. leo el sensor
          if (valEndIzquierda < threshold) {    //si llega al sensor
          posX = 0;                             // cree que llegó al punto
          counterX= posX;
          } 
        digitalWrite(dir, LOW);
        if (counterX < posX) {
          moveMotor(steps, velocity);           //Move
          counterX++;
        }
      }
      else if (posX < 0) {
        digitalWrite(dir, HIGH);
        if (counterX < (-posX)) {
          moveMotor(steps, velocity);
          counterX++;
        }
      }

      if (posX_2 > 0) {                         //hacia abajo
        digitalWrite(dir_2, LOW);
        if (counterX_2 < posX_2) {
          moveMotor(steps_2, velocity);
          counterX_2++;
        }
      }
      else if (posX_2 < 0) {                         //hacia arriba
        valEndDerecha = analogRead(A2);             //LÍMITES MECÁNICOS. leo el sensor
          if (valEndDerecha < threshold) {          //si llega al sensor
           posX_2 = 0;                              // cree que llegó al punto
           counterX_2 = posX_2;
          }  
        digitalWrite(dir_2, HIGH);
        if (counterX_2 < (-posX_2)) {
          moveMotor(steps_2, velocity);
          counterX_2++;
        }
      }
    }
    if (counterX == abs(posX) && counterX_2 == abs(posX_2)) {
      eraseMovement();                                 //marco la fijacion
      counterX = 0;
      counterX_2 = 0;
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
   posX = pgm_read_word_near(pixelX + n);                            //leo nueva cordenada en X
    while ( posX < minX || posX > maxX) {                             //si posX se sale de lo límites
    n++;                                                            //avanzo una posición
    posX = pgm_read_word_near(pixelX + n);
    digitalWrite(LED_1, HIGH);
    delay(200);
    digitalWrite(LED_1, LOW);
  }
  
  posX = pgm_read_word_near(pixelX + n);                             //leo nueva posición en X
  posX = (posX - pgm_read_word_near(pixelX + m)) * f;                //posX = cantidad de pasos de motor en "x" que debe efectuar para ir a destino
}
void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}
void eraseMovement() {
  digitalWrite(dir, HIGH);
  delay(1000);
  eraserZDown();
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase();
  }
  digitalWrite(dir, LOW);
  for (unsigned long i = 0; i < stepsMotorErase; i++) {
    functionMoveErase();
  }
  digitalWrite(dir, HIGH);
  eraserZUp();
}
void eraserZDown(){/*MOVIMIENTO EN Z DEL ERASER*/}
void eraserZUp(){/*MOVIMIENTO EN Z DEL ERASER*/}
void right() {
  digitalWrite(dir, HIGH);
  moveMotor(steps, velocity);
}
void right_2() {
  digitalWrite(dir_2, HIGH);
  moveMotor(steps_2, velocity);
}
void left() {
  digitalWrite(dir, LOW);
  moveMotor(steps, velocity);
}
void left_2() {
  digitalWrite(dir_2, LOW);
  moveMotor(steps_2, velocity);
}
void functionMoveErase() {
  digitalWrite(steps, HIGH);
  delayMicroseconds(velocityErase);
  digitalWrite(steps, LOW);
  delayMicroseconds(velocityErase);
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
void turnOff()  {
  digitalWrite(reset, LOW)   ;
}
void turnOff_2() {
  digitalWrite(reset_2, LOW)  ;
}
void turnOn()   {
  digitalWrite(reset, HIGH)  ;
}
void turnOn_2() {
  digitalWrite(reset_2, HIGH);
}
