#include "src/services/hal_network.h"
#include <cstring>

void hal_network_init(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass) {
    // Initialize network
}

bool hal_network_is_connected() {
    // Return network status
    return true;
}

NetworkInfo hal_network_get_info() {
    NetworkInfo info;
    // Fill with dummy data for now
    strcpy(info.ip, "192.168.4.1");
    strcpy(info.ssid, "ESP32_AP");
    info.connected = true;
    return info;
}
