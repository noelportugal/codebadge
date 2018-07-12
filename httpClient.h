/*
  httpClient.h
  
*/

void parseJson(JsonObject& root) {
  String jsonStr;
  root.printTo(jsonStr);
  Serial.println("Response: ");
  Serial.print("  ");
  Serial.println(jsonStr);
  Serial.println();
  
  if (!root.success()) {
    Serial.println(F("Parsing failed!"));
    template1("Invalid JSON!","", "Please make sure to return the JSON format speficied at " + projectSite,"fail","","");
    saveToMemory(getKeyIndex("defaultscreen"), "true");
    return;
  }
  
  String templateName = root["template"].as<String>();
  String title = root["title"].as<String>();
  String subtitle = root["subtitle"].as<String>();
  String body = root["body"].as<String>();
  String icon = root["icon"].as<String>();
  String badge = root["badge"].as<String>();
  String iconData = root["iconData"].as<String>();
  String imageData = root["iconData"].as<String>();
  
  //char imageData[1024];
  //root["imageData"]["data"].printTo(imageData);
  //String imageData = root["imageData"].as<String>();
//  JsonArray& imageData = root["imageData"];
//  for (int i = 0; i < imageData.size(); i++){
//    Serial.println(imageData[i].as<String>());
//  }

  saveToMemory(getKeyIndex("defaultscreen"), "false");
  
  if (templateName == "template1") {
    template1(title, subtitle, body, icon, badge, iconData);
  } else if (templateName == "template2") {
    template2(title, subtitle, body, icon, badge, iconData);
  } else if (templateName == "template3") {
    template3(title, subtitle, body, icon, badge, iconData);
  } else if (templateName == "template4") {
    template4(title, subtitle, body, icon, badge, iconData);
  } else if (templateName == "template5") {
    template5(title, subtitle, body);
  } else if (templateName == "template6") {
    template6(imageData);    
  } else {
    template1(title, subtitle, body, icon, badge, iconData);
  }
}


void httpsClient(String host, int port, String url, int btnId, String type) {
  WiFiClientSecure client;
  String shaKey = type + "sha" + String(btnId);
  String sha = getFromMemory(shaKey);

  String methodKey = type + "method" + String(btnId);
  String httpMethod = getFromMemory(methodKey);

  Serial.println("Request:");
  Serial.print("  host: ");
  Serial.println(host);
  Serial.print("  port: ");
  Serial.println(port);  
  Serial.print("  url: ");
  Serial.println(url);
  Serial.print("  method: ");
  Serial.println(httpMethod);

  if (sha == "") {
    Serial.println("  This SSL url needs to have a corresponding SHA fingerprint.");
    Serial.println("  Add one by typing '[double]sha[btnNumber]=XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX XX'.");
    Serial.println("  To learn how to retrieve an SSL SHA fingerprint go to " + projectSite);
    return;
  }

  client.setTimeout(10000);
  if (!client.connect(host, port)) {
    Serial.println("  SSL connection failed");
    return;
  }

  if (!client.verify(sha.c_str(), host.c_str())) {
    Serial.println("  Connection insecure! Halting execution.");
    return;
  }

  String mac = WiFi.macAddress();
  mac.replace(":", "");

  client.print(httpMethod + " " + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" + 
               "X-CODEBADGE-ID: " + mac + "\r\n" +                
               "Accept: */*\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("  Request timeout!");
      return;
    }
  }       
                            
  if (client.println() == 0) {
    Serial.println(F("  Failed to send request"));
    return;
  }

  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("  Unexpected response: "));
    Serial.println(status);
    client.stop();
    return;
  }

//  while (client.available()) {
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }

  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("  Invalid response"));
    return;
  }

  
  const size_t capacity = JSON_OBJECT_SIZE(7) + JSON_ARRAY_SIZE(2) + 60;
  //const size_t capacity = JSON_OBJECT_SIZE(7) + 33460;
  DynamicJsonBuffer jsonBuffer(capacity);
  
  JsonObject& root = jsonBuffer.parseObject(client);
  client.stop();
  parseJson(root);  

  
}

void httpCient(String host, int port, String url, int btnId, String type){
  WiFiClient client;

  String methodKey = type + "method" + String(btnId);
  String httpMethod = getFromMemory(methodKey);

  Serial.println("Request:");
  Serial.print("  host: ");
  Serial.println(host);
  Serial.print("  port: ");
  Serial.println(port);  
  Serial.print("  url: ");
  Serial.println(url);
  Serial.print("  method: ");
  Serial.println(httpMethod);

  client.setTimeout(10000);
  if (!client.connect(host, port)) {
    Serial.println("  Connection failed");
    return;
  }

  String mac = WiFi.macAddress();
  mac.replace(":", "");
  
  client.print(httpMethod + " " + url + " HTTP/1.0\r\n" +
               "Host: " + host + "\r\n" + 
               "X-CODEBADGE-ID: " + mac + "\r\n" +                    
               "Accept: */*\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println("  Request timeout!");
      client.stop();
      return;
    }
  } 
                 
  if (client.println() == 0) {
    Serial.println(F("  Failed to send request"));
    return;
  }

  char status[32] = {0};
  client.readBytesUntil('\r', status, sizeof(status));
  if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
    Serial.print(F("  Unexpected response: "));
    Serial.println(status);
    return;
  }

//  while (client.available()) {
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//  }

  char endOfHeaders[] = "\r\n\r\n";
  if (!client.find(endOfHeaders)) {
    Serial.println(F("  Invalid response"));
    return;
  }

  //const size_t capacity = JSON_OBJECT_SIZE(7) + JSON_ARRAY_SIZE(2) + 60;
  const size_t capacity = JSON_ARRAY_SIZE(10000) + JSON_OBJECT_SIZE(7) + 33460;
  DynamicJsonBuffer jsonBuffer(capacity);

  
  JsonObject& root = jsonBuffer.parseObject(client);
  client.stop(); 
  parseJson(root);
  
}






