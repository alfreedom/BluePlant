 /***************************************************************************************
 *
 *     Copyrigth© 2016  Alfredo Orozco de la Paz 
 *     e-mail:  alfredoopa@gmail.com 
 *                
 *     Descripción
 *                
 *     Configuración de la aplicación BLE, basado en la plantilla BLE de Nordic.
 *     
 *     Este  archivo  define los parámetros  para la configuración de la aplicación 
 *     BLE de usuario.
 *     
 *     Se puede  modificar  el nombre  del dispositivo  a  mostrar,  el nombre  de 
 *     Manufactura, el intervalo  de  advertising   el  timeout   del  advertisin, 
 *     parámetros de conexión, de seguridad, configura parámetros de los timers de 
 *     aplicación, y las configuraciónes del usuario.
 *          
 ***************************************************************************************
 *     Licencia:
 *
 *        Este programa es software libre; usted lo puede distribuir y/o modificar
 *        bajo los terminos   de la General Public License GNU, según es publicada
 *        en la  Free  Software  Foundation;  ya se la versión 2 de la Licencia, o
 *        (a su elección) una versión posterior.
 *
 *        Este  programa se  distribuye  con la  esperanza  de que sea  útil, pero
 *        SIN   NINGUNA   GARANTÍA,  incluso   sin   la   garantía   implícita  de
 *        COMERCIALIZACIÓN  o  IDONEIDAD PARA UN PROPÓSITO PARTICULAR. consulte la
 *        Licencia Pública General de GNU para más detalles.
 *
 *        Debería haber recibido una copia de  la  Licencia Pública General de GNU
 *        junto con este programa; si no, visite http://www.gnu.org/licenses.
 *      
 ***************************************************************************************/

#ifndef BLE_PARAMS_H_
#define BLE_PARAMS_H_

#define IS_SRVC_CHANGED_CHARACT_PRESENT  0                  // Include or not the service_changed characteristic. if not enabled, the server's database cannot be changed for the lifetime of the device

#define DEVICE_NAME                      "Blue Plant"         // Name of device. Will be included in the advertising data.
#define MANUFACTURER_NAME                "Fred Labs ;)"     // Manufacturer. Will be passed to Device Information Service.
#define MANUFACTURER_ID                  0xDEAD             // Manufacturer. Will be passed to Device Information Service.
#define DEVICE_APPEARANCE                0

#define APP_ADV_INTERVAL                 100                // The advertising interval (in units of 0.625 ms. This value corresponds to 25 ms).
#define APP_ADV_TIMEOUT_IN_SECONDS       120             

#define APP_TIMER_PRESCALER              255                  // Value of the RTC1 PRESCALER register.
#define APP_TIMER_OP_QUEUE_SIZE          15                  // Size of timer operation queues.

#define MIN_CONN_INTERVAL                MSEC_TO_UNITS(100, UNIT_1_25_MS)   // Minimum acceptable connection interval (0.5 seconds).
#define MAX_CONN_INTERVAL                MSEC_TO_UNITS(200, UNIT_1_25_MS)   // Maximum acceptable connection interval (1 second).
#define SLAVE_LATENCY                    0                                  // Slave latency.
#define CONN_SUP_TIMEOUT                 MSEC_TO_UNITS(4000, UNIT_10_MS)    // Connection supervisory timeout (4 seconds).

#define FIRST_CONN_PARAMS_UPDATE_DELAY   APP_TIMER_TICKS(5000, APP_TIMER_PRESCALER)     // Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds).
#define NEXT_CONN_PARAMS_UPDATE_DELAY    APP_TIMER_TICKS(30000, APP_TIMER_PRESCALER)    // Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds).
#define MAX_CONN_PARAMS_UPDATE_COUNT     3                                              // Number of attempts before giving up the connection parameter negotiation.

#define SEC_PARAM_TIMEOUT                30                     // Timeout for Pairing Request or Security Request (in seconds).
#define SEC_PARAM_BOND                   1                      // Perform bonding.
#define SEC_PARAM_MITM                   0                      // Man In The Middle protection not required.
#define SEC_PARAM_IO_CAPABILITIES        BLE_GAP_IO_CAPS_NONE   // No I/O capabilities.
#define SEC_PARAM_OOB                    0                      // Out Of Band data not available.
#define SEC_PARAM_MIN_KEY_SIZE           7                      // Minimum encryption key size.
#define SEC_PARAM_MAX_KEY_SIZE           16                     // Maximum encryption key size.

#define DEAD_BEEF                        0xDEADBEEF             // Value used as error code on stack dump, can be used to identify stack location on stack unwind.

// Definiciones de Usuario
#define APP_GPIOTE_MAX_USERS            1                       // Maximum number of users of the GPIOTE handler.
#define BUTTON_DETECTION_DELAY          APP_TIMER_TICKS(50, APP_TIMER_PRESCALER)    // Delay from a GPIOTE event until a button is reported as pushed (in number of timer ticks).


#endif // BLE_PARAMS_H_
