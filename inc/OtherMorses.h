#ifndef OTHER_MORSES_H
#define OTHER_MORSES_H

// W przypadku klas morseFile, morseTerminal, morseLight pozwolilem sobie
// umiescic je wszystkie w jednum pliku z wzgledu na fakt ich zwiezlosci i
// podobienstwa. Mimo iz przyjeta zasada jest aby rozdielac je na osobne pliki
// moim zdaniem takie ulozenie bedzie bardziej czytelne

/*  Klasy: morseFile, morseLight, morseTerminal
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  18.01.2021
 *  Zmiany:
 *    - Tworze bazowe klasy dla roznych metod "emitowania" kodu morsa
 *    - Dodaje metody clone
 *    - Poprawiam const corectness
 *    
 *
 */
#include "morse.h"
#include <fstream>

// ----- morseFile: morse do obslugi pliku
class morseFile : public MorseInterface {
public:
  morseFile() = delete;
  morseFile(const std::string &path);
  ~morseFile() override = default;

  void emit(morse_code code) final;
  [[nodiscard]] std::unique_ptr<MorseInterface> clone() const override;

  std::string get_path() { return path_; }

  void set_path(const std::string &path) { path_ = path; }

private:
  std::string path_;
};

// ----- morseTerminal: morse do wypisywania w terminalu
class morseTerminal : public MorseInterface {
public:
  morseTerminal() : MorseInterface() {}
  ~morseTerminal() override = default;

  void emit(morse_code code) final;
  [[nodiscard]] std::unique_ptr<MorseInterface> clone() const override;
};

// ----- morseLight: morse do migania klawiszem na klawiaturze
class morseLight : public MorseInterface {

public:
  morseLight(unsigned dot_time, unsigned dash_time, unsigned pause_time);
  ~morseLight() override = default;

  void emit(morse_code code) final;
  [[nodiscard]] std::unique_ptr<MorseInterface> clone() const override;

  void set_dot_time(unsigned val) { dot_time_ = val; }
  void set_dash_time(unsigned val) { dash_time_ = val; }
  void set_pause_time(unsigned val) { pause_time_ = val; }

  unsigned set_dot_time() { return dot_time_; }
  unsigned set_dash_time() { return dash_time_; }
  unsigned set_pause_time() { return pause_time_; }

private:
  static void blink_scroll_lock(unsigned time);
  static void press_scroll_lock();
  unsigned dot_time_;
  unsigned dash_time_;
  unsigned pause_time_;
};

#endif