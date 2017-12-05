#ifndef _BLE_INITS_H_
#define _BLE_INITS_H_


#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "softdevice_handler.h"
#include "app_error.h"
#include "app_timer.h"

#include "ble_events.h"
#include "ble_params.h"

#define MAX_ADV_ELEMENTS 5

// Macro para checar errores sin bloqueo.
#define CHECK_ERROR(ERR_CODE)  if (ERR_CODE != NRF_SUCCESS) return ERR_CODE

typedef struct{
    uint8_t size;
    uint8_t *p_data;
}my_adv_data_t;
/**@brief Función para inicializar el Advertisin (Publicidad)
 *
 *  Esta fución inicializa los parámetros de advertising, enviando
 *  los datos como Nombre del dispositivo, Nombre de Manufactura
 *  entre otros datos.
 *  
 *  Se pueden enviar tamién datos de advertising con la opción
 *  Scanner Request en la función ble_advertising_init del mismo 
 *  modo que en los parámetros de nombre.
 *  
 *  Sólo se pueden enviar 31 bytes por advertising y 31 datos por
 *  Scanner Request, teniendo un total de 62 bytes para enviar mediante
 *  Advertising.
 */
uint32_t advertising_init();

/**
 * @brief Función para iniciarlizar el Stack Ble y SoftDevice.
 * 
 *        Configura el softdevice y el Stack Ble.
 */
uint32_t ble_stack_init();


/**@brief Funcion para la inicializar del GAP.
 *
 * @details Esta funcion inicializa todos los parámetros GAP (Generic Access Profile) 
 * del dispositivo incluyendo el nombre, la apariencia, y el parámetro de conexión preferida.
 */
uint32_t gap_params_init();

/**@brief Funcion para inicializar los parámetros de conexión.
 */
uint32_t conn_params_init();

void sec_params_init();

uint32_t advertisement_update(uint16_t UUID, uint8_t* p_data, uint8_t size);
uint32_t advertisement_update_multiple(uint16_t *UUIDs, uint8_array_t* p_data, uint8_t elements_lenght);

#endif // _BLE_INITS_H