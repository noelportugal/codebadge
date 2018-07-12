/*
  codeBadge
  
  Copyright (c) 2018 Noel Portugal.  All rights reserved.
  
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  
  - Redistributions of source code must retain the above copyright notice,
    this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright notice,
    this list of conditions and the following disclaimer in the documentation
    and/or other materials provided with the distribution.
  
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
*/

// These dependencies need to be loaeded in this specific sequence.
#include "config.h" // contains all dependencies includes and global variables
#include "utils.h"
#include "memory.h"
#include "wifi.h"
#include "icons.h"
#include "templates.h"
#include "httpClient.h"
#include "buttonEvents.h"
#include "cli.h"

void setup() {
  Serial.begin(baudSpeed);
  delay(10);
  EEPROM.begin(eepromSize);
  initButtons();
  initScreen();
  help();
  wifiConnect();
  String isDefaultScreen = getFromMemory("defaultscreen");
  if (isDefaultScreen == "true"){
    defaultScreen();
  }
}

 
void loop() {
  if (Serial.available()) {
    String input = Serial.readString();
    input.trim();
    evalInput(input);
  }
  button1.check();
  button2.check();
}

void initScreen() {
  display.init();
  display.setRotation(3);
}

void initButtons() {
  buttonConfig.setEventHandler(handlePushEvent);
  buttonConfig.setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterClick);
  buttonConfig.setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);

  pinMode(BUTTON1_PIN, INPUT);
  button1.setButtonConfig(&buttonConfig);
  button1.init(BUTTON1_PIN, HIGH, 1);

  pinMode(BUTTON2_PIN, INPUT);
  button2.setButtonConfig(&buttonConfig);
  button2.init(BUTTON2_PIN, HIGH, 2);
}

