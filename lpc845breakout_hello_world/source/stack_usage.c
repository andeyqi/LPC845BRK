#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FreeRTOS.h"
#if (configUSE_PERF_CNT == 1)
#include "perf_counter.h"
#endif
#include "littleshell.h"
#include "trace_dump.h"
#include "fsl_debug_console.h"

#if ((configUSE_STACK_MAX_USAGE == 0 )&& (configUSE_PERF_CNT == 1))
    #error perf is depend on configUSE_STACK_MAX_USAGE = 1
#endif


#if ( configUSE_STACK_MAX_USAGE == 1 )

struct task_stack_info
{
    char task_name[configMAX_TASK_NAME_LEN];
    uint32_t stack_deep;
    uint32_t*  stack_tail;
};

struct task_stack_info_tbl
{
    uint8_t num;
    struct task_stack_info * tasks;
};

#define OS_NUM_TASKS_SUPPORT 10

static struct task_stack_info stack_all[OS_NUM_TASKS_SUPPORT];

static struct task_stack_info_tbl task_stacks =
{
    .num = 0,
    .tasks = stack_all,
};


#define TASK_STACK_NAME(i) task_stacks.tasks[i].task_name
#define TASK_STACK_DEEP(i) task_stacks.tasks[i].stack_deep
#define TASK_STACK_TAIL(i) task_stacks.tasks[i].stack_tail
#define TASK_STACK_TAIL_OFF_ADDR(i,off) &task_stacks.tasks[i].stack_tail[off]



void task_create_hook_stack(char * name ,unsigned int deep,unsigned int * stack_tail)
{
    uint8_t i_loop = task_stacks.num;
    uint8_t len,i;
    char * p_task_name;

    if(i_loop < OS_NUM_TASKS_SUPPORT)
    {
        p_task_name = TASK_STACK_NAME(i_loop);
        strcpy(TASK_STACK_NAME(i_loop),name);
        if((len = strlen(TASK_STACK_NAME(i_loop))) != (configMAX_TASK_NAME_LEN-1))
        {
            for(i = len;i < configMAX_TASK_NAME_LEN-1;i++)
                p_task_name[i] = '\0';
        }
        p_task_name[configMAX_TASK_NAME_LEN-1] = '\0';
        TASK_STACK_DEEP(i_loop) = deep*4;
        TASK_STACK_TAIL(i_loop) = stack_tail;
        /* if use pref to set perf default value */
#if ( configUSE_PERF_CNT == 1 )
        memset((void*)TASK_STACK_TAIL(i_loop),0,sizeof(task_cycle_info_t)+8);
#endif
        task_stacks.num++;
    }
    else
    {
        PRINTF("task num is max than OS_NUM_TASKS_SUPPORT.\r\n");
    }
}


static int buff_continuous_numbers(uint8_t * buff,uint8_t data)
{
    int l = 0;

    if(NULL == buff)
        return 0;

    while(data == buff[l++]);

    return  --l;
}

extern size_t xPortGetFreeHeapSize( void );

unsigned int stack(char argc,char ** argv)
{
    uint8_t i,j;
    int len,name_len;
    char task_name[configMAX_TASK_NAME_LEN];

    if(argc == 1)
    {
        //logctrl_instance()->is_sync = 1;
        PRINTF("taskname\tdeep\tused\taddress\t\t\tusage\r\n");
        for(i = 0;i < task_stacks.num;i++)
        {
#if ( configUSE_PERF_CNT != 1 )
            len = buff_continuous_numbers((uint8_t *)TASK_STACK_TAIL(i),0xa5);
#else
            len = buff_continuous_numbers((uint8_t *)TASK_STACK_TAIL_OFF_ADDR(i,WORD_OF_CYCEL_INFO),0xa5);
            if(len)
                len += BYTE_OF_CYCEL_INFO;
#endif
        strcpy(task_name,TASK_STACK_NAME(i));
        task_name[configMAX_TASK_NAME_LEN - 1] = '\0';
        if((name_len = strlen(TASK_STACK_NAME(i))) != (configMAX_TASK_NAME_LEN-1))
        {
            for(j = name_len;j < configMAX_TASK_NAME_LEN-1;j++)
                task_name[j] = ' ';
        }
            PRINTF("%s\t%d\t%d\t0x%p~0x%p\t%d%%\r\n",task_name,TASK_STACK_DEEP(i),
            TASK_STACK_DEEP(i)-len,TASK_STACK_TAIL(i),
            TASK_STACK_TAIL(i)+(TASK_STACK_DEEP(i)/4),(100-(len*100)/TASK_STACK_DEEP(i)));
        }
        PRINTF("\r\nHeap Total:%d\tFree:%d\r\n",configTOTAL_HEAP_SIZE,xPortGetFreeHeapSize());
        //logctrl_instance()->is_sync = 0;
    }
    if(argc == 2)
    {
        uint8_t index = atoi(argv[1]);
        if(index >=  task_stacks.num)
            goto out;
        PRINTF("task name [%s] stack deep 0x%x\r\n",TASK_STACK_NAME(index),TASK_STACK_DEEP(index));
        //logctrl_instance()->is_sync = 1;
        trace_byte_stream((uint8_t *)TASK_STACK_TAIL(index),TASK_STACK_DEEP(index),0);
        //logctrl_instance()->is_sync = 0;
    }
out:
    return 0;
}

LTSH_FUNCTION_EXPORT(stack,"show task statck info");

#if ( configUSE_PERF_CNT == 1 )

unsigned int perf(char argc,char ** argv)
{
    uint8_t i,j,len;
    int64_t count = get_system_ticks();
    char task_name[configMAX_TASK_NAME_LEN];

    //logctrl_instance()->is_sync = 1;
    if(argc == 1)
    {
        PRINTF("taskname\trecent\t\tactive\tusedmax\t\tusedmin\t\tusedavg\t\tcpuusage\r\n");
        for(i = 0;i < task_stacks.num;i++)
        {
            task_cycle_info_t * pcycle = get_rtos_task_cycle_info_by_stack(TASK_STACK_TAIL(i));
            task_name[configMAX_TASK_NAME_LEN - 1] = '\0';
            strcpy(task_name,TASK_STACK_NAME(i));
            if((len = strlen(TASK_STACK_NAME(i))) != (configMAX_TASK_NAME_LEN-1))
            {
                for(j = len;j < configMAX_TASK_NAME_LEN-1;j++)
                    task_name[j] = ' ';
            }
            PRINTF("%s\t%010d\t%d\t%010d\t%010d\t%010d\t%.2f\r\n",
                   task_name,pcycle->nUsedRecent,pcycle->wActiveCount,
                   pcycle->nUsedMax,pcycle->nUsedMin,pcycle->lUsedTotal/pcycle->wActiveCount,
                   ((double)(pcycle->lUsedTotal))/((double)count)*((double)100.0f));
        }
    }
    //logctrl_instance()->is_sync = 0;
    return 0;
}

LTSH_FUNCTION_EXPORT(perf,"show perf info");
#endif

#endif /* end of configUSE_STACK_MAX_USAGE */

