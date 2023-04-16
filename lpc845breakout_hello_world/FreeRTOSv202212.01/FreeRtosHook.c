/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#if ( configUSE_PERF_CNT == 1 )
#include "perf_counter.h"
#endif


extern void vApplicationTickHook(void)
{
#if ( configUSE_PERF_CNT == 1 )
    user_code_insert_to_systick_handler();
#endif
}

extern void vApplicationStartHook(void)
{
#if ( configUSE_PERF_CNT == 1 )
       init_cycle_counter();
#endif
}


extern void vApplicationTaskSwitchInHook(void * name,void *ptTCB)
{
#if ( configUSE_PERF_CNT == 1 )
    __on_context_switch_in((uint32_t *)ptTCB);
#endif
}

extern void vApplicationTaskSwitchOutHook(void *ptTCB)
{
#if ( configUSE_PERF_CNT == 1 )
    __on_context_switch_out((uint32_t *)ptTCB);
#endif
}


#if ( configUSE_STACK_MAX_USAGE == 1 )
void task_create_hook(char * name ,unsigned int deep,unsigned int * stack_tail)
{
    {
        extern void task_create_hook_stack(char * name ,unsigned int deep,unsigned int * stack_tail);
        task_create_hook_stack(name,deep,stack_tail);
    }
    
}
#endif


