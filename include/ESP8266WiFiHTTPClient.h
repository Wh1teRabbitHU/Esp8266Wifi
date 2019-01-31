/*
 * ESP8266WiFiHTTPClient.h
 *
 *  Created on: Apr 24, 2017
 *      Author: tamasruszka
 */

#ifndef ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFIHTTPCLIENT_H_
#define ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFIHTTPCLIENT_H_

#include "Arduino.h"
#include "ESP8266WiFiCommunicator.h"
#include "avr/pgmspace.h"

namespace esp8266wifi {

class ESP8266WiFiHTTPClient {
	public:
		ESP8266WiFiHTTPClient(ESP8266WiFiCommunicator &com);
		virtual ~ESP8266WiFiHTTPClient();

		bool isSecured;
		String server;
		int port;
		String endPoint;

		String getReq();
		String postReq(String data);
		String putReq(String data);
		String deleteReq(String data);
	private:
		ESP8266WiFiCommunicator* communicator;

		String createHttpRequest(String method);
		String createHttpRequest(String method, String data);

		const String TRANSFER_PROTOKOL PROGMEM = "TCP";
};

} /* namespace esp8266wifi */

#endif /* ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFIHTTPCLIENT_H_ */
