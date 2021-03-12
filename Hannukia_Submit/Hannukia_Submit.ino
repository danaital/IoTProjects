/*
  BLYNK Hannukia
  The Hannukia is the symbol of the jewish holiday "Hannukkah"; 
  We want to create this iconic symbol using CPX + the "BLYNK" app
  
  NOTE: Before starting to run this code you need to switch few params:
  1. ssid -> to your network name
  2. pass -> to the network's password if there is no password use ""
  3. auth -> to the BLYNK auth' code sent by the app.

  The BLYNK Hannukia can control the nubmer of Candles and color (if you want).
  Futhermore it emulates a way some candles burn.
  
  The BLYNK Hannukia has 2 main modes:
  - Non Active mode - the Hannukia is not active
  - Active mode - The Hannukia is Active

  Inside Active mode there are 3 modes:
  - regular mode - all the candles have the same color and you control them with 3 sliders that control the red value , green value and blue value. 
  - random mode - all the candles have the same color which is randomized.
  - party mode - each candle have different color which is randomized. you cannot access party mode if random mode is not activated. 
  
  The APP:
  In order for you this code running you need to create 4 sliders and 3 button and connect them in order to the virtual pins mentioned
  - V0 - Number of candles  , Comp' => Slider : min value: 0, max value : 8 . 
  - V1 - Red Value          , Comp' => Slider : min value: 0, max value : 255 . 
  - V2 - Green Value        , Comp' => Slider : min value: 0, max value : 255 . 
  - V3 - Blue Value         , Comp' => Slider : min value: 0, max value : 255 .
  - V4 - Active Hannukia    , Comp' => Button : min value: 0, max value : 1 .
  - V5 - Active Random Mode , Comp' => Slider : min value: 0, max value : 1 .   
  - V6 - Active Party Mode  , Comp' => Slider : min value: 0, max value : 1 .   

  Example view : https://docs.google.com/document/d/19hRhpKcV3GGHJUQUoXSiNOQIDg2T1Dx5Pt7ehsVUSzg/edit?usp=sharing
  Video link   : https://drive.google.com/file/d/1bLh_GUMvl7v8UetXPadX1etg8oJbYmkc/view?usp=sharing
  Created By   :
    Tal Danai  
*/
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <Adafruit_CircuitPlayground.h> 

// setting up BLYNK + WiFi  //
char ssid[] = "****";                              //enter your WIFI name (SSID) here 
char pass[] = "****" ;                             //enter your WIFI password here 
char auth[] = "****";                              // BLYNK Auth' code -> change it

#define EspSerial Serial1
#define ESP8266_BAUD 9600

ESP8266 wifi(&EspSerial);


// Setup Candles
uint8_t ner_led[] = {9, 0, 1, 2, 3, 4, 5, 6, 7}; // 0-7 regular candles, 9 shamash
uint8_t candles;// the number of candles given 

// Setup brightness factors 
uint8_t brightness_factor = 1, brightness_factor_sign = -1;

// Setup colors
uint8_t red = 0, blue = 0, green = 0;    // regular mode 
uint8_t rand_red, rand_blue, rand_green; // random mode
uint8_t randomized_color_candles[9][3];  // party mode

// Setup buttons
uint8_t isRandomColor, wasRandom=0 , isActive, isOn =0, isPartyMode, wasPartyMode = 0;// set up the other modes (Active, Random, Party)
bool isInit = true;

void setup() {
  CircuitPlayground.begin();
  SerialUSB.begin(9600);
  EspSerial.begin(ESP8266_BAUD);
  delay(100);
  Blynk.begin(auth, wifi, ssid, pass);
}
BLYNK_WRITE(V0){
  candles = param.asInt(); // assigning incoming value from pin V0 to a variable
}
BLYNK_WRITE(V1){
  red  = param.asInt(); // assigning incoming value from pin V1 to a variable
}
BLYNK_WRITE(V2){
  green = param.asInt(); // assigning incoming value from pin V2 to a variable
}
BLYNK_WRITE(V3){
  blue = param.asInt(); // assigning incoming value from pin V3 to a variable
}
BLYNK_WRITE(V4){
  isActive = param.asInt(); // assigning incoming value from pin V4 to a variable
}
BLYNK_WRITE(V5){
  isRandomColor = param.asInt(); // assigning incoming value from pin V5 to a variable
}
BLYNK_WRITE(V6){
  isPartyMode = param.asInt(); // assigning incoming value from pin V5 to a variable
}

void loop() {
        Blynk.run(); // run BLYNK
        if (isActive == 1) {
            // if Hanuukia is activated
            for (int i = 0; i < sizeof(ner_led); i++) {
                // if is part of the candles we want, Shamash is the first two indexes
                if (i <= candles) {
                    // if we want randomized colors / party mode  
                    if (isRandomColor == 1) {
                        red = 0, blue = 0, green = 0;// reset the inputs
                        // if we changed this right now random 
                        if (isPartyMode == 1 && wasPartyMode == 0) {
                          // check party mode 
                            for (int j = 0; j <= sizeof(ner_led); j++) {
                                // random color for each led
                                randomized_color_candles[j][0] = random(0, 255);
                                randomized_color_candles[j][1] = random(0, 255);
                                randomized_color_candles[j][2] = random(0, 255);
                            }
                            wasRandom = 0;
                            wasPartyMode = 1;
                        } else {
                            if (wasRandom == 0 && isPartyMode == 0) {
                                // fixed color for all leds random mode 
                                rand_red = random(0, 255);
                                rand_green = random(0, 255);
                                rand_blue = random(0, 255);
                                wasRandom = 1;
                                wasPartyMode = 0;
                            }
                        }
                        if (isPartyMode == 0) {
                            // stay with fixed randomized lights for all leds 
                            CircuitPlayground.setPixelColor(ner_led[i], rand_red / brightness_factor, rand_green / brightness_factor, rand_blue / brightness_factor);
                            wasPartyMode = 0;
                            wasRandom = 0;
                        } else {
                            // random color for each led
                            CircuitPlayground.setPixelColor(ner_led[i], randomized_color_candles[i][0] / brightness_factor, randomized_color_candles[i][1] / brightness_factor, randomized_color_candles[i][2] / brightness_factor);
                        }
                    } else {
                        // giving colors from BLYNK
                        wasRandom = 0;// reset the randomizer
                        wasPartyMode = 0;// reset Partymode
                        CircuitPlayground.setPixelColor(ner_led[i], red / brightness_factor, green / brightness_factor, blue / brightness_factor);
                    }
                } else {
                    // otherwise clear data
                    CircuitPlayground.setPixelColor(ner_led[i], 0x000000);
                }
                if (isInit) {
                    delay(100);// to get effect of "Hannukka" night lighting ceremony
                }
            }
            // change the brightness in order to make the illustion of burning light
            if (brightness_factor == 1 || brightness_factor == 2) {
                brightness_factor_sign *= -1;
            }

            brightness_factor += brightness_factor_sign;
            if (isInit) {
                isInit = false;
            }
        } else {
            // The Hannukia is not active OR we closed the lights 
            wasRandom = 0;// reset the randomizer
            wasPartyMode = 0; // reset party mode
            CircuitPlayground.clearPixels();
        }
    }
