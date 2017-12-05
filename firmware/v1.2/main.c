 /***************************************************************************************
 *
 *     Copyrigth© 2016  Alfredo Orozco de la Paz 
 *     e-mail:  alfredoopa@gmail.com 
 *                
 *     Descripción
 *                
 *          Archivo main.c para compilación de un proyecto para el SOC BLE 
 *          nRF51822_xxAC con el SDK de Nordic Semiconductors en su versión
 *          10.0.0.
 *          
 *          Junto este archivo se incluyen el árbol de directorios y los archivos
 *          necesarios para configurar el BLE y el SoftDevice de Nordic, atender
 *          los eventos que generen, agregar servicios personalizados y la 
 *          configuración de drivers y parámetros para el Bluetooth.
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

#include <stdint.h>
#include <string.h>
#include "nrf.h"
#include "nordic_common.h"
#include "nrf_gpio.h"
#include "app_timer.h"
#include "nrf_delay.h"

#include "ble400.h"
#include "blueplant.h"
#include "ble_inits.h"
#include "onewire.h"
#include "ds18b20.h"
#include "light_sensor.h"
#include "soil_sensor.h"


#define SENSORS_UPDATE_INTERVAL APP_TIMER_TICKS(500, APP_TIMER_PRESCALER)
#define ADVERTISING_LED_INTERVAL APP_TIMER_TICKS(2000, APP_TIMER_PRESCALER)

#define ADVERTISING_LED     LED_B_PIN    // Led para indicar Advertising.
#define CONNECTION_LED      LED_G_PIN    // Led para indicar conexión.
#define ERROR_LED           LED_R_PIN    // Led para indicar Error.
#define WAKE_UP_BUTTON      BUTTON_PIN // Boton para despertar al chip.

// Definición de pines a los que se conectan los sensores.
#define ONE_WIRE_BUS_PIN        DS18B20_SENSOR_PIN      // Pin para el bus One Wire (pin #00)
#define TEMPERATURE_SENSOR_PIN  ONE_WIRE_BUS_PIN        // Pin para el sensor de temperatura digital DS18B20 
#define LDR_SENSOR_PIN          LIGHT_SENSOR_PIN        // Pin para el sensor de luz analógico (pin #04)


/**
 * Funciones para inicialización y control del sistema
 */
void sleep(void);
void app_timers_init(void);
void app_timers_start(void);
void power_manage(void);
void leds_init();
void init_system();
void services_init(void);
/********************************************/

/**
 * Funciones para el sensor de temperatura
 * DS18B20
 */
void onewire_init();
void pin_set_low(uint8_t pin_no);
void pin_set_input(uint8_t pin_no);
uint8_t pin_read(uint8_t pin_no);
void delay_us(uint32_t us);
/********************************************/


uint16_t  m_conn_handle; /* Variable para el manejador de la conexión actual.*/

// Declaración de variable para guardar el ID del app timer.
APP_TIMER_DEF(sensors_update_app_timer_id);
APP_TIMER_DEF(advertising_led_app_timer_id);


//contador para el timer.
int16_t counter=0;
int16_t temperatura;
uint16_t humedad_tierra;
uint16_t luminosidad = 30;
// YOUR_JOB: Use UUIDs for service(s) used in your application.

/* YOUR_JOB: Declare all services structure your application is using
static ble_xx_service_t                     m_xxs;
static ble_yy_service_t                     m_yys;
*/
void advertising_led_timeout_handler(){

    nrf_gpio_pin_set(ADVERTISING_LED);
    nrf_delay_ms(50);
    nrf_gpio_pin_clear(ADVERTISING_LED);
}

void sensors_update_timeout_handler(){

    uint16_t err_code=0;
    uint16_t sensors_uuids[3] ={BLE_UUID_HEALTH_THERMOMETER_SERVICE, 0xDED0, 0xDAD0 } ;
    uint8_array_t data[3];

    // Lee la temperatura del sensor DS18B20.
    err_code = ds18b20_read_temp(&temperatura);
    if(err_code != DS18B20_OK)
        temperatura = 0xFFFF;

    // Lee el sensor LDR
    luminosidad=LS_read_sensor();
    
    humedad_tierra =  soil_sensor_read();

    data[0].p_data=(uint8_t*)&temperatura;
    data[0].size=2;

    data[1].p_data=(uint8_t*)&humedad_tierra;
    data[1].size=2;

    data[2].p_data=(uint8_t*)&luminosidad;
    data[2].size=2;

    advertisement_update_multiple(sensors_uuids, data, 3);

    nrf_gpio_pin_set(LED_G_PIN);
    nrf_delay_ms(40);
    nrf_gpio_pin_clear(LED_G_PIN);
    nrf_delay_ms(40);
    nrf_gpio_pin_set(LED_G_PIN);
    nrf_delay_ms(40);
    nrf_gpio_pin_clear(LED_G_PIN);
    
}
/**
 * Función main
 */
