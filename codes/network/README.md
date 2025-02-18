# **Network Monitor on Raspberry Pi**

This project is designed to monitor real-time network usage (download and upload speeds) and display the top 5 Wi-Fi networks available based on signal strength using your Raspberry Pi. The program is implemented in **C++** and uses basic file operations and system commands to gather information.

---

## **Prerequisites**

Before running the program, ensure the following:

1. **Raspberry Pi** with **Raspberry Pi OS** installed.
2. **C++ compiler** (`g++`).
3. **Wireless network interface** (Wi-Fi adapter) connected and enabled on the Raspberry Pi.
4. **`iwlist` tool** (for Wi-Fi scanning) should be installed.
   
You can install `iwlist` by running:

```bash
sudo apt-get update
sudo apt-get install wireless-tools

```
===== Real-Time Network Traffic =====
Download Speed: 100.5 KB/s
Upload Speed:   45.2 KB/s

===== Top 5 Wi-Fi Networks (Strongest Signal) =====
SSID: Network1 | Signal: -45 dBm | Security: Encrypted
SSID: Network2 | Signal: -50 dBm | Security: Open
SSID: Network3 | Signal: -60 dBm | Security: Encrypted
SSID: Network4 | Signal: -65 dBm | Security: Open
SSID: Network5 | Signal: -70 dBm | Security: Encrypted

