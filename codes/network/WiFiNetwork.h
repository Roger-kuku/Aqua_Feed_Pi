#ifndef WIFI_NETWORK_H
#define WIFI_NETWORK_H

#include <string>
#include <iostream>

using namespace std;

class WiFiNetwork {
public:
    string ssid;
    int signalStrength;
    string encryption;

    WiFiNetwork(string ssid, int signalStrength, string encryption);

    // Display the details of the Wi-Fi network
    void display() const;
};

#endif
