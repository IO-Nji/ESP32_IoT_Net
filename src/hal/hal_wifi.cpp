#include "src/hal/hal_wifi.h"
#include <WiFi.h>

void hal_wifi_init_ap_sta(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass) {
    Serial.println("[WiFi] Initializing AP+STA mode...");
    WiFi.mode(WIFI_AP_STA);
    bool apStarted = WiFi.softAP(ap_ssid, ap_pass);
    if (apStarted) {
        Serial.print("[WiFi] AP started. SSID: ");
        Serial.print(ap_ssid);
        Serial.print(" IP: ");
        Serial.println(WiFi.softAPIP());
    } else {
        Serial.println("[WiFi] AP failed to start!");
    }
    WiFi.begin(sta_ssid, sta_pass);
    Serial.print("[WiFi] Connecting to STA SSID: ");
    Serial.println(sta_ssid);
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.print("\n[WiFi] STA connected. IP: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\n[WiFi] STA failed to connect!");
    }
}

bool hal_wifi_is_connected() {
    return WiFi.status() == WL_CONNECTED;
}
