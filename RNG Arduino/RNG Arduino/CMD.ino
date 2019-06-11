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
	threshold [1/2 [nb/AUTO]]
	ethernet [IP/STATUS]
	save
*/
void commandAnalysis(String *cmd, void(*callback)(String)) {
	int argc = 0;
	char **argv = NULL;

	int i = 0;
	bool vn = false;

	splitCMD(cmd, &argc, &argv);

	long int tmp;
	int tmp2;

	if (argc > 0) {

		if (String(argv[i]).equalsIgnoreCase("generate")) {
			i++;
			if (argc > i && (tmp = String(argv[i]).toInt()) <= 0) {
				freeCharMat(&argc, &argv);
				(*callback)("Failure: Please enter a strictly positive number for bits");
				return;
			}
			i++;

			if (argc == i) {
				generateSerial(tmp, vn, callback);
				freeCharMat(&argc, &argv);
				return;
			}

			if (String(argv[i]).equalsIgnoreCase("VN")) {
				i++;
				vn = true;
			}

			if (String(argv[i]).equalsIgnoreCase("SD")) {
				String filename = "test.txt";
				if (argc > i) {
					filename = argv[++i];
				}

				generateSD(tmp, filename, vn, callback);
				freeCharMat(&argc, &argv);
				return;
			}

			generateSerial(tmp, vn, callback);
			freeCharMat(&argc, &argv);
			return;
		}


		if (String(argv[i]).equalsIgnoreCase("threshold")) {
			i++;
			if (argc == i) {
				freeCharMat(&argc, &argv);
				(*callback)(String(getThreshold1()) + " " + String(getThreshold2()));
				return;
			}

			if (String(argv[i]).toInt() <= 0) {
				freeCharMat(&argc, &argv);
				(*callback)("Failure: Please enter a strictly positive number for threshold id");
				return;
			}
			tmp2 = String(argv[i]).toInt();
			i++;

			if (argc == i) {
				freeCharMat(&argc, &argv);
				switch (tmp2) {
				case 1:
					(*callback)(String(getThreshold1()));
					break;
				case 2:
					(*callback)(String(getThreshold2()));
					break;
				default:
					(*callback)("Failure: Invalid threshold id");
					break;
				}
				return;
			}

			if (String(argv[i]).equalsIgnoreCase("AUTO")) {
				i++;
				if (argc < i || (tmp = String(argv[i]).toInt()) <= 0) {
					tmp = 10000000;
				}
				freeCharMat(&argc, &argv);
				switch (tmp2) {
				case 1:
					adjustThreshold1(tmp);
					(*callback)(String(getThreshold1()));
					break;
				case 2:
					adjustThreshold2(tmp);
					(*callback)(String(getThreshold2()));
					break;
				default:
					(*callback)("Failure: Invalid threshold id");
					break;
				}
				return;
			}

			if ((tmp = String(argv[i]).toInt()) < 0) {
				(*callback)("Failure: Please enter a positive number for threshold");
			}
			freeCharMat(&argc, &argv);
			switch (tmp2) {
			case 1:
				setThreshold1(tmp);
				(*callback)(String(getThreshold1()));
				break;
			case 2:
				setThreshold2(tmp);
				(*callback)(String(getThreshold2()));
				break;
			default:
				(*callback)("Failure: Invalid threshold id");
				break;
			}
			return;
		}


		if (String(argv[i]).equalsIgnoreCase("ethernet")) {
			i++;
			if (argc > i) {
				if (String(argv[i]).equalsIgnoreCase("IP")) {
					freeCharMat(&argc, &argv);
					(*callback)(getEthernetIp());
					return;
				}

				if (String(argv[i]).equalsIgnoreCase("STATUS")) {
					freeCharMat(&argc, &argv);
					(*callback)(getEthernetStatus());
					return;
				}

				freeCharMat(&argc, &argv);
				(*callback)("Failure: Invalid parameters");
				return;
			}

			freeCharMat(&argc, &argv);
			if (initEthernet()) {
				(*callback)("Success");
				return;
			}
			else {
				(*callback)("Failure");
				return;
			}
		}


		if (String(argv[i]).equalsIgnoreCase("save")) {
			freeCharMat(&argc, &argv);
			save(callback);
			return;
		}


		freeCharMat(&argc, &argv);
		(*callback)("Failure: Unknown command");
		return;
	}

	freeCharMat(&argc, &argv);
	(*callback)("Failure: Empty command");
	return;
}