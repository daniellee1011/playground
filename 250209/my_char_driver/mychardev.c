#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define DEVICE_NAME "mychardev"

static char device_buffer[1024];
static int major_number;

// Open function
static int my_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device opened\n");
    return 0;
}

// Read function
static ssize_t my_read(struct file *file, char __user *buffer, size_t len, loff_t *offset) {
    int bytes_read;

    // If offset is at or beyond the buffer size, return 0 (EOF)
    if (*offset >= sizeof(device_buffer)) {
        return 0;
    }

    // Calculate the number of bytes to read
    bytes_read = len < (sizeof(device_buffer) - *offset) ? len : (sizeof(device_buffer) - *offset);

    // Copy data to user space
    if (copy_to_user(buffer, device_buffer, bytes_read)) {
        return -EFAULT;
    }

    // Update file offset
    *offset += bytes_read;

    return bytes_read;
}

// Write function
static ssize_t my_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset) {
    int bytes_written = len < sizeof(device_buffer) ? len : sizeof(device_buffer);
    if (copy_from_user(device_buffer, buffer, bytes_written)) {
        return -EFAULT;
    }
    return bytes_written;
}

// Close function
static int my_close(struct inode *inode, struct file *file) {
    printk(KERN_INFO "Device closed\n");
    return 0;
}

// File operations
static struct file_operations fops = {
    .open = my_open,
    .read = my_read,
    .write = my_write,
    .release = my_close,
};

// Module initialization
static int __init my_driver_init(void) {
    major_number = register_chrdev(0, DEVICE_NAME, &fops);
    if (major_number < 0) {
        printk(KERN_ERR "Failed to register character devcie\n");
        return major_number;
    }
    printk(KERN_INFO "Character device registered with major number %d\n", major_number);
    return 0;
}

// Module cleanup
static void __exit my_driver_exit(void) {
    unregister_chrdev(major_number, DEVICE_NAME);
    printk(KERN_INFO "Character device unregistered\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);
MODULE_LICENSE("GPL");
