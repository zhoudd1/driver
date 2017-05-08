#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include "../../bsp/soc/soc_config.h"
#include "../../bsp/soc/device.h"

static struct td_device **all_devices = NULL;
static uint32_t all_devices_count = 0;

void init_devices(struct td_device **_all_devices, uint32_t _all_devices_count)
{
    if (all_devices != NULL)
        /* Devices already init */
        return;

    /* Link array with root device */
    all_devices = _all_devices;
    all_devices_count = _all_devices_count;

    uint32_t i;
    int ret = 0;

    for (i = 0; i < all_devices_count; ++i)
    {
        struct td_device *dev = all_devices[i];

        if (dev->driver->init && (ret = dev->driver->init(dev)))
        {
            dev->powerstate = PM_NOT_INIT;
            printf("dev(%d) is not init",dev->id);
        }
        dev->powerstate = PM_RUNNING;
    }
}

static void resume_devices_from_index(uint32_t i)
{
    int ret = 0;
    struct td_device *dev = NULL;

    for (; i < all_devices_count; ++i)
    {
        dev = all_devices[i];

        printf("resume device %d", dev->id);
        if (dev->powerstate <= PM_SHUTDOWN)
        {
            ret = -EINVAL;
            goto err_resume_device;
        }

        if (dev->powerstate == PM_RUNNING)
            /* Device already running */
            continue;

        if (dev->driver->resume && (ret = dev->driver->resume(dev)))
            goto err_resume_device;

        /* Current device resumed */
        dev->powerstate = PM_RUNNING;
    }

    return;

err_resume_device:
    printf("failed to resume device %d (%d)", dev->id,ret);

}

void resume_devices(void)
{
    resume_devices_from_index(0);
}

int suspend_devices(PM_POWERSTATE state)
{
    int32_t i;
    int ret = 0;

    /* Use the reverse order used for init, i.e. we suspend bus devices first,
     * then buses, then top level devices */
    for (i = all_devices_count - 1; i >= 0; --i)
    {
        struct td_device *dev = all_devices[i];

        // device already suspended
        if (dev->powerstate <= state)
            continue;

        printf("suspend dev %d", dev->id);

        if (!dev->driver->suspend)
        {
            dev->powerstate = state;
            continue;
        }

        ret = dev->driver->suspend(dev, state);
        if (!ret)
        {
            dev->powerstate = state;
            continue;
        }

        break;
    }

    if (!ret)
        return 0;

    /* Suspend aborted, resume all devices starting from where we had
     * an issue */
    if (state > PM_SHUTDOWN)
        resume_devices_from_index(i + 1);

    return -1;
}
