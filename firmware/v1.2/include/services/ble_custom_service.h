#ifndef _BLE_CUSTOM_SERVICE_H_
#define _BLE_CUSTOM_SERVICE_H_

#include <stdint.h>
#include <stdbool.h>
#include "ble.h"
#include "ble_srv_common.h"

// UUID Base del servicio.
#define CSRV_UUID_BASE          {0x23, 0xD4, 0xBC, 0xEA, 0x5F, 0x78, 0x23, 0x15, 0xDE, 0xEF, 0x12, 0x12, 0x00, 0x00, 0x00, 0x00}

// UUID del servicio
#define CSRV_UUID_SERVICE       0xAA01

// UUIDE de las características que incluye el servicio.
#define CSRV_UUID_WRITE_CHAR    0xAA02
#define CSRV_UUID_READ_CHAR     0xAA03


// Declaración para el tipo ble_csrv_t.
typedef struct ble_csrv_s ble_csrv_t;

// Apuntador(es) a manejadore(s) de escritura para la(s) caracteristica(s)
typedef void (*ble_csrv_write_handler_t) (ble_csrv_t * p_csrv, uint8_t new_data);

// Estructura para pasar datos y los apuntadores de escritura al servicio.
typedef struct
{
    ble_csrv_write_handler_t write_handler;     /*Manejador de eventos que se llama cuando se desea escribir en*/
} ble_csrv_init_t;

/**
 * Estructura del servicio. Contiene información de estado del servicio, asi como los
 * manejadores de sus características
 */
typedef struct ble_csrv_s
{

    uint16_t                    service_handle;         // Manejador del servicio al que pertenece la característica.
    ble_gatts_char_handles_t    write_char_handles;     // Manejador de la característica de escritura (se pueden agregar mas).
    ble_gatts_char_handles_t    read_char_handles;      // Manejador de la característica de lectura (se pueden agregar mas).
    uint8_t                     uuid_type;              // Tipo del UUID 
    uint16_t                    conn_handle;            // Manjeador de la conexión.
    ble_csrv_write_handler_t    write_handler;          // Apuntador a la función para la característica de escritura.
                                                        // Se debe agregar un manejador por cada caraterística de escritura
                                                        // definida
} ble_csrv_t;

/**
 * Funcion para inicializar el servicio.
 *
 * p_csrv       Estructura del servicio. Esta estructura tiene que ser proporcionada 
 *              por la aplicación. Sera inicializada por esta función, que podrá ser usada
 *              para identificar esta instancia del servicio en particular.
 *              
 * p_csrv_init  Información necesaria para inicalizar el servicio.
 *
 * return       NRF_SUCCESS si se inicializa correctamente, de otra manera error.
 */
uint32_t ble_csrv_init(ble_csrv_t * p_csrv, const ble_csrv_init_t * p_csrv_init);

/**
 * Función para manejar los eventos de aplicación del Stack BLE como conexión, 
 * desconexión, escritura, entre otros.
 *
 * Maneja todos los eventos del Stack BLE que sean de interes para el servicio.
 *
 * p_csrv      Estructura del servicio.
 * p_ble_evt   Evento recibido del Stack BLE.
 */
void ble_csrv_on_ble_evt(ble_csrv_t * p_csrv, ble_evt_t * p_ble_evt);

/**
 * Función para enviar datos a una petición de lectura.
 * 
 * Debe haber una función manejadora de envío de daros para cada característica de lectura.
 * 
 * p_csrv      Estructura del servicio.
 * new_data    Dato a enviar al dispositivo.
 */
uint32_t ble_csrv_on_read(ble_csrv_t * p_csrv, uint8_t new_data);


#endif // _BLE_CUSTOM_SERVICE_H_


