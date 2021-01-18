#include "morse.h"

void morse::setFrequency(unsigned freq) { freq_ = freq; }

void morse::setDotTime(unsigned dot_time) { dot_time_ = dot_time; }

void morse::setDashTime(unsigned dash_time) { dash_time_ = dash_time; }

void morse::setPause(unsigned pause_time) { pause_time_ = pause_time; }

void morse::setCharPause(unsigned char_pause) { char_pause_ = char_pause; }

// majac morse_code na podstawie parametrow ustawionych wczesniej emitujemy
// dzwieki i robimy pauzy
void morse::emit(morse_code code) {
  for (auto znak : code.get_code()) {
    switch (znak) {
    case '.':
      Beep(freq_, dot_time_);
      break;
    case '-':
      Beep(freq_, dash_time_);
      break;
    case '_':
      Sleep(pause_time_);
      break;
    }
  }
}

morse &morse::operator<<(morse_code &a) {
  this->emit(a);
  return *this;
}

morse &morse::operator<<(morse &(*func)(morse &)) { return func(*this); }

morse &morse::operator<<(long a) {
  this->emit(morse_code(a));
  return *this;
}

morse &morse::operator<<(double a) {
  this->emit(morse_code(a));
  return *this;
}

morse &morse::operator<<(const std::string &a) {
  this->emit(morse_code(a));
  return *this;
}

morse &morse::operator<<(const char *a) {
  this->emit(morse_code(a));
  return *this;
}

morse &pause(morse &a) {
  a.emit(morse_code("__"));
  return a;
}