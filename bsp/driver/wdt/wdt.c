#include <stdio.h>
#include <stdlib.h>
#include "../../soc/soc_config.h"
#include "../../soc/device.h"
#include "../../driver/wdt/wdt.h"

int wdt_init(struct td_device *dev)
{
    return 0;
}

static int wdt_suspend(struct td_device *dev, PM_POWERSTATE state)
{
    return 0;
}

static int wdt_resume(struct td_device *dev)
{
    return 0;
}

struct driver watchdog_driver =
{
    .init = wdt_init,
    .suspend = wdt_suspend,
    .resume = wdt_resume
};
