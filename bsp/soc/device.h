#ifndef __DEVICE_H_
#define __DEVICE_H_

#include <stdint.h>

typedef enum
{
    PM_NOT_INIT = 0,
    PM_SHUTDOWN,
    PM_SUSPENDED,
    PM_RUNNING,
    PM_COUNT
} PM_POWERSTATE;

struct td_device;
struct driver;

//struct __packed __aligned(4) td_device
struct td_device
{
    void *priv;
    struct driver *driver;
    PM_POWERSTATE powerstate : 8;
    uint8_t id;
};

struct driver
{
    int (*init)(struct td_device *dev);
    int (*suspend)(struct td_device *dev, PM_POWERSTATE state);
    int (*resume)(struct td_device *dev);
};

int suspend_devices(PM_POWERSTATE state);
void resume_devices(void);
void init_devices(struct td_device **all_devices, uint32_t all_devices_count);
void init_all_devices(void);

#endif
