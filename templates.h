/*
  template.h
  
*/

//// TODO figure out how to decode base64 image and display in e-paper :(
//#include "libb64/cdecode.h"
//#define SIZE 1024
//char* b64decode(String input) {
//  char* output = (char*)malloc(SIZE);
//  char* c = output;
//  int cnt = 0;
//  base64_decodestate s;
//  base64_init_decodestate(&s);
//  cnt = base64_decode_block(input.c_str(), input.length(), c, &s);
//  c += cnt;
//  *c = 0;
//  return output;
//}

void drawBarcode39(int x, int y, int width, int height, int pitch, String barcode){
  int c = 0;
  display.fillRect(x, y, width, height, GxEPD_WHITE);
  c = (pitch * 10);

  for(int i = 0; i < barcode.length(); i++){
     String binCode = getBinCode(barcode.charAt(i));
     bool bk = true;
     for(int j = 0; j < 9; j++){
      int color;
      if(bk){
        color = GxEPD_BLACK; 
      }else{
        color = GxEPD_WHITE;
      }
      bk = !bk;
      int bw;
      if(binCode.charAt(j) == '0'){
        bw = pitch;
      }else{
        bw = pitch * 2;
      }
      display.fillRect( c, y, bw, height, color);
      c = c + bw;
     }
     //Gap
     display.fillRect( c, y, pitch, height, GxEPD_WHITE);
     c = c + pitch;
  }
  
}

