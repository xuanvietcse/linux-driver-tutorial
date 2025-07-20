#include <linux/gpio/consumer.h>
#include <linux/init.h>
#include <linux/module.h>

static struct gpio_desc *led, *button;

#define IO_LED (21)
#define IO_BUTTON (22)
#define IO_OFFSET (512)

static int __init my_init(void) {
  int status;

  led = gpio_to_desc(IO_LED + IO_OFFSET);
  if (!led) {
    printk("gpioctrl - Error getting pin %d\n", IO_LED);
    return -ENODEV;
  }

  button = gpio_to_desc(IO_BUTTON + IO_OFFSET);
  if (!button) {
    printk("gpioctrl - Error getting pin %d\n", IO_BUTTON);
    return -ENODEV;
  }

  status = gpiod_direction_output(led, 0);
  if (status)  // Not 0
  {
    printk("gpioctrl - Error setting pin %d to output\n", IO_LED);
    return status;
  }

  status = gpiod_direction_input(button);
  if (status)  // Not 0
  {
    printk("gpioctrl - Error setting pin %d to input\n", IO_BUTTON);
    return status;
  }

  gpiod_set_value(led, 1);
  printk("gpioctrl - LED is ON\n");

  printk("gpioctrl - Button is %s pressed\n",
         gpiod_get_value(button) ? "" : "NOT");
  return 0;
}

static void __exit my_exit(void) {
  gpiod_set_value(led, 0);
  printk("gpioctrl - LED is OFF\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Xuan Viet <hxv1305@gmail.com>");
MODULE_DESCRIPTION("An example for using GPIOs without the device tree");