#pragma once
/*
    Autor: Mateus Kojro
    Opis: Klasa przechowujaca wiadomosci zapsiane w kodzie morsa i pozwalajaca na konwertowanie wiadomosci z roznego rodzaju zmiennych 
    Zmiany: 
        9.11 - Utworzono, @parse - zamiana litery na kod morsa, konstruktory dla roznych typow
        15.11 - dodaje wyjatek i mozliwosc rzutowania na const char* 
*/


#ifndef MORSE_CODE_H
#define MORSE_CODE_H
#include <iostream>
#include <string>

class morse_code {
public:
  // tworzenie obiektow kodu morsa z roznych typow danych
  morse_code(std::string text);
  morse_code(long num);
  morse_code(double num);

  // geter wiadomosci zakodowaniej kodem morsa
  std::string get_code();
  void append(morse_code a);

  // Operator rzutowania na const char*
  operator const char *() const;

  // zamienia znak na kod morsa
  std::string parse(char znak);

  // wyjatek do wyrzucania podczas kodowania tekstu kiedy napotkamy znak dla
  // ktorego nie mamy odpowiednika w kodzie morsa
  class parse_err : std::exception {
  public:
    virtual const char *what() const throw() {
      return "There is no known conversion to morse code from that symbol";
    }
  } bad_symbol;

private:

  std::string code;
};

#endif // !MORSE_CODE_H