int main(void)
{
    uint32_t err_code;

    // Inicializa el sistema
    init_system();

    // Inicia Advertising y checa el error.
    err_code = ble_advertising_start(BLE_ADV_MODE_FAST);
    APP_ERROR_CHECK(err_code);

    // Entra en el ciclo main.
    for (;;)
    {
        power_manage();
    }
}


void init_system()
{
    uint32_t err_code;

    // Inicializa los timers.
    // Los timers es lo primero que se debe de incializar.
    app_timers_init();

    // Configura los leds de la aplicación.
    leds_init();

    // Initialize.
    err_code = ble_stack_init();
    APP_ERROR_CHECK(err_code);
    err_code = gap_params_init();
    APP_ERROR_CHECK(err_code);
    err_code = advertising_init();
    APP_ERROR_CHECK(err_code);
    err_code = conn_params_init();
    APP_ERROR_CHECK(err_code);
    
    // Inicializa los servicios.
    services_init();
    // Inicia la ejecución de los timers de aplicación.
    app_timers_start();

    onewire_init();
    APP_ERROR_CHECK(ds18b20_init(DS18B20_RESOLUTION_12_BITS));

    LS_ADC_init();//Inicializacion del sensor de luz
    //counter = d18b20_init(DS18B20_RESOLUTION_12_BITS);
}

void leds_init(){
    nrf_gpio_cfg_output(ADVERTISING_LED);
    nrf_gpio_cfg_output(CONNECTION_LED);
    nrf_gpio_cfg_output(ERROR_LED);
    nrf_gpio_pin_clear(ERROR_LED);
    nrf_gpio_pin_clear(ADVERTISING_LED);
    nrf_gpio_pin_clear(CONNECTION_LED);
}

void onewire_init(){
    one_wire_cfg_t config_onewire;

    config_onewire.bus_pin              = ONE_WIRE_BUS_PIN;
    config_onewire.delay_us_func        = delay_us;
    config_onewire.bus_drive_low_func   = pin_set_low;
    config_onewire.bus_release_func     = pin_set_input;
    config_onewire.bus_read_func        = pin_read;

    APP_ERROR_CHECK(one_wire_init(&config_onewire));    
}

void app_timers_init(void)
{
    // Initialize timer module.
    APP_TIMER_INIT(APP_TIMER_PRESCALER, APP_TIMER_OP_QUEUE_SIZE, false);

    // Create timers.
    /* YOUR_JOB: Create any timers to be used by the application.
                 Below is an example of how to create a timer.
                 For every new timer needed, increase the value of the macro APP_TIMER_MAX_TIMERS by
                 one.*/
    uint32_t err_code;
    err_code = app_timer_create(&sensors_update_app_timer_id, APP_TIMER_MODE_REPEATED, sensors_update_timeout_handler);
    APP_ERROR_CHECK(err_code); 
    err_code = app_timer_create(&advertising_led_app_timer_id, APP_TIMER_MODE_REPEATED, advertising_led_timeout_handler);
    APP_ERROR_CHECK(err_code); 
}


void app_timers_start(void)
{
    /* YOUR_JOB: Start your timers. below is an example of how to start a timer.*/
    uint32_t err_code;
    err_code = app_timer_start(sensors_update_app_timer_id, SENSORS_UPDATE_INTERVAL, NULL);
    APP_ERROR_CHECK(err_code); 
   
}
void pin_set_low(uint8_t pin_no){
    nrf_gpio_cfg_output(pin_no);
    nrf_gpio_pin_clear(pin_no);
}
void pin_set_input(uint8_t pin_no){
    nrf_gpio_cfg_input(pin_no, NRF_GPIO_PIN_PULLUP);
}
uint8_t pin_read(uint8_t pin_no){
    nrf_gpio_cfg_input(pin_no, NRF_GPIO_PIN_PULLUP);
    return nrf_gpio_pin_read(pin_no);
}
void delay_us(uint32_t us){
    nrf_delay_us(us);
}
/**
 * Función para manejar los Eventos de Advertising.
 */
void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{
    uint32_t err_code;
    switch (ble_adv_evt)
    {
        case BLE_ADV_EVT_FAST:            
            // Inicia el timer para el led de advertising.
            err_code = app_timer_start(advertising_led_app_timer_id, ADVERTISING_LED_INTERVAL, NULL);
            APP_ERROR_CHECK(err_code); 
            break;
        case BLE_ADV_EVT_IDLE:
            break;
        default:
            break;
    }
}

/**
 * Función para manejar los Eventos de Aplicación del Stack BLE..
 */
