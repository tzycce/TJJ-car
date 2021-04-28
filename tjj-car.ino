//introduce global variables for the selection of loops in void 
// not using boolean because we would need three of them and writing them all correct in every scenario is a mess
int speed1 = 0; 
// are led is red so why not go with that
int red = 2;
//easier to remember for ultrasonic sensor
int echoPin = 7;
int trigPin = 8;
// distance values for rotating and backing up
int d1 = 30;
int d2 = 15;
// for the measurements
long duration, cm;

void setup() {
  
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(red, OUTPUT);
}

void loop() {
 
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
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
  //distance over 30cm -> full throttle 

    if (cm > d1) {
    // turn of the light
    digitalWrite(red, LOW);
    delay(10);
    //is already at full throttle pass this if-loop
    if (speed1 != 50) {
      // slow down the dc motors
      analogWrite(10, 128);
      analogWrite(9, 128);
      for (int i = 128; i >= 0; i--) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //choose direction and accelerate
      digitalWrite(6, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      for (int i = 0; i < 255; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //write to avoid going through previous loop again
      speed1 = 50;
     
    }
  }
  //distance measurement between 15 and 30
  if (cm > d2 && cm < d1) {
    digitalWrite(red, LOW);
    //condition to go through loop
    if (speed1 != 40) {
      //slow down the motors
      for (int i = 128; i >= 0; i--) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //choose rotation direction
      digitalWrite(6, LOW);
      digitalWrite(5, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(3, LOW);
      //write variable to avoid looping
      speed1 = 40;
      //accelerate the motors
      for (int i = 0; i < 128; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      
    }
  }

if (cm < d2) {
   //turn on the warning light
    digitalWrite(red, HIGH);
    //check if loop condition is met
    if (speed1 != -50) {
      

      //slow down the motors
      for (int i = 128; i >= 0; i--) {
        analogWrite(10, i);
        delay(10);
      }
      //choose the direction
      digitalWrite(6, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(3, HIGH);
      for (int i = 0; i < 128; i++) {
        analogWrite(9, i);
        analogWrite(10, i);
        delay(10);
      }
      //write the variable to avoid loop
      speed1 = -50;
     
    }
  }

  //print distance for testing
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  delay(50);
}
