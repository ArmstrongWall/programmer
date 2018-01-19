#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define BULKOUT_BUFFER_SIZE 512
char *bulkout_buffer;
struct usb_device *udev;
__u8 bulk_out_endaddr;

static struct usb_device_id dnw_id_table [] = {
        { USB_DEVICE(0x5345, 0x1234) },
            { }
};

static int dnw_open(struct inode* inode, struct file *file)
{
         bulkout_buffer = kmalloc(BULKOUT_BUFFER_SIZE,GFP_KERNEL);
              return 0;
}

static int dnw_release (struct inode* inode, struct file *file)
{
        kfree(bulkout_buffer);
            return 0;   
}

static ssize_t dnw_write(struct file *file, const char __user *buf, size_t len, loff_t *pos)
{
        size_t to_write;
            size_t total_write = 0;
                size_t act_len;
                    
                    while(len>0)    
                            {
                                        to_write = min(len,(size_t)BULKOUT_BUFFER_SIZE);
                                                    
                                            copy_from_user(bulkout_buffer,buf+total_write,to_write);
                                                
                                                usb_bulk_msg(udev,usb_sndbulkpipe(udev,bulk_out_endaddr),bulkout_buffer,to_write,&act_len,3*HZ);
                                                    
                                                    len -= to_write;
                                                        total_write += to_write;
                                                            }
                        
                        return total_write;
}

static struct file_operations dnw_ops =
{
        .owner =    THIS_MODULE,
            .write =    dnw_write,
                .open =     dnw_open,
                    .release =  dnw_release,
};

static struct usb_class_driver dnw_class = {
        .name =     "secbulk%d",
            .fops =     &dnw_ops,
                .minor_base =   100,
};


static int dnw_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
        /* 接口设置描述 */
        struct usb_host_interface *interface;
            struct usb_endpoint_descriptor *endpoint;   
                int i;
                    
                    interface = intf->cur_altsetting;
                        
                        
                        
                        for(i=0;i<interface->desc.bNumEndpoints;i++)
                                {
                                            endpoint = &interface->endpoint[i].desc;
                                                    if(usb_endpoint_is_bulk_out(endpoint))
                                                                {
                                                                                bulk_out_endaddr =  endpoint->bEndpointAddress;
                                                                                            break;
                                                                                                    }
                                                            
                                                        }
                            
                            usb_register_dev(intf,&dnw_class);
                                
                                udev = usb_get_dev(interface_to_usbdev(intf));
                                    
}

static void dnw_disconnect(struct usb_interface *intf)
{
        usb_deregister_dev(intf,&dnw_class);
}

struct usb_driver dnw_driver = {
        .name       = "dnw",   /* 驱动名 */
            .probe      = dnw_probe, /* 捕获函数 */
                .disconnect = dnw_disconnect, /* 卸载函数 */
                    .id_table   = dnw_id_table, /* 设备列表 */
};



int dnw_init(void)
{
        usb_register(&dnw_driver);
            return 0;   
}

void dnw_exit(void)
{
        usb_deregister(&dnw_driver);    
}


module_init(dnw_init);
module_exit(dnw_exit);
MODULE_LICENSE("GPL");
