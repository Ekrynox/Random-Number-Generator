#include "../RNGLib/RNG.h"

int main() {
	RNG device = initRNGSerial(L"COM3");
	if (!device) {
		return -1;
	}

	closeRNG(device);
	return 0;
}