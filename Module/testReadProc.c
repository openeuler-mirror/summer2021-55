#include <linux/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <asm/irq.h>
#include <asm/io.h>

#define MSG_BUF_LEN     1024

static unsigned char msg_buf[MSG_BUF_LEN] = {0};
static unsigned int msg_len = 10;
// static DECLARE_WAIT_QUEUE_HEAD(proc_msg_waitq);

static ssize_t proc_msg_read(struct file *file, char __user *user_buf,
             size_t count, loff_t *ppos)
{
    
    static unsigned ret = 0;
    /* 如果 msg_len 为 0，则等待数据 */
//    wait_event_interruptible(proc_msg_waitq, msg_len);
    printk(KERN_ALERT "read method\n");

    copy_to_user(user_buf, msg_buf, msg_len);
    if (msg_len != 0){
        ret = msg_len;
        msg_len = 0;
        return ret;
    }
    
    return 0;
}

static ssize_t proc_msg_write(struct file *file, const char __user *user_buf,
             size_t count, loff_t *ppos)
{
    printk(KERN_ALERT "write message\n");
    if(copy_from_user(msg_buf, user_buf, count)) {
        return -EFAULT;
    }
    // msg_len = count;
//    wake_up_interruptible(&proc_msg_waitq);
    msg_len = 10;
    return count;
}

const struct file_operations proc_msg_operations = {
    .read =    proc_msg_read,
    .write = proc_msg_write,
};

static int proc_msg_init(void)
{
    /* 在 proc 下创建了 proc_msg */
    printk(KERN_ALERT "read and write message\n");
    proc_create("proc_msg", S_IRUSR, NULL, &proc_msg_operations);

    return 0;
}

static void proc_msg_exit(void)
{
    remove_proc_entry("proc_msg", NULL);
}

module_init(proc_msg_init);
module_exit(proc_msg_exit);
MODULE_LICENSE("GPL");