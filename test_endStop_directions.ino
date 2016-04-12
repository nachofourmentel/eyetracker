const int reset = 2;
const int steps = 3;
const int dir = 4;

const unsigned long stepsMotor = 160000; //220000 to 2 meters aprox.

const int velocity = 650;   //maxima 650
const int timer = 100;

int sensorValueA0;
int sensorValueA1;

int FLAG = 0;

const int LED = 11;
const int LED_2 = 10;

void setup() {
  //Serial.begin(9600);
  pinMode(reset, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);
 
  digitalWrite(reset, HIGH);

  pinMode(LED, OUTPUT);
  pinMode(LED_2, OUTPUT);
  digitalWrite(LED, LOW);
  digitalWrite(LED_2, LOW);
}

void loop() {
   //Serial.print(sensorValueA0 = analogRead(0));
  //Serial.print("   ;   ");
  //Serial.println(sensorValueA1 = analogRead(1));
  sensorValueA0 = analogRead(A0);
  sensorValueA1 = analogRead(A1);
  
  if (sensorValueA0 < 10 && sensorValueA1 > 30) {
   FLAG = 1;
 }
  if (sensorValueA1 < 10 && sensorValueA0 > 30) {
   FLAG = 0;
}
  if (FLAG == 1) {
    right();
  }
  if (FLAG == 0) {
    left();
  }
}

void right() {
  digitalWrite(dir, HIGH);
  digitalWrite(LED, HIGH);
  digitalWrite(LED_2, LOW);
  for (unsigned long i = 0; i < 200; i++) {
    functionMove();
  }
}

void left() {
  digitalWrite(dir, LOW);
  digitalWrite(LED, LOW);
  digitalWrite(LED_2, HIGH);
  for (unsigned long i = 0; i < 200; i++) {
    functionMove();
  }
}

void functionMove() {
  digitalWrite(steps, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps, LOW);
  delayMicroseconds(velocity);
}
