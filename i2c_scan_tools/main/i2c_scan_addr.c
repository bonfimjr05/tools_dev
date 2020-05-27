/*
 *
 *@file        i2c_scan_addr.c
 *@Author      Paulo Bonfim Jr
 *@date        27/05/2020
 *@version     1.0.0
 *
 *@brief Scan device addresses, detects multiple devices
 */


/*************************************************** Includes ************************************************/

#include "i2c_scan_addr.h"




/**************************************** Function Definitions  **********************************************/

/*!
 *
 *@brief Scan device addresses
 *@param Structure instance of i2c_dev_t
 *
 *@return Nothing
 *
 */

void i2c_scan(struct i2c_dev_t *dev) {
  
  uint8_t address;
  int8_t ret, count = 0;
  
  printf("     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
  for (int i = 0; i < 128; i += 16) {
     printf("%02x: ", i);
     
     for (int j = 0; j < 16; j++) {
       fflush(stdout);
       address = i + j;
       
       ret = dev-> write_fptr(address); /*!< Generic communication function pointer i2c_write*/
      
       if (ret == 0) {
         printf("%02x ", address);
         count++;
          
       }
       else if (ret == 1) {
         printf("UU ");
          
       }
       else {
         printf("-- ");
          
       }
       
     }
     
     printf("\r\n");
     
  }
  
  if(count != dev-> NUM_DEV) {
    printf("Device Number:%d different Device Address: %d \n", count, dev-> NUM_DEV );
    printf("ERROR: Device unplugged or Address equal");
    
  }
  else {
    printf("Device Number:%d and Device Address: %d \n ", count, dev-> NUM_DEV );
    
  }
  
  printf("\r\n");

}


