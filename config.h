/*
  config.h

*/

#include <ESP8266WiFi.h>      // ESP8266 Board support needed. Add http://arduino.esp8266.com/stable/package_esp8266com_index.json to Borad Manager Urls (Preferences)
#include <AceButton.h>        // Search and add using Arduino Library Manager
using namespace ace_button;
#include <ArduinoJson.h>      // Search and add using Arduino Library Manager
#include <pgmspace.h>
#include <EEPROM.h>
#include <GxEPD.h>            // Download/Clone and put in Arduino Library https://github.com/ZinggJM/GxEPD

// Uncommnet to chose your display
#include <GxGDEW0154Z04/GxGDEW0154Z04.cpp>    // 1.54" b/w/r 200x200
//#include <GxGDE0213B1/GxGDE0213B1.cpp>      // 2.13" b/w 250x122
//#include <GxGDEW027W3/GxGDEW027W3.cpp>      // 2.7" b/w 264x176

#include <GxIO/GxIO_SPI/GxIO_SPI.cpp>
#include <GxIO/GxIO.cpp>

// FreeFonts from Adafruit_GFX
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMonoBold12pt7b.h>
#include <Fonts/FreeMonoBold18pt7b.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSans12pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>
#include <Fonts/FreeSansBold12pt7b.h>
#include <Fonts/TomThumb.h>
//#define TOMTHUMB_USE_EXTENDED 1

long baudSpeed = 115200;

ButtonConfig buttonConfig;
AceButton button1;
AceButton button2;

String projectName = "CodeBadge";
String projectVersion = "1.0";
String projectAuthor = "Noel Portugal";
String projectSite = "github.com/noelportugal/codebadge";
const int screenWidth = 250;
const int screenHeight = 122;

// Button pins
const uint8_t BUTTON1_PIN = 0;   //borad button1 pin GPIO10 = 12
const uint8_t BUTTON2_PIN = 18;    //borad button2 pin GPIO12 = 6

// E-ink SPI pins
const uint8_t CS_PIN = 15;      //15
const uint8_t DC_PIN = 4;       //4
const uint8_t RST_PIN = 5;      //5
const uint8_t BUSY_PIN = 16;    //16

GxIO_Class io(SPI, CS_PIN, DC_PIN, RST_PIN);
GxEPD_Class display(io, RST_PIN, BUSY_PIN);

// temp use with ModeMCU setup
//GxIO_Class io(SPI, 15, 16, 2);
//GxEPD_Class display(io);

char arrayToStore[100];
int maxValue = 200;
const int eepromSize = 4096;

// Available keys
char* keys[] = {
  "ssid", 
  "password", 
  "button1", 
  "button2", 
  "doublebutton1", 
  "doublebutton2", 
  "sha1", 
  "sha2", 
  "doublesha1", 
  "doublesha2", 
  "method1", 
  "method2", 
  "doublemethod1", 
  "doublemethod2", 
  "defaultscreen"
  };

  int keysLen = sizeof(keys)/sizeof(keys[0]);

