byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
int tcpPort = 25565;

EthernetServer tcpServer = EthernetServer(tcpPort);


bool initEthernet() {
	Ethernet.init(SPI_ETHERNET_PIN);
	if (Ethernet.linkStatus() == LinkOFF) {
		return false;
	}
	if (!Ethernet.begin(mac)) {
		return false;
	}

	tcpServer.begin();
	return true;
}

String getEthernetStatus() {
	if (Ethernet.linkStatus() == Unknown) {
		return "Unknown";
	}
	else if (Ethernet.linkStatus() == LinkON) {
		return "Connected";
	}
	else if (Ethernet.linkStatus() == LinkOFF) {
		return "Disconnected";
	}
}

String getEthernetIp() {
	IPAddress ip = Ethernet.localIP();
	char sip[16];
	sprintf(sip, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
	return String(sip);
}


void checkEthernetClient() {
	EthernetClient client = tcpServer.available();
	if (client) {
		Serial.println(client.read());
	}
}