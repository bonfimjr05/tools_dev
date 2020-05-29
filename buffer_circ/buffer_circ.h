/*
 *
 *@file        buffer_circ.h
 *@Author      Paulo Bonfim Jr
 *@date        29/05/2020
 *@version     1.0.0
 *
 *@brief Buffer Circular
 */




#ifndef BUFFER_CIRC_H
#define BUFFER_CIRC_H


#define SIZE_BUFF 6

int16_t circBuffer[SIZE_BUFF];
int16_t iniBuffer;
int16_t endBuffer;




void init_buffer();
int16_t next(elem);
void add_buffer(int16_t elem);
void rmv_buffer(void);

#endif