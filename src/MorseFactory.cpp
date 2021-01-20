#include "MorseFactory.h"
#include "debug.h"
#include "morse_code.h"
#include <string>

// "klika" scroll lock
void press_scroll_lock() {
  INPUT in[2];
  in[0].type = INPUT_KEYBOARD;
  in[0].ki.wVk = VK_SCROLL;
  in[0].ki.wScan = 0;
  in[0].ki.time = 0;
  in[0].ki.dwFlags = 0;
  in[0].ki.dwExtraInfo = 0;
  in[1] = in[0];
  in[1].ki.dwFlags = KEYEVENTF_KEYUP;
  ::SendInput(2, in, sizeof(INPUT));
}

// zmienia stan scroll-locka na podany czas
void blink_scroll_lock(unsigned time) {
  press_scroll_lock();
  Sleep(time);
  press_scroll_lock();
}

enum Operation { ToFile, ToConsole, ToAudio, ToLight };

Operation parse(std::string text) {
  if (text == "plik") {
    return Operation::ToFile;
  } else if (text == "number") {
    return Operation::ToConsole;
  } else if (text == "light") {
    return Operation::ToLight;
  } else if (text == "console") {
    return Operation::ToConsole;
  } else {
    ERR("String cannot be parsed corectly");
  }
}

void MorseFactory::set_output(out option) {

  delete data_;
  switch (option) {
  case out::DISK:
    data_ = new morseFile;
    break;
  case out::BEEP:
    data_ = new morse;
    break;
  case out::CONSOLE:
    data_ = new morseTerminal;
    break;
  case out::BLINK:
    data_ = new morseLight;
    break;
  }
}

void MorseFactory::set_external_info(std::string text) {

  delete data_;
  switch (parse(text)) {
  case Operation::ToFile:
    data_ = new morseFile;
    break;
  case Operation::ToAudio:
    data_ = new morse;
    break;
  case Operation::ToConsole:
    data_ = new morseTerminal;
    break;
  case Operation::ToLight:
    data_ = new morseLight;
    break;
  }
}

void MorseFactory::convert(std::string text) { data_->emit(morse_code(text)); }
void MorseFactory::convert(int text) { data_->emit(morse_code((long)text)); }
