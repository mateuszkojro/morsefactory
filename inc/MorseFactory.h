#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include "debug.h"
#include "morse.h"
#include "morse_code.h"
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vcruntime_string.h>

/*  Klasa MorseFactory
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  16.01.2021
 *  Zmiany:
 *    - Lacze morse_factory z klasa morse z wczesniejszego zadania
 *
 */
void blink_scroll_lock(unsigned time);
void press_scroll_lock();

// morse do obslugi pliku
class morseFile : public morse {
public:
  morseFile() { path_ = "a.out"; }
  void set_path(std::string path) { path_ = path; }
  virtual void emit(morse_code code) final override {

    LOG("Co jak plik nie istnieje");
    std::fstream file;
    file.open(this->path_, std::ios::out);
    file << "freq:" << this->freq_ << std::endl;
    file << "dot_time:" << this->dot_time_ << std::endl;
    file << "dash_time:" << this->dash_time_ << std::endl;
    file << "pause_time:" << this->pause_time_ << std::endl;
    file << "char_pause:" << this->char_pause_ << std::endl;

    file << "code: " << code;

    file.close();
  }
  virtual ~morseFile(){};

private:
  std::string path_;
};

// morse do migania klawiszem na klawiaturze
class morseLight : public morse {
public:
  virtual void emit(morse_code code) final override {
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
  virtual ~morseLight(){};

private:
  std::string path_;
};

// morse do wypisywania w terminalu
class morseTerminal : public morse {
public:
  morseTerminal() : morse() {}
  virtual void emit(morse_code code) final override {

    std::cout << "freq:" << this->freq_ << std::endl;
    std::cout << "dot_time:" << this->dot_time_ << std::endl;
    std::cout << "dash_time:" << this->dash_time_ << std::endl;
    std::cout << "pause_time:" << this->pause_time_ << std::endl;
    std::cout << "char_pause:" << this->char_pause_ << std::endl;

    std::cout << "code: " << code << std::endl;
  }
  virtual ~morseTerminal(){};

private:
  std::string path_;
};



class MorseFactory {
public:
  enum out { BEEP, DISK, CONSOLE, BLINK };

  // domyslnie tworze obiekt typu morse = arbitrary decision
  MorseFactory() { data_ = new morse; };
  ~MorseFactory() { delete data_; };
  // nie chcemy zeby morsefactory poniewaz nadpisalo to by nasze vtable
  // bylo kopiowane jezeli chcemy skopiowac obiekt
  // powinnismy pobrac obiekt wewnetrzny maybe typeid can solve that with ifs
  const MorseFactory &operator=(const MorseFactory &other) = delete;
  MorseFactory(const MorseFactory &) = delete;
  void set_output(out);
  void set_external_info(std::string);
  void convert(std::string);
  void convert(int);

private:
  // tutaj przechoujemy aktualny obj klasy
  morse *data_;
};

#endif
