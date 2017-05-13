#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <errno.h>
#include "../soc/soc_config.h"
#include "../soc/device.h"
#include "../driver/wdt/wdt.h"
#include "../driver/clk/clk.h"
#include "../driver/test/test.h"

typedef enum
{
    WDT_ID = 0,
    CLK_ID=1,
    TEST_ID =2,
} DEVICE_ID;

struct td_device pf_device_wdt =
{
    .id = WDT_ID,
    .driver = &watchdog_driver,
    .priv = &(struct wdt_pm_data){
        .a = 1,
        .b =2,
    },
};

struct td_device pf_device_clk =
{
    .id = CLK_ID,
    .driver = &clk_driver,
    .priv = &(struct clk_data){
        .a=5,
        .b=6,
    },
};

struct td_device pf_device_test =
{
    .id = TEST_ID,
    .driver = &test_driver,
    .priv = &(struct test_data){
    },
};

static struct td_device *platform_devices[] =
{
    &pf_device_wdt,
    &pf_device_clk,
    &pf_device_test,
};

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
void init_all_devices(void)
{
    /* Init plateform devices and buses */
    init_devices(platform_devices, ARRAY_SIZE(platform_devices));

}
