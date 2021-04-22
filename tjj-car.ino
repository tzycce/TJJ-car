void setup() {

  int red = 2;

  // initialize serial communication:
  Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // establish variables
  long duration, cm;
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  const int echoPin = 7;
  const int trigPin = 8;
  int red = 2;
  int speed1;
  int speed2;

  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);

  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  cm = (duration / 2) / 29.1;

  if (cm < 15) {
    digitalWrite(red, HIGH);

    if (speed1 != -50) {
      //less than 15 cm
      //motor 1


      for (int i = 128; i >= 0; i--) {
        analogWrite(10, i);
        delay(10);
      }

      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      for (int i = 0; i < 128; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //delay(10);
      //analogWrite(9, 50);
      //digitalWrite(6, LOW);
      //digitalWrite(5, HIGH);
      speed1 = -50;
      //motor 2
      //for (int i=64; i>=0; i--) {
      //analogWrite(10, i);
      //delay(10);
      //}
      //for (int i=0; i<64; i++) { analogWrite(10, i); delay(10); }
      //analogWrite(10, 50);
      //digitalWrite(4, LOW);
      //digitalWrite(3, HIGH);
    }
  }

  if (cm > 30) {
    // turn of the light
    digitalWrite(red, LOW);
    delay(10);
    if (speed1 != 50) {
      analogWrite(10, 128);

      analogWrite(9, 128);
      for (int i = 128; i >= 0; i--) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //analogWrite(9, 50);
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      for (int i = 0; i < 255; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      speed1 = 50;
      // motor 1
      //digitalWrite(6, HIGH);
      //digitalWrite(5, LOW);
      //motor 2
      //analogWrite(10, 50);
      //digitalWrite(4, HIGH);
      //digitalWrite(3, LOW);
    }
  }

  if (cm > 15 && cm < 30) {
    digitalWrite(red, LOW);
    if (speed1 != 40) {
      for (int i = 255; i >= 0; i--) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //analogWrite(9, 50);
      //between 10 and 30 cm
      //motor 1
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      speed1 = 40;
      for (int i = 0; i < 128; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //motor 2
      //analogWrite(10, 50);
      //digitalWrite(6, LOW);
      //digitalWrite(5, LOW);
      //digitalWrite(4, HIGH);
      //digitalWrite(3, LOW);

      //  for (int i=0; i<50; i++) { analogWrite(9, i); delay(100); }
    }
  }


  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(50);
}
