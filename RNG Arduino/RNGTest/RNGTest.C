#include "../RNGLib/RNG.h"

int main(int argc, char **argv) {
	RNG device = initRNGSerial(L"\\\\.\\COM8");
	if (!device) {
		printf("unable to connect");
		return -1;
	}

	if (argc > 1 && atoi(argv[1]) > 0) {
		printf("%s", RNGGenerate(device, atoi(argv[1]), false));
	}
	else {
		printf("%s", RNGGenerate(device, 100000, false));
	}

	closeRNG(&device);

	/*initRNGLib();

	RNG device = initRNGEthernet("192.168.1.29", 25565);
	if (!device) {
		freeRNGLib();
		return -1;
	}

	freeRNGLib();*/
	return 0;
}