String cmd;


void serialCommand() {
	if (Serial.available() > 0) {
		cmd = Serial.readStringUntil('\n');

		if (cmd.startsWith("generate ")) {
			cmd.remove(0, 9);
			cmd.toInt();
		}
	}
}
