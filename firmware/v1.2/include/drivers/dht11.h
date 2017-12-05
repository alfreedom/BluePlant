#ifndef _DHT11_H_
#define _DHT11_H_


typedef enum{
    DHT11_OK = 0,
    DHT11_ERROR_CONFIG,
    DHT11_ERROR_NO_RESPONSE,
    DHT11_ERROR_DATA,
}dht11_error_t;

/**
 * @brief Inicializa el hardware para el sensor DHT11.
 * @details Configura el pin del sensor como entrada y con la resistencia 
 *          Pull-Up interna y configra el Timer 1 para medir los pulsos en alto.
 * 
 * @param pin_number Pin a configurar para el sensor DHT11.
 * @return 1 si no hay errores de configuración, de lo contrario 0.
 */
dht11_error_t dht11_init(uint32_t pin_number);

/**
 * @brief Lee el sensor DHT11
 * @details Lee la temperatura y humedad del sensor DHt11.
 *          
 * 
 * @param pin_number Pin al que está conectado el pin de datos del sensor.
 * @param temp Variable de salida donde guarda la temperatura leida
 * @param humidity Variable de salida donde guarda la humedad leida.    
 * @return Devuelve error si no se detecta el sensor o si hubo un error en
 * la lectura de datos (cálculo del checksum).
 */
dht11_error_t dht11_read(uint32_t pin_number, uint16_t* temp, uint16_t* humidity);

/**
 * @brief Prueba la conexión del sensor.
 * @details Checa si hay un sensor DH11 conectado en el pin especificado.
 * 
 * @param pin_number Pin donde se checa la presencia del sensor.
 * @return Si detecta el sensor devuelve 1, de lo contrario 0.
 */
dht11_error_t dht11_is_connected(uint32_t pin_number);

#endif // _DHT11_H_
