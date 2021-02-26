#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/module.h>
#include <linux/signal.h>
#include <asm/io.h>

#include <linux/timekeeping.h>
#include <linux/gpio.h>

#define BUTTON 25
#define LED_1 24
#define IRQ_NAME "button_irq_demo"
#define DEV_NAME "button_1"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Marco Ma");
MODULE_DESCRIPTION("irq demo ofr RTES lab");
MODULE_VERSION("0.2");

static short int button_irq = 0;
static ktime_t last_time;
static char on_off = 1;


irq_handler_t irq_handler (int irq, void *data)    {
    
    ktime_t this_time = ktime_get();
    if(this_time - last_time > 200000000){
        printk (KERN_ALERT "\nbutton pressed !\n");
	gpio_direction_output(LED_1, on_off);
	on_off ^= 0x01;
	last_time = this_time;
    }
    return (irq_handler_t) IRQ_HANDLED;
}

int init_module (){
    gpio_free(BUTTON);
    gpio_free(LED_1);
    if(gpio_request(BUTTON,"BUTTON") != 0) return -1;
    if(gpio_request(LED_1,"LED") != 0) return -1;

    last_time = ktime_get();
    if( (button_irq = gpio_to_irq(BUTTON)) < 0 )  return -1;
    printk (KERN_ALERT "\nbutton_isr loaded !\n");
    
    return request_irq (button_irq, (irq_handler_t) irq_handler, IRQF_TRIGGER_RISING, IRQ_NAME, (void *)(DEV_NAME));
}

void cleanup_module(void){
    printk (KERN_ALERT "\n1 button_isr unloaded !\n");
    free_irq(button_irq, DEV_NAME);
    gpio_free(BUTTON);
    gpio_free(LED_1);
}

