/**
 * Libreria para el manejo del sensor de luminocidad
 * Se utiliza el ADC del SOC y como sensor una fotoresistencia.
 */

#ifndef _SOIL_SENSOR_H_
#define _SOIL_SENSOR_H_

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


#define SOIL_SENSOR_ADC_CONFIGURATION_3_0_V { NRF_ADC_CONFIG_RES_10BIT,                  \
                                              NRF_ADC_CONFIG_SCALING_INPUT_ONE_THIRD,    \
                                              NRF_ADC_CONFIG_REF_VBG }

/**
 * @brief Funcion que configura al ADC para leer el sensor de humedad de la tierra.
 */
void soil_sensor_adc_init();


/**
 * @brief Lectura de sensor
 * @details Realiza la lectura del sensor de humedad en la tierra.
 * @return Regresa el promedio de 
 */
uint16_t soil_sensor_read();

#endif