/**
 * @file api_system_startup.cpp
 * @author Aaron Lynn ()
 * @brief 
 * @version 0.1
 * @date 2018-12-09
 * 
 * @copyright Copyright (c) Aaron Lynn 2018
 * All Rights Reserved
 * 
 */

/**
 * @brief Start up STM32 with system tick and vector table
 * 
 */
#include "api_system_startup.h"
uint32_t u32_system_tick;
uint32_t u32_system_delay_tick;
void api_system_start(void)
{
    SystemInit();
    SystemCoreClockUpdate();

    api_system_init_tick();

    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x00);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); /* Configure the Priority Group to 2 bits */
}

/**
 * @brief Set up system tick to 1ms
 * 
 */
void api_system_init_tick(void)
{
    /* Code */
    NVIC_SetPriority(SysTick_IRQn, 0x0);  /* Configure the SysTick handler priority */
    SysTick->CTRL |= SysTick_CTRL_ENABLE; /* Enable the SysTick Counter */
    SysTick->VAL = (uint32_t)0x0;         /* Clear the SysTick Counter */

    if (SysTick_Config(SystemCoreClock / 1000))
    { /* Setup SysTick Timer for 1 msec interrupts  */
        while (1)
            ; /* Capture error */
    }

    return;
}
/**
 * @brief ms delay counter
 * 
 */
void api_system_cntr(void)
{
    if (u32_system_delay_tick)
        u32_system_delay_tick--;
//    u32_system_delay_tick++;
}

/**
 * @brief delay ms
 * 
 * @param count 
 */
void api_ms_delay(uint32_t count)
{
    u32_system_delay_tick = count;
    while (u32_system_delay_tick)
        ;
}

/**
 * @brief read the system tick counter
 * 
 * @return uint32_t 
 */
uint32_t api_system_tick_read(void)
{

    return u32_system_delay_tick;
}