#ifndef _DS1820B_H_
#define _DS1820B_H_


#include "onewire.h"

// Se envian datos comenzando por el bit menos significativos del byte 3 (máximo 3 bytes a enviar)
// y se leen los bytes comenzado por el bit menos significativo del byte 1.

// Secuencia de intercambio de datos.
//  1- Inicialización
//  2- Envio del comando ROM seguido de los datos de petición requerida.
//  3- Comando de función para el DS1820B seguido de los datos de petición requerida.
//
//  Es importante seguir esta secuencia cada vez que se quiere acceder al sensor DS1820B.  

#define DS18B20_FAMILY_CODE     0x28
#define DS18B20_SCRATCHPAD_SIZE 9


typedef enum{
    DS18B20_OK = 0x00,
    DS18B20_ERROR_NOT_FOUND = 0x48,
    DS18B20_ERROR_DATA_CRC = 0x49,
}ds18b20_error_t;

typedef enum{
    DS18B20_COMMAND_WRITE_SCRATCHPAD    = 0x4E,
    DS18B20_COMMAND_READ_SCRATCHPAD     = 0xBE,
    DS18B20_COMMAND_COPY_SCRATCHPAD     = 0x48,
    DS18B20_COMMAND_CONVERT_TEMPERATURE = 0x44,
    DS18B20_COMMAND_RECALL_EEPROM       = 0xB8,
    DS18B20_COMMAND_READ_POWER_SUPPLY   = 0xB4,
}ds18b20_command_t;

// Define las resouluciones de bits para la temperatura.
typedef enum{
    DS18B20_RESOLUTION_9_BITS   = 0x1F,
    DS18B20_RESOLUTION_10_BITS  = 0x3F,
    DS18B20_RESOLUTION_11_BITS  = 0x5F,
    DS18B20_RESOLUTION_12_BITS  = 0x7F,
}ds18b20_resolution_t;


typedef struct{
    uint8_t temp_l;
    uint8_t temp_h;
    uint8_t tl;
    uint8_t th;
    uint8_t resolution;
    uint8_t reserved_0;
    uint8_t reserved_1;
    uint8_t reserved_2;
    uint8_t crc;
}ds18b20_scratchpad_t;

ds18b20_error_t ds18b20_init(ds18b20_resolution_t resolution);
ds18b20_error_t ds18b20_read_temp(int16_t* temperature);

#endif // _DS1820B_H_
