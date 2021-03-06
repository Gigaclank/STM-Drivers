/**
 * @file main.cpp
 * @author Aaron Lynn ()
 * @brief 
 * @version 0.1
 * @date 2018-12-09
 * 
 * @copyright Copyright (c) Aaron Lynn 2018
 * All Rights Reserved
 * 
 */
#include <stdio.h>
#include <iostream>
#include "api_system_startup.h"
#include "iwdg.h"

int main()
{
  
  api_system_start();
  STM_IWDG iwdg(2.0);
  iwdg.reset_source();
  while (1)
  {   
    iwdg.reload();
  }
}