#include "fsl_device_registers.h"
#include "littleshell.h"
#include "fsl_clock.h"
#include "fsl_debug_console.h"
#include "fsl_syscon.h"
#include "rtlist.h"

enum clock_node_id
{
    CLK_NODE_MAIN_CLK = 0,
    CLK_NODE_MAIN_CLK_PRE_PLL,
    CLK_NODE_FRO,
    CLK_NODE_FRO_OSC,
    CLK_NODE_SYSTEM,
    CLK_NODE_UART0,
    CLK_NODE_UART1,
    CLK_NODE_CAPT,
    CLK_NODE_MAX
};


typedef struct clock_node
{
    const char * name;
    const char * muxhelp;
    uint32_t rate;
    enum clock_node_id id;
    uint8_t is_update;
    uint8_t parents_num;
    uint8_t mux;
    struct clock_node * parents[8];
    /*clock node ops*/
    uint32_t (*get_rate)(struct clock_node * node);
    int (*set_rate)(struct clock_node * node,uint32_t rate);
    uint8_t (*get_parent)(struct clock_node * node);
    rt_list_t list;
}clock_node_t;

static uint32_t lpc845_get_main_clk_pre_pll(struct clock_node * node)
{
    uint8_t parent = 0xffu;
    uint32_t rate = 0x00;
    if(node->get_parent)
    {
        parent = node->get_parent(node);
    }

    /* 0-FRO 1- External clock 2- Watchdog oscillator 3- FRO_DIV = FRO / 2 */
    switch(parent)
    {
    case 0:
        rate = CLOCK_GetFreq(kCLOCK_Fro);
        break;
    case 1:
        rate = CLOCK_GetFreq(kCLOCK_ExtClk);
        break;
    case 2:
        rate = CLOCK_GetFreq(kCLOCK_WdtOsc);
        break;
    case 3:
        rate = CLOCK_GetFreq(kCLOCK_FroDiv);
        break;
    default:
        break;
    }
    return rate;
}

static uint32_t lpc845_get_fro_clk(struct clock_node * node)
{
    uint8_t parent = 0xffu;
    uint32_t rate = 0x00;
    
    if(node->get_parent)
    {
        parent = node->get_parent(node);
    }
    
    /* 0-fro_oscout is divided by 2 (normal boot) or 16 (low power boot), depending on FAIM low power boot value.
     * 1-FRO clock is direct from FRO oscillator
    */
    switch(parent)
    {
    case 0:
        rate = CLOCK_GetFreq(kCLOCK_FroDiv);
        break;
    case 1:
        rate = CLOCK_GetFreq(kCLOCK_Fro);
        break;
    default:
        break;
    }
    return rate;

}


static uint32_t lpc845_get_uart_clk(struct clock_node * node)
{
    uint8_t parent = 0xffu;
    uint32_t rate = 0x00;
    
    if(node->get_parent)
    {
        parent = node->get_parent(node);
    }
    
    /* 0-fro_oscout is divided by 2 (normal boot) or 16 (low power boot), depending on FAIM low power boot value.
     * 1-FRO clock is direct from FRO oscillator
    */
    switch(parent)
    {
    case 0:
        rate = CLOCK_GetFreq(kCLOCK_Fro);
        break;
    case 1:
        rate = CLOCK_GetFreq(kCLOCK_MainClk);
        break;
    case 2:
        rate = CLOCK_GetFreq(kCLOCK_Frg0);
        break;
    case 3:
        rate = CLOCK_GetFreq(kCLOCK_Frg1);
        break;
    case 4:
        rate = CLOCK_GetFreq(kCLOCK_FroDiv);
        break;    
    default:
        break;
    }
    return rate;

}

static uint32_t lpc845_get_capt_clk(struct clock_node * node)
{
    uint8_t parent = 0xffu;
    uint32_t rate = 0x00;
    
    if(node->get_parent)
    {
        parent = node->get_parent(node);
    }
    
    /* 0-fro_oscout is divided by 2 (normal boot) or 16 (low power boot), depending on FAIM low power boot value.
     * 1-FRO clock is direct from FRO oscillator
    */
    switch(parent)
    {
    case 0:
        rate = CLOCK_GetFreq(kCLOCK_Fro);
        break;
    case 1:
        rate = CLOCK_GetFreq(kCLOCK_MainClk);
        break;
    case 2:
        rate = CLOCK_GetFreq(kCLOCK_PllOut);
        break;
    case 3:
        rate = CLOCK_GetFreq(kCLOCK_FroDiv);
        break;
    case 4:
        rate = CLOCK_GetFreq(kCLOCK_WdtOsc);
        break;    
    default:
        break;
    }
    return rate;

}


static uint32_t lpc845_get_clock_rate(struct clock_node * node)
{
    uint32_t rate = 0u;
    
    switch(node->id)
    {
    case CLK_NODE_MAIN_CLK:
        rate = CLOCK_GetFreq(kCLOCK_MainClk);
        break;
    case CLK_NODE_MAIN_CLK_PRE_PLL:
        rate = lpc845_get_main_clk_pre_pll(node);
        break;
    case CLK_NODE_FRO:
        rate = lpc845_get_fro_clk(node);
        break;
    case CLK_NODE_FRO_OSC:
        rate = CLOCK_GetFreq(kCLOCK_Fro);
        break;
    case CLK_NODE_SYSTEM:
        rate = CLOCK_GetFreq(kCLOCK_CoreSysClk);
        break;
    case CLK_NODE_UART0:
    case CLK_NODE_UART1:
        rate = lpc845_get_uart_clk(node);
        break;
    default:
        break;
    }

    return rate;
}

static uint8_t lpc845_get_parent(struct clock_node * node)
{
    uint8_t parent;
    switch(node->id)
    {
    case CLK_NODE_MAIN_CLK:
        parent = SYSCON->MAINCLKPLLSEL & 0x03;
        break;
    case CLK_NODE_MAIN_CLK_PRE_PLL:
        parent = SYSCON->MAINCLKSEL & 0x03;
        break;
    case CLK_NODE_FRO:
        parent = (SYSCON->FROOSCCTRL & SYSCON_FROOSCCTRL_FRO_DIRECT_MASK)>>SYSCON_FROOSCCTRL_FRO_DIRECT_SHIFT;
        break;
    case CLK_NODE_SYSTEM:
        parent = 0;
        break;
    case CLK_NODE_UART0:
        parent = SYSCON->FCLKSEL[0] & 0x07;
        break;
    case CLK_NODE_UART1:
        parent = SYSCON->FCLKSEL[1] & 0x07;
        break;
    case CLK_NODE_CAPT:
        parent = SYSCON->CAPTCLKSEL & 0x07;
        break;        
    default:
        break;
    }
    
    return parent;
}

static clock_node_t fro_osc = 
{
    .name = "fro_osc",
    .rate = 0xffffffffu,
    .id = CLK_NODE_FRO_OSC,
    .parents_num = 0,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = NULL,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = NULL,    
};



static clock_node_t fro = 
{
    .name = "fro",
    .rate = 0xffffffffu,
    .id = CLK_NODE_FRO,
    .parents_num = 2,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0:fro_oscout is divided2 1:FRO oscillator",
    .parents[0] = NULL,
    .parents[1] = &fro_osc,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,    
};


static clock_node_t main_clk_pre_pll = 
{
    .name = "main_clk_pre_pll",
    .rate = 0xffffffffu,
    .id = CLK_NODE_MAIN_CLK_PRE_PLL,
    .parents_num = 4,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0-FRO 1- External clock 2- Watchdog oscillator 3- FRO_DIV = FRO / 2",
    .parents[0] = &fro,
    .parents[1] = NULL,
    .parents[2] = NULL,
    .parents[3] = NULL,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};

static clock_node_t  main_clk =
{
    .name = "main_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_MAIN_CLK,
    .parents_num = 2,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0-main_clk_pre_pll 1-SYS PLL 2/3-none",
    .parents[0] = &main_clk_pre_pll,
    .parents[1] = NULL,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};

static clock_node_t  system_clk =
{
    .name = "system_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_SYSTEM,
    .parents_num = 1,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = NULL,
    .parents[0] = &main_clk,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};


static clock_node_t  uart0_clk =
{
    .name = "uart0_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_UART0,
    .parents_num = 5,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0-FRO 1-Main clock 2-FRG0 clock 3-FRG1 clock 4-FRO_DIV = FRO / 2 5~7-none",
    .parents[0] = &fro,
    .parents[1] = &main_clk,
    .parents[2] = &fro,
    .parents[3] = NULL,
    .parents[4] = NULL,
    .parents[5] = NULL,
    .parents[6] = NULL,
    .parents[7] = NULL,
    .get_rate = lpc845_get_uart_clk,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};

static clock_node_t  uart1_clk =
{
    .name = "uart1_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_UART1,
    .parents_num = 5,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0-FRO 1-Main clock 2-FRG0 clock 3-FRG1 clock 4-FRO_DIV = FRO / 2 5~7-none",
    .parents[0] = &fro,
    .parents[1] = &main_clk,
    .parents[2] = &fro,
    .parents[3] = NULL,
    .parents[4] = NULL,
    .parents[5] = NULL,
    .parents[6] = NULL,
    .parents[7] = NULL,
    .get_rate = lpc845_get_uart_clk,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};

