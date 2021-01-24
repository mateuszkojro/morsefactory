#include "MorseFactory.h"
#include <optional>

// "klika" scroll lock
void morseLight::press_scroll_lock() {
  INPUT in[2];
  in[0].type = INPUT_KEYBOARD;
  in[0].ki.wVk = VK_SCROLL;
  in[0].ki.wScan = 0;
  in[0].ki.time = 0;
  in[0].ki.dwFlags = 0;
  in[0].ki.dwExtraInfo = 0;
  in[1] = in[0];
  in[1].ki.dwFlags = KEYEVENTF_KEYUP;
  ::SendInput(2, in, sizeof(INPUT));
}

// zmienia stan scroll-locka na podany czas
void morseLight::blink_scroll_lock(unsigned time) {
  press_scroll_lock();
  Sleep(time);
  press_scroll_lock();
}

enum Operation { ToFile, ToConsole, ToAudio, ToLight };

// zgodnie z zadaniem ustawiamy output na ktory wyslemy morsa
// czyli towrzymy odpowiednia klase na naszym polu prywatnym
void MorseFactory::set_output(out option) {

  // delete data_;
  switch (option) {
  case out::DISK:
    data_ = std::make_unique<morseFile>(this->file_path_.value_or("a.out"));
    break;
  case out::BEEP:
    data_ = std::make_unique<morse>(
        this->freq_.value_or(800), this->dot_time_.value_or(200),
        this->dash_time_.value_or(400), this->pause_time_.value_or(100),
        this->char_pause_.value_or(100));
    break;
  case out::CONSOLE:
    data_ = std::make_unique<morseTerminal>();
    break;
  case out::BLINK:
    data_ = std::make_unique<morseLight>(this->dot_time_.value_or(400),
                                         this->dash_time_.value_or(800),
                                         this->pause_time_.value_or(200));
    break;
  }
}

bool MorseFactory::is_whitespace(char znak) {
  // uznajemy ze whitespacem jest tab newline lub spacja
  return znak == '\t' || znak == '\n' || znak == ' ';
}

void MorseFactory::set_external_info(std::string text) {
  // mozna by w sumie dodac set external info for blink zeby wybrac klawisz

  std::string buffer = "";
  std::vector<std::optional<unsigned>> options;

  // przechodzimy po wszytskihc literach
  for (char letter : text) {
    if (is_whitespace(letter)) {
      // jezeli natrafiamy na whitesapce to analizuemy bufor
      char *conversion_failed;
      // probujemy konwerotwac na liczbe
      unsigned converted = strtol(buffer.c_str(), &conversion_failed, 10);
      if (*conversion_failed) {
        // jezeli konwrsjaa sie nie udala to znaczy ze nie liczba zaapisuje jako
        // nazwe pliku
        this->file_path_ = buffer;
      } else {
        // jezeli sie udalo to po prostu dodaje do vectora
        options.push_back(std::make_optional(converted));
      }
      // czyszcze buffer
      buffer = "";
    } else {
      // inaczaczej dodajemy znak do buffora
      buffer += letter;
    }
  }

  // jezeli podano za malo wartosci to wypelniamy pustymi az do czasu kiedy
  // bedziemy mieli dopowiedzni rozmiar
  while (options.size() < 5) {
    options.push_back(std::nullopt);
  }

  // jak ktos poda wiecej wartosci to zostana po prostu zignorowane
  this->freq_ = options[0];
  this->dot_time_ = options[1];
  this->dash_time_ = options[2];
  this->pause_time_ = options[3];
  this->char_pause_ = options[4];
}

// Klasa morse i pochodne przeciazaja emmit takze nasz konwert jest tylko
// wraperem dookola niej
void MorseFactory::convert(std::string text) const {
  data_->emit(morse_code(text));
}
void MorseFactory::convert(double text) const {
  data_->emit(morse_code(text));
}
void MorseFactory::convert(int text) const {
  data_->emit(morse_code((long)text));
}

MorseFactory::MorseFactory(const MorseFactory &other) {
  this->data_ = other.data_->clone();
  this->freq_ = other.freq_;
  this->dot_time_ = other.dot_time_;
  this->dash_time_ = other.dash_time_;
  this->pause_time_ = other.pause_time_;
  this->char_pause_ = other.char_pause_;
  this->file_path_ = other.file_path_;
}

const MorseFactory &MorseFactory::operator=(const MorseFactory &other) {
  if (this == &other) {
    return *this;
  }
  this->data_ = other.data_->clone();
  this->freq_ = other.freq_;
  this->dot_time_ = other.dot_time_;
  this->dash_time_ = other.dash_time_;
  this->pause_time_ = other.pause_time_;
  this->char_pause_ = other.char_pause_;
  this->file_path_ = other.file_path_;
  return *this;
}