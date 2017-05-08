#ifndef _TEST_H_
#define _TEST_H_

#include <stdint.h>

typedef void (*test_api_open)(struct td_device *dev);
typedef void (*test_api_close)(struct td_device *dev);

struct test_driver_api {
	test_api_open open;
	test_api_close close;
};

struct test_data
{
	void *driver_api;
	void *driver_data;
};

extern struct driver test_driver;

#endif
