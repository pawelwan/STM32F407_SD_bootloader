#include "ustime.h"
#include <FreeRTOS.h>
#include "stm32f4xx.h"

/**
 * Get time count in microseconds.
 *
 * \note
 *   this function must be called at least
 *   once every 65ms to work correctly.
 *
 */
uint64_t get_us_time()
{
    static uint16_t t0;
    static uint64_t tickcount;

    vPortEnterCritical();

    int t = TIM7->CNT;
    if (t < t0)
        t += 0x10000;

    tickcount += t - t0;
    t0 = t;

    vPortExitCritical();

    return tickcount;
}


/**
 * Perform a microsecond delay
 *
 * \param  us  number of microseconds to wait.
 * \note   The actual delay will last between us and (us-1) microseconds.
 *         To wait _at_least_ 1 us, you should use delay_us(2).
 */
void delay_us(unsigned long us)
{
    uint16_t  t0 = TIM7->CNT;
    for (;;) {
        int  t = TIM7->CNT;
        if (t < t0)
            t += 0x10000;

        if (us < t - t0)
            return;

        us -= t - t0;
        t0  = t;
    }
}


/**
 * Perform a millisecond delay
 *
 * \param  ms  number of milliseconds to wait.
 */
void delay_ms(unsigned long ms)
{
    delay_us(ms * 1000);
}


/**
 * Set up TIM7 as a 16bit, microsecond-timer.
 *
 */
void init_us_timer()
{
    RCC_ClocksTypeDef RCC_Clocks;
    RCC_GetClocksFreq(&RCC_Clocks);

    RCC->APB1ENR |= RCC_APB1Periph_TIM7;
    TIM7->PSC = (RCC_Clocks.PCLK2_Frequency / 1000000) - 1;
    TIM7->ARR = 0xFFFF;
    TIM7->CR1 = TIM_CR1_CEN;
}
