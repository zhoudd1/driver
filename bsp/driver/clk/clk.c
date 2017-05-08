#include <stdio.h>
#include <stdlib.h>
#include "../../soc/soc_config.h"
#include "../../soc/device.h"
#include "../../driver/clk/clk.h"

int clk_init(struct td_device *dev)
{
    return 0;
}

static int clk_suspend(struct td_device *dev, PM_POWERSTATE state)
{
    return 0;
}

static int clk_resume(struct td_device *dev)
{
    return 0;
}

struct driver clk_driver =
{
    .init = clk_init,
    .suspend = clk_suspend,
    .resume = clk_resume
};
