
#include "onewire.h"


// Escribir reset:  Poner el bus en LOW, esperar 480us, 
//                  liberar bus, esperar 70us,
//                  leer el estado del bus (0 = dispositivos en el bus, 1 = sin dispositivos en el bus)
//                  esperar 410us
//                  
// Escribir un 1 en el bus: Poner el bus en LOW, esperar 6 microsegundos, 
//                          liberar el bus, esperar 64 microsegundos
// 
// Escribir un 0 en el bus: Poner el bus en LOW, esperar 60 microsegundos, 
//                          liberar el bus, esperar 10 microsegundos
// 
// Leer un bit:     Poner el bus en LOW, esperar 6 microsegundos,
//                  liberar el bus, esperar 9 microsegundos,
//                  leer el bit en el bus enviado.
//                  esperar 55 microsegundos
//                  
static volatile one_wire_cfg_t  m_one_wire;
one_wire_error_t one_wire_init(one_wire_cfg_t* one_wire_config){

    m_one_wire.is_ready=0;

    if(one_wire_config){

        // Guarda el pin del bus One wire
        m_one_wire.bus_pin = one_wire_config->bus_pin;

        // Si tiene manejador para poner el bus a LOW lo guarda, de lo contrario manda error.
        if(one_wire_config->bus_drive_low_func)
            m_one_wire.bus_drive_low_func = one_wire_config->bus_drive_low_func;
        else
            return ONE_WIRE_ERROR_INVALID_PARAM;

        // Si tiene manejador para liberar el bus lo guarda, de lo contrario manda error.
        if(one_wire_config->bus_release_func)
            m_one_wire.bus_release_func = one_wire_config->bus_release_func;
        else
            return ONE_WIRE_ERROR_INVALID_PARAM;

        if(one_wire_config->bus_read_func)
            m_one_wire.bus_read_func = one_wire_config->bus_read_func; 
        else
            return ONE_WIRE_ERROR_INVALID_PARAM;

        if(one_wire_config->delay_us_func)
            m_one_wire.delay_us_func = one_wire_config->delay_us_func; 
        else
            return ONE_WIRE_ERROR_INVALID_PARAM;

    }
    else
        return ONE_WIRE_ERROR_INVALID_PARAM;

    m_one_wire.bus_release_func(m_one_wire.bus_pin);
    m_one_wire.is_ready=1;

    return ONE_WIRE_OK;
}

void one_wire_uninit(){

    if(m_one_wire.is_ready)
    {
        m_one_wire.bus_release_func(m_one_wire.bus_pin);
        m_one_wire.is_ready=0;
        m_one_wire.bus_read_func = 0;
        m_one_wire.bus_release_func =0;
        m_one_wire.bus_drive_low_func =0;
        m_one_wire.delay_us_func =0;
    }
}

one_wire_error_t one_wire_read_rom(one_wire_rom_code_t* rom_code){

    one_wire_error_t err_code= ONE_WIRE_OK;

    err_code = one_wire_write_byte(ONE_WIRE_COMMAND_READ_ROM);
    if(err_code == ONE_WIRE_OK)
        err_code = one_wire_read_buffer((uint8_t*)rom_code, 8);

    return err_code;
}

one_wire_error_t one_wire_match_rom(one_wire_rom_code_t* rom_code){

    // Sin implementar, la función siempre regresa error.
    return ONE_WIRE_ERROR_MATCH;
}

one_wire_error_t one_wire_skip_rom(){
    return one_wire_write_byte(ONE_WIRE_COMMAND_SKIP_ROM);
}

one_wire_error_t one_wire_write_buffer(uint8_t* p_buffer, uint16_t buffer_size){
    uint16_t i;
    uint8_t j;
    one_wire_error_t err_code= ONE_WIRE_OK;

    for(i=0;i<buffer_size && err_code;+i++){
        for (j = 0; j < 8 && err_code == ONE_WIRE_OK; ++j)
            if((p_buffer[i]>>j) & 0x01)
                err_code = one_wire_write_1();
            else
                err_code = one_wire_write_0();
    }

    return err_code;
}

