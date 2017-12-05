#include "light_sensor.h"


#define NUM_SAMPLES 50	//Numero de muestras del ADC que se toman para obtener la cantidad de luz captada
/**
 * @brief Realiza un mapeo de un valor
 * @details Usa una regla relacional entre los valores extremos y el valor dado.
 * 
 * @param x 		Valor que sera mapeado
 * @param in_min 	Rango minimo de entrada
 * @param in_max 	Rango maximo de entrada
 * @param out_min 	Rango minimo de salida
 * @param out_max 	Rango maximo de salida
 * @return 			Retorna un valor entre out_min y out_max dependiendo de la entrada x
 */
uint32_t map_value(uint32_t x,uint32_t in_min, uint32_t in_max,uint32_t out_min,uint32_t out_max)
{
    return (x - in_min) * (out_max -out_min) / (in_max - in_min) + out_min;
}


/**
 * @brief Configura el ADC tomando la configuracion establecida en la estructura ADC_LS_CONFIGURATION
 */
void LS_ADC_init()
{
    nrf_adc_config_t adc_cfg= ADC_LS_CONFIGURATION_3_0_V;

    nrf_adc_configure(&adc_cfg);
}


/**
 * @brief Lectura del sensor
 * @details Realiza un promedio de lecturas del ADC para generar la lectura del sensor de luz
 * @return lectura del sensor,
 */
uint16_t LS_read_sensor()
{
	uint32_t read=0;

    for (int i = 0; i < NUM_SAMPLES; i++)
        read += nrf_adc_convert_single(LIGHT_SENSOR_PIN);

    return (uint16_t)(read/NUM_SAMPLES);
    //return (uint16_t)map_value(read / NUM_SAMPLES,0,1023,0,1023);
}