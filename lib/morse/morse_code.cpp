#include "morse_code.h"

std::string morse_code::parse(char znak) {
  /* Zaczerpniete z: https://www.geeksforgeeks.org/morse-code-implementation/ */
    /*Pozwolilem sobie nie dopisywac kolejnych wielkich liter jezeli by je dopisac to w taki sposob jak 'A'*/
  switch (znak) {
  case 'a': case 'A':
    return ".-";
  case 'b':
    return "-...";
  case 'c':
    return "-.-.";
  case 'd':
    return "-..";
  case 'e':
    return ".";
  case 'f':
    return "..-.";
  case 'g':
    return "--.";
  case 'h':
    return "....";
  case 'i':
    return "..";
  case 'j':
    return ".---";
  case 'k':
    return "-.-";
  case 'l':
    return ".-..";
  case 'm':
    return "--";
  case 'n':
    return "-.";
  case 'o':
    return "---";
  case 'p':
    return ".--.";
  case 'q':
    return "--.-";
  case 'r':
    return ".-.";
  case 's':
    return "...";
  case 't':
    return "-";
  case 'u':
    return "..-";
  case 'v':
    return "...-";
  case 'w':
    return ".--";
  case 'x':
    return "-..-";
  case 'y':
    return "-.--";
  case 'z':
    return "--..";
  case ' ':
    return "_";
  case '0':
      return "-";
  case '1':
      return ".-";
  case '2':
      return "..-";
  case '3':
      return "...-";
  case '4':
      return "....-";
  case '5':
      return ".....";
  case '6':
      return "-....";
  case '7':
      return "-...";
  case '8':
      return "-..";
  case '9':
      return "-.";
  default:
    throw bad_symbol;
  }
}

morse_code::morse_code(std::string text) {
  code = "";
  for (char znak : text) {
    code += parse(znak); // parse text and save it into code here
    code += "_";
  }
}

morse_code::morse_code(long num) {
  std::string text = std::to_string(num);
  code = "";
  for (char znak : text) {
    code += parse(znak); // parse text and save it into code here
    code += "_";
  }
}

morse_code::morse_code(double num) {
  std::string text = std::to_string(num);
  code = "";
  for (char znak : text) {
    code += parse(znak); // parse text and save it into code here
    code += "_";
  }
}

morse_code::operator const char *() const { return code.c_str(); }

std::string morse_code::get_code() { return code; }

void morse_code::append(morse_code a) { code += a.get_code(); }
