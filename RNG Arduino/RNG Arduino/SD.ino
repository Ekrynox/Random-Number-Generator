#define SD_CONFIG_PATH "/Config/"
#define SD_OUTPUT_PATH "/Output/"
#define SD_BUFFER_SIZE 1024


SdFat SD;
char buffSD[SD_BUFFER_SIZE + 1];


bool generateSD(long int nb, String filename, bool vn, void(*callback)(String)) {
	if (!SD.begin(SPI_SD_PIN, SPI_FULL_SPEED)) {
		(*callback)("Failure: No Valid SD Card");
		return false;
	}

	if (!SD.exists(SD_OUTPUT_PATH)) {
		SD.mkdir(SD_OUTPUT_PATH);
	}

	File myFile = SD.open(SD_OUTPUT_PATH + filename, O_WRITE | O_TRUNC | O_CREAT);
	if (!myFile) {
		(*callback)("Failure: Could't open the file");
		return false;
	}

	(*callback)("Ok");

	int i;
	unsigned long start = millis();

	if (vn) {
		while (nb > 0) {
			for (i = 0; i < SD_BUFFER_SIZE; i++) {
				buffSD[i] = genBitCharVN();
			}
			buffSD[min(SD_BUFFER_SIZE, abs(nb))] = '\0';
			myFile.print(buffSD);
			nb -= SD_BUFFER_SIZE;
		}
	}
	else {
		while (nb > 0) {
			for (i = 0; i < SD_BUFFER_SIZE; i++) {
				buffSD[i] = genBitChar();
			}
			buffSD[min(SD_BUFFER_SIZE, abs(nb))] = '\0';
			myFile.print(buffSD);
			nb -= SD_BUFFER_SIZE;
		}
	}

	myFile.flush();
	myFile.close();

	unsigned long end = millis();
	delay(2000);
	(*callback)(String(end - start) + "ms");

	return true;
}


bool save(void(*callback)(String)) {
	if (!SD.begin(SPI_SD_PIN, SPI_FULL_SPEED)) {
		(*callback)("Failure: No Valid SD Card");
		return false;
	}

	if (!SD.exists(SD_CONFIG_PATH)) {
		SD.mkdir(SD_CONFIG_PATH);
	}


	File myFile = SD.open(SD_CONFIG_PATH + String("threshold"), O_WRITE | O_TRUNC | O_CREAT);
	if (!myFile) {
		(*callback)("Failure: Could't open the threshold file");
		return false;
	}

	myFile.println(getThreshold1());
	myFile.println(getThreshold2());

	myFile.flush();
	myFile.close();

	(*callback)("Success");

	return true;
}

bool loadSave() {
	if (!SD.begin(SPI_SD_PIN, SPI_FULL_SPEED)) {
		return false;
	}

	if (!SD.exists(SD_CONFIG_PATH)) {
		return false;
	}


	File myFile = SD.open(SD_CONFIG_PATH + String("threshold"), O_READ);
	if (myFile) {
		long tmp1 = myFile.readStringUntil('\n').toInt();
		long tmp2 = myFile.readStringUntil('\n').toInt();
		if (tmp1 >= 0 || tmp2 >= 0) {
			setThreshold1(tmp1);
			setThreshold2(tmp2);
		}
		myFile.close();
	}

	return true;
}