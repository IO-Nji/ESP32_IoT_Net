#include <WebServer.h>
#include "src/hal/hal_wifi.h"
#include "src/hal/hal_bme280.h"

WebServer server(80);

// HTML page template
String htmlPage(float temp, float hum, float pres, size_t freeHeap, size_t totalHeap) {
    String page = "<html><head><title>ESP32 IoT Server</title></head><body>";
    page += "<h1>ESP32 IoT Server Info</h1>";
    page += "<p><b>RAM:</b> " + String(freeHeap) + " / " + String(totalHeap) + " bytes</p>";
    page += "<p><b>Temperature:</b> " + String(temp, 1) + " C</p>";
    page += "<p><b>Humidity:</b> " + String(hum, 1) + " %</p>";
    page += "<p><b>Pressure:</b> " + String(pres / 100.0, 1) + " hPa</p>";
    page += "</body></html>";
    return page;
}

void handleRoot() {
    float temp = 0, hum = 0, pres = 0;
    hal_bme280_read(&temp, &hum, &pres);
    size_t freeHeap = ESP.getFreeHeap();
    size_t totalHeap = ESP.getHeapSize();
    server.send(200, "text/html", htmlPage(temp, hum, pres, freeHeap, totalHeap));
}

void web_server_init() {
    server.on("/", handleRoot);
    server.begin();
}

void web_server_loop() {
    server.handleClient();
}
