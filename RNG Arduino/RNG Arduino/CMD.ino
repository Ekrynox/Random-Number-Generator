void splitCMD(String *cmd, int *argc, char ***argv) {
	int i = 0;
	int size = (*cmd).length();
	int quote = 0;
	int slash = 0;
	String tmp = "";

	*argc = 0;
	*argv = (char **)malloc(*argc * sizeof(char *));

	while (i < size) {
		if (slash % 2 == 1) {
			tmp += (*cmd)[i];
			slash++;
		}
		else if ((*cmd)[i] == ' ' && quote % 2 == 0) {
			if (tmp.length() > 0) {
				*argv = (char **)realloc(*argv, ++(*argc) * sizeof(char *));
				(*argv)[*argc - 1] = (char *)malloc((tmp.length() + 1) * sizeof(char));
				strcpy((*argv)[*argc - 1], tmp.c_str());
				tmp = "";
			}
		}
		else {
			if ((*cmd)[i] == '"') {
				quote++;
			}
			else if ((*cmd)[i] == '\\') {
				slash++;
			}
			else {
				tmp += (*cmd)[i];
			}
		}

		i++;
	}

	if (tmp.length() > 0) {
		*argv = (char **)realloc(*argv, ++(*argc) * sizeof(char *));
		(*argv)[*argc - 1] = (char *)malloc((tmp.length() + 1) * sizeof(char));
		strcpy((*argv)[*argc - 1], tmp.c_str());
	}
}

void freeCharMat(int *argc, char ***argv) {
	if (*argv != NULL) {
		for (int i = 0; i < *argc; i++) {
			free((*argv)[i]);
		}
		free(*argv);

		*argv = NULL;
		*argc = 0;
	}
}


/*
	generate {nb} [VN] [SD [Filename]]
	threshold [nb/AUTO]
	ethernet [IP/STATUS]
*/
String commandAnalysis(String *cmd) {
	int argc = 0;
	char **argv = NULL;

	splitCMD(cmd, &argc, &argv);

	long int tmp;
	unsigned long int start, end;

	if (argc > 0) {

		if (String(argv[0]).equalsIgnoreCase("generate")) {
			if (argc > 1 && (tmp = String(argv[1]).toInt()) > 0) {
				if (argc == 2) {
					start = millis();
					if (generateSerial(tmp)) {
						end = millis();
						freeCharMat(&argc, &argv);
						return "Success: " + String(end - start) + "ms";
					}
					else {
						freeCharMat(&argc, &argv);
						return "Failure";
					}
				}

				if (String(argv[2]).equalsIgnoreCase("SD")) {
					if (argc == 3) {
						start = millis();
						if (generateSD(tmp, "test.txt")) {
							end = millis();
							freeCharMat(&argc, &argv);
							return "Success: " + String(end - start) + "ms";
						}
						else {
							freeCharMat(&argc, &argv);
							return "Failure";
						}
					}

					start = millis();
					if (generateSD(tmp, argv[3])) {
						end = millis();
						freeCharMat(&argc, &argv);
						return "Success: " + String(end - start) + "ms";
					}
					else {
						freeCharMat(&argc, &argv);
						return "Failure";
					}
				}

				if (String(argv[2]).equalsIgnoreCase("VN")) {
					if (argc == 3) {
						start = millis();
						if (generateSerialVN(tmp)) {
							end = millis();
							freeCharMat(&argc, &argv);
							return "Success: " + String(end - start) + "ms";
						}
						else {
							freeCharMat(&argc, &argv);
							return "Failure";
						}
					}

					if (String(argv[3]).equalsIgnoreCase("SD")) {
						if (argc == 4) {
							start = millis();
							if (generateSDVN(tmp, "test.txt")) {
								end = millis();
								freeCharMat(&argc, &argv);
								return "Success: " + String(end - start) + "ms";
							}
							else {
								freeCharMat(&argc, &argv);
								return "Failure";
							}
						}

						start = millis();
						if (generateSDVN(tmp, argv[4])) {
							end = millis();
							freeCharMat(&argc, &argv);
							return "Success: " + String(end - start) + "ms";
						}
						else {
							freeCharMat(&argc, &argv);
							return "Failure";
						}
					}

				}

				freeCharMat(&argc, &argv);
				return "Failure: Invalid parameters!";
			}

			freeCharMat(&argc, &argv);
			return "Failure: Please enter a strictly positive number!";
		}


		if (String(argv[0]).equalsIgnoreCase("threshold")) {
			if (argc == 1) {
				freeCharMat(&argc, &argv);
				return String(getThreshold());
			}

			if (String(argv[1]).equalsIgnoreCase("AUTO")) {
				if (argc < 2 || (tmp = String(argv[2]).toInt()) <= 0) {
					tmp = 10000000;
				}
				start = millis();
				adjustThreshold(tmp);
				end = millis();
				freeCharMat(&argc, &argv);
				return String(getThreshold()) + " : " + String(end - start) + "ms";
			}

			setThreshold(String(argv[1]).toInt());
			freeCharMat(&argc, &argv);
			return String(getThreshold());
		}


		if (String(argv[0]).equalsIgnoreCase("ethernet")) {
			if (argc > 1) {
				if (String(argv[1]).equalsIgnoreCase("IP")) {
					freeCharMat(&argc, &argv);
					return getEthernetIp();
				}

				if (String(argv[1]).equalsIgnoreCase("STATUS")) {
					freeCharMat(&argc, &argv);
					return getEthernetStatus();
				}

				freeCharMat(&argc, &argv);
				return "Failure: Invalid parameters!";
			}

			freeCharMat(&argc, &argv);
			start = millis();
			if (initEthernet()) {
				end = millis();
				return "Success: " + String(end - start) + "ms";
			}
			else {
				return "Failure";
			}
		}

		freeCharMat(&argc, &argv);
		return "Failure: Unknown command!";
	}

	freeCharMat(&argc, &argv);
	return "Failure: Empty command!";
}