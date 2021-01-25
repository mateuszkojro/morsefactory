#include "OtherMorses.h"

// ----- Morse File
morseFile::morseFile(const std::string &path) { this->path_ = path; }

std::unique_ptr<MorseInterface> morseFile::clone() const {
  return std::make_unique<morseFile>(*this);
}

void morseFile::emit(morse_code code) {

  std::fstream file;
  file.open(this->path_, std::ios::out);

  file << "code: " << code;

  file.close();
}

// ----- Morse Terminal

[[nodiscard]] std::unique_ptr<MorseInterface> morseTerminal::clone() const {
  return std::make_unique<morseTerminal>(*this);
}
void morseTerminal::emit(morse_code code) {
  std::cout << "code: " << code << std::endl;
}

// ----- Morse Light

[[nodiscard]] std::unique_ptr<MorseInterface> morseLight::clone() const {
  return std::make_unique<morseLight>(*this);
}

morseLight::morseLight(unsigned dot_time, unsigned dash_time,
                       unsigned pause_time)
    : MorseInterface() {
  this->dot_time_ = dot_time;
  this->dash_time_ = dash_time;
  this->pause_time_ = pause_time;
}

void morseLight::emit(morse_code code) {
  for (auto znak : code.get_code()) {
    switch (znak) {
    case '.':
      blink_scroll_lock(dot_time_);
      break;
    case '-':
      blink_scroll_lock(dash_time_);
      break;
    case '_':
      Sleep(pause_time_);
      break;
    }
  }
}