#include "MorseFactory.h"
#include "debug.h"
#include <iostream>
#include <time.h>
#include <windows.h>
//#define _WIN32_WINNT 0x500//0x403

int main() {
  MorseFactory f;

  f.set_output(MorseFactory::CONSOLE);
  f.convert("ala ma kota");

  f.set_external_info("light");
  f.convert("ala ma kota");

  f.set_output(MorseFactory::BEEP);
  f.convert("ala ma kota");

  return 0;
}
