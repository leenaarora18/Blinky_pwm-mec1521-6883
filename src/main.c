/*
 * Copyright (c) 2016 Intel Corporation
 * Copyright (c) 2020 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file Sample app to demonstrate PWM.
 */



#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>

/* Define PWM specifications for the LED */
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));

#define MIN_PERIOD PWM_MSEC(1)
#define MAX_PERIOD PWM_SEC(1U)

void main(void) {
    printk("PWM LED Control Example\n");

    if (!pwm_is_ready_dt(&pwm_led0)) {
        printk("Error: PWM device is not ready\n");
        return;
    }

    uint32_t period = MAX_PERIOD;
    uint8_t dir = 0; /* Direction of change: 0 = decrease, 1 = increase */

    while (1) {
        /* Set PWM for the LED */
        pwm_set_dt(&pwm_led0, period, period / 2);
        printk("PWM Period: %u\n", period);

        /* Adjust period */
        if (dir) {
            period *= 2;
            if (period > MAX_PERIOD) {
                period = MAX_PERIOD / 2;
                dir = 0;
            }
        } else {
            period /= 2;
            if (period < MIN_PERIOD) {
                period = MIN_PERIOD * 2;
                dir = 1;
            }
        }

        k_sleep(K_MSEC(500)); /* Adjust delay as needed */
    }
}
