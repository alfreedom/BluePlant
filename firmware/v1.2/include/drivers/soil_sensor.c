#include "soil_sensor.h"


#define NUM_SOIL_SAMPLES 50  //Numero de muestras del ADC que se toman para obtener la cantidad de luz captada

/**
 * @brief Configura el ADC tomando la configuracion establecida en la estructura ADC_LS_CONFIGURATION
 */
void soil_sensor_adc_init()
{
    nrf_adc_config_t adc_cfg = SOIL_SENSOR_ADC_CONFIGURATION_3_0_V;

    nrf_adc_configure(&adc_cfg);
}


/**
 * @brief Lectura del sensor
 * @details Realiza un promedio de lecturas del ADC para generar la lectura del sensor de luz
 * @return lectura del sensor,
 */
uint16_t soil_sensor_read()
{
    uint32_t read=0;

    for (int i = 0; i < NUM_SOIL_SAMPLES; i++)
        read += nrf_adc_convert_single(SOIL_SENSOR_PIN);

    return (uint16_t)(read/NUM_SOIL_SAMPLES);
    //return (uint16_t)map_value(read / NUM_SOIL_SAMPLES,0,1023,0,1023);
}