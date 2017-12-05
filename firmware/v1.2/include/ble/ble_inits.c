#include "ble_inits.h"


ble_gap_sec_params_t     m_sec_params;                               /**< Security requirements for this application. */
ble_uuid_t m_adv_uuids[] = {{BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}}; /**< Universally unique service identifiers. */

uint32_t advertisement_update_multiple(uint16_t *UUIDs, uint8_array_t* p_data, uint8_t elements_lenght){


    uint8_t count=0;
    uint32_t err_code;         // Variable para guardar el error.

    ble_advdata_t advdata;                      // Estructura de configuración para los datos del advertising.
    ble_advdata_service_data_t adv_data[MAX_ADV_ELEMENTS];     // Arreglo de datos de advertising
    
    for (int i = 0; i < elements_lenght && i < MAX_ADV_ELEMENTS; ++i)
    {
        adv_data[i].service_uuid = UUIDs[i];
        adv_data[i].data = p_data[i];
        count++;
    }

    // Inicia la estructura de datos de Advertising que se pasará a @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;        // Indica como muestra el nombre del dispositivo.
    //advdata.short_name_len          = 6;                            // Tamaño para el nombre corto del advertising.
    advdata.include_appearance      = false;                        // Muestra la apariencia (2 bytes ḿas al paquete)                         // Indica si incluye la apariencia
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    //advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    //advdata.uuids_complete.p_uuids  = m_adv_uuids;
    //advdata.include_ble_device_addr = true;
    //advdata.p_manuf_specific_data   = &manuf_data;                  // Datos de manufactura.
    advdata.p_service_data_array    = &*adv_data;
    advdata.service_data_count      = count;                            // Numero de estructuras en el arreglo de datos. 

    err_code = ble_advdata_set(&advdata, NULL);
    CHECK_ERROR(err_code);

    return err_code;
    
}

uint32_t advertisement_update(uint16_t UUID, uint8_t* p_data, uint8_t size)
{
    uint32_t      err_code;
    ble_advdata_t advdata;
    //ble_advdata_manuf_data_t manuf_data; // Variable para guardar los datos de manufactura
    uint8_array_t data;                      // Arreglo de datos a enviar
    ble_advdata_service_data_t adv_data;     // Arreglo de datos de advertising

    data.p_data     = p_data;       // Llena el primer arreglo datos a enviar.
    data.size       = size;         // Tamaño de arreglo de datos.

    adv_data.service_uuid = UUID;         // UUID del servicio para el primer arreglo de datos
    adv_data.data=data;                   // Datos

    // Máximo 31 bytes entre el nombre del dispositivo y los datos
    // configurados en esta función.
    // 
    // Inicializa los datos de manofactura
    /*
    uint8_t man_data[] = MANUFACTURER_NAME; // Datos de manufactura.
    manuf_data.company_identifier   = MANUFACTURER_ID;                       // Nordics company ID
    manuf_data.data.p_data          = man_data;     
    manuf_data.data.size            = sizeof(man_data); 
    */

    // Inicia la estructura de datos de Advertising que se pasará a @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;        // Indica como muestra el nombre del dispositivo.
    //advdata.short_name_len          = 6;                            // Tamaño para el nombre corto del advertising.
    advdata.include_appearance      = false;                        // Muestra la apariencia (2 bytes ḿas al paquete)                         // Indica si incluye la apariencia
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    //advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    //advdata.uuids_complete.p_uuids  = m_adv_uuids;
    //advdata.include_ble_device_addr = true;
    //advdata.p_manuf_specific_data   = &manuf_data;                  // Datos de manufactura.
    advdata.p_service_data_array    = &adv_data;
    advdata.service_data_count      = 1;                            // Numero de estructuras en el arreglo de datos. 

    err_code = ble_advdata_set(&advdata, NULL);
    CHECK_ERROR(err_code);

    return err_code;
}

uint32_t advertising_init()
{
    uint32_t      err_code;
    ble_advdata_t advdata;
    ble_advdata_t scanrsp;
    ble_advdata_manuf_data_t manuf_data; // Variable para guardar los datos de manufactura

    // Máximo 31 bytes entre el nombre del dispositivo y los datos
    // configurados en esta función.
    // 
    // Inicializa los datos de manufactura
    uint8_t man_data[] = MANUFACTURER_NAME; // Datos de manufactura.
    manuf_data.company_identifier   = MANUFACTURER_ID;                       // Nordics company ID
    manuf_data.data.p_data          = man_data;     
    manuf_data.data.size            = sizeof(man_data);

    // Inicia la estructura de datos de Advertising que se pasará a @ref ble_advertising_init.
    memset(&advdata, 0, sizeof(advdata));

    advdata.name_type               = BLE_ADVDATA_FULL_NAME;        // Indica como muestra el nombre del dispositivo.
    //advdata.short_name_len          = 6;                            // Tamaño para el nombre corto del advertising.
    advdata.include_appearance      = false;                        // Muestra la apariencia (2 bytes ḿas al paquete)                         // Indica si incluye la apariencia
    advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    //advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    //advdata.uuids_complete.p_uuids  = m_adv_uuids;
    //advdata.include_ble_device_addr = true;
    //advdata.p_manuf_specific_data   = &manuf_data;                  // Datos de manufactura.
    //advdata.p_service_data_array    = &*adv_data;
    //advdata.service_data_count      = 1;                            // Numero de estructuras en el arreglo de datos. 

    memset(&scanrsp, 0, sizeof(scanrsp));
    scanrsp.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    scanrsp.uuids_complete.p_uuids  = m_adv_uuids;
    scanrsp.p_manuf_specific_data   = &manuf_data;


    ble_adv_modes_config_t options = {0};
    options.ble_adv_fast_enabled  = BLE_ADV_FAST_ENABLED;
    options.ble_adv_fast_interval = APP_ADV_INTERVAL;
    options.ble_adv_fast_timeout  = APP_ADV_TIMEOUT_IN_SECONDS;

    err_code = ble_advertising_init(&advdata, &scanrsp, &options, on_adv_evt, NULL);
    CHECK_ERROR(err_code);

    return err_code;

}

