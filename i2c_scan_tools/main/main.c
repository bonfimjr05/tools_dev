/*
 *
 *@file        main.c
 *@Author      Paulo Bonfim Jr
 *@date        27/05/2020
 *@version     1.0.0
 *
 *@brief       Application Example ESP32, using ESP-IDF.
 *
 */


/*************************************************** Includes ************************************************/

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

#include "i2c_scan_addr.h"


/*************************************************** Defines *************************************************/

#define I2C_MASTER_TX_BUF_DISABLE               0                   /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE               0                   /*!< I2C master doesn't need buffer */
#define WRITE_BIT                               I2C_MASTER_WRITE    /*!< I2C master write */
#define READ_BIT                                I2C_MASTER_READ     /*!< I2C master read */
#define ACK_CHECK_EN                            0x1                 /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS                           0x0                 /*!< I2C master will not check ack from slave */
#define ACK_VAL                                 0x0                 /*!< I2C ack value */
#define NACK_VAL                                0x1                 /*!< I2C nack value */


/************************************************ Global Variebles ***************************************************/

static gpio_num_t i2c_gpio_sda                  = 18;               /*!< I2C GPIO SDA */
static gpio_num_t i2c_gpio_scl                  = 19;               /*!< I2C GPIO SDL */
static uint32_t i2c_frequency                   = 100000;           /*!< I2C FREQUENCY */
static i2c_port_t i2c_port                      = I2C_NUM_0;        /*!< I2C PORT */


/*************************************************** Function prototype  ******************************************/

int8_t i2c_write_user(uint8_t dev_addr);
static void i2c_initDriver();


/*************************************************** APP MAIN ******************************************************/

void app_main() {
  
/* !Instantiates i2c_dev*/

 i2c_dev_t i2c_dev = {
   
   .write_fptr = i2c_write_user, /*!< Function pointers*/
   .NUM_DEV = 2                  /*!< Number device*/
 };
  

 i2c_driver_install(i2c_port, I2C_MODE_MASTER, I2C_MASTER_RX_BUF_DISABLE,I2C_MASTER_TX_BUF_DISABLE,0);
 i2c_initDriver();
 i2c_scan(&i2c_dev);
 
}



/**************************************** Global Function Definitions  **********************************************/
	
/*!
 *@brief Function instantiates i2c and initialize.
 *
 *@return Nothing
 *
 */
static void i2c_initDriver() {
  
  
  i2c_config_t conf_i2c = {
    
    .mode = I2C_MODE_MASTER,
    .sda_io_num = i2c_gpio_sda,
    .sda_pullup_en = GPIO_PULLUP_ENABLE,
    .scl_io_num = i2c_gpio_scl,
    .scl_pullup_en = GPIO_PULLUP_ENABLE,
    .master.clk_speed = i2c_frequency
    
  };
  
  i2c_param_config(i2c_port, &conf_i2c);
}
	

/*!
 *
 *@brief Function of write i2c
 *@param Address device
 *
 *@return result of execution status
 *@retval zero -> Success / +ve Timeout / -ve Error
 *
 */

int8_t i2c_write_user(uint8_t dev_addr) {
  
   int8_t st;
  
 /*! 2. Crie um link de comando com i2c_cmd_link_create().*/
   i2c_cmd_handle_t cmd = i2c_cmd_link_create();
       
  /*! 3. Bit de início -i2c_master_start()*/
   i2c_master_start(cmd);
       
  /*! 4. Endereço do escravo - i2c_master_write_byte()*/
   i2c_master_write_byte(cmd, (dev_addr << 1) | WRITE_BIT, ACK_CHECK_EN);
       
  /*! 5. Dados - um ou mais bytes como argumento de i2c_master_write()*/
       
  /*! 6. Bit de parada -i2c_master_stop()*/
   i2c_master_stop(cmd);
       
  /*! 7. Acione a execução do link de comando pelo controlador I2C chamando i2c_master_cmd_begin(). */
   esp_err_t ret = i2c_master_cmd_begin(i2c_port, cmd, 50 / portTICK_RATE_MS);
      
  /*! 8. Após a transmissão dos comandos, libere os recursos usados pelo link de comando chamando i2c_cmd_link_delete().*/
   i2c_cmd_link_delete(cmd);
      
      
    if (ret == ESP_OK) {
      st = 0;
        
    }
    else if (ret == ESP_ERR_TIMEOUT) {
      st = 1;
        
    }
    else {
       st = -1;
        
    }
      
      
    return st;
       
  }
  


