#include<linux/module.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/slab.h>

static char buffer[PAGE_SIZE];
struct cdev *my_cdev;
dev_t my_dev;
char devname[] = "zhaomingyin";

static int device_open(struct inode *inode,  struct file *file)
{
    /* This can be used to synchronization purpose to say if the device is already in use*/
    return 0;
}

static ssize_t device_write(struct file *file,  const char *buf, size_t lbuf,  loff_t *ppos)
{
    int nbytes = lbuf  - copy_from_user(buffer + *ppos, buf, lbuf);
    *ppos += nbytes;
    pr_info("Rec''vd data from app %s,  nbytes=%d\n", buffer, nbytes);
    return nbytes;

}

static ssize_t device_read(struct file *file, char *buf,  size_t lbuf,  loff_t *ppos)
{
    int nbytes;
    int maxbytes;
    int bytes_to_do;
    
    maxbytes = PAGE_SIZE - *ppos;

    if(maxbytes > lbuf)
        bytes_to_do = lbuf;
    else
        bytes_to_do = maxbytes;
 
    nbytes = bytes_to_do - copy_to_user(buf, buffer+ *ppos, bytes_to_do);
    *ppos += nbytes;
    pr_info("Data send to app %s,  nbytes=%d\n", buffer, nbytes);
    return nbytes;
}

static struct file_operations device_fops = {
    .owner = THIS_MODULE, 
    .write = device_write, 
    .read  = device_read, 
    .open  = device_open, 
};

static int __init driver_init_char(void)
{
    int status;
    my_dev = MKDEV(100, 0); /* Major and Minor Number */
    register_chrdev_region(my_dev, 1, devname);

    //alloc_chrdev_region(&my_dev,0,1,"chrdev"); // 

    my_cdev = cdev_alloc();
    cdev_init(my_cdev,  &device_fops);

    status = cdev_add(my_cdev, my_dev, 1);

    if(status <0)
    {
        pr_info("Driver init failed\n");
        return status;
    }

    memset(buffer, '\0', PAGE_SIZE);
    return 0;

}

static void __exit driver_exit_char(void)
{
    cdev_del(my_cdev);
    unregister_chrdev_region(my_dev, 1);
}

module_init(driver_init_char);
module_exit(driver_exit_char);

MODULE_AUTHOR("zhaomingyin");
MODULE_DESCRIPTION("Device to demonstrate read/write calls of char driver");
MODULE_LICENSE("GPLV3");
/*End of code */

