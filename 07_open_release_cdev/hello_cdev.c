#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>

static int major;

int my_open(struct inode* inode_p, struct file* file_p) {
  pr_info("hello cdev - Major: %d, Minor: %d\n", imajor(inode_p),
          iminor(inode_p));
  pr_info("hello cdev - file_p->f_pos: %lld\n", file_p->f_pos);
  pr_info("hello cdev - file_p->f_mode: 0x%x\n", file_p->f_mode);
  pr_info("hello cdev - file_p->f_flags: 0x%x\n", file_p->f_flags);
  return 0;
}

int my_release(struct inode* inode_p, struct file* file_p) {
  pr_info("hello cdev - File is closed\n");
  return 0;
}

static struct file_operations fops = {
    .open = my_open,
    .release = my_release,
};

static int __init my_init(void) {
  major = register_chrdev(0, "hello_cdev", &fops);
  if (major < 0) {
    pr_err("hello_cdev - Error registering chrdev\n");
  }
  pr_info("hello_cdev - Major Device Number: %d\n", major);
  return 0;
}

static void __exit my_exit(void) { unregister_chrdev(major, "hello_cdev"); }

module_init(my_init);
module_exit(my_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hoang Xuan Viet <hxv1305@gmail.com>");
MODULE_DESCRIPTION("A sample driver for open and release a character device");