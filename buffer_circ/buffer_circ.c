/*
 *
 *@file        buffer_circ.c
 *@Author      Paulo Bonfim Jr
 *@date        29/05/2020
 *@version     1.0.0
 *
 *@brief Buffer Circular
 */


#include "buffer_circ.h"


void init_buffer() {
  
  iniBuffer = 0;
  endBuffer = 0;
  
}

int16_t next(elem) {
  
  if((elem + 1) < SIZE_BUFF) {
    
    return ++elem;
    
  } else {
    
    return 0;
  }
  
}


void add_buffer(int16_t elem) {
  
  if(next(endBuffer) != iniBuffer) {
    
    circBuffer[endBuffer] = elem;
    endBuffer = next(endBuffer);
    
  }
  
  
}


void rmv_buffer() {
  
  if(iniBuffer =! endBuffer) {
    
    iniBuffer = next(iniBuffer);
    
  }
  
}
