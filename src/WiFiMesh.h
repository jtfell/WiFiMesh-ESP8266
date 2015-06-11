/**
 *	WiFiMesh Library
 *
 *	Sets up a Mesh Node which acts as a router via other "Mesh Nodes", creating a Mesh Network. All information
 *	is passed in both directions, but it is up to the user what the data sent is and how it is dealt with.
 *
 *
 *	Created 1 June 2015
 *	By Julian Fell
 */

#ifndef __WIFIMESH_H__
#define __WIFIMESH_H__

#include <WiFiClient.h> 
#include <WiFiServer.h>
#include <functional>

class WiFiMesh {

private:
	String _ssid;
	String _ssid_prefix;
	uint32_t _chip_id;

	std::function<String(String)> _handler;
	
	WiFiServer  _server;
	WiFiClient  _client;

	/**
	 * Connect to the AP at ssid, send them a message then disconnect.
	 *
	 * @message The string to send to a node.
	 * @ssid The name of the AP the other node has set up.
	 * 
	 */
	void connectToNode(String target_ssid, String message);
	bool exchangeInfo(String message, WiFiClient curr_client);
	bool waitForClient(WiFiClient curr_client, int max_wait);

public:

	/**
	 * WiFiMesh Constructor method. Creates a WiFi Mesh Node, ready to be initialised.
	 *
	 * @chip_id A unique identifier number for the node.
	 * @handler The callback handler for dealing with received messages. Takes a string as an argument which
	 *          is the string received from another node and returns the string to send back.
	 * 
	 */
	WiFiMesh(uint32_t chip_id, std::function<String(String)> handler);

	/**
	 * Initialises the node.
	 */
	void begin();

	/**
	 * Scan for other nodes, and exchange the chosen message with any that are found.
	 *
	 * @message The message to send to all other nodes.
	 * 
	 */
	void attemptScan(String message);

	/**
	 * If a client is connected, accept their request and call the hander function.
	 */
	void acceptRequest();
};

#endif
