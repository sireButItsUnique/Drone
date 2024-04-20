#include <WiFi.h>

WiFiServer server(80);

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	Serial.println("ESP32 Booted");

	WiFi.mode(WIFI_AP);
	WiFi.softAP("Drone", NULL);
	IPAddress IP = WiFi.softAPIP();

	Serial.println(IP);
	server.begin();
}

void loop() {
	WiFiClient client = server.available();

	if (client) {
		Serial.println("New Client.");

		// make a String to hold incoming data from the client
		String currentLine = "";
		while (client.connected()) {

			// read byte from the client
			if (client.available()) {
				char c = client.read();

				// newline -> reset line or end request
				if (c == '\n') {

					// two blanks in a row = request ended, send response
					if (currentLine.length() == 0) {

						// start http response
						client.println("HTTP/1.1 200 OK");
						client.println("Content-type:text/html");
						client.println("Connection: close");
						client.println();

						// Send client data
						break;
					} else {
						Serial.println(currentLine);
						currentLine = "";
					}
				}

				// add everything else to cur line
				else if (c != '\r') {
					currentLine += c;
				}
			}
		}

		// Close the connection
		client.stop();
		Serial.println("Client disconnected.");
		Serial.println("");
	}
}
