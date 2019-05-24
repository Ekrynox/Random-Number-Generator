#include "RNG.h"

#include "math.h"
#include "stdlib.h"


boolean initRNGLib() {

}

boolean freeRNGLin() {

}


RNG initRNGSerial(const wchar_t *port) {
	RNG device = (RNG)malloc(sizeof(RNG));
	if (!device) {
		return NULL;
	}

	device->hComm = CreateFile(port, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (device->hComm == INVALID_HANDLE_VALUE) {
		free(device);
		return NULL;
	}


	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	GetCommState(device->hComm, &dcbSerialParams);

	dcbSerialParams.BaudRate = CBR_57600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;

	SetCommState(device->hComm, &dcbSerialParams);

	SetCommMask(device->hComm, EV_RXCHAR);

	device->isSerial = true;

	return device;
}

void closeRNG(RNG device) {
	if (!device) {
		return;
	}

	if (device->isSerial) {
		CloseHandle(device->hComm);
	}

	free(device);
}


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
		if (vn) {
			size += 3;
		}
		char *bits = (char *)malloc(sizeof(char) * size);
		char TempChar;

		if (!bits) {
			return NULL;
		}

		if (vn) {
			sprintf(bits, "generate %d VN\n", nb);
		}
		else {
			sprintf(bits, "generate %d\n", nb);
		}

		if (!WriteFile(device->hComm, bits, sizeof(char) * (size - 1), &Bytes, NULL)) {
			free(bits);
			return NULL;
		}

		WaitCommEvent(device->hComm, &Bytes, NULL);

		Bytes = 0;

		free(bits);
		size = 0;
		bits = (char *)malloc(sizeof(char) * (nb + 1));

		int i = nb - nb % 8;

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