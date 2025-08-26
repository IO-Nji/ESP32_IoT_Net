#ifndef INTERNET_DATA_SERVICE_H
#define INTERNET_DATA_SERVICE_H
#include <stdint.h>

struct WeatherInfo {
    char description[32];
    float temperature;
    float humidity;
};


void internet_data_service_init(const char* openweather_api_key, const char* city);
void internet_data_service_update();
void internet_data_service_print();

#ifdef __cplusplus
extern "C" {
#endif
const WeatherInfo* getWeatherInfo();
const char* getFormattedTime();
#ifdef __cplusplus
}
#endif

#endif // INTERNET_DATA_SERVICE_H
