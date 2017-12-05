#include "ble_custom_service.h"
#include <string.h>
#include "nordic_common.h"
#include "ble_srv_common.h"
#include "app_util.h"

/**
 * Función para manejar el evento de conexión.
 *
 * p_service       Estructura del servicio.
 * p_ble_evt       Evento recibido del Stack BLE.
 */
static void on_connect(ble_csrv_t * p_csrv, ble_evt_t * p_ble_evt)
{
    p_csrv->conn_handle = p_ble_evt->evt.gap_evt.conn_handle;
}

/**
 * Función para manejar el evento de desconexión.
 *
 * p_service       Estructura del servicio.
 * p_ble_evt       Evento recibido del Stack BLE.
 */
static void on_disconnect(ble_csrv_t * p_csrv, ble_evt_t * p_ble_evt)
{
    UNUSED_PARAMETER(p_ble_evt);
    p_csrv->conn_handle = BLE_CONN_HANDLE_INVALID;
}

/**
 * Función para manejar el evento de conexión.
 *
 * p_service       Estructura del servicio.
 * p_ble_evt   Evento recibido del Stack BLE.
 */
static void on_write(ble_csrv_t * p_csrv, ble_evt_t * p_ble_evt)
{
    ble_gatts_evt_write_t * p_evt_write = &p_ble_evt->evt.gatts_evt.params.write;
    
    if ((p_evt_write->handle == p_csrv->write_char_handles.value_handle) &&
        (p_evt_write->len == 1) &&
        (p_csrv->write_handler != NULL))
    {
        p_csrv->write_handler(p_csrv, p_evt_write->data[0]);
    }
}


void ble_csrv_on_ble_evt(ble_csrv_t * p_csrv, ble_evt_t * p_ble_evt)
{
    switch (p_ble_evt->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            on_connect(p_csrv, p_ble_evt);
            break;
            
        case BLE_GAP_EVT_DISCONNECTED:
            on_disconnect(p_csrv, p_ble_evt);
            break;
            
        case BLE_GATTS_EVT_WRITE:
            on_write(p_csrv, p_ble_evt);
            break;
            
        default:
            // No implementation needed.
            break;
    }
}

/**
 * Función para agregar la característica de escritura.
 */
static uint32_t write_char_add(ble_csrv_t * p_csrv, const ble_csrv_init_t * p_csrv_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&char_md, 0, sizeof(char_md));
    
    char_md.char_props.read   = 1;
    char_md.char_props.write  = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = NULL;
    char_md.p_sccd_md         = NULL;
    
    ble_uuid.type = p_csrv->uuid_type;
    ble_uuid.uuid = CSRV_UUID_WRITE_CHAR;
    
    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = NULL;
    
    return sd_ble_gatts_characteristic_add(p_csrv->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_csrv->write_char_handles);
}

/**
 * Función para agregar la característica de lectura.
 */
static uint32_t read_char_add(ble_csrv_t * p_csrv, const ble_csrv_init_t * p_csrv_init)
{
    ble_gatts_char_md_t char_md;
    ble_gatts_attr_md_t cccd_md;
    ble_gatts_attr_t    attr_char_value;
    ble_uuid_t          ble_uuid;
    ble_gatts_attr_md_t attr_md;

    memset(&cccd_md, 0, sizeof(cccd_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&cccd_md.write_perm);
    cccd_md.vloc = BLE_GATTS_VLOC_STACK;
    
    memset(&char_md, 0, sizeof(char_md));
    
    char_md.char_props.read   = 1;
    char_md.char_props.notify = 1;
    char_md.p_char_user_desc  = NULL;
    char_md.p_char_pf         = NULL;
    char_md.p_user_desc_md    = NULL;
    char_md.p_cccd_md         = &cccd_md;
    char_md.p_sccd_md         = NULL;
    
    ble_uuid.type = p_csrv->uuid_type;
    ble_uuid.uuid = CSRV_UUID_READ_CHAR;
    
    memset(&attr_md, 0, sizeof(attr_md));

    BLE_GAP_CONN_SEC_MODE_SET_OPEN(&attr_md.read_perm);
    BLE_GAP_CONN_SEC_MODE_SET_NO_ACCESS(&attr_md.write_perm);
    attr_md.vloc       = BLE_GATTS_VLOC_STACK;
    attr_md.rd_auth    = 0;
    attr_md.wr_auth    = 0;
    attr_md.vlen       = 0;
    
    memset(&attr_char_value, 0, sizeof(attr_char_value));

    attr_char_value.p_uuid       = &ble_uuid;
    attr_char_value.p_attr_md    = &attr_md;
    attr_char_value.init_len     = sizeof(uint8_t);
    attr_char_value.init_offs    = 0;
    attr_char_value.max_len      = sizeof(uint8_t);
    attr_char_value.p_value      = NULL;
    
    return sd_ble_gatts_characteristic_add(p_csrv->service_handle, &char_md,
                                               &attr_char_value,
                                               &p_csrv->read_char_handles);
}

uint32_t ble_csrv_init(ble_csrv_t * p_csrv, const ble_csrv_init_t * p_csrv_init)
{
    uint32_t   err_code;
    ble_uuid_t ble_uuid;

    // Inicializa la estructura de servicio.
    p_csrv->conn_handle       = BLE_CONN_HANDLE_INVALID;
    p_csrv->write_handler = p_csrv_init->write_handler;
    
    // Agrega el servicio.
    ble_uuid128_t base_uuid = {CSRV_UUID_BASE};
    err_code = sd_ble_uuid_vs_add(&base_uuid, &p_csrv->uuid_type);
    if (err_code != NRF_SUCCESS)
        return err_code;
    
    ble_uuid.type = p_csrv->uuid_type;
    ble_uuid.uuid = CSRV_UUID_SERVICE;

    err_code = sd_ble_gatts_service_add(BLE_GATTS_SRVC_TYPE_PRIMARY, &ble_uuid, &p_csrv->service_handle);
    if (err_code != NRF_SUCCESS)
        return err_code;
    
    // Agrega la característica de lectura
    err_code = read_char_add(p_csrv, p_csrv_init);
    if (err_code != NRF_SUCCESS)
        return err_code;
    
    // Agrega la característica de escritura
    err_code = write_char_add(p_csrv, p_csrv_init);
    if (err_code != NRF_SUCCESS)
        return err_code;

    
    return NRF_SUCCESS;
}

uint32_t ble_csrv_on_read(ble_csrv_t * p_csrv, uint8_t new_data)
{
    ble_gatts_hvx_params_t params;
    uint16_t len = sizeof(new_data);
    
    memset(&params, 0, sizeof(params));
    params.type = BLE_GATT_HVX_NOTIFICATION;
    params.handle = p_csrv->read_char_handles.value_handle;
    params.p_data = &new_data;
    params.p_len = &len;
    
    return sd_ble_gatts_hvx(p_csrv->conn_handle, &params);
}
