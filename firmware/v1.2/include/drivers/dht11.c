
#include "dht11.h"

// Librería para el manejo de los pines GPIO en el NRF51822.
#include "nrf_gpio.h"
#include "nrf_drv_timer.h"
#include "nrf_delay.h"

static const nrf_drv_timer_t TIMER_DHT11 = NRF_DRV_TIMER_INSTANCE(1);


static void send_start_signal(uint32_t pin_number){

    // Configura el pin como salida y escribe LOW.
    nrf_gpio_cfg_output(pin_number);
    nrf_gpio_pin_clear(pin_number);

    // Espera 20 ms para que el sensor reconozca el reset.
    nrf_delay_ms(18);

    // Configura el pin como entrada con resistencia pullup.
    nrf_gpio_cfg_input(pin_number, NRF_GPIO_PIN_PULLUP);
    
}
dht11_error_t dht11_init(uint32_t pin_number){

    uint32_t err_code;
    nrf_gpio_cfg_input(pin_number, NRF_GPIO_PIN_PULLUP);

    err_code = nrf_drv_timer_init(&TIMER_DHT11, NULL, NULL);
    if(err_code != NRF_SUCCESS)
        return 0;

    return 1;
}

dht11_error_t dht11_read(uint32_t pin_number, uint8_t temp, uint8_t* humidity){

    uint32_t pulses_time[40];

    if(dht11_is_connected(pin_number)){

        send_start_signal(pin_number);
        nrf_delay_us(50);

        if(nrf_gpio_pin_read(pin_number))
            return DHT11_ERROR_NO_RESPONSE;

        while(!nrf_gpio_pin_read(pin_number));

        while(nrf_gpio_pin_read(pin_number));


        for (int i = 0; i < 40; ++i)
        {
            while(!nrf_gpio_pin_read(pin_number));
            nrf_drv_timer_enable(&TIMER_DHT11);

            while(nrf_gpio_pin_read(pin_number));
            nrf_drv_timer_capture(&TIMER_DHT11, NRF_TIMER_CC_CHANNEL0);
            pulses_time[i] = nrf_drv_timer_capture_get(NRF_TIMER_CC_CHANNEL0);
            nrf_drv_timer_disable(&TIMER_DHT11);
            nrf_drv_timer_clear();

        }
    }
    else
        return DHT11_ERROR_NO_RESPONSE;
}
dht11_error_t dht11_is_connected(uint32_t pin_number){
    
    send_start_signal(pin_number);
    nrf_delay_us(50);

    if(nrf_gpio_port_read(pin_number))
        return DHT11_ERROR_NO_RESPONSE;

    nrf_delay_ms(100);

    return DHT11_OK;
}
