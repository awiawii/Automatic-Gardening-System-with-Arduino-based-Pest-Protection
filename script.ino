const byte interrupt_pin = 2;
const byte buzzer = 8;
volatile byte state = LOW;
#include <Servo.h>
Servo myservo;
int pos = 0;
int pompa=13;


void setup() {
  Serial.begin(9600);    // open Serial Monitor and set baud rate
  pinMode(buzzer,OUTPUT);
  pinMode(pompa, OUTPUT);
  myservo.attach(9);
  attachInterrupt(digitalPinToInterrupt(interrupt_pin),interrupt_routine,RISING);
}
void loop() {
  int val = analogRead(0);     // sensor Aout pin connected to A0 pin of Arduino
  Serial.println(val);
  if (val > 460) {
    digitalWrite(pompa, HIGH);
  } else if (val < 350) {
    digitalWrite(pompa, LOW);
  }
  delay(1);

  if (state == HIGH) {
    digitalWrite(buzzer,HIGH);
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);   // tell servo to go to position in variable 'pos'
      delay(15);   // waits 15ms for the servo to reach the position
    }
      for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);   // tell servo to go to position in variable 'pos'
      delay(15);   // waits 15ms for the servo to reach the position
    }
      state = LOW;
      digitalWrite(buzzer,LOW);
      for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
      myservo.write(pos);   // tell servo to go to position in variable 'pos'
      delay(15);  // waits 15ms for the servo to reach the position
    }
  }
}
void interrupt_routine(){
  state = HIGH;
}
