

 /***************************************************************************************
 *
 *     Copyrigth© 2016  Alfredo Orozco de la Paz 
 *     e-mail:  alfredoopa@gmail.com 
 *                
 *     Descripción
 *                
 *          Ĺibrería que define los componentes conectados a la tarjeta Blue Plant,
 *          es decir, a que pines del chip NRF51822 están conectados los sensores,
 *          leds y el push button.
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


/**
 * Todas las definiciones de estos pines se pueden cambiar acorde a la placa, es decir
 * se puede re-definir este archivo y agregar más conexiones según el diseño de la placa.
 * 
 * El chip NRF51822 puede redirecciónas las salidas de sus periféricos (UART,SPI,TWI.. etc)
 * a cualquier pin GPIO, esto da versatilidad y facilidad a la hora de realizar un diseño
 * con este chip.
 */

/**
* Librería de definiciones para la tarjeta Blue Plant
*/

#ifndef _BLUE_PLANT_H_
#define _BLUE_PLANT_H_


#define LED_R_PIN       22      // Led 2 de la tarjeta, pin GPIO del LED 2 (Activo en alto)
#define LED_G_PIN       21      // Led 3 de la tarjeta, pin GPIO del LED 3 (Activo en alto)
#define LED_B_PIN       20      // Led 4 de la tarjeta, pin GPIO del LED 4 (Activo en alto)

// El push button de la placa está conectado a tierra en un extremo y a un pin del NRF51822 en el otro,
// por lo que se debe configurar resistencias PULL-UP para el push button
#define BUTTON_PIN      16                      // Push button 1 (En la placa KEY1)    
#define BUTTON_PULL     NRF_GPIO_PIN_PULLUP     // Configuración de la resistencia para los botones (PULL-UP o PULL-DOWN), 

// Definiciones de pines para los sensores de la tarjeta.
#define DS18B20_SENSOR_PIN      28                      // (pin #28) Pin para el bus One Wire.
#define LIGHT_SENSOR_PIN        NRF_ADC_CONFIG_INPUT_2  // (pin #02) Pin para el sensor de luz (analógico).
#define DHT11_SENSOR_PIN        3                       // (pin #03) Pin para el sensor de temperatura y humedad DHT11.
#define SOIL_SENSOR_PIN         NRF_ADC_CONFIG_INPUT_6  // (pin #05) Pin para el sensor de humedad de la tierra (analógico).
//#define BATTERY_PIN             NRF_ADC_CONFIG_INPUT_5  // (pin #04) Pin para medir el voltaje de la batería (analógico).
#endif // _BLUE_PLANT_H_
