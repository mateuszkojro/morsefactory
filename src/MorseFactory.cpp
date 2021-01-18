#include "MorseFactory.h"
#include "debug.h"
#include "morse_code.h"
#include <string>

enum Operation { ToFile, ToConsole, ToAudio };

Operation parse(std::string text) {
  if (text == "plik") {
    return Operation::ToFile;
  } else if (text == "number") {
    return Operation::ToConsole;
  } else {
    ERR("String cannot be parsed corectly");
  }
}

void MorseFactory::set_external_info(std::string text) {

  switch (parse(text)) {
  case Operation::ToFile:
    delete data_;
    data_ = new morseFile;
    break;
  default:
    ERR("Not correct operation");
  }
}

void MorseFactory::convert(std::string text) { *data_ << morse_code(text); }
void MorseFactory::convert(int text) { *data_ << morse_code((long)text); }
