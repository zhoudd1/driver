#include <stdio.h>
#include <stdlib.h>
#include "../../soc/soc_config.h"
#include "../../soc/device.h"
#include "../../driver/test/test.h"


static void test_open_cb(struct td_device *dev)
{
    printf("test dev open sucss !\r\n");
}

static void test_close_cb(struct td_device *dev)
{
}

struct test_driver_api test_funcs = {
	.open = test_open_cb,
	.close = test_close_cb,
};

int test_init(struct td_device *dev)
{
    struct test_data *data = (struct test_data *)dev->priv;
    data->driver_api= &test_funcs;
    return 0;
}

static int test_suspend(struct td_device *dev, PM_POWERSTATE state)
{
    return 0;
}

static int test_resume(struct td_device *dev)
{
    return 0;
}

struct driver test_driver =
{
    .init = test_init,
    .suspend = test_suspend,
    .resume = test_resume
};
