
#include "ble_events.h"


__WEAK void ble_evt_dispatch(ble_evt_t * p_ble_evt)
{

    ble_conn_params_on_ble_evt(p_ble_evt);
    on_ble_evt(p_ble_evt);

    //ble_advertising_on_ble_evt(p_ble_evt);
    /*YOUR_JOB add calls to _on_ble_evt functions from each service your application is using
    ble_xxs_on_ble_evt(&m_xxs, p_ble_evt);
    ble_yys_on_ble_evt(&m_yys, p_ble_evt);
    */
}

__WEAK void on_adv_evt(ble_adv_evt_t ble_adv_evt)
{

    switch (ble_adv_evt)
    {

        case BLE_ADV_EVT_FAST:            
            // No hace nada, redefinir esta funcion de eventos en main.c
            break;
        case BLE_ADV_EVT_IDLE:
            // No hace nada, redefinir esta funcion de eventos en main.c            
            break;
        default:
            break;
    }
}


__WEAK void on_ble_evt(ble_evt_t * p_ble_evt)
{
   
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:            
            // No hace nada, redefinir esta funcion de eventos en main.c
            
            // Actualiza el manejador de conexión.
            //m_conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
            //
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            // No hace nada, redefinir esta funcion de eventos en main.c
             
            // Actualiza el manejador de conexión: = NULL
            // m_conn_handle = BLE_CONN_HANDLE_INVALID;
            
            break;

        case BLE_GAP_EVT_TIMEOUT:   // Evento que se genera con un Time Out de conexión (No hubo peticiónes de conexíón en un cierto tiempo)
            // No hace nada, redefinir esta funcion de eventos en main.c
            break;

        case BLE_GAP_EVT_SEC_PARAMS_REQUEST:    // Evento que se genera de una petición de parámetros de seguridad.
            //err_code = sd_ble_gap_sec_params_reply(m_conn_handle, BLE_GAP_SEC_STATUS_SUCCESS, &m_sec_params,&keys_exchanged);
            //APP_ERROR_CHECK(err_code);
            break;
        default:
            break;
    }
}

__WEAK void conn_params_error_handler(uint32_t nrf_error)
{
    APP_ERROR_HANDLER(nrf_error);
}

__WEAK void on_conn_params_evt(ble_conn_params_evt_t * p_evt)
{
    uint32_t err_code = NRF_SUCCESS;

    if (p_evt->evt_type == BLE_CONN_PARAMS_EVT_FAILED)
    {
        //err_code = sd_ble_gap_disconnect(m_conn_handle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE);
        APP_ERROR_CHECK(err_code);
    }
}

