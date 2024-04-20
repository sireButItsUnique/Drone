#include <WiFi.h>
#include <WiFiUdp.h>
#define UDP_PORT 4210

// UDP
WiFiUDP UDP;
char packet[255];
char reply[] = "Packet received!";

WiFiServer server(80);
void setup() {
	// Setup serial port
	Serial.begin(115200);
	Serial.println("ESP32 Booted");

	WiFi.mode(WIFI_AP);
	WiFi.softAP("Drone", NULL);
	IPAddress IP = WiFi.softAPIP();

	Serial.println(IP);
	server.begin();

	// Begin listening to UDP port
	UDP.begin(UDP_PORT);
	Serial.print("Listening on UDP port ");
	Serial.println(UDP_PORT);
}

void loop() {

	// If packet received
	int packetSize = UDP.parsePacket();
	if (packetSize) {
		int len = UDP.read(packet, 255);
		if (len > 0) {
			packet[len] = '\0';
		}
		Serial.print("Packet received: ");
		Serial.println(packet);
	}
}