#include "fsl_device_registers.h"
#include "littleshell.h"
#include "fsl_clock.h"
#include "fsl_debug_console.h"
#include "fsl_syscon.h"

enum clock_node_id
{
    CLK_NODE_MAIN_CLK = 0,
    CLK_NODE_MAX
};


typedef struct clock_node
{
    const char * name;
    uint32_t rate;
    enum clock_node_id id;
    uint8_t is_update;
    uint8_t parents_num;
    uint8_t mux;
    struct clock_node * parents[6];
    /*clock node ops*/
    uint32_t (*get_rate)(struct clock_node * node);
    int (*set_rate)(struct clock_node * node,uint32_t rate);
    uint8_t (*get_parent)(struct clock_node * node);
}clock_node_t;

uint32_t lpc845_get_clock_rate(struct clock_node * node)
{
    struct clk_id_table
    {
        clock_name_t table[CLK_NODE_MAX];
    };

    const struct clk_id_table id_table = 
    {
        .table[CLK_NODE_MAIN_CLK] = kCLOCK_MainClk,
    };

    return CLOCK_GetFreq(id_table.table[node->id]);
}


static clock_node_t  main_clk =
{
    .name = "main_clk",
    .rate = 0xffffffffu,
    .id = CLK_NODE_MAIN_CLK,
    .parents_num = 2,
    .is_update = 0,
    .mux = 0xff,
    .parents[0] = NULL,
    .parents[1] = NULL,
    .get_rate = lpc845_get_clock_rate,
    .set_rate = NULL,
    .get_parent = NULL,
};

void update_clk_node(struct clock_node * node)
{
    if(!node->is_update)
    {
        if(node->get_rate)
        {
            node->rate = node->get_rate(node);
        }
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
    }
    else
    {
        PRINTF("%s node need update info.\r\n",node->name);
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
    default:
        break;
    }
    return 1;
}
LTSH_FUNCTION_EXPORT(clkdump,"dump clk info");


