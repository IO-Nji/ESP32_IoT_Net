#ifndef HAL_NETWORK_H
#define HAL_NETWORK_H
#include <stdint.h>
#include <stdbool.h>

// Network HAL Interface
typedef struct {
    char ip[16];
    char ssid[32];
    bool connected;
} NetworkInfo;

void hal_network_init(const char* ap_ssid, const char* ap_pass, const char* sta_ssid, const char* sta_pass);
bool hal_network_is_connected();
NetworkInfo hal_network_get_info();

#endif // HAL_NETWORK_H
