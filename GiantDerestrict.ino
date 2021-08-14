// wheel 700c = 622 diameter - 622 * 3.14 /1000 = 1.953 it is the distance for each wheel turn

const int reedSwitch = 2;         // Declaring pin for reed switch to be used. Pin 2 or 3 must be used for the reed switch on the Uno
const int electroMagnet = 3;      // ElectroMagnet

const float wheelLong = 1.953;   // Wheel Long when 700C

unsigned long printTime;                    // declaring the total time until the next trip on the reed switch variable
float speed;                      // declaring the Speed variable
unsigned long timer;                        // declaring the timer to calculate the total time variable
unsigned long lastCurrentTime;
boolean lightOn;

void setup(){
  Serial.begin(9600);                 // Start serial monitor after a few seconds. Mainly for testing code to get it to work.
   
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);    //Begins the count of seconds when the reed switch in pin 2 is set off
  pinMode(reedSwitch, INPUT_PULLUP);                         // Sets the reed switch to be an input
  pinMode(electroMagnet, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  lastCurrentTime = 0;
  timer = millis();                                                 // Sets timer to 0 seconds
  speed = 0;                                                 // sets the speed to 0 seconds
  printTime = 0;
  lastCurrentTime = millis();
  lightOn = false;
}

void isr()           
 {
  if (millis() - lastCurrentTime > 300)
  { // We report the speed to the bike
    digitalWrite(electroMagnet, HIGH);        
    delay(50);
    if (lightOn){
      digitalWrite(LED_BUILTIN, HIGH);
      lightOn = false;
    }
    else
    {
      digitalWrite(LED_BUILTIN, LOW);
      lightOn = true;
    }
    
    digitalWrite(electroMagnet, LOW);
    lastCurrentTime = millis();
  };
 }

void loop() {

  if (millis() - printTime >= 1000) {
    printTime = millis();
    // speed = ( 22 / (millis() - totalTime)*timer);
    timer = 0;                                                   // Makes the timer go back to zero
    // attachInterrupt(digitalPinToInterrupt(2), isr, RISING);             // Make the ISR loop attach back
    // Serial.print("Speed");                                              // Prints "Speed" to serial monitor. Mainly for troubleshooting.  
    // Serial.print(speed);                                                // Prints the speed to the serial monitor. Mainly for troubleshooting.
  }
}
