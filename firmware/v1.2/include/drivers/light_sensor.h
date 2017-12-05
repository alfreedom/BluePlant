/**
 * Libreria para el manejo del sensor de luminocidad
 * Se utiliza el ADC del SOC y como sensor una fotoresistencia.
 */

#ifndef LIGHT_SENSOR_H__
#define LIGHT_SENSOR_H__

#include "nrf_adc.h"
#include "blueplant.h"

/**
 * Pines Analógicos del SOC NRF51822
 * p.45 - AIN0/XL2
 * p.46 - AIN1/XL1
 * P.01 - AIN2
 * P.02 - AIN3
 
 * P.03 - AIN4
 * P.04 - AIN5
 * P.05 - AIN6
 * P.06 - AIN7
 */

//#define LS_PIN NRF_ADC_CONFIG_INPUT_2

#define ADC_LS_CONFIGURATION_3_0_V { NRF_ADC_CONFIG_RES_10BIT,               \
                                     NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD,    \
                                     NRF_ADC_CONFIG_REF_VBG }

/**
 * @brief Funcion que configura al ADC para leer el sensor.
 */
void LS_ADC_init();

/**
 * @brief Realiza un mapeo de un valor
 */
//uint32_t map_value(uint32_t x,uint32_t in_min, uint32_t in_max,uint32_t out_min,uint32_t out_max);

/**
 * @brief Lectura de sensor
 * @details Realiza la lectura del sensor de luminocidad
 * @return Retorna un valor entre 0y 255 dependiendo de la cantidad de luz percibida.
 */
uint16_t LS_read_sensor();

#endif