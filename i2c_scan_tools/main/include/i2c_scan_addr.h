/*
 *
 *@file        i2c_scan_addr.c
 *@Author      Paulo Bonfim Jr
 *@date        27/05/2020
 *@version     1.0.0
 *
 *@brief Scan device addresses, detects multiple devices
 */

#ifndef I2C_SCAN_ADDR_H
#define I2C_SCAN_ADDR_H
/*************************************************** Includes ************************************************/

#include <stdio.h>




/*************************************************** Structure ************************************************/

/*! Structure i2c_dev_t*/
typedef struct {
  
  i2c_scan_fptr_t write_fptr;
  int8_t NUM_DEV;
  
  
}i2c_dev_t;

/*************************************************** Function prototype  ******************************************/


/*!
 *
 *@brief Generic communication function pointer
 *@param Address device
 *
 *@return result of execution status
 *@retval zero -> Success / +ve Timeout / -ve Error
 *
 */

typedef int8_t (*i2c_scan_fptr_t)(uint8_t dev_addr);


/*!
 *
 *@brief Scan device addresses
 *@param Structure instance of i2c_dev_t
 *
 *@return Nothing
 *
 */

void i2c_scan(i2c_dev_t *dev);


#endif