uint32_t gap_params_init()
{
    uint32_t                err_code;
    ble_gap_conn_params_t   gap_conn_params;
    ble_gap_conn_sec_mode_t sec_mode;

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&sec_mode);

    err_code = sd_ble_gap_device_name_set(&sec_mode,
                                          (const uint8_t *)DEVICE_NAME,
                                          strlen(DEVICE_NAME));
    CHECK_ERROR(err_code);

    //err_code = sd_ble_gap_appearance_set(DEVICE_APPEARANCE);  // Indica el tipo de apariencia del dispositivo, 961 = Mostar Como Teclado
    //CHECK_ERROR(err_code);                                    // Checa si hubo error.

    memset(&gap_conn_params, 0, sizeof(gap_conn_params));

    gap_conn_params.min_conn_interval = MIN_CONN_INTERVAL;
    gap_conn_params.max_conn_interval = MAX_CONN_INTERVAL;
    gap_conn_params.slave_latency     = SLAVE_LATENCY;
    gap_conn_params.conn_sup_timeout  = CONN_SUP_TIMEOUT;

    err_code = sd_ble_gap_ppcp_set(&gap_conn_params);
    CHECK_ERROR(err_code);

    return err_code;

}

uint32_t ble_stack_init()
{
    uint32_t err_code;

    // Initialize the SoftDevice handler module.
    SOFTDEVICE_HANDLER_INIT(NRF_CLOCK_LFCLKSRC_XTAL_20_PPM, NULL);

    // Enable BLE stack.
    ble_enable_params_t ble_enable_params;
    memset(&ble_enable_params, 0, sizeof(ble_enable_params));
    ble_enable_params.gatts_enable_params.service_changed = IS_SRVC_CHANGED_CHARACT_PRESENT;
    err_code = sd_ble_enable(&ble_enable_params);
    CHECK_ERROR(err_code);

    // Activa el manejador de Scann Request
    //const ble_opt_t scan_req_opt={ .gap_opt = { .scan_req_report = { .enable=1} } };
    //sd_ble_opt_set(BLE_GAP_OPT_SCAN_REQ_REPORT, &scan_req_opt);

    // Register with the SoftDevice handler module for BLE events.
    err_code = softdevice_ble_evt_handler_set(ble_evt_dispatch);
    CHECK_ERROR(err_code);

    // Register with the SoftDevice handler module for BLE events.
    //err_code = softdevice_sys_evt_handler_set(sys_evt_dispatch);
    //CHECK_ERROR(err_code);
    return err_code;
}

uint32_t conn_params_init()
{
    uint32_t               err_code;
    ble_conn_params_init_t cp_init;

    memset(&cp_init, 0, sizeof(cp_init));

    cp_init.p_conn_params                  = NULL;
    cp_init.first_conn_params_update_delay = FIRST_CONN_PARAMS_UPDATE_DELAY;
    cp_init.next_conn_params_update_delay  = NEXT_CONN_PARAMS_UPDATE_DELAY;
    cp_init.max_conn_params_update_count   = MAX_CONN_PARAMS_UPDATE_COUNT;
    cp_init.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    cp_init.disconnect_on_fail             = false;
    cp_init.evt_handler                    = on_conn_params_evt;
    cp_init.error_handler                  = conn_params_error_handler;

    err_code = ble_conn_params_init(&cp_init);
    CHECK_ERROR(err_code);

    return err_code;

}

void sec_params_init(void)
{
    m_sec_params.bond         = SEC_PARAM_BOND;
    m_sec_params.mitm         = SEC_PARAM_MITM;
    m_sec_params.io_caps      = SEC_PARAM_IO_CAPABILITIES;
    m_sec_params.oob          = SEC_PARAM_OOB;
    m_sec_params.min_key_size = SEC_PARAM_MIN_KEY_SIZE;
    m_sec_params.max_key_size = SEC_PARAM_MAX_KEY_SIZE;
}