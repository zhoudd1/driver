#ifndef _WDT_H_
#define _WDT_H_

#include <stdint.h>

extern struct driver watchdog_driver;

struct wdt_pm_data
{
    uint32_t a;
    uint32_t b;
};

#endif /* INTEL_QRK_WDT_H_ */
