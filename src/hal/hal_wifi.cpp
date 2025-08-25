#include "src/hal/hal_wifi.h"
#include <WiFi.h>

void hal_wifi_init_ap_sta(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass) {
    WiFi.mode(WIFI_AP_STA);
    WiFi.softAP(ap_ssid, ap_pass);
    WiFi.begin(sta_ssid, sta_pass);
}

bool hal_wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}
