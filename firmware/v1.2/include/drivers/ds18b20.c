
#include "ds18b20.h"

// Busca si hay un sensor ds18b20 conecato al bus One Wire, si no lo detecta
// devuelve error.
static ds18b20_error_t ds18b20_search_sensor(){
    one_wire_error_t err_code;
    one_wire_rom_code_t rom_code;

    err_code = one_wire_reset();
    if(err_code == ONE_WIRE_OK){
        one_wire_read_rom(&rom_code);

        if(rom_code.family_code != DS18B20_FAMILY_CODE)
             return DS18B20_ERROR_NOT_FOUND;

        err_code = DS18B20_OK;
    }

    return err_code;
}

// Escribe la resolución de la lectura de temperatura en sel sensor.
// Recibe la resolución a programar.
static ds18b20_error_t ds18b20_set_resolution(ds18b20_resolution_t resolution){
    one_wire_error_t err_code;

    err_code = one_wire_reset();
    if(err_code == ONE_WIRE_OK){
        one_wire_skip_rom();
        one_wire_write_byte(DS18B20_COMMAND_WRITE_SCRATCHPAD);
        one_wire_write_byte(0);
        one_wire_write_byte(0);
        one_wire_write_byte(resolution);

        err_code = DS18B20_OK;
    }

    return err_code;
}

// Checa si hay errores en la transmisión de la temperatura haciendo el
// cálculo CRC con los datos del scratchpad.
// Recib el scratchpad al que hay que calcular el CRC.
static ds18b20_error_t ds18b20_check_crc(ds18b20_scratchpad_t* scratchpad){

    uint8_t fb,i,j;
    uint8_t shift_reg=0;

    for (i = 0; i < DS18B20_SCRATCHPAD_SIZE; i++)
    {
        for (j = 0; j < 8; j++){

            // Operación xor con el bit de entrada y el bit menos significativo
            // del registro para determinar el bit de operación
            fb = (shift_reg & 0x01) ^ (((uint8_t*)scratchpad)[i] >>j & 0x01);
    
            // Hace un corrimiento del registro hacia la derecha
            shift_reg >>= 1;     
            
            // SI el bit de operación es 1, hace la operación xor
            // con la máscara
            if (fb==1)
             shift_reg ^= 0x8C;  /* CRC ^ 1000 1100 */
            
        }
    }

    // Si el resultado del cálculo del CRC con los 8 bytes del scratchpad
    // + el byte del CRC es diferente de 0, hay error en los datos
    if(shift_reg)
        return DS18B20_ERROR_DATA_CRC;

    return DS18B20_OK;
}

// Inicializa el sensor buscandolo en el bus y programando la resolución.
// Recibe la resolución de conversión del sensor.
// Devuelve error si hay problemas de comunicación con el sensor.
ds18b20_error_t ds18b20_init(ds18b20_resolution_t resolution){

    ds18b20_error_t err_code;

    err_code = ds18b20_search_sensor();
    if(err_code == DS18B20_OK)
        err_code = ds18b20_set_resolution(resolution);

    return err_code;
}


// Lee la temperatura registrada por el sensor. Busca el sensor en el bus, si lo
// encuentra lee la temperatura, si no devuelve un error de comunicación. 
// Si la comunicación fue correcta, verifica que los datos sean correctos, si no
// devuelve un error de chequeo de CRC.
ds18b20_error_t ds18b20_read_temp(int16_t* temperature){

    ds18b20_scratchpad_t scrpad;
    ds18b20_error_t err_code;

    *temperature=0;
    
    err_code = ds18b20_search_sensor();
    if(err_code == DS18B20_OK){

        one_wire_reset();
        one_wire_skip_rom();
        one_wire_write_byte(DS18B20_COMMAND_CONVERT_TEMPERATURE);
        one_wire_delay(900000);

        one_wire_reset();
        one_wire_skip_rom();
        one_wire_write_byte(DS18B20_COMMAND_READ_SCRATCHPAD);
        one_wire_read_buffer((uint8_t*)&scrpad, DS18B20_SCRATCHPAD_SIZE);
        err_code = ds18b20_check_crc(&scrpad);
        one_wire_reset();

        *temperature |= ((uint16_t)scrpad.temp_l);
        *temperature |= ((uint16_t)scrpad.temp_h)<<8;

    }
    return err_code;
}
