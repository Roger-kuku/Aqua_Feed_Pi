#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>

using namespace std;

// Function to get CPU usage
double getCPUUsage() {
    ifstream file("/proc/stat");
    string line;
    getline(file, line);
    file.close();

    istringstream iss(line);
    string cpu;
    long user, nice, system, idle, iowait, irq, softirq, steal;
    iss >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;

    static long prevTotal = 0, prevIdle = 0;
    long total = user + nice + system + idle + iowait + irq + softirq + steal;
    long totalDiff = total - prevTotal;
    long idleDiff = idle - prevIdle;

    prevTotal = total;
    prevIdle = idle;

    return 100.0 * (1.0 - ((double)idleDiff / totalDiff));
}

// Function to get memory usage
void getMemoryUsage(long &total, long &free) {
    ifstream file("/proc/meminfo");
    string line;
    
    getline(file, line);
    sscanf(line.c_str(), "MemTotal: %ld kB", &total);
    
    getline(file, line);
    sscanf(line.c_str(), "MemFree: %ld kB", &free);

    file.close();
}

// Function to get disk usage
double getDiskUsage() {
    system("df / > disk_usage.txt");
    ifstream file("disk_usage.txt");
    string line;
    getline(file, line);
    getline(file, line); // Get second line with actual data

    istringstream iss(line);
    string filesystem, size, used, avail, percent, mountpoint;
    iss >> filesystem >> size >> used >> avail >> percent >> mountpoint;

    file.close();
    return stod(percent.substr(0, percent.size() - 1)); // Remove '%' sign
}

int main() {
    while (true) {
        double cpuUsage = getCPUUsage();
        long totalMem, freeMem;
        getMemoryUsage(totalMem, freeMem);
        double diskUsage = getDiskUsage();

        system("clear"); // Clear screen for a clean refresh
        cout << "===== Raspberry Pi System Monitor =====" << endl;
        cout << "CPU Usage: " << cpuUsage << "%" << endl;
        cout << "Memory Usage: " << ((totalMem - freeMem) / (double)totalMem) * 100 << "%" << endl;
        cout << "Disk Usage: " << diskUsage << "%" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Refresh every second
    }
    
    return 0;
}
