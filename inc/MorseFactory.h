#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include "debug.h"
#include "morse.h"
#include "morse_code.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>

/*  Klasa MorseFactory
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  16.01.2021
 *  Zmiany:
 *    - Lacze morse_factory z klasa morse z wczesniejszego zadania
 *    -
 *
 */

/*
Sczerze moiwac jestem rozdarty pomiedzy 2 implemetnacjami taka w ktorej klasy
dziedzica tylko iwylacznie po interface i takiej w ktorej dziedzica rownierz po
morse jedna zapewnia nam brak powtralnosci kodu ( we morse mamy napisane juz
operatory gettery i settery ) natomiast droga ogrnaicza pola obecne w klasie do
tylkjo i wylacznie tych wymaganych ( teorteczynie w klasie morseFile nie
potrzbuje czestotliwosci ani dlugosci dzwiekow ) na koncu uznalem ze wszytswko
zaalezy w sumie od sytuacji wiec dobralem te 2 metody zaelznie od tego ktoraa w
danym przypadku mial wiekszy sens

*/

// morse do obslugi pliku
class morseFile : public MorseInterface {
public:
  morseFile() { path_ = "a.out"; }
  morseFile(std::string path) { this->path_ = path; }
  void set_path(std::string path) { path_ = path; }
  std::string get_path() { return path_; }
  virtual void emit(morse_code code) final override {

    std::fstream file;
    file.open(this->path_, std::ios::out);

    file << "code: " << code;

    file.close();
  }
  virtual ~morseFile(){};

private:
  std::string path_;
};

// morse do wypisywania w terminalu
class morseTerminal : public MorseInterface {
public:
  morseTerminal() : MorseInterface() {}
  virtual void emit(morse_code code) final override {
    std::cout << "code: " << code << std::endl;
  }
  virtual ~morseTerminal(){};
};
// morse do migania klawiszem na klawiaturze
class morseLight : public MorseInterface {

public:
  morseLight(unsigned dot_time, unsigned dash_time, unsigned pause_time)
      : MorseInterface() {
    this->dot_time_ = dot_time;
    this->dash_time_ = dash_time;
    this->pause_time_ = pause_time;
  }
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
  static void blink_scroll_lock(unsigned time);
  static void press_scroll_lock();
  unsigned dot_time_;
  unsigned dash_time_;
  unsigned pause_time_;
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
  void convert(std::string) const;
  void convert(int) const;

private:
  std::optional<unsigned> freq_;
  std::optional<unsigned> dot_time_;
  std::optional<unsigned> dash_time_;
  std::optional<unsigned> pause_time_;
  std::optional<unsigned> char_pause_;
  std::optional<std::string> file_path_;
  // tutaj przechoujemy aktualny obj klasy
  MorseInterface *data_;
};

#endif
