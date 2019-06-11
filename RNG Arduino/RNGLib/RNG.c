#include "RNG.h"

#include "math.h"
#include "stdlib.h"


#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


void initRNGLib() {
	#ifdef WIN32
		WSADATA WSAData;
		WSAStartup(MAKEWORD(2, 2), &WSAData);
	#endif
}

void freeRNGLib() {
	#ifdef WIN32
		WSACleanup();
	#endif
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

	if (!SetCommState(device->hComm, &dcbSerialParams)) {
		closeRNG(&device);
		return NULL;
	}

	COMMTIMEOUTS timeouts = { 0 };
	timeouts.ReadIntervalTimeout = 50; // in milliseconds
	timeouts.ReadTotalTimeoutConstant = 50; // in milliseconds
	timeouts.ReadTotalTimeoutMultiplier = 10; // in milliseconds
	timeouts.WriteTotalTimeoutConstant = 50; // in milliseconds
	timeouts.WriteTotalTimeoutMultiplier = 10; // in milliseconds

	if(!SetCommTimeouts(device->hComm, &timeouts)) {
		closeRNG(&device);
		return NULL;
	}

	device->isSerial = true;
	device->isEthernet = false;

	return device;
}


RNG initRNGEthernet(char addr[], int port) {
	RNG device = (RNG)malloc(sizeof(RNG));
	if (!device) {
		return NULL;
	}

	device->sock = socket(AF_INET, SOCK_STREAM, 0);
	device->sin.sin_addr.s_addr = inet_addr(addr);
	device->sin.sin_family = AF_INET;
	device->sin.sin_port = htons(port);

	if (connect(device->sock, (SOCKADDR*)&(device->sin), sizeof(device->sin)) == SOCKET_ERROR) {
		closesocket(device->sock);
		free(device);
		return NULL;
	}

	device->isSerial = false;
	device->isEthernet = true;
	return device;
}


void closeRNG(RNG *device) {
	if (!device || !*device) {
		device = NULL;
		return;
	}

	if ((*device)->isSerial) {
		CloseHandle((*device)->hComm);
	}

	if ((*device)->isEthernet) {
		closesocket((*device)->sock);
	}

	free(*device);
	device = NULL;
}