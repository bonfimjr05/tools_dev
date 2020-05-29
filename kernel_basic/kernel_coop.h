#ifndef KERNEL_COOP_H
#define KERNEL_COOP_H


#define NUMBER_OF_TASKS               50
#define TIMER_MAX_RUN                 100 //ms


#define success                        1
#define fail                           0

#define _true                          success
#define _false                         fail
#define ENABLE                         success
#define DISABLE                        fail


typedef void(*task_fptr)();
typedef void(*reset_fptr)();
typedef uint32_t(*systick_fptr)();


typedef struct {
  
  task_fptr _Function;
  reset_fptr _Reset;
  systick_fptr _SysTick;
  unsigned char *taskName;
  uint16_t taskPeriod;
  int8_t taskEnable;
  
  
}task_handle_t;


task_handle_t kernelBuffer[NUMBER_OF_TASKS];


volatile uint32_t taskCounter[NUMBER_OF_TASKS];
volatile int16_t  timerOfRun;
volatile int8_t   taskRun;



int8_t kenel_init(void);
int16_t add_task(task_fptr _function, unsigned char _taskName,uint16_t _period, int8_t _taskEnable,task_handle_t *_task);
int8_t rmv_task(task_handle_t *_task);
void star_task(systick_fptr _sysTickCounter);
void manager_task(reset_fptr _reset);




#endif