#include <Servo.h>
#include <SPI.h>

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;


Servo servos[] = {servo0, servo1, servo2, servo3, servo4, servo5};

//int misoPin = 10;
//int mosiPin = 11;
//int clkPin = 12;
//int sselPin = 13;


char buf [100];

int controlPin = 3;
int servoDelay = 10;

volatile byte pos;
volatile boolean process_it;
// variable to store the servo position

void setup() {
  Serial.begin(9600);

  SPCR |= bit (SPE);

  pinMode(MISO, OUTPUT);

  pos = 0;
  process_it = false;

  SPI.beginTransaction(SPISettings(14000000, LSBFIRST, SPI_MODE0));
  SPI.attachInterrupt();

  servo0.attach(9);
  servo1.attach(8);
  servo2.attach(7);
  servo3.attach(6);
  servo4.attach(5);
  servo5.attach(4);
}

ISR(SPI_STC_vect) {
  byte c = SPDR;
//  Serial.print("c: ");
//  Serial.println(c, BIN);
//  Serial.print("Interrupting\n");
  delay(25);
  if (pos < (sizeof(buf) - 1)) {
    buf[pos++] = c;
  }

  if (pos >= 2) {
    process_it = true;
    pos = 0;
  }
}

void loop() {
  if (process_it) {
    readInput(buf);
  }
}

unsigned int readInput(char* buf) {

  // for i in numservos
  uint16_t result = *(uint16_t*)buf;

  int servoPos = result & 511;
  int servoNumber = result >> 9;

  moveServo(servoNumber, servoPos);

  process_it = false;

}

void moveServo(int servoNumber, int servoPosition) {
  if (servoNumber == 4) {
    servos[4].write(servoPosition);
    servos[5].write(180 - servoPosition);
  } else if (servoNumber != 5) {
    servos[servoNumber].write(servoPosition);
  }
}
