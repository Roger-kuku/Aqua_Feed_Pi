#include "NetworkMonitor.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

void NetworkMonitor::getNetworkTraffic(long &rxBytes, long &txBytes) {
    ifstream fileRx("/sys/class/net/wlan0/statistics/rx_bytes");
    ifstream fileTx("/sys/class/net/wlan0/statistics/tx_bytes");

    if (fileRx && fileTx) {
        fileRx >> rxBytes;
        fileTx >> txBytes;
    } else {
        cerr << "Error: Could not read network statistics." << endl;
    }

    fileRx.close();
    fileTx.close();
}

vector<WiFiNetwork> NetworkMonitor::scanWiFiNetworks() {
    vector<WiFiNetwork> networks;
    system("sudo iwlist wlan0 scan > wifi_scan.txt");

    ifstream file("wifi_scan.txt");
    string line, ssid = "", encryption = "";
    int signalStrength = -100; // Default worst signal

    while (getline(file, line)) {
        if (line.find("ESSID:") != string::npos) {
            ssid = line.substr(line.find("ESSID:") + 7);
            ssid.erase(remove(ssid.begin(), ssid.end(), '\"'), ssid.end()); // Remove quotes
        }
        if (line.find("Signal level=") != string::npos) {
            size_t pos = line.find("Signal level=");
            signalStrength = stoi(line.substr(pos + 13, line.find(" dBm") - pos - 13));
        }
        if (line.find("Encryption key:") != string::npos) {
            encryption = (line.find("on") != string::npos) ? "on" : "off";
        }

        if (!ssid.empty() && signalStrength > -100) {
            networks.emplace_back(ssid, signalStrength, encryption);
            ssid = ""; // Reset for next network
            signalStrength = -100;
        }
    }
    file.close();

    // Sort networks by signal strength (higher is better)
    sort(networks.begin(), networks.end(), [](WiFiNetwork &a, WiFiNetwork &b) {
        return a.signalStrength > b.signalStrength;
    });

    return networks;
}

void NetworkMonitor::trackNetworkUsage() {
    while (true) {
        long currRx, currTx;
        getNetworkTraffic(currRx, currTx);

        if (prevRx != 0 && prevTx != 0) {
            double downloadSpeed = (currRx - prevRx) / 1024.0; // KB/s
            double uploadSpeed = (currTx - prevTx) / 1024.0;   // KB/s

            system("clear"); // Clear screen for a clean display
            cout << "===== Real-Time Network Traffic =====" << endl;
            cout << "Download Speed: " << downloadSpeed << " KB/s" << endl;
            cout << "Upload Speed:   " << uploadSpeed << " KB/s" << endl;
            
            displayTopWiFiNetworks();
        }

        prevRx = currRx;
        prevTx = currTx;

        this_thread::sleep_for(chrono::seconds(1)); // Refresh every 3 sec
    }
}

void NetworkMonitor::displayTopWiFiNetworks() {
    vector<WiFiNetwork> networks = scanWiFiNetworks();

    cout << "\n===== Top 5 Wi-Fi Networks (Strongest Signal) =====" << endl;
    int count = 0;
    for (const auto &network : networks) {
        network.display();
        if (++count >= 5) break; // Show only top 5
    }
}
