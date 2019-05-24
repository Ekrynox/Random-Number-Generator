#pragma once

#include <stdbool.h>
#include <stdio.h>

#include <windows.h>


typedef struct {
	HANDLE hComm;

	boolean isSerial;
} rng;

typedef rng *RNG;

boolean initRNGLib();
boolean freeRNGLin();

RNG initRNGSerial(const wchar_t *port);
void closeRNG(RNG device);

char *RNGGenerate(RNG device, int nb, boolean vn);