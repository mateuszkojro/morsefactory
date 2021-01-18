#include <iostream>
#include <windows.h>
#include <time.h>
#include "debug.h"
#include "MorseFactory.h"
//#define _WIN32_WINNT 0x500//0x403


int main() {
	MorseFactory f;
	
	f.set_external_info("light");
	f.convert("ala ma kota");

	std::cout << "hello_world";

	return 0;
}

