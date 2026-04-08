#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <pwm_z42.h>                // Biblioteca personalizada com funções de controle do TPM (Timer/PWM Module)

#define SLEEP_TIME_MS 1000

// Define o LED usando Device Tree
#define LED0_NODE DT_ALIAS(led0)

// Verifica se o LED está definido no Device Tree
#if DT_NODE_HAS_STATUS(LED0_NODE, okay)
static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
#else
#error "Unsupported board: led0 devicetree alias is not defined"
#endif



void main(void)
{
    int ret0;

    // Verifica se o device está pronto
    if (!gpio_is_ready_dt(&led0)) {
        printk("Error: LED device %s is not ready\n", led0.port->name);
        return;
    }
    
    // Configura o pino como saída
    ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    if (ret0 < 0) {
        printk("Error %d: failed to configure LED pin\n", ret0);
        return;
    }
    
    printk("LED blinking on %s pin %d\n", led0.port->name, led0.pin);
    
    while (1) {
            gpio_pin_set_dt(&led0, 1); // on green
            k_msleep(SLEEP_TIME_MS);
            gpio_pin_set_dt(&led0, 0); // off green
            k_msleep(SLEEP_TIME_MS);
    }
    
}
