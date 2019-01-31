
#include "ESP8266WiFiHTTPClient.h"

namespace esp8266wifi {

	ESP8266WiFiHTTPClient::ESP8266WiFiHTTPClient(ESP8266WiFiCommunicator &com) {
		communicator = &com;

		isSecured = false;
		port = 3000;
	}

	ESP8266WiFiHTTPClient::~ESP8266WiFiHTTPClient() {
		// TODO Auto-generated destructor stub
	}

	String ESP8266WiFiHTTPClient::createHttpRequest(String method) {
		String headers[] = {
			method + " " + endPoint + " HTTP/1.1",
			"Host: http://" + server + ":" + String(port),
			"Connection: close",
			"Content-Type: application/x-www-form-urlencoded",
			""
		};

		return communicator->sendData(headers, 5);
	}

	String ESP8266WiFiHTTPClient::createHttpRequest(String method, String data) {
		unsigned int dataLength = data.length();
		String headers[] = {
			method + " " + endPoint + " HTTP/1.1",
			"Host: http://" + server + ":" + String(port),
			"Connection: close",
			"Content-Type: application/x-www-form-urlencoded",
			"Content-Length: " + String(dataLength),
			"",
			data,
			""
		};

		Serial.println("Sending data");

		return communicator->sendData(headers, 8);
	}

	String ESP8266WiFiHTTPClient::getReq() {
		communicator->connectToServer(TRANSFER_PROTOKOL, server, port);

		return createHttpRequest("GET");
	}

	String ESP8266WiFiHTTPClient::postReq(String data) {
		communicator->connectToServer(TRANSFER_PROTOKOL, server, port);

		Serial.println("Connect to server");

		return createHttpRequest("POST", data);
	}


	String ESP8266WiFiHTTPClient::putReq(String data) {
		communicator->connectToServer(TRANSFER_PROTOKOL, server, port);

		return createHttpRequest("PUT", data);
	}

	String ESP8266WiFiHTTPClient::deleteReq(String data) {
		communicator->connectToServer(TRANSFER_PROTOKOL, server, port);

		return createHttpRequest("DELETE", data);
	}

}
