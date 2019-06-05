#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


#define WIN32


#ifdef WIN32
	#include <winsock2.h>
	#include <windows.h>
	

	typedef int socklen_t;

#elif defined linux
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <unistd.h>

	#define INVALID_SOCKET -1
	#define SOCKET_ERROR -1
	#define closesocket(s) close (s)

	typedef int SOCKET;
	typedef struct sockaddr_in SOCKADDR_IN;
	typedef struct sockaddr SOCKADDR;
#endif


typedef struct {
	HANDLE hComm;

	SOCKET sock;
	SOCKADDR_IN sin;

	boolean isSerial;
	boolean isEthernet;
} rng;

typedef rng *RNG;

void initRNGLib();
void freeRNGLib();

RNG initRNGSerial(const wchar_t *port);
RNG initRNGEthernet(char addr[], int port);
void closeRNG(RNG *device);

char *RNGGenerate(RNG device, int nb, boolean vn);