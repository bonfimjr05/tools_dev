/*
 *
 *@file        kernel_coop_bc.h
 *@Author      Paulo Bonfim Jr
 *@date        29/05/2020
 *@version     1.0.0
 *
 *@brief kernel cooperativo (não preemptivo)
 */


#include "kernel_coop.h"


uint16_t iniBuffer, endBuffer;

int16_t next(int16_t elem) {
  
  if((elem + 1) < NUMBER_OF_TASKS) {
    
    return (++elem);
  }else {
  
    return 0;
  }

}

int16_t addBuff(task_handle_t addTask) {
  
  if(next(endBuffer) != iniBuffer) {
    kernelBuffer[endBuffer] = addTask;
    endBuffer = next(endBuffer);
    
    return endBuffer - 1;
  }
  
}


int8_t kenel_init() {
  
  memset(kernelBuffer, NULL, sizeof(NUMBER_OF_TASKS));
  memset(taskCounter, 0, sizeof(NUMBER_OF_TASKS));
  
  
  taskRun = _false;
  
  
  return success;
  
}


int16_t add_task(task_fptr _function, unsigned char _taskName, uint16_t _period, int8_t _taskEnable,task_handle_t *_task) {
  
  int i;
  
  _task->_Function = _function;
  _task-> taskName = _taskName;
  _task-> taskPeriod = _period;
  _task-> taskEnable = _taskEnable;
  
  
  for(i = 0 ; i < NUMBER_OF_TASKS; i++) {
    
    if((kernelBuffer[i] != NULL) && (kernelBuffer[i] == _task)) {
      return i;
    }
  }
  
  if(!kernelBuffer[i]) {
    
    return addBuff(_task);
    
  }
  
  
  return -1;

}


int8_t rmv_task(task_handle_t *_task) {
  
  
  for (int i = 0 ; i < NUMBER_OF_TASKS ; i++) {
    
    if(kernelBuffer[i] == _task) {
      
      kernelBuffer[i] = NULL;
      
      return success
      
    }
    
  }
  
  return fail;
}



void star_task(systick_fptr _sysTickCounter) {
  
  
  int i;
  uint32_t _sysTick = _sysTickCounter();
  
  for(;;) {
    
    for(i = 0; i < NUMBER_OF_TASKS ; i++) {
      
      if(kernelBuffer[i] != 0) {
        
        if((_sysTick - taskCounter[i] > kernelBuffer[i]->taskPeriod) && (kernelBuffer[i]->taskEnable == ENABLE)) {
        
          taskRun = _true;
          timerOfRun = TIMER_MAX_RUN;
          kernelBuffer[i]->_Function();
          taskRun = _false;
          taskCounter[i] = _sysTick;
        
        }
      
      }
      
    }
    
  }
  
}



void manager_task(reset_fptr _reset) {
  
  if(taskRun == _true) {
    
    timerOfRun--;
    
    if(!timerOfRun) {
      
      /*! reset micro  */
      _reset();
      
      while(1);
    }
    
  }
  
  
}