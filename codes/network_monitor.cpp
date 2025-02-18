#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <cstdlib>

using namespace std;

// Function to get network traffic statistics
void getNetworkTraffic(long &rxBytes, long &txBytes) {
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

// Function to list available Wi-Fi networks
void listWiFiNetworks() {
    cout << "\n===== Available Wi-Fi Networks =====" << endl;
    system("sudo iwlist wlan0 scan | grep -E 'ESSID|Signal level|Encryption key'");
}

int main() {
    cout << "===== Network Monitor & Wi-Fi Scanner =====" << endl;
    
    long prevRx = 0, prevTx = 0;

    while (true) {
        long currRx, currTx;
        getNetworkTraffic(currRx, currTx);

        if (prevRx != 0 && prevTx != 0) {
            double downloadSpeed = (currRx - prevRx) / 1024.0; // KB/s
            double uploadSpeed = (currTx - prevTx) / 1024.0;   // KB/s

            system("clear"); // Clear screen for clean output
            cout << "===== Network Traffic =====" << endl;
            cout << "Download Speed: " << downloadSpeed << " KB/s" << endl;
            cout << "Upload Speed:   " << uploadSpeed << " KB/s" << endl;
            
            listWiFiNetworks(); // Show available Wi-Fi networks
        }

        prevRx = currRx;
        prevTx = currTx;

        this_thread::sleep_for(chrono::seconds(3)); // Refresh every 3 seconds
    }

    return 0;
}
