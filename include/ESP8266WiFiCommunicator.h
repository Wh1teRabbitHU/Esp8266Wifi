/*
 * ESP8266WiFiCommunicator.h
 *
 *  Created on: Apr 24, 2017
 *      Author: tamasruszka
 */

#ifndef ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_
#define ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_

#include "Arduino.h"
#include "Stream.h"
#include "avr/pgmspace.h"

namespace esp8266wifi {

class ESP8266WiFiCommunicator {
	public:
		// Constructors/destructor
		virtual ~ESP8266WiFiCommunicator();
		ESP8266WiFiCommunicator(Stream &in, Stream &out);

		Stream* logger;
		bool logResponse;
		int delayBetweenResponse;

		void message(String msg);
		String messageln(String msg);
		String readResponse();

		// Communication methods

		String test(void);
		String restart(void);
		String version(void);
		String factoryReset(void);
		String changeBaudRate(int baud, int databits, int stopbits, int parity, int flowControl);
		String changeBaudRatePermanent(int baud, int databits, int stopbits, int parity, int flowControl);
		String setWifiMode(int mode);
		String setWifiModePermanent(int mode);
		String connectToAp(String ssid, String password);
		String connectToAp(String ssid, String password, int channel);
		String connectToApPermanent(String ssid, String password);
		String connectToApPermanent(String ssid, String password, int channel);
		String listAvailableAps(void);
		String disconnectFromAp(void);
		String setupHotspot(String name, String password, int channel, int security);
		String setupHotspotPermanent(String name, String password, int channel, int security);
		String clientList(void);
		String changeDhcp(int mode, bool enable);
		String changeDhcpPermanent(int mode, bool enable);
		String changeAutoConnection(bool autoConnect);
		String connectionStatus(void);
		String connectToServer(String protocol, String address, int port);
		String connectToServer(String protocol, String address, int port, int channel);
		String sendData(String data[], int rows);
		String sendData(String data[], int rows, int channel);
		String closeConnection(void);
		String closeConnection(int channel);
		String getIpAddress(void);
		String changeMultipleConnection(bool multiple);
		String configureTcpServer(int mode);
		String configureTcpServer(int mode, int port);
		String ping(String address);

	private:
		const String CMD_TEST PROGMEM = "AT";
		const String CMD_RESTART PROGMEM = "AT+RST";
		const String CMD_VERSION PROGMEM = "AT+GMR";
		const String CMD_FACTORY_RESET PROGMEM = "AT+RESTORE";
		const String CMD_BAUD_CUR PROGMEM = "AT+UART_CUR";
		const String CMD_BAUD_DEF PROGMEM = "AT+UART_DEF";
		const String CMD_WIFI_MODE_CUR PROGMEM = "AT+CWMODE_CUR";
		const String CMD_WIFI_MODE_DEF PROGMEM = "AT+CWMODE_DEF";
		const String CMD_AP_CONNECT_CUR PROGMEM = "AT+CWJAP_CUR";
		const String CMD_AP_CONNECT_DEF PROGMEM = "AT+CWJAP_DEF";
		const String CMD_AP_LIST PROGMEM = "AT+CWLAP";
		const String CMD_AP_DISCONNECT PROGMEM = "AT+CWQAP";
		const String CMD_HOTSPOT_MODE_CUR PROGMEM = "AT+CWSAP_CUR";
		const String CMD_HOTSPOT_MODE_DEF PROGMEM = "AT+CWSAP_DEF";
		const String CMD_CLIENTS_IP_LIST PROGMEM = "AT+CWLIF";
		const String CMD_DHCP_CUR PROGMEM = "AT+CWDHCP_CUR";
		const String CMD_DHCP_DEF PROGMEM = "AT+CWDHCP_DEF";
		const String CMD_AUTOCONNECT PROGMEM = "AT+CWAUTOCONN";
		const String CMD_CONN_STATUS PROGMEM = "AT+CIPSTATUS";
		const String CMD_CONN_SERVER PROGMEM = "AT+CIPSTART";
		const String CMD_SEND_DATA PROGMEM = "AT+CIPSEND";
		const String CMD_CONN_CLOSE PROGMEM = "AT+CIPCLOSE";
		const String CMD_GET_IP PROGMEM = "AT+CIFSR";
		const String CMD_CONN_MULTIPLE PROGMEM = "AT+CIPMUX";
		const String CMD_TCP_SRV PROGMEM = "AT+CIPSERVER";
		const String CMD_PING PROGMEM = "AT+PING";

		Stream* serialIn;
		Stream* serialOut;
};

} /* namespace esp8266wifi */

#endif /* ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_ */
