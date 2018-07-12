/*
  buttonEvents.h
  
*/

void pushButton(int btnId, String type){
  String button = type + "button" + String(btnId);
  String url = getFromMemory(button);
  String protocol = parseValue(url, '/', 0);
  String host = parseValue(url, '/', 2);
  String portString = parseValue(host, ':', 1) ;
  host = parseValue(host, ':', 0);
  
  if (protocol == "https:") {
    int port = (portString.length() != 0) ? portString.toInt() : 443;
    httpsClient(host, port, url, btnId, type);
  } else {
    int port = (portString.length() != 0) ? portString.toInt() : 80;
    httpCient(host, port, url, btnId, type);
  }
}

// The event handler for the button.
void handlePushEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventReleased:
      pushButton(button->getId(), "");
      break;
    case AceButton::kEventDoubleClicked:
      pushButton(button->getId(), "double");
      break;
  }
}

