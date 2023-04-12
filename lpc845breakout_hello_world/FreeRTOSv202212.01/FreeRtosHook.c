/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"

#if ( configUSE_STACK_MAX_USAGE == 1 )
void task_create_hook(char * name ,unsigned int deep,unsigned int * stack_tail)
{
    {
        extern void task_create_hook_stack(char * name ,unsigned int deep,unsigned int * stack_tail);
        task_create_hook_stack(name,deep,stack_tail);
    }
    
}
#endif


