#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include <sys/sysinfo.h>
#include <cstdlib>

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

// Function to get memory usage (total & free)
void getMemoryUsage(long &total, long &free) {
    struct sysinfo info;
    sysinfo(&info);

    total = info.totalram / (1024 * 1024); // Convert to MB
    free = info.freeram / (1024 * 1024);   // Convert to MB
}

// Function to get disk usage (actual size & percentage)
void getDiskUsage(long &total, long &used, long &free, double &percent) {
    system("df / > disk_usage.txt"); // Get disk usage info
    ifstream file("disk_usage.txt");
    string line;
    getline(file, line); // Skip header
    getline(file, line); // Read actual data

    istringstream iss(line);
    string filesystem, size, usedSpace, available, percentStr, mountpoint;
    iss >> filesystem >> size >> usedSpace >> available >> percentStr >> mountpoint;

    total = stol(size) / 1024; // Convert to MB
    used = stol(usedSpace) / 1024;
    free = stol(available) / 1024;
    percent = stod(percentStr.substr(0, percentStr.size() - 1)); // Remove '%' sign

    file.close();
}

// Function to get system uptime
string getUptime() {
    ifstream file("/proc/uptime");
    double uptimeSec;
    file >> uptimeSec;
    file.close();

    int hours = uptimeSec / 3600;
    int minutes = ((int)uptimeSec % 3600) / 60;
    return to_string(hours) + "h " + to_string(minutes) + "m";
}

// Function to get the number of running processes
int getRunningProcesses() {
    ifstream file("/proc/stat");
    string line;
    int processes = 0;
    while (getline(file, line)) {
        if (line.find("procs_running") != string::npos) {
            istringstream iss(line);
            string key;
            iss >> key >> processes;
            break;
        }
    }
    file.close();
    return processes;
}

// Function to get system load averages
void getLoadAverage(double &load1, double &load5, double &load15) {
    ifstream file("/proc/loadavg");
    file >> load1 >> load5 >> load15;
    file.close();
}

int main() {
    while (true) {
        double cpuUsage = getCPUUsage();
        long totalMem, freeMem;
        getMemoryUsage(totalMem, freeMem);

        long totalDisk, usedDisk, freeDisk;
        double diskUsagePercent;
        getDiskUsage(totalDisk, usedDisk, freeDisk, diskUsagePercent);

        string uptime = getUptime();
        int runningProcesses = getRunningProcesses();
        double load1, load5, load15;
        getLoadAverage(load1, load5, load15);

        system("clear"); // Clear screen for a clean refresh
        cout << "===== Raspberry Pi System Monitor =====" << endl;
        cout << "CPU Usage:       " << cpuUsage << " %" << endl;
        cout << "Memory Usage:    " << (totalMem - freeMem) << " MB / " << totalMem << " MB (" 
             << ((totalMem - freeMem) / (double)totalMem) * 100 << " %)" << endl;
        cout << "Disk Usage:      " << usedDisk << " MB / " << totalDisk << " MB (" 
             << diskUsagePercent << " %)" << endl;
        cout << "Free Disk Space: " << freeDisk << " MB" << endl;
        cout << "System Uptime:   " << uptime << endl;
        cout << "Running Processes: " << runningProcesses << endl;
        cout << "Load Average:    " << load1 << " (1m), " << load5 << " (5m), " << load15 << " (15m)" << endl;

        this_thread::sleep_for(chrono::seconds(1)); // Refresh every second
    }
    
    return 0;
}