one_wire_error_t one_wire_read_buffer(uint8_t* p_buffer, uint16_t buffer_size){
    uint16_t i;
    uint8_t j, in_bit=0;
    one_wire_error_t err_code= ONE_WIRE_OK;

    for(i=0;i<buffer_size && err_code == ONE_WIRE_OK; i++){

        p_buffer[i] = 0;
        for (j = 0; j < 8 && err_code == ONE_WIRE_OK; j++){
            p_buffer[i] >>= 1;
            err_code = one_wire_read_bit(&in_bit);
            p_buffer[i] |= in_bit<<7; 
        }
    }

    return err_code;
}

one_wire_error_t one_wire_write_byte(uint8_t data){

    uint8_t i;
    one_wire_error_t err_code= ONE_WIRE_OK;

    for (i = 0; i < 8 && err_code == ONE_WIRE_OK ; i++)
        if((data>>i) & 0x01)
            err_code = one_wire_write_1();
        else
            err_code = one_wire_write_0();

    return err_code;
}

one_wire_error_t one_wire_read_byte(uint8_t* in_data){
    uint8_t i;
    uint8_t in_bit=0;
    one_wire_error_t err_code= ONE_WIRE_OK;

    *in_data=0;


    for (i = 0; i < 8 && err_code == ONE_WIRE_OK; i++){
        *in_data >>= 1;
        err_code = one_wire_read_bit(&in_bit);
        *in_data |= in_bit<<7; 
    }

    return err_code;
}

one_wire_error_t one_wire_write_0(){

    if(m_one_wire.is_ready)
    {
        m_one_wire.bus_drive_low_func(m_one_wire.bus_pin);
        //m_one_wire.delay_us_func(65);
        m_one_wire.delay_us_func(ONE_WIRE_START_TIME + ONE_WIRE_WRITE_TIME);
        m_one_wire.bus_release_func(m_one_wire.bus_pin);
        //m_one_wire.delay_us_func(10);
        m_one_wire.delay_us_func(ONE_WIRE_RECUPERATION_TIME);
    }
    else
        return ONE_WIRE_ERROR_NO_INIT;

    return ONE_WIRE_OK;

}

one_wire_error_t one_wire_write_1(){

    if(m_one_wire.is_ready)
    {
        m_one_wire.bus_drive_low_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_START_TIME);
        //m_one_wire.delay_us_func(10);
        m_one_wire.bus_release_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_WRITE_TIME + ONE_WIRE_RECUPERATION_TIME);
        //m_one_wire.delay_us_func(55);
    }
    else
        return ONE_WIRE_ERROR_NO_INIT;

    return ONE_WIRE_OK;

}

one_wire_error_t one_wire_read_bit(uint8_t* in_bit){

    if(m_one_wire.is_ready)
    {  
        m_one_wire.bus_drive_low_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_START_TIME);
        //m_one_wire.delay_us_func(3);
        m_one_wire.bus_release_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_SAMPLE_TIME);
        //m_one_wire.delay_us_func(10);
        *in_bit = m_one_wire.bus_read_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_SAMPLE_DELAY);
    }
    else
        return ONE_WIRE_ERROR_NO_INIT;

    return ONE_WIRE_OK;
}

one_wire_error_t one_wire_reset(){

    uint8_t is_present = 0;

    if(m_one_wire.is_ready)
    {    
        m_one_wire.bus_drive_low_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_RESET_DURATION);
        m_one_wire.bus_release_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_WAIT_RESPONSE_DURATION);
        is_present = !m_one_wire.bus_read_func(m_one_wire.bus_pin);
        m_one_wire.delay_us_func(ONE_WIRE_RESET_DELAY);
    }
    else
        return ONE_WIRE_ERROR_NO_INIT;

    return is_present ? ONE_WIRE_OK : ONE_WIRE_ERROR_NO_RESPONSE;
}

one_wire_error_t one_wire_delay(uint32_t us){

    if(m_one_wire.is_ready)
        m_one_wire.delay_us_func(us);
    else
        return ONE_WIRE_ERROR_NO_INIT; 

    return ONE_WIRE_OK;

}

