#include "RNG.h"

#include "math.h"
#include "stdlib.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")



char *RNGGenerate(RNG device, int nb, boolean vn) {
	if (!device) {
		return NULL;
	}

	if (nb < 1) {
		return NULL;
	}

	if (device->isSerial) {
		DWORD Bytes = 0;


		int size = 12 + (int)log10(nb + 1);
		if (vn == true) {
			size += 3;
		}
		char *bits = (char *)malloc(sizeof(char) * size);
		char TempChar;

		if (!bits) {
			return NULL;
		}

		if (vn == true) {
			sprintf(bits, "generate %d VN\n", nb);
		}
		else {
			sprintf(bits, "generate %d\n", nb);
		}

		if (!WriteFile(device->hComm, bits, sizeof(char) * (size - 1), &Bytes, NULL)) {
			free(bits);
			return NULL;
		}

		Bytes = 0;

		free(bits);
		size = 0;
		bits = (char *)malloc(sizeof(char) * (nb + 1));

		int i = nb - nb % 8;

		WaitCommEvent(device->hComm, &Bytes, NULL);

		do {
			ReadFile(device->hComm, &TempChar, sizeof(char), &Bytes, NULL);
			if (Bytes > 0) {
				size += 8;
				bits[size - 1] = TempChar & 0b00000001 ? '1' : '0';
				bits[size - 2] = TempChar & 0b00000010 ? '1' : '0';
				bits[size - 3] = TempChar & 0b00000100 ? '1' : '0';
				bits[size - 4] = TempChar & 0b00001000 ? '1' : '0';
				bits[size - 5] = TempChar & 0b00010000 ? '1' : '0';
				bits[size - 6] = TempChar & 0b00100000 ? '1' : '0';
				bits[size - 7] = TempChar & 0b01000000 ? '1' : '0';
				bits[size - 8] = TempChar & 0b10000000 ? '1' : '0';
			}
		} while (Bytes > 0 && size < i);

		if (size < nb) {
			ReadFile(device->hComm, &TempChar, sizeof(char), &Bytes, NULL);
			if (Bytes > 0) {
				if (size < nb)
					bits[size++] = TempChar & 0b10000000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b01000000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00100000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00010000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00001000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000100 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000010 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000001 ? '1' : '0';
			}
		}

		bits[size] = '\0';

		return bits;
	}

	return NULL;
}


char *RNGGenerateSD(RNG device, int nb, boolean vn, char filename[]) {
	if (!device) {
		return NULL;
	}

	if (nb < 1) {
		return NULL;
	}

	if (strlen(filename) <= 0) {
		return NULL;
	}

	if (device->isSerial) {
		DWORD Bytes = 0;


		int size = 16 + (int)log10(nb + 1);
		if (vn == true) {
			size += 3;
		}
		char *bits = (char *)malloc(sizeof(char) * size);
		char TempChar;

		if (!bits) {
			return NULL;
		}

		if (vn == true) {
			sprintf(bits, "generate %d VN SD %s\n", nb, filename);
		}
		else {
			sprintf(bits, "generate %d SD %s\n", nb, filename);
		}

		if (!WriteFile(device->hComm, bits, sizeof(char) * (size - 1), &Bytes, NULL)) {
			free(bits);
			return NULL;
		}

		Bytes = 0;

		free(bits);
		size = 0;
		bits = (char *)malloc(sizeof(char) * (nb + 1));

		int i = nb - nb % 8;

		WaitCommEvent(device->hComm, &Bytes, NULL);

		do {
			ReadFile(device->hComm, &TempChar, sizeof(char), &Bytes, NULL);
			if (Bytes > 0) {
				size += 8;
				bits[size - 1] = TempChar & 0b00000001 ? '1' : '0';
				bits[size - 2] = TempChar & 0b00000010 ? '1' : '0';
				bits[size - 3] = TempChar & 0b00000100 ? '1' : '0';
				bits[size - 4] = TempChar & 0b00001000 ? '1' : '0';
				bits[size - 5] = TempChar & 0b00010000 ? '1' : '0';
				bits[size - 6] = TempChar & 0b00100000 ? '1' : '0';
				bits[size - 7] = TempChar & 0b01000000 ? '1' : '0';
				bits[size - 8] = TempChar & 0b10000000 ? '1' : '0';
			}
		} while (Bytes > 0 && size < i);

		if (size < nb) {
			ReadFile(device->hComm, &TempChar, sizeof(char), &Bytes, NULL);
			if (Bytes > 0) {
				if (size < nb)
					bits[size++] = TempChar & 0b10000000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b01000000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00100000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00010000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00001000 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000100 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000010 ? '1' : '0';
				if (size < nb)
					bits[size++] = TempChar & 0b00000001 ? '1' : '0';
			}
		}

		bits[size] = '\0';

		return bits;
	}

	return NULL;
}