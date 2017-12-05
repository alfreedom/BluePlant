
#ifndef _ONE_WIRE_H_
#define _ONE_WIRE_H_

#include <stdint.h>

#define ROM_CODE_SIZE 8     // Numero de bytes del ROM CODE


#define ONE_WIRE_RESET_DURATION          480     // Duración de la señal de reset (en microsegundos).
#define ONE_WIRE_WAIT_RESPONSE_DURATION  70      // Espera para leer la respuesta del dispositivo despues de un reset (en microsegundos).
#define ONE_WIRE_RESET_DELAY             410

#define ONE_WIRE_RECUPERATION_TIME       10      // Tiempo de espera entre cada envío de bit para esperar a que se estabilice la señal (en microsegundos).
#define ONE_WIRE_TIME_SLOT               60      // Duración de los ciclos de escritura y lectura de un bit (en microsegundos).

#define ONE_WIRE_START_TIME              6       // Tiempo de la señal de inicio que indica transmisión de bit.
#define ONE_WIRE_WRITE_TIME              (ONE_WIRE_TIME_SLOT - ONE_WIRE_START_TIME)      // Duración de los ciclos de escritura y lectura de un bit (en microsegundos).
#define ONE_WIRE_SAMPLE_TIME             10      // Tiempo de espera para leer un bit en el bus despues de la señal de inicio.
#define ONE_WIRE_SAMPLE_DELAY            (ONE_WIRE_WRITE_TIME - ONE_WIRE_SAMPLE_TIME)

// Apuntadores a las funciones que manipulan físicamente los pines
// de E/S del Hardware y para la función que hace retardos en microsegundos.
typedef void (*gpio_one_wire_pin_clear)(uint8_t pin_no);        // Función para poner un pin a 0.
typedef void(*gpio_one_wire_pin_set_input)(uint8_t pin_no); // Función para poner un pin como entrada.
typedef uint8_t (*gpio_one_wire_pin_test)(uint8_t pin_no);      // Función para leer el estado de un pin.
typedef void (*one_wire_delay_us)(uint32_t microseconds);       // Función para hacer delay en microsegundos.


// Define los comandos de ROM para el protocolo 1 Wire.
typedef enum{
    ONE_WIRE_COMMAND_ALAMR_SEARCH        = 0xEC,
    ONE_WIRE_COMMAND_SEARCH_ROM          = 0xF0,
    ONE_WIRE_COMMAND_READ_ROM            = 0x33,
    ONE_WIRE_COMMAND_MATCH_ROM           = 0x55,
    ONE_WIRE_COMMAND_SKIP_ROM            = 0xCC,
    ONE_WIRE_COMMAND_OVERDRIVE_SKIP_ROM  = 0X3C,
    ONE_WIRE_COMMAND_OVERDRIVE_MATCH_ROM = 0X68
}one_wire_command_t;

// Define los errores del protocolo 1 wire.
typedef enum{
    ONE_WIRE_OK = 0,
    ONE_WIRE_ERROR_NO_RESPONSE,
    ONE_WIRE_ERROR_NO_INIT,
    ONE_WIRE_ERROR_MATCH,
    ONE_WIRE_ERROR_INVALID_PARAM
}one_wire_error_t;

typedef struct{
    uint8_t family_code;
    uint8_t serial_number0;
    uint8_t serial_number1;
    uint8_t serial_number2;
    uint8_t serial_number3;
    uint8_t serial_number4;
    uint8_t serial_number5;
    uint8_t crc;
}one_wire_rom_code_t;

typedef struct{
    uint8_t                     is_ready;
    uint8_t                     bus_pin;
    gpio_one_wire_pin_clear     bus_drive_low_func;
    gpio_one_wire_pin_set_input bus_release_func;
    gpio_one_wire_pin_test      bus_read_func;
    one_wire_delay_us           delay_us_func;
}one_wire_cfg_t;


// Inicializa el driver y el bus para el protocolo One Wire
one_wire_error_t one_wire_init(one_wire_cfg_t* one_wire_config);

void one_wire_uninit();

// Envia un 1 por el bus
one_wire_error_t one_wire_write_1();

// Envía un 0 por el bus.
one_wire_error_t one_wire_write_0();

// Lee un bit del bus.
one_wire_error_t one_wire_read_bit(uint8_t* in_bit);

// Envía la señal de reset al bus.
one_wire_error_t one_wire_reset();

// Función para escribir un byte en el bus.
one_wire_error_t one_wire_write_byte(uint8_t data);

// Función para leer un byte deel bus.
one_wire_error_t one_wire_read_byte(uint8_t* in_data);

// Función para escribir un arreglo de bytes en el bus.
one_wire_error_t one_wire_write_buffer(uint8_t* p_buffer, uint16_t buffer_size);

// Función para leer un arreglo de bytes del bus.
one_wire_error_t one_wire_read_buffer(uint8_t* p_buffer, uint16_t buffer_size);


// Función para leer la dirección guardada en la memoria ROM del dispositivo.
// Recibe una estructura donde se guardan los datos de la ROM.
one_wire_error_t one_wire_read_rom(one_wire_rom_code_t* rom_code);

// Función para direccíonar un dispositivo mediante la dirección de la ROM.
one_wire_error_t one_wire_match_rom(one_wire_rom_code_t* rom_code);

// Función para saltar el direccionamiento. Se puede saltar el direccionamiento
// si hay sólo un dispositivo en el bus, de lo contrario se tendrá que direccionar
// el dispositivo con la función  one_wire_match_rom.
one_wire_error_t one_wire_skip_rom();

one_wire_error_t one_wire_delay(uint32_t us);

#endif // _ONE_WIRE_H_
