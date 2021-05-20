/*
 * @Author: your name
 * @Date: 2021-04-08 22:19:34
 * @LastEditTime: 2021-04-11 12:17:58
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \junior-lessons_second-term\EmbeddedSystem\Experiment\实验1-跑马灯\闪烁顺序判断.c
 */
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"

// led灯左移,右边灯亮,然后右边灯灭的时候左边灯亮,循环次数由入口参数决定
void led_left(int x)        // x->循环次数
{
    while (x)                // 控制循环体执行次数为x
    {
        LED1 = 0;            //  右边灯亮
        LED0 = 1;            // 左边灯灭
        delay_ms(300);        // 延时300ms
        LED0 = 0;            // 左边灯亮
        LED1 = 1;            // 右边灯灭
        delay_ms(300);        // 延时300ms
        LED0 = LED1 = 1;    // 左右灯灭
        delay_ms(300);        // 延时300ms
        x -= 1;                // 循环次数-1
    }
}

// 与上面的反过来即可,led右移
void led_right(int x)
{
    while (x)
    {
        LED0 = 0;
        LED1 = 1;
        delay_ms(300);
        LED0 = 1;
        LED1 = 0;
        delay_ms(300);
        LED0 = LED1 = 1;
        delay_ms(300);
        x -= 1;
    }
}

/**
 *  led闪烁(和原始代码的表现形式一致) *
 * 先判断左灯使能及闪烁次数并执行,再判断右灯使能及闪烁次数再执行 *
 **/ 
void led_blink(int left_en, int left_times, int right_en, int right_times)
{
    if(left_en){
        while(left_times){
            LED0 = 0;
            delay_ms(300);
            LED0 = 1;
            left_times -= 1;
        }
        LED0 = 1;
    }
    
    if(right_en){
        while (right_times)
        {
            LED1 = 0;
            delay_ms(300);
            LED1 = 1;
            delay_ms(300);
            right_times -= 1;
        }
        LED1 = 1;
    }

}

// 0-3的数值的显示
void led_gcd(int x){
    if (x == 0) LED0 = LED1 = 0;
    else if (x == 1) LED0 = 0, LED1 = 1;
    else if (x == 2) LED0 = 1, LED1 = 0;
    else LED0 = LED1 = 1;
}



int main(void)
{ 
 
    delay_init(168);              // 初始化延时参数
    LED_Init();                    // 初始化LED端口
    
    led_left(3);

    led_right(3);
    
    led_blink(1,2,1,3);            // 左2右3
    
    led_gcd(0);
    delay_ms(1000);
    
    led_gcd(1);
    delay_ms(1000);
    
    led_gcd(2);
    delay_ms(1000);
    
    led_gcd(3);
    delay_ms(1000);
    
    while (1); 
}




