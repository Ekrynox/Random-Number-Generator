byte mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

EthernetUDP Udp;


bool initEthernet() {
	Ethernet.init(SPI_ETHERNET_PIN);
	if (!Ethernet.begin(mac)) {
		return false;
	}

	return true;
}