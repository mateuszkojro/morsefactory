
#include "MorseFactory.h" //--- includujemy jedną swoją klasę ---

int main() {

  MorseFactory f; //--- tworzymy jeden obiekt ---

  f.set_external_info(
      "200 200 400"); //--- wprowadzamy ustawienia dla BEEP w jednym stringu
                      //(tutaj podane wartości  przykładowe) ---
  f.set_output(MorseFactory::BEEP); //--- ustawiamy co ma być wykonywane --
                                    //tutaj na głośnikach systemowych ---
  f.convert("Ala ma kota");         //--- odtwarzany ciąg znaków ---

  f.set_external_info(
      "nazwapliku.txt"); //--- ustawienie parserem nazwy pliku/ścieżki ---
  f.set_output(
      MorseFactory::DISK); //--- ustawienie zapisu w kodzie morsa do pliku ---
  f.convert("A kot ma");   //--- zapisywany ciąg znaków ---
  f.convert(123);          //--- zapisana liczba ---
  f.convert(1.23);         //--- zapisywana liczba dziesiętna ---

  f.set_external_info(
      "300 100 300 100 700 500"); //--- ustawienie parserem dla BLINK ---
  f.set_output(
      MorseFactory::BLINK); //--- ustawienie migania diody na klawiaturze, przy
                            //braku diody na klawiaturze zapalanie pustego znaku
                            //(tła) w konsoli ---
  f.convert("Ala ma kota"); //--- odtwarzany ciąg znaków ---

  f.set_external_info(
      "300 100 300 100 700 500");      //--- ustawienie parserem dla CONSOLE ---
  f.set_output(MorseFactory::CONSOLE); //--- ustawienie morsa na wyświetlenie na
                                       //konsoli ---
  f.convert("Ala ma kota"); //--- wyświetlany ciąg znaków ---

  return 0;
}
