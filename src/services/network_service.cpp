#include "src/services/network_service.h"
#include <cstring>

void network_service_init(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass) {
    // Initialize network
}

bool network_service_is_connected() {
    // Return network status
    return true;
}

#include <WiFi.h>


NetworkInfo network_service_get_info() {
    NetworkInfo info;
    // Get STA IP address
    IPAddress sta_ip = WiFi.localIP();
    snprintf(info.ip, sizeof(info.ip), "%d.%d.%d.%d", sta_ip[0], sta_ip[1], sta_ip[2], sta_ip[3]);
    // Get AP IP address
    IPAddress ap_ip = WiFi.softAPIP();
    snprintf(info.ap_ip, sizeof(info.ap_ip), "%d.%d.%d.%d", ap_ip[0], ap_ip[1], ap_ip[2], ap_ip[3]);
    // Get connection status
    info.connected = (WiFi.status() == WL_CONNECTED);
    // Get STA SSID or "NA" if not connected
    if (info.connected) {
        strncpy(info.ssid, WiFi.SSID().c_str(), sizeof(info.ssid));
        info.ssid[sizeof(info.ssid) - 1] = '\0'; // Ensure null-termination
    } else {
        strncpy(info.ssid, "NA", sizeof(info.ssid));
        info.ssid[sizeof(info.ssid) - 1] = '\0';
    }
    // Get AP SSID
    strncpy(info.ap_ssid, WiFi.softAPSSID().c_str(), sizeof(info.ap_ssid));
    info.ap_ssid[sizeof(info.ap_ssid) - 1] = '\0';
    return info;
}
