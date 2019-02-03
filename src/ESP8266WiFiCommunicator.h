
#ifndef ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_
#define ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_

#include "Arduino.h"
#include "Stream.h"
#include "avr/pgmspace.h"

namespace ESP8266Wifi {

const char CMD_TEST[] PROGMEM = "AT";
const char CMD_RESTART[] PROGMEM = "AT+RST";
const char CMD_VERSION[] PROGMEM = "AT+GMR";
const char CMD_FACTORY_RESET[] PROGMEM = "AT+RESTORE";
const char CMD_BAUD_CUR[] PROGMEM = "AT+UART_CUR";
const char CMD_BAUD_DEF[] PROGMEM = "AT+UART_DEF";
const char CMD_WIFI_MODE_CUR[] PROGMEM = "AT+CWMODE_CUR";
const char CMD_WIFI_MODE_DEF[] PROGMEM = "AT+CWMODE_DEF";
const char CMD_AP_CONNECT_CUR[] PROGMEM = "AT+CWJAP_CUR";
const char CMD_AP_CONNECT_DEF[] PROGMEM = "AT+CWJAP_DEF";
const char CMD_AP_LIST[] PROGMEM = "AT+CWLAP";
const char CMD_AP_DISCONNECT[] PROGMEM = "AT+CWQAP";
const char CMD_HOTSPOT_MODE_CUR[] PROGMEM = "AT+CWSAP_CUR";
const char CMD_HOTSPOT_MODE_DEF[] PROGMEM = "AT+CWSAP_DEF";
const char CMD_CLIENTS_IP_LIST[] PROGMEM = "AT+CWLIF";
const char CMD_DHCP_CUR[] PROGMEM = "AT+CWDHCP_CUR";
const char CMD_DHCP_DEF[] PROGMEM = "AT+CWDHCP_DEF";
const char CMD_AUTOCONNECT[] PROGMEM = "AT+CWAUTOCONN";
const char CMD_CONN_STATUS[] PROGMEM = "AT+CIPSTATUS";
const char CMD_CONN_SERVER[] PROGMEM = "AT+CIPSTART";
const char CMD_SEND_DATA[] PROGMEM = "AT+CIPSEND";
const char CMD_CONN_CLOSE[] PROGMEM = "AT+CIPCLOSE";
const char CMD_GET_IP[] PROGMEM = "AT+CIFSR";
const char CMD_CONN_MULTIPLE[] PROGMEM = "AT+CIPMUX";
const char CMD_TCP_SRV[] PROGMEM = "AT+CIPSERVER";
const char CMD_PING[] PROGMEM = "AT+PING";

class ESP8266WiFiCommunicator {
	public:
		// Constructors/destructor
		virtual ~ESP8266WiFiCommunicator();
		ESP8266WiFiCommunicator(Stream &in, Stream &out);

		Stream* logger;
		bool logEnabled;
		int delayBetweenResponse;
		unsigned char readerBufferSize;

		// Helper methods

		void message(String msg);
		char * messageln(char msg[]);
		char * messageln(String msg);
		char * readResponse();
		void log(char character[]);
		void logln(char message[]);

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
		Stream* serialIn;
		Stream* serialOut;
};

} /* namespace esp8266wifi */

#endif /* ARDUINO_SENSORS_ESP8266WIFI_ESP8266WIFICOMMUNICATOR_H_ */
