#include <stdio.h>
#include "../bsp/soc/device.h"
#include "../bsp/soc/soc_config.h"
#include "../bsp/driver/wdt/wdt.h"
#include "../bsp/driver/clk/clk.h"
#include "../bsp/driver/test/test.h"

int main()
{
    //driver framework test!
    init_all_devices();

    //driver struct test!
    struct td_device *test_device =(struct td_device *)&pf_device_test;
    printf("\r\n===test device(%d) ok!===\r\n",test_device->id);

    //driver api test!
    struct driver *test_driver = (struct driver *)test_device->driver;
    if(test_driver->init(test_device)==0)  printf("test init ok!\n");

    struct test_data *data = (struct test_data *)test_device->priv;

    struct test_driver_api *b = data->driver_api;
    b->open(test_device);


    return 0;
}
