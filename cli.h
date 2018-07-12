/*
  cli.h
  
*/

void help() {
  Serial.println("****************************************************************");
  Serial.println(); 
  Serial.println("  " + projectName + " v" + projectVersion);
  Serial.println("  " + projectAuthor);
  Serial.println("  " + projectSite);
  Serial.println();  
  Serial.println("****************************************************************");  
  Serial.println("Commands:");
  Serial.println("  ls                Show all stored key/values");
  Serial.println("  help              Show this help");  
  Serial.println("  press[btn]        Simulate single press of a button"); 
  Serial.println("  doublepress[btn]  Simulate double press of a button");  
  Serial.println("  connect           Connect to wifi");  
  Serial.println("  disconnect        Disconnect wifi");   
  Serial.println("  restart           Restart wifi");  
  Serial.println("  status            Show wifi status");     
  Serial.println();
  Serial.println("Usage:");
  Serial.println("  Read saved key value:");
  Serial.println("    key");
  Serial.println("  Save new key value:");  
  Serial.println("    key=[value]");
  Serial.println();
  Serial.print("Available keys:");
  for (int i=0; i < keysLen; i++) {
    Serial.print(" '");
    Serial.print(keys[i]);
    if (i == 6) {
      Serial.println("' ");
      Serial.print("  ");
    } else {
      Serial.print("' ");
    }
  }
  Serial.println(""); 
  Serial.println("");
}

void showStatus() {
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
  WiFi.printDiag(Serial);
}


void listAll() {
  for (int i=0; i < keysLen; i++) {
    String key = keys[i];
    Serial.print(key);
    Serial.print(": ");
    String val = getFromMemory(i);
    if (key.indexOf("method") > -1 && val == "") {
      val = "GET";
    }
    if (key.indexOf("defaultscreen") > -1 && val == "") {
      val = "true";
    }    
    Serial.println(val);
  }
}

void eraseAll(){
  for (int i = 0; i < eepromSize; i++) {
    EEPROM.write(i, 0);
  }
  EEPROM.commit();
  WiFi.disconnect(true);
  Serial.println("All values have been erased!");
  listAll();
}

void evalInput(String input) {

  String key = parseValue(input, '=', 0);
  String val = parseValue(input, '=', 1);
  if (key == "ls" || key == "ll") { listAll(); return; }
  if (key == "help") { help(); return; }
  if (key == "eraseall") { eraseAll(); return; } // not displayed under help
  if (key == "status") { showStatus(); return; }
  if (key == "connect") { connectWifi(); return; }  
  if (key == "disconnect") { disconnectWifi(); return; }  
  if (key == "restart") { restartWifi();; return; }   
  if (key.indexOf("doublepress") > -1) {
    int btn = key.substring(key.length() - 1).toInt();
    pushButton(btn, "double");
    return;
  }  
  if (key.indexOf("press") > -1) {
    int btn = key.substring(key.length() - 1).toInt();
    pushButton(btn, "");
    return;
  }

  
  int keyIndex = getKeyIndex(key);
  if (keyIndex == -1) { 
    Serial.print(key);
    Serial.println(" is not a valid key or command! Type 'help' or 'ls' for more info.");
    return; 
  }

  if (val != "") {
      if (key.indexOf("method") > -1) {
        val.toUpperCase();  
      }
      if (val == "\"\"" || val == "''") { val=""; }
      saveToMemory(keyIndex, val);
      Serial.print("Value saved for ");
      Serial.print(key);
      Serial.print(": ");
      Serial.println(val);
      if (key == "ssid" || key == "password"){
        Serial.println("Use the command 'restart' for changes to take effect. ");
      }
      if (key == "defaultscreen" && val == "true"){
        defaultScreen();
      }
      if (val.indexOf("http:") > -1) {
        // clear corresponding SHA fingerprint
        int btn = key.substring(key.length() - 1).toInt();
        if (key.indexOf("double") > -1) {
          saveToMemory(getKeyIndex("doublesha" + String(btn)), "");
        } else {
          saveToMemory(getKeyIndex("sha" + String(btn)), "");
        }
      }
  } else {
      Serial.print(key);
      Serial.print(": ");
      String val = getFromMemory(keyIndex);
      if (key.indexOf("method") > -1 && val == "") {
        val = "GET";
      }
      if (key.indexOf("defaultscreen") > -1 && val == "") {
        val = "true";
      }
      Serial.println(val);
  }
    
}
