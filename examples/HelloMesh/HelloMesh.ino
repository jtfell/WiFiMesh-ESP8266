#include <ESP8266WiFi.h>
#include "WiFiMesh.h"

/* Create the mesh node object */
WiFiMesh mesh_node = WiFiMesh(ESP.getChipId(), manageRequest);

/**
 * Callback for when other nodes send you data. (Documented in WiFiMesh.h)
 */
String manageRequest(String request)
{
	Serial.print("received: ");
	Serial.println(request);
	return String("Hello world response.");
}

void setup()
{
	Serial.begin(115200);
	delay(10);

	Serial.println();
	Serial.println();
	Serial.println("Setting up mesh node...");

	/* Initialise the mesh node */
	mesh_node.begin();
}

void loop()
{
	/* Accept any incoming connections */
	mesh_node.acceptRequest();

	/* Scan for other nodes and send them a message */
	mesh_node.attemptScan("Hello world request.");
	delay(1000);
}
