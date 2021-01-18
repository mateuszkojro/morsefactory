/*
        Autor: Mateus Kojro
        Opis: Klasa umozliwiajaca nadawanie sygnalow w kodzie morsa poprzez
   wbudowane glosnii komputera, lub wyswietlanie traskryptu Zmiany: 9.11 -
   Utworzono, translacja dla malych liter, proste przeciazenie @operatora<<,
   prosty @emit 15.11 - obsluga '<<' i dodaje manipulator @pause
*/

#pragma once
#ifndef MORSE_H
#define MORSE_H

#include <Windows.h>
#include <iostream>
#include <string>

#include "morse_code.h"

class morse {
public:
  // konstruktor bezparametrowy inicjalizuje pola klasy jako przykladowe
  // wartosci
  morse() {
    freq_ = 800;
    dot_time_ = 200;
    dash_time_ = 400;
    pause_time_ = 100;
    char_pause_ = 100;
  };

  // ustawianie parametrow dotyczacyhch "emitowania" dzwiekow
  void setPause(unsigned pause_time);
  void setDotTime(unsigned dot_time);
  void setDashTime(unsigned dash_time);
  void setCharPause(unsigned char_pause);
  void setFrequency(unsigned freq);

  // Przeciazenia operatorow do obslugi danych wejsciowych roznego rodzaju
  morse &operator<<(long a);
  morse &operator<<(double a);
  morse &operator<<(const char *a);
  morse &operator<<(morse_code &a);
  morse &operator<<(const std::string &a);
  morse &operator<<(morse &(*func)(morse &));

  // Funkcja "wydajaca dzwieki" na podstawie kodu morsa - przedstawionego w
  // postaci klasy @morse_code
  virtual void emit(morse_code);
  virtual ~morse() {};

private:
  unsigned freq_;
  unsigned dot_time_;
  unsigned dash_time_;
  unsigned pause_time_;
  unsigned char_pause_;
};

// manipulator strumienia - pauzuje przekazywanie strumenia
morse &pause(morse &);

#endif // !MORSE_H
