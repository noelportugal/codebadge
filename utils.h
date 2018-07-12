/*
  utils.h
  
*/

String parseValue(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

String getBinCode(char str){
  if(str == '@') return String("010010100");
  if(str == '0') return String("000110100");
  if(str == '1') return String("100100001");
  if(str == '2') return String("001100001");
  if(str == '3') return String("101100000");
  if(str == '4') return String("000110001");
  if(str == '5') return String("100110000");
  if(str == '6') return String("001110000");
  if(str == '7') return String("000100101");
  if(str == '8') return String("100100100");
  if(str == '9') return String("001100100");
  if(str == 'A') return String("100001001");
  if(str == 'B') return String("001001001");
  if(str == 'C') return String("101001000");
  if(str == 'D') return String("000011001");
  if(str == 'E') return String("100011000");
  if(str == 'F') return String("001011000");
  if(str == 'G') return String("000001101");
  if(str == 'H') return String("100001100");
  if(str == 'I') return String("001001100");
  if(str == 'J') return String("000011100");
  if(str == 'K') return String("100000011");
  if(str == 'L') return String("001000011");
  if(str == 'M') return String("101000010");
  if(str == 'N') return String("000010011");
  if(str == 'O') return String("100010010");
  if(str == 'P') return String("001010010");
  if(str == 'Q') return String("000000111");
  if(str == 'R') return String("100000110");
  if(str == 'S') return String("001000110");
  if(str == 'T') return String("000010110");
  if(str == 'U') return String("110000001");
  if(str == 'V') return String("011000001");
  if(str == 'W') return String("111000000");
  if(str == 'X') return String("010010001");
  if(str == 'Y') return String("110010000");
  if(str == 'Z') return String("011010000");
  if(str == '-') return String("010000101");
  if(str == '.') return String("110000100");
  if(str == ' ') return String("011000100");
  if(str == '*') return String("010010100");
  if(str == '$') return String("010101000");
  if(str == '/') return String("010100010");
  if(str == '+') return String("010001010");
  if(str == '%') return String("000101010");  
  if(str == '#') return String("010010100");
}

