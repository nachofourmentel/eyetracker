const int reset = 2;
const int steps = 3;
const int dir = 4;

const unsigned long stepsMotor = 160000; //220000 to 2 meters aprox.

const int velocity = 650; // 650 is the fastest

const int LED = 13;

void setup() {
  pinMode(reset, OUTPUT);
  pinMode(steps, OUTPUT);
  pinMode(dir, OUTPUT);

  digitalWrite(reset, HIGH);

  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
}

void loop() {
  moveMotor();
}

void moveMotor() {
  //left();
  //delay(4000);
  right();
  //delay(4000);
}

void right() {
  digitalWrite(dir, HIGH);
  digitalWrite(LED, HIGH);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove();
  }
}

void left() {
  digitalWrite(dir, LOW);
  digitalWrite(LED, LOW);
  for (unsigned long i = 0; i < stepsMotor; i++) {
    functionMove();
  }
}

void functionMove() {
  digitalWrite(steps, HIGH);
  delayMicroseconds(velocity);
  digitalWrite(steps, LOW);
  delayMicroseconds(velocity);
}
