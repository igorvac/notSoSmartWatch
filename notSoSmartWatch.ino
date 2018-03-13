#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DS3231.h>
#include <avr/sleep.h>
#include <avr/power.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 
  B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void interruptEnable();
void sleepNow();
void turnOnLed();

DS3231 clock;
RTCDateTime dt;

const int buttonPin = 2;
boolean buttonState;


void setup()   {                
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  clock.begin();
  //clock.setDateTime(__DATE__, __TIME__);
  sleepNow();
}


void loop() {
  if (buttonState){
    for(int i = 0; i <= 10; i++){
      display.clearDisplay();
      dt = clock.getDateTime();
      clock.forceConversion();
      showTime();

      delay(1000);
    }
    buttonState = false;
    sleepNow();
  }
}

void interruptEnable() {  
  buttonState = true;

}

void showTime(){
  display.setCursor(110,0);
  display.setTextSize(1);
  display.print(int(clock.readTemperature()));
  display.drawCircle(125, 2.5, 2.5, WHITE);

  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(20,20);
  if(dt.hour < 10){
    display.print(0);
    display.print(dt.hour);
  }
  else{
    display.print(dt.hour);
  }
  display.print(":");
  if(dt.minute < 10){
    display.print(0);
    display.print(dt.minute);
  }
  else{
    display.print(dt.minute);
  }
  /*
  display.print(":");
   if(dt.second < 10){
   display.print(0);
   display.print(dt.second);
   }
   else{
   display.print(dt.second);
   }
   */
  display.setTextSize(1);
  display.setCursor(35,55);
  if(dt.day < 10){
    display.print(0);
    display.print(dt.day);
  }
  else{
    display.print(dt.day);
  }
  display.print("/");
  if(dt.month < 10){
    display.print(0);
    display.print(dt.month);
  }
  else{
    display.print(dt.month);
  }
  display.print("/");
  display.print(dt.year);

  display.drawRoundRect(10, 13, 105, 35, 10, WHITE);


  display.display();
  delay(1);
}

void sleepNow() {
  Serial.println("Dormindo... Zzz...");

  display.clearDisplay();
  display.display();
  attachInterrupt(0, interruptEnable, LOW); 
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();   
  sleep_bod_disable();
  sleep_mode();
  sleep_disable();
  power_all_enable();
  detachInterrupt(0);
  
}

//GITHUB REMINDER
//
//git pull
//git add --all
//git commit -m "put some menssage here"
//git push -u origin master






//void DrawText(float tam, int content) {
//  display.setTextSize(tam);
//  display.setTextColor(WHITE);
//  display.setCursor(0,20);
//
//  
//  display.println(content);
//  
//  display.display();
//  delay(1);
//}
//












