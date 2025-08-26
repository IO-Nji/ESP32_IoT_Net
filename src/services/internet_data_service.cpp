#include "internet_data_service.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ArduinoJson.h>
#include <Arduino.h> // For String type

static WiFiUDP ntpUDP;
// Set your timezone offset in seconds (e.g., 3600 for UTC+1)
static const long TIMEZONE_OFFSET = 7200; // Berlin summer time (UTC+2)
static NTPClient timeClient(ntpUDP, "pool.ntp.org", TIMEZONE_OFFSET, 60000); // update every 60s
static char weatherApiKey[64] = "";
static char weatherCity[32] = "";
static WeatherInfo lastWeather = {"", 0, 0};
static unsigned long lastUpdate = 0;

void internet_data_service_init(const char* openweather_api_key, const char* city) {
    strncpy(weatherApiKey, openweather_api_key, sizeof(weatherApiKey));
    weatherApiKey[sizeof(weatherApiKey)-1] = '\0';
    strncpy(weatherCity, city, sizeof(weatherCity));
    weatherCity[sizeof(weatherCity)-1] = '\0';
    timeClient.begin();
}

void fetch_weather() {
    if (strlen(weatherApiKey) == 0 || strlen(weatherCity) == 0) return;
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(F("[Weather] WiFi not connected, skipping fetch."));
        return;
    }
    HTTPClient http;
    String url = String("http://api.openweathermap.org/data/2.5/weather?q=") + weatherCity + "&appid=" + weatherApiKey + "&units=metric";
    http.begin(url);
    int httpCode = http.GET();
    Serial.print(F("[Weather] HTTP GET code: "));
    Serial.println(httpCode);
    if (httpCode == 200) {
        String payload = http.getString();
        Serial.print(F("[Weather] HTTP payload: "));
        Serial.println(payload);
    JsonDocument doc;
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print(F("[Weather] JSON parse error: "));
            Serial.println(error.c_str());
        } else {
            // Weather description
            const char* desc = doc["weather"][0]["description"] | "";
            strncpy(lastWeather.description, desc, sizeof(lastWeather.description));
            lastWeather.description[sizeof(lastWeather.description)-1] = '\0';
            // Temperature
            lastWeather.temperature = doc["main"]["temp"] | 0.0;
            // Humidity
            lastWeather.humidity = doc["main"]["humidity"] | 0.0;
        }
    } else {
        Serial.println(F("[Weather] HTTP request failed."));
    }
    http.end();
}

void internet_data_service_update() {
    unsigned long now = millis();
    if (now - lastUpdate < 60000) return; // Only update every minute
    lastUpdate = now;
    timeClient.update();
    fetch_weather();
}

void internet_data_service_print() {
    Serial.print(F("NTP Time: "));
    Serial.println(timeClient.getFormattedTime());
    Serial.print(F("Weather: "));
    Serial.print(lastWeather.description);
    Serial.print(F(", Temp: "));
    Serial.print(lastWeather.temperature);
    Serial.print(F("C, Humidity: "));
    Serial.print(lastWeather.humidity);
    Serial.println(F("%"));
}

#ifdef __cplusplus
extern "C" {
#endif

const WeatherInfo* getWeatherInfo();
const char* getFormattedTime();

#ifdef __cplusplus
}
#endif

// Implementation of C-linkage getter functions
const WeatherInfo* getWeatherInfo() {
    return &lastWeather;
}

const char* getFormattedTime() {
    static char buf[16];
    String t = timeClient.getFormattedTime();
    strncpy(buf, t.c_str(), sizeof(buf));
    buf[sizeof(buf)-1] = '\0';
    return buf;
}