#include<Adafruit_NeoPixel.h>


// Initialize all variable and pins used
const int pingPin = 7;
long dist_in_cm, duration;
#define neopixel_pin 9
#define no_of_leds 20
// Initialize object of NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(no_of_leds, neopixel_pin, NEO_GRB + NEO_KHZ800);


//Set up Arduino
void setup() {
  strip.begin(); 
  strip.show();
}

//Main function
void loop() {
  duration=get_ping_time();          //Ultra Sonic sensor signal travel time
  dist_in_cm = TIMEtoDIST(duration); // get distance from time
  set_lights(dist_in_cm);            //Light up green, red leds & buzzer based on distance
  delay(100);
}



// This function gives time taken for Ultra Sonic signal to travel to & from object
long get_ping_time(){
  long duration;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  return duration;
}


//This function converts time taken by signal to distance
long TIMEtoDIST(long microseconds) {
  return microseconds / 29 / 2;
}


// This Function Switches on NeoPixel LEDs and buzzer based on distance
// Trigger for Buzzer is distance less than 130cms
void set_lights(float distance){
  int i=0;
  int red_leds=(330-distance)/10;
  if (distance>330) {
    for (i=0;i<20;i++){
    strip.setPixelColor(i  , 0, 255, 0);
    }
    noTone(3);
    strip.show();
    goto endoffunc;
  }
  else if (distance<130) {
    tone(3,1000,50);
    for (i=0;i<20;i++){
    strip.setPixelColor(i  , 255, 0, 0);
    }
    strip.show();
    goto endoffunc;
  }
  noTone(3);
  for (i=0;i<red_leds;i++){
    strip.setPixelColor(i  , 255, 0, 0);
  }
  strip.show();
  i=i-1;
  for (i;i<20;i++){
    strip.setPixelColor(i  , 0, 255, 0);
  }
  strip.show();
  endoffunc:
  strip.show();
}
