/* 实现每隔一秒向内核log中打印一条信息 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>

static struct timer_list tm;
struct timeval oldtv;

void callback(struct timer_list * arg)
{
   
    
    printk(KERN_WARNING "flags: %d",arg->flags);
    printk(KERN_WARNING "call back");

    


    tm.expires = jiffies+5*HZ;    
    add_timer(&tm);        //重新开始计时
}

static int __init demo_init(void)
{
    //printk(KERN_EMERG,"%s : %s : %d - ok.\n", __FILE__, __func__, __LINE__);

    printk(KERN_WARNING "my second timer");
    timer_setup(&tm,callback,1);    //初始化内核定时器

  
    //do_gettimeofday(&oldtv);        //获取当前时间
    //tm.function= callback;            //指定定时时间到后的回调函数
    //tm.data    = (unsigned long)"hello world";        //回调函数的参数
    tm.expires = jiffies+5*HZ;        //定时时间
    add_timer(&tm);        //注册定时器
    printk(KERN_WARNING "zhu ce wan cheng");
    return 0;
}

static void __exit demo_exit(void)
{
    printk(KERN_WARNING "I quit");
    del_timer(&tm);        //注销定时器
}

module_init(demo_init);
module_exit(demo_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liuxuezhuo");
MODULE_DESCRIPTION("timerlist");