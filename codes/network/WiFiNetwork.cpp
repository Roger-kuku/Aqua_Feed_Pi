#include "WiFiNetwork.h"

WiFiNetwork::WiFiNetwork(string ssid, int signalStrength, string encryption) {
    this->ssid = ssid;
    this->signalStrength = signalStrength;
    this->encryption = encryption;
}

void WiFiNetwork::display() const {
    cout << "SSID: " << ssid 
         << " | Signal: " << signalStrength << " dBm"
         << " | Security: " << (encryption == "on" ? "Encrypted" : "Open") 
         << endl;
}