void on_ble_evt(ble_evt_t * p_ble_evt)
{
    uint32_t err_code;

    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:            
            
            // Actualiza el manejador de conexión.
            m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            
            // Enciende el led que indica conexión.
            nrf_gpio_pin_set(CONNECTION_LED);
            // Detiene el timer para el led de advertising.
            err_code = app_timer_stop(advertising_led_app_timer_id);
            APP_ERROR_CHECK(err_code);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
             
            // Actualiza el manejador de conexión: = NULL
             m_conn_handle = BLE_CONN_HANDLE_INVALID;
            
            // Apaga el led que indica conexión.
            nrf_gpio_pin_clear(CONNECTION_LED);

            // Inicia Advertising y checa el error.
            APP_ERROR_CHECK(ble_advertising_start(BLE_ADV_MODE_FAST));

            // Entra en modo sleep
            //sleep();
            break;

        case BLE_GAP_EVT_TIMEOUT:   // Evento que se genera con un Time Out de conexión (No hubo peticiónes de conexíón en un cierto tiempo)
            // Detiene el timer para el led de advertising.
            err_code = app_timer_stop(advertising_led_app_timer_id);
            APP_ERROR_CHECK(err_code);

            // Entra en modo sleep
            sleep();
            break;
        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:    // Evento que se genera de una petición de parámetros de seguridad.
            //err_code = sd_ble_gap_sec_params_reply(m_conn_handle, BLE_GAP_SEC_STATUS_SUCCESS, &m_sec_params,&keys_exchanged);
            //APP_ERROR_CHECK(err_code);
            break;
        default:
            break;
    }
}

void services_init(void)
{
    /* YOUR_JOB: Add code to initialize the services used by the application.
    uint32_t                           err_code;
    ble_xxs_init_t                     xxs_init;
    ble_yys_init_t                     yys_init;

    // Initialize XXX Service.
    memset(&xxs_init, 0, sizeof(xxs_init));

    xxs_init.evt_handler                = NULL;
    xxs_init.is_xxx_notify_supported    = true;
    xxs_init.ble_xx_initial_value.level = 100; 
    
    err_code = ble_bas_init(&m_xxs, &xxs_init);
    APP_ERROR_CHECK(err_code);

    // Initialize YYY Service.
    memset(&yys_init, 0, sizeof(yys_init));
    yys_init.evt_handler                  = on_yys_evt;
    yys_init.ble_yy_initial_value.counter = 0;

    err_code = ble_yy_service_init(&yys_init, &yy_init);
    APP_ERROR_CHECK(err_code);
    */
}


/**@brief Function for handling the YYY Service events. 
 * YOUR_JOB implement a service handler function depending on the event the service you are using can generate
 *
 * @details This function will be called for all YY Service events which are passed to
 *          the application.
 *
 * @param[in]   p_yy_service   YY Service structure.
 * @param[in]   p_evt          Event received from the YY Service.
 *
 *
static void on_yys_evt(ble_yy_service_t     * p_yy_service, 
                       ble_yy_service_evt_t * p_evt)
{
    switch (p_evt->evt_type)
    {
        case BLE_YY_NAME_EVT_WRITE:
            APPL_LOG("[APPL]: charact written with value %s. \r\n", p_evt->params.char_xx.value.p_str);
            break;
        
        default:
            // No implementation needed.
            break;
    }
}*/

/**
 * Función para manejar los errores de aplicación.
 */
void app_error_handler(uint32_t error_code, uint32_t line_num, const uint8_t * p_file_name)
{
    uint8_t i;
    if(error_code == ONE_WIRE_ERROR_NO_INIT){
        for(i=0; i<2; i++){
            nrf_gpio_pin_set(ERROR_LED);
            nrf_delay_ms(150);
            nrf_gpio_pin_clear(ERROR_LED);
            nrf_delay_ms(150);
        }
    }else
    if(error_code == ONE_WIRE_ERROR_INVALID_PARAM){
        for(i=0; i<4; i++){
            nrf_gpio_pin_set(ERROR_LED);
            nrf_delay_ms(150);
            nrf_gpio_pin_clear(ERROR_LED);
            nrf_delay_ms(150);
        }
    }else
    if(error_code == ONE_WIRE_ERROR_NO_RESPONSE){
        for(i=0; i<6; i++){
            nrf_gpio_pin_set(ERROR_LED);
            nrf_delay_ms(150);
            nrf_gpio_pin_clear(ERROR_LED);
            nrf_delay_ms(150);
        }
    }else
    if(error_code == DS18B20_ERROR_NOT_FOUND){
        for(i=0; i<8; i++){
            advertisement_update(0xDEAD, (uint8_t*)&error_code , 2);
            nrf_gpio_pin_set(ERROR_LED);
            nrf_delay_ms(150);
            nrf_gpio_pin_clear(ERROR_LED);
            nrf_delay_ms(150);
        }
    }

    if(line_num)
        sleep();
}

void power_manage(void)
{
    uint32_t err_code = sd_app_evt_wait();
    APP_ERROR_CHECK(err_code);
}

void sleep(void)
{
    uint32_t err_code;

    // Configura el boton 1 de la placa para que reactive el sistema despues de dormir.
    nrf_gpio_cfg_sense_input(WAKE_UP_BUTTON , BUTTON_PULL, NRF_GPIO_PIN_SENSE_LOW);

    // Va a System Off (esta funcion puede no tener retorno, al despertar puede causar reset).
    err_code = sd_power_system_off();
    APP_ERROR_CHECK(err_code);
}