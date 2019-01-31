
#include "ESP8266WiFiCommunicator.h"

namespace esp8266wifi {

	ESP8266WiFiCommunicator::ESP8266WiFiCommunicator(Stream &in, Stream &out){
		serialIn = &in;
		serialOut = &out;

		logger = &Serial;
		logResponse = true;
		delayBetweenResponse = 150;
	}

	ESP8266WiFiCommunicator::~ESP8266WiFiCommunicator() {
		// TODO Auto-generated destructor stub
	}

	void ESP8266WiFiCommunicator::message(String msg) {
		serialOut->print(msg);
	}

	String ESP8266WiFiCommunicator::messageln(String msg) {
		serialOut->println(msg);

		delay(delayBetweenResponse);

		return readResponse();
	}

	String ESP8266WiFiCommunicator::readResponse() {
		char c = '\0';
		String response = "";

		while (serialIn->available()) {
			c = serialIn->read();
			response += c;
		}

		if (logResponse && response != "") {
			logger->println(response);
		}

		return response;
	}

	#ifdef USE_TEST
	String ESP8266WiFiCommunicator::test() {
		return messageln(CMD_TEST);
	}
	#endif

	String ESP8266WiFiCommunicator::restart() {
		return messageln(CMD_RESTART);
	}

	String ESP8266WiFiCommunicator::version() {
		return messageln(CMD_VERSION);
	}

	String ESP8266WiFiCommunicator::factoryReset() {
		return messageln(CMD_FACTORY_RESET);
	}

	String ESP8266WiFiCommunicator::changeBaudRate(int baud, int databits, int stopbits, int parity, int flowControl) {
		return messageln(CMD_BAUD_CUR + "=" + String(baud) + "," + String(databits) + "," + String(stopbits) + "," + String(parity) + "," + String(flowControl));
	}

	String ESP8266WiFiCommunicator::changeBaudRatePermanent(int baud, int databits, int stopbits, int parity, int flowControl) {
		return messageln(CMD_BAUD_DEF + "=" + String(baud) + "," + String(databits) + "," + String(stopbits) + "," + String(parity) + "," + String(flowControl));
	}

	String ESP8266WiFiCommunicator::setWifiMode(int mode) {
		return messageln(CMD_WIFI_MODE_CUR + "=" + String(mode));
	}

	String ESP8266WiFiCommunicator::setWifiModePermanent(int mode) {
		return messageln(CMD_WIFI_MODE_DEF + "=" + String(mode));
	}

	String ESP8266WiFiCommunicator::connectToAp(String ssid, String password) {
		return messageln(CMD_AP_CONNECT_CUR + "=\"" + String(ssid) + "\",\"" + String(password) + "\"");
	}

	String ESP8266WiFiCommunicator::connectToAp(String ssid, String password, int channel) {
		return messageln(CMD_AP_CONNECT_CUR + "=" + String(channel) + ",\"" + String(ssid) + "\",\"" + String(password) + "\"");
	}

	String ESP8266WiFiCommunicator::connectToApPermanent(String ssid, String password) {
		return messageln(CMD_AP_CONNECT_DEF + "=\"" + String(ssid) + "\",\"" + String(password) + "\"");
	}

	String ESP8266WiFiCommunicator::connectToApPermanent(String ssid, String password, int channel) {
		return messageln(CMD_AP_CONNECT_DEF + "=" + String(channel) + ",\"" + String(ssid) + "\",\"" + String(password) + "\"");
	}

	String ESP8266WiFiCommunicator::listAvailableAps() {
		return messageln(CMD_AP_LIST);
	}

	String ESP8266WiFiCommunicator::disconnectFromAp() {
		return messageln(CMD_AP_DISCONNECT);
	}

	String ESP8266WiFiCommunicator::setupHotspot(String name, String password, int channel, int security) {
		return messageln(CMD_HOTSPOT_MODE_CUR + "=\"" + String(name) + "\",\"" + String(password) + "\"," + String(channel) + "," + String(security));
	}

	String ESP8266WiFiCommunicator::setupHotspotPermanent(String name, String password, int channel, int security) {
		return messageln(CMD_HOTSPOT_MODE_DEF + "=\"" + String(name) + "\",\"" + String(password) + "\"," + String(channel) + "," + String(security));
	}

	String ESP8266WiFiCommunicator::clientList() {
		return messageln(CMD_CLIENTS_IP_LIST);
	}

	String ESP8266WiFiCommunicator::changeDhcp(int mode, bool enable) {
		return messageln(CMD_DHCP_CUR + "=" + String(mode) + "," + (enable ? "1" : "0"));
	}

	String ESP8266WiFiCommunicator::changeDhcpPermanent(int mode, bool enable) {
		return messageln(CMD_DHCP_DEF + "=" + String(mode) + "," + (enable ? "1" : "0"));
	}

	String ESP8266WiFiCommunicator::changeAutoConnection(bool autoConnect) {
		return messageln(CMD_AUTOCONNECT + "=" + (autoConnect ? "1" : "0"));
	}

	String ESP8266WiFiCommunicator::connectionStatus() {
		return messageln(CMD_CONN_STATUS);
	}

	String ESP8266WiFiCommunicator::connectToServer(String protocol, String address, int port) {
		return messageln(CMD_CONN_SERVER + "=\"" + protocol + "\",\"" + address + "\"," + String(port));
	}

	String ESP8266WiFiCommunicator::connectToServer(String protocol, String address, int port, int channel) {
		return messageln(CMD_CONN_SERVER + "=" + String(channel) + ",\"" + protocol + "\",\"" + address + "\"," + String(port));
	}

	String ESP8266WiFiCommunicator::sendData(String data[], int rows) {
		unsigned int dataLength = 0;

		for (int i = 0; i < 8; i++) {
			dataLength += data[i].length() + 2;
		}

		message(CMD_SEND_DATA + "=" + String(dataLength) + "\r\n");

		for (int i = 0; i < 8; i++) {
			message(data[i] + "\r\n");
			delay(150);
		}

		return readResponse();
	}

	String ESP8266WiFiCommunicator::sendData(String data[], int rows, int channel) {
		unsigned int dataLength = 0;

		for (int i = 0; i < rows; i++) {
			dataLength += data[i].length() + 2;
		}

		messageln(CMD_SEND_DATA + "=" + String(channel) + "," + String(dataLength) + "\r\n");

		for (int i = 0; i < rows; i++) {
			message(data[i] + "\r\n");
		}

		return readResponse();
	}

	String ESP8266WiFiCommunicator::closeConnection() {
		return messageln(CMD_CONN_CLOSE);
	}

	String ESP8266WiFiCommunicator::closeConnection(int channel) {
		return messageln(CMD_CONN_CLOSE + "=" + String(channel));
	}

	String ESP8266WiFiCommunicator::getIpAddress() {
		return messageln(CMD_GET_IP);
	}

	String ESP8266WiFiCommunicator::changeMultipleConnection(bool multiple) {
		return messageln(CMD_CONN_MULTIPLE + "=" + (multiple ? "1" : "0"));
	}

	String ESP8266WiFiCommunicator::configureTcpServer(int mode) {
		return messageln(CMD_TCP_SRV + "=" + String(mode));
	}

	String ESP8266WiFiCommunicator::configureTcpServer(int mode, int port) {
		return messageln(CMD_TCP_SRV + "=" + String(mode) + "," + String(port));
	}

	String ESP8266WiFiCommunicator::ping(String address) {
		return messageln(CMD_PING);
	}

}
