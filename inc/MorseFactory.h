#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include "debug.h"
#include "morse.h"
#include "morse_code.h"
#include <iostream>
#include <stack>
#include <string>

/*  Klasa MorseFactory
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  16.01.2021
 *  Zmiany:
 *    - Lacze morse_factory z klasa morse z wczesniejszego zadania
 *
 */

class morseFile : public morse {
public:
  virtual void emit(morse_code); // save to file
  virtual ~morseFile();
};

class MorseFactory {
public:
  enum out { BEEP, DISK, CONSOLE, BLINK };

  MorseFactory(){ WARN("konstruktor nie tworzy obiektu na wskazniku") };
  MorseFactory(const MorseFactory &) = delete;
  ~MorseFactory() { delete data_; };
  const MorseFactory &operator=(const MorseFactory &) = delete;
  void set_output(out);
  void set_external_info(std::string);
  void convert(std::string);
  void convert(int);

private:
  morse *data_;
};

#endif
