#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include "OtherMorses.h"
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
 *  Repo: https://github.com/mateuszkojro/morsefactory
 *  Zmiany:
 *    - Lacze morse_factory z klasa morse z wczesniejszego zadania
 *    - convert, set_output ready
 *    - set_external info ready
 *    - uzywam std::optional, i zmieniam raw pointer na "smart" (latwiejsze zarzadzanie 
 *       i latwijszy clone - odbiorcaa nie musi zarzadzac usuwaniemd)
 *    - improving const corectmess
 *    - male ulepszenia zgodne z linterem
 *
 */

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
  void set_external_info(const std::string &);
  void convert(const std::string &) const;
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
