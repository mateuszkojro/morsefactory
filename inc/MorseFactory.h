#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include "debug.h"
#include "morse.h"
#include "morse_code.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

/*  Klasa MorseFactory
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  16.01.2021
 *  Zmiany:
 *    - Lacze morse_factory z klasa morse z wczesniejszego zadania
 *    -
 *
 */

// morse do obslugi pliku
class morseFile : public MorseInterface {
public:
  morseFile() { path_ = "a.out"; }
  morseFile(const std::string& path) { this->path_ = path; }
  std::unique_ptr<MorseInterface> clone() const override {
    return std::make_unique<morseFile>(*this);
  }
  void set_path(const std::string& path) { path_ = path; }
  std::string get_path() { return path_; }
  void emit(morse_code code) final {

    std::fstream file;
    file.open(this->path_, std::ios::out);

    file << "code: " << code;

    file.close();
  }
  ~morseFile() override = default;

private:
  std::string path_;
};

// morse do wypisywania w terminalu
class morseTerminal : public MorseInterface {
public:
  morseTerminal() : MorseInterface() {}
  std::unique_ptr<MorseInterface> clone() const override {
    return std::make_unique<morseTerminal>(*this);
  }
  void emit(morse_code code) final {
    std::cout << "code: " << code << std::endl;
  }
  ~morseTerminal() override = default;
};
// morse do migania klawiszem na klawiaturze
class morseLight : public MorseInterface {

public:
  std::unique_ptr<MorseInterface> clone() const override {
    return std::make_unique<morseLight>(*this);
  }
  morseLight(unsigned dot_time, unsigned dash_time, unsigned pause_time)
      : MorseInterface() {
    this->dot_time_ = dot_time;
    this->dash_time_ = dash_time;
    this->pause_time_ = pause_time;
  }
  void emit(morse_code code) final {
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
  ~morseLight() override = default;

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
  MorseFactory() { data_ = std::make_unique<morse>(); };
  // jako ze uzywam "smart" ptr nie musze miec specjalnego destruktora
  ~MorseFactory() = default;
  // nie chcemy zeby MorseFactory poniewaz nadpisalo to by nasze vtable
  // bylo kopiowane jezeli chcemy skopiowac obiekt
  // powinnismy pobrac obiekt wewnetrzny maybe typeid can solve that with ifs
  const MorseFactory &operator=(const MorseFactory &other); // = delete;
  MorseFactory(const MorseFactory &);                       //= delete;
  void set_output(out);
  void set_external_info(const std::string&);
  void convert(const std::string&) const;
  void convert(double) const;
  void convert(int) const;

private:
  static bool is_whitespace(char);
  std::optional<unsigned> freq_;
  std::optional<unsigned> dot_time_;
  std::optional<unsigned> dash_time_;
  std::optional<unsigned> pause_time_;
  std::optional<unsigned> char_pause_;
  std::optional<std::string> file_path_;
  // tutaj przechoujemy aktualny obj klasy
  std::unique_ptr<MorseInterface> data_;
};

#endif
