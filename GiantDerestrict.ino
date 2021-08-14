// wheel 700c = 622 diameter - 622 * 3.14 /1000 = 1.953 it is the distance for each wheel turn

const int reedSwitch = 2;     // Declaring pin for reed switch to be used. Pin 2 or 3 must be used for the reed switch on the Uno
const int electroMagnet = 3;  // ElectroMagnet

const float wheelLong = 1.953;  // Wheel Long when 700C

unsigned long printTime;  // declaring the total time until the next trip on the reed switch variable
float speed;              // declaring the Speed variable
unsigned long duration;   // declaring the timer to calculate the total time variable
unsigned long lastCurrentTime;
boolean lightOn;
boolean highSpeed;


void setup() {

  Serial.begin(9600);  // Start serial monitor after a few seconds. Mainly for testing code to get it to work.
  attachInterrupt(digitalPinToInterrupt(2), isr, RISING);  //Begins the count of seconds when the reed switch in pin 2 is set off
  pinMode(reedSwitch, INPUT_PULLUP);                       // Sets the reed switch to be an input
  pinMode(electroMagnet, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  lastCurrentTime = 0;
  duration = 0;
  speed = 0;
  printTime = 0;
  lastCurrentTime = millis();
  lightOn = false;
  highSpeed = false;
}

void isr() {
  // some LED activity for visual debug
  if (lightOn) {
    digitalWrite(LED_BUILTIN, HIGH);
    lightOn = false;
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    lightOn = true;
  }

  if (millis() - lastCurrentTime < 300)
    highSpeed = true;
  else
    highSpeed = false;

  if (highSpeed == false)
  {  
    // We report the speed to the bike when < 25 kmh
    digitalWrite(electroMagnet, HIGH);
    delay(10);
    digitalWrite(electroMagnet, LOW);
    lastCurrentTime = millis();
  }
  
}

void loop() {
  duration = millis() - lastCurrentTime;
  if (duration > 4000) {
    duration = 0;
    speed = 0;
  } 
  else
    speed = (wheelLong * 3.6 * 1000) / duration;


  if (millis() - printTime >= 1000) {
    printTime = millis();

    Serial.print("Speed ");  // Prints "Speed" to serial monitor. Mainly for troubleshooting.
    Serial.print(speed);
    Serial.print('\n');  // Prints the speed to the serial monitor. Mainly for troubleshooting.
  }
}
