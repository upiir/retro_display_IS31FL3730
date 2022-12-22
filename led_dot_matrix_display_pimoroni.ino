// simple project using the Pimoroni retro LED matrices displays to display time
// created by upir, 2022
// youtube channel: https://www.youtube.com/upir_upir
//
// FULL TUTORIAL: https://youtu.be/PBaL9w5w-2c
//
//
// Links from the video:
// Display: https://shop.pimoroni.com/products/led-dot-matrix-breakout?variant=32274405621843
// Arduino Library: https://github.com/jbkim/IS31FL3730/
// Custom character creator: https://tusindfryd.github.io/screenduino/
// Another custom character creator: https://maxpromer.github.io/LCD-Character-Creator/
// Arduino UNO: https://s.click.aliexpress.com/e/_AXDw1h
// Arduino UNO MINI: https://store.arduino.cc/products/uno-mini-le
// Arduino breadboard prototyping shield: https://s.click.aliexpress.com/e/_ApbCwx
//
// Related videos using 16x2 character display (and custom characters):
// Arduino Gauge in 11 Minutes ??? - https://youtu.be/upE17NHrdPc
// Smooth Arduino 16x2 Gauge - https://youtu.be/cx9CoGqpsfg
// 1 DISPLAY 3 SENSORS - https://youtu.be/lj_7UmM0EPY



#include <Wire.h>
#include <IS31FL3730.h> // please install this library first - https://github.com/jbkim/IS31FL3730/

#define M1 0 // right display
#define M2 1 // left display

IS31FL3730 m1; // the display

int hours = 10; // hour value
int minutes = 30; // minutes value

char hours_string[5]; // hours converted to string
char minutes_string[5]; // minutes converted to string

byte image_arrow[8] = {B00100, B01110, B10101, B00100, B00100, B00100, B00100, B00000}; // arrow image
byte image_smile[8] = {B00000, B01010, B00000, B10001, B01110, B00000, B00000, B00000}; // smile face image

byte image_digit_01[8] = {B10001, B11111, B10000, B00000, B00000, B00000, B00000, B00000}; // digits 0-9
byte image_digit_02[8] = {B11101, B10101, B10111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_03[8] = {B10001, B10101, B11111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_04[8] = {B00111, B00100, B11111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_05[8] = {B10111, B10101, B11101, B00000, B00000, B00000, B00000, B00000};
byte image_digit_06[8] = {B11111, B10101, B11101, B00000, B00000, B00000, B00000, B00000};
byte image_digit_07[8] = {B00001, B00001, B11111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_08[8] = {B11111, B10101, B11111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_09[8] = {B10111, B10101, B11111, B00000, B00000, B00000, B00000, B00000};
byte image_digit_00[8] = {B11111, B10001, B11111, B00000, B00000, B00000, B00000, B00000};

byte image_digit_M1[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000}; // two digits combined for one display
byte image_digit_M2[8] = {B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000}; // two digits combined for one display

const byte* image_digit_array[10] { // array with all 10 digits
  image_digit_00,
  image_digit_01,
  image_digit_02,
  image_digit_03,
  image_digit_04,
  image_digit_05,
  image_digit_06,
  image_digit_07,
  image_digit_08,            
  image_digit_09  
};


void setup() {

  m1.begin(0x61); // establish IIC connection to the display
  
  // set Lighting Effect Register to 10mA
  m1.set_le(0x9);

  m1.clear(); // clear the display

 }



void loop() {

  // increment minutes and hours
  minutes++;
  if (minutes >= 60) {
    minutes = 0;
    hours++;
    if (hours >= 12) {
      hours = 0;
    }  
  }

  
  // convert hours and minutes to strings with leading zeros
  sprintf(hours_string, "%02d", hours);
  sprintf(minutes_string, "%02d", minutes);  

  for (int i = 0; i < 4; i++) { // first digit, first display
    image_digit_M1[i] = image_digit_array[hours_string[0]-48][i];
  }
  for (int i = 4; i < 7; i++) { // second digit, first display
    image_digit_M1[i] = image_digit_array[hours_string[1]-48][i-4];
  }  

  for (int i = 0; i < 4; i++) { // first digit, second display
    image_digit_M2[i] = image_digit_array[minutes_string[0]-48][i];
  }
  for (int i = 4; i < 7; i++) { // second digit, second display
    image_digit_M2[i] = image_digit_array[minutes_string[1]-48][i-4];
  }    
  
  m1.set_data(M1, image_digit_M1); // draw two digits on the first display
  m1.set_data(M2, image_digit_M2); // draw two digits on the second display 

  m1.update(); // update both displays

  delay(200); // wait a while
}
