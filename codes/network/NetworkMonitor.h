#ifndef NETWORK_MONITOR_H
#define NETWORK_MONITOR_H

#include "WiFiNetwork.h"
#include <vector>

class NetworkMonitor {
private:
    long prevRx = 0, prevTx = 0;

    // Get network traffic statistics
    void getNetworkTraffic(long &rxBytes, long &txBytes);

    // Scan and return a list of available Wi-Fi networks
    std::vector<WiFiNetwork> scanWiFiNetworks();

public:
    // Track network usage in real-time
    void trackNetworkUsage();

    // Display the top 5 Wi-Fi networks based on signal strength
    void displayTopWiFiNetworks();
};

#endif
