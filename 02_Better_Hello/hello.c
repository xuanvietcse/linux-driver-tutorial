#include <linux/module.h>
#include <linux/init.h>

static int __init my_init(void)
{
  printk("Hello - Hello Kernel!\n");
  return 0;
}

static void __exit my_exit(void)
{
  printk("Goodbye - Goodbye Kernel!\n");
}

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Xuan Viet <hxv1305@gmail.com>");
MODULE_DESCRIPTION("A simple Hello World Linux Kernel Module");