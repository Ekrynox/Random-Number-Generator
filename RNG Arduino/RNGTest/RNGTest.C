#include "../RNGLib/RNG.h"

int main() {
	RNG device = initRNGSerial(L"\\\\.\\COM9");
	if (!device) {
		printf("unable to connect");
		return -1;
	}

	printf("%s", RNGGenerate(device, 1000000, true));

	closeRNG(device);
	return 0;
}