#ifndef MORSE_FACTORY
#define MORSE_FACTORY
#include <iostream>

/*  Klasa MorseFactory
 *  Autor: Mateusz Kojro
 *  Data utworzenia:  16.01.2021
 *  Zmiany:
 *    - 
 *
 */
class IMorse {
  public:
    IMorse();
    virtual void convert() = 0;
};

class MorseAudio : public IMorse {
  public:
    MorseAudio(){}
    virtual void convert() final override;
};

class MorseFactory {
public:
  enum out { BEEP, DISK, CONSOLE };

  MorseFactory();
  MorseFactory(const MorseFactory&) = delete;
  ~MorseFactory() = delete;
  const MorseFactory& operator=(const MorseFactory&) = delete;
  void set_output(out);
  void set_external_info(std::string);
  void convert(std::string);
  void convert(int);

private:
  IMorse* data_;
};

#endif
