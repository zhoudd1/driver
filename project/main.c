#include <stdio.h>
#include "../bsp/soc/device.h"
#include "../bsp/soc/soc_config.h"
#include "../bsp/driver/wdt/wdt.h"
#include "../bsp/driver/clk/clk.h"
#include "../bsp/driver/test/test.h"

int main()
{
    //device driver framework test!
    init_all_devices();

    //device struct test!
    struct td_device *test_device =(struct td_device *)&pf_device_test;
    printf("test device(%d) ok!\r\n",test_device->id);

    //driver struct test!
    struct driver *test_driver = (struct driver *)test_device->driver;
    printf("test init %d!\n",test_driver->init(test_device));

    //driver data test!
    struct test_data *data = (struct test_data *)test_device->priv;

    //driver api test!
    struct test_driver_api *b = data->driver_api;
    b->open(test_device);

    //driver api data test!
    int *d = (int*)data->driver_data;

    return 0;
}
