//pins
const int echoPin = 7;
const int trigPin = 8;
int red = 2;

void setup() {
  // initialize serial communication:
   Serial.begin(9600);
   pinMode(red,OUTPUT);
   pinMode(6,OUTPUT);
   pinMode(5,OUTPUT);
   pinMode(4,OUTPUT);
   pinMode(3,OUTPUT);
}

void loop() {
  // establish variables 
  long duration, cm;
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
  cm = (duration/2) /29.1;
  
     //distance less than 15cm 
  if(cm < 15){
  
	// turn on the light
	digitalWrite(red,HIGH);
	
	// reverse direction
	//motor 1 
  	digitalWrite(6, LOW);
  	digitalWrite(5, HIGH);
  	//motor 2
  	digitalWrite(4, LOW);
  	digitalWrite(3, HIGH);
	}
	
    	//distance greater than 30cm
     if(cm>30){
	// turn of the light
	digitalWrite(red,LOW);
	      
        //turn the motors normally    
        // motor 1 
  	digitalWrite(6, HIGH);
  	digitalWrite(5, LOW);
  	//motor 2
  	digitalWrite(4, HIGH);
  	digitalWrite(3, LOW);
      
	}
	
	//distance between 15 and 30 cm
    if(cm>15 && cm<30){
  	
  	//turn off the light
	digitalWrite(red,LOW);
	
	// only turn motor 2 to rotate   
    	//motor 1 
  	digitalWrite(6, LOW);
  	digitalWrite(5, LOW);
   	//motor 2
  	digitalWrite(4, HIGH);
  	digitalWrite(3, LOW);
          
	}

    //print distance to serial		
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
   
}