void drawIcon(int x, int y, String icon){
  if (icon == "01d" || icon == "01n") { display.drawBitmap(weather01, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "02d" || icon == "02n") { display.drawBitmap(weather02, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "03d" || icon == "03n") { display.drawBitmap(weather03, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "04d" || icon == "04n") { display.drawBitmap(weather04, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "09d" || icon == "09n") { display.drawBitmap(weather09, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "10d" || icon == "10n") { display.drawBitmap(weather10, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "11d" || icon == "11n") { display.drawBitmap(weather11, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "13d" || icon == "13n") { display.drawBitmap(weather13, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "50d" || icon == "50n") { display.drawBitmap(weather50, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "twitter") { display.drawBitmap(twitter, x, y, 64, 64, GxEPD_BLACK); }
  if (icon == "mail") { display.drawBitmap(mail, x, y, 64, 64, GxEPD_BLACK); } 
  if (icon == "fail") { display.drawBitmap(fail, x, y, 64, 64, GxEPD_BLACK); }   
  if (icon == "noel") { display.drawBitmap(noel, x, y, 64, 64, GxEPD_BLACK); } 
}

void drawBadge(int x, int y, String badge) {
    int offset = 32;
    bool isDegree = false;
    if (badge.indexOf("u00B0") > -1 ){
      badge.replace("u00B0", "");
      isDegree = true;
    }
    display.fillCircle(x + offset, y + offset, offset, GxEPD_BLACK);
    display.setTextColor(GxEPD_WHITE);
    if (badge.length() > 1 && badge.length() < 3) {
      // Two characters
      display.setFont(&FreeMonoBold18pt7b);
      display.setCursor(x  + 11, y + 42); 
    } else if (badge.length() == 1 ) {
      // One character
      display.setFont(&FreeMonoBold18pt7b);  
      display.setCursor(x + 21, y + 44);
    } else if (badge.length() > 2 ) {
      // Three characters
      display.setFont(&FreeMonoBold12pt7b);  
      display.setCursor(x + 11, y + 40);
    }
    display.print(badge);

    if (isDegree == true) {
      display.setFont(&TomThumb);
      display.setTextSize(2);
      display.setCursor(x + offset + offset / 2 + 5, y + offset - offset / 3 + 5);
      display.print("o");
    }
 

}

void defaultScreen(){
  String mac = WiFi.macAddress();
  mac.replace(":", "");
  
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);

  display.setFont(&FreeSansBold12pt7b);
  display.setCursor(0, 20);
  display.println(projectName);
  
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 40);
  display.println(projectAuthor);

  mac.toUpperCase();  
  String barcode = String("@" + mac + "#");

  display.setFont(&FreeMono9pt7b);
  display.setCursor(10, 143);
  display.println(mac);

  drawBarcode39(0, 70, 264, 60, 1.9, barcode);

  display.setFont(&FreeSans9pt7b);
  display.setCursor(-1, 170);
  display.println(projectSite);
  
  display.update();
}

void template1(String title, String subtitle, String body, String icon, String badge, String iconData){
  // clear screen
  display.fillScreen(GxEPD_WHITE);


  if (badge != "") {
    // badge
    drawBadge(0, 0, badge);  
  } else {
    // icon
    drawIcon(0, 0, icon);
  }

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  // title
  display.setFont(&FreeSansBold12pt7b);  
  display.setCursor(72, 25);
  display.println(title.substring(0, 16));  

    // subtitle 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(73, 43);
  display.println(subtitle.substring(0, 20));

  // body
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 80);
  display.println(body.substring(0, 170));
  display.update();
}

void template2(String title, String subtitle, String body, String icon, String badge, String iconData){
  // clear screen
  display.fillScreen(GxEPD_WHITE);

  int middle = screenWidth / 2 - 32;

  if (badge != "") {
    // badge
    drawBadge(middle, 45, badge); 
  } else {
    // icon
    drawIcon(middle, 45, icon);   
  }

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  // title
  display.setFont(&FreeSansBold12pt7b);  
  display.setCursor(0, 20);
  display.println(title.substring(0, 22));  

  // subtitle 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 38);
  display.println(subtitle.substring(0, 26));
  
  // body 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 125);
  display.println(body.substring(0, 105));
  
  display.update();
}


void template3(String title, String subtitle, String body, String icon, String badge, String iconData){
  // clear screen
  display.fillScreen(GxEPD_WHITE);


  if (badge != "") {
    // badge
    drawBadge(screenWidth - 68, 0, badge);  
  } else {
    // icon
    drawIcon(screenWidth - 68, 0, icon);
  }

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  // title
  display.setFont(&FreeSansBold12pt7b);  
  display.setCursor(0, 25);
  display.println(title.substring(0, 15));  

    // subtitle 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(1, 43);
  display.println(subtitle.substring(0, 20));

  // body
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 85);
  display.println(body.substring(0, 178));
  display.update();
}

void template4(String title, String subtitle, String body, String icon, String badge, String iconData) {
  // clear screen
  display.fillScreen(GxEPD_WHITE);


  if (badge != "") {
    // badge
    drawBadge(screenWidth - 68, screenHeight - 68, badge);  
  } else {
    // icon
    drawIcon(screenWidth - 68, screenHeight - 68, icon);
  }

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  // title
  display.setFont(&FreeSansBold12pt7b);  
  display.setCursor(0, 25);
  display.println(title);  

    // subtitle 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 43);
  display.println(subtitle);

  // body
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 70);
  display.println(body);
  display.update();
}

void template5(String title, String subtitle, String body) {
  // clear screen
  display.fillScreen(GxEPD_WHITE);

  display.setTextColor(GxEPD_BLACK);
  display.setTextSize(1);
  
  // title
  display.setFont(&FreeSansBold9pt7b);  
  display.setCursor(0, 20);
  display.println(title);  

    // subtitle 
  display.setFont(&FreeSans9pt7b);
  display.setCursor(0, 38);
  display.println(subtitle);

  // body
  display.setFont(&TomThumb);
  display.setCursor(0, 60);
  display.print(body);
  
  display.update();
}

void template6(String imageData) {
  // clear screen
  display.fillScreen(GxEPD_WHITE);

  //char* decoded = b64decode(imageData);
  Serial.println(imageData);
  
  display.update();
}

