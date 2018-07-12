/*
  wifi.h
  
*/

void wifiConnect() {
  String ssid = EEPROM.get(0*maxValue, arrayToStore);
  String password = EEPROM.get(1*maxValue, arrayToStore);

  if (ssid == "") { Serial.println(); Serial.println("Cannot connect to WiFi because there is no ssid defined. Please save a value for 'ssid' and 'password'."); return; }
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.print("Connecting to '");
  Serial.print(ssid);
  Serial.print("' ");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if((millis() - start) > 10000) { //try to connect for 10 seconds.
      Serial.println();
      Serial.print("Could not connect to '");
      Serial.print(ssid);
      Serial.println("'. Please check your ssid and password values. Type 'help' for more info.");
      return;
    }
  }
  Serial.println("connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void connectWifi() {
  WiFi.disconnect(true);
  wifiConnect();
}

void disconnectWifi() {
  WiFi.disconnect(true);
  Serial.println("Wifi disconnected.");
}

void restartWifi() {
  Serial.println("Restarting...");
  WiFi.disconnect(true);
  wifiConnect();
}
