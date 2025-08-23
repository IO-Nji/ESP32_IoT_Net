#pragma once

// WiFi HAL for ESP32 IoT Server System
void hal_wifi_init_ap_sta(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass);
bool hal_wifi_is_connected();