static clock_node_t  capt_clk =
{
    .name = "capt_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_CAPT,
    .parents_num = 5,
    .is_update = 0,
    .mux = 0xff,
    .muxhelp = "0-FRO 1-Main clock 2-SYS PLL 3-FRO_DIV = FRO/2 clock 4-Watchdog oscillator 5~7-none",
    .parents[0] = &fro,
    .parents[1] = &main_clk,
    .parents[2] = NULL,
    .parents[3] = NULL,
    .parents[4] = NULL,
    .parents[5] = NULL,
    .parents[6] = NULL,
    .parents[7] = NULL,
    .get_rate = lpc845_get_capt_clk,
    .set_rate = NULL,
    .get_parent = lpc845_get_parent,
};


void update_clk_node(struct clock_node * node)
{
    if(!node->is_update)
    {
        if(node->get_rate)
        {
            node->rate = node->get_rate(node);
        }
        if(node->get_parent)
        {
            node->mux = node->get_parent(node);
        }
        rt_list_init(&node->list);
        node->is_update = 1;
    }
}

void dump_clk_node(struct clock_node * node)
{
    if(node->is_update)
    {
        PRINTF(".name = %s\r\n",node->name);
        PRINTF(".rate = %d\r\n",node->rate);
        PRINTF(".id = %d\r\n",node->id);
        PRINTF(".parents_num = %d\r\n",node->parents_num);
        if(node->parents_num != 0xff && node->parents_num != 0)
            PRINTF("%s parent id is %d\r\n",node->muxhelp,node->mux);
    }
    else
    {
        PRINTF("%s node need update info.\r\n",node->name);
    }
}

void trace_clk_node(struct clock_node * node)
{
    rt_list_t head = RT_LIST_OBJECT_INIT(head);
    rt_list_t * pos;
    struct clock_node * p_node = node;
    uint8_t i_loop = 0;

    const char * root_clk[10] = {
        "|-- ",
        "|   |-- ",
        "|   |   |-- ",
        "|   |   |   |-- ",
        "|   |   |   |   |-- ",
        "|   |   |   |   |   |-- ",
        "|   |   |   |   |   |   |-- ",
        "|   |   |   |   |   |   |   |-- ",
        "|   |   |   |   |   |   |   |   |-- ",
        "|   |   |   |   |   |   |   |   |   |-- ",
    };
    
    
    do
    {
        update_clk_node(p_node);
        rt_list_insert_after(&head,&p_node->list);
        if(p_node->parents_num)
            p_node = p_node->parents[p_node->mux];
    }while(p_node && p_node->parents_num);

    if(p_node)
    {
        update_clk_node(p_node);
        rt_list_insert_after(&head,&p_node->list);
    }
    
    PRINTF("\r\n\r\n");

    rt_list_for_each(pos,&head)
    {
        p_node = rt_list_entry(pos, clock_node_t, list);
        PRINTF("%s *%s\r\n",root_clk[i_loop],p_node->name);
        PRINTF("%s [rate]%d\r\n",root_clk[i_loop+1],p_node->rate);
        if(p_node->muxhelp)
            PRINTF("%s [%s]:[%d]\r\n",root_clk[i_loop+1],p_node->muxhelp,p_node->mux);  
        i_loop++;
    }
}

unsigned int clkdump(char argc,char ** argv)
{
    uint8_t index = atoi(argv[1]);

    switch(index)
    {
    case 0:
        dump_clk_node(&main_clk);
        update_clk_node(&main_clk);
        dump_clk_node(&main_clk);
        break;
    case 1:
        dump_clk_node(&main_clk_pre_pll);
        update_clk_node(&main_clk_pre_pll);
        dump_clk_node(&main_clk_pre_pll);
        break;
    case 2:
        dump_clk_node(&fro);
        update_clk_node(&fro);
        dump_clk_node(&fro);
        break;
    case 3:
        dump_clk_node(&fro_osc);
        update_clk_node(&fro_osc);
        dump_clk_node(&fro_osc);
        break;
    case 4:
        trace_clk_node(&system_clk);
        break;    
    case 5:
        trace_clk_node(&uart0_clk);
        break;
    case 6:
        trace_clk_node(&uart1_clk);
        break; 
    case 7:
        trace_clk_node(&capt_clk);
        break;    
    default:
        break;
    }
    return 1;
}
LTSH_FUNCTION_EXPORT(clkdump,"dump clk info");


