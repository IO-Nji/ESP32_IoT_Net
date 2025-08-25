#ifndef NETWORK_SERVICE_H
#define NETWORK_SERVICE_H
#include <stdint.h>
#include <stdbool.h>

// Network HAL Interface
typedef struct {
    char ip[16];      // STA IP
    char ssid[32];    // STA SSID
    char ap_ip[16];   // AP IP
    char ap_ssid[32]; // AP SSID
    bool connected;
} NetworkInfo;

void network_service_init(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass);
bool network_service_is_connected();
NetworkInfo network_service_get_info();

#endif // NETWORK_SERVICE_H
