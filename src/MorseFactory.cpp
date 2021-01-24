#include "MorseFactory.h"

// "klika" scroll lock
void morseLight::press_scroll_lock() {
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
void morseLight::blink_scroll_lock(unsigned time) {
  press_scroll_lock();
  Sleep(time);
  press_scroll_lock();
}

enum Operation { ToFile, ToConsole, ToAudio, ToLight };

// @TODO - what up with that
// Parsujemy podany string aby odczytac z niego odpoiwednie parametry
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

// zgodnie z zadaniem ustawiamy output na ktory wyslemy morsa
// czyli towrzymy odpowiednia klase na naszym polu prywatnym
void MorseFactory::set_output(out option) {

  delete data_;
  switch (option) {
  case out::DISK:
    data_ = new morseFile(this->file_path_.value_or("a.out"));
    break;
  case out::BEEP:
    data_ = new morse(this->freq_.value_or(100), this->dot_time_.value_or(100),
                      this->dash_time_.value_or(100),
                      this->pause_time_.value_or(100),
                      this->char_pause_.value_or(100));
    break;
  case out::CONSOLE:
    data_ = new morseTerminal;
    break;
  case out::BLINK:
    data_ = new morseLight(this->dot_time_.value_or(100),
                           this->dash_time_.value_or(100),
                           this->pause_time_.value_or(100));
    break;
  }
}

// yyy jeszcze w sumie nie wiem co to powinno robic
void MorseFactory::set_external_info(std::string text) {
  // mozna by w sumie dodac set external info for blink zeby wybrac klawisz
}

// Klasa morse i pochodne przeciazaja emmit takze nasz konwert jest tylko
// wraperem dookola niej
void MorseFactory::convert(std::string text) const {
  data_->emit(morse_code(text));
}
void MorseFactory::convert(int text) const {
  data_->emit(morse_code((long)text));
}
