#define SD_OUTPUT_PATH "/Output/"
#define SD_BUFFER_SIZE 1024


SdFat SD;
char buffSD[SD_BUFFER_SIZE + 1];


bool generateSD(long int nb, String filename) {
	if (!SD.begin(SPI_SD_PIN, SPI_FULL_SPEED)) {
		return false;
	}

	if (!SD.exists(SD_OUTPUT_PATH)) {
		SD.mkdir(SD_OUTPUT_PATH);
	}

	File myFile = SD.open(SD_OUTPUT_PATH + filename, O_WRITE | O_TRUNC | O_CREAT);
	if (!myFile) {
		return false;
	}

	int i;

	while (nb > 0) {
		for (i = 0; i < SD_BUFFER_SIZE; i++) {
			buffSD[i] = genBitChar();
		}
		buffSD[min(SD_BUFFER_SIZE, abs(nb))] = '\0';
		myFile.print(buffSD);
		nb -= SD_BUFFER_SIZE;
	}

	myFile.flush();
	myFile.close();
	return true;
}

bool generateSDVN(long int nb, String filename) {
	if (!SD.begin(SPI_SD_PIN, SPI_FULL_SPEED)) {
		return false;
	}

	if (!SD.exists(SD_OUTPUT_PATH)) {
		SD.mkdir(SD_OUTPUT_PATH);
	}

	File myFile = SD.open(SD_OUTPUT_PATH + filename, O_WRITE | O_TRUNC | O_CREAT);
	if (!myFile) {
		return false;
	}

	int i;

	while (nb > 0) {
		i = 0;
		while (i < SD_BUFFER_SIZE) {
			if (genBit()) {
				if (!genBit()) {
					buffSD[i] = '1';
					i++;
				}
			}
			else {
				if (genBit()) {
					buffSD[i] = '0';
					i++;
				}
			}
		}
		buffSD[min(SD_BUFFER_SIZE, abs(nb))] = '\0';
		myFile.print(buffSD);
		nb -= SD_BUFFER_SIZE;
	}

	myFile.flush();
	myFile.close();
	return true;
}
