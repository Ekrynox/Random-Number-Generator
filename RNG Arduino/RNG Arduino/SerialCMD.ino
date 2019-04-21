String cmd;


void serialCommand() {
	if (Serial.available() > 0) {
		cmd = Serial.readStringUntil('\n');

		if (cmd.startsWith("generate ")) {
			cmd.remove(0, 9);
			cmd.toInt();
			return;
		}

		if (cmd.startsWith("generateSD ")) {
			cmd.remove(0, 11);
			uint32_t ts1 = millis();
			if (generateSD(cmd.toInt(), "test.txt")) {
				//Serial.println("Success");
				Serial.println(millis() - ts1);
			}
			else {
				Serial.println("Failure");
			}
			return;
		}
	}
}
