void rcc_ini();

void rcc_ini()
{
    // RCC->CR|=RCC_CR_HSION;

    RCC->CFGR&=~RCC_CFGR_SW; // SW=00 - HSI selected as system clock
    RCC->CR&=~RCC_CR_PLLON;  // выключаем PLL чтобы можно было бы записывать в PLLCFGR
    RCC->CFGR=0; // обнуляем регистр настройки частоты
    RCC->CR|=RCC_CR_HSION; // включаем внутренний генератор
    RCC->CR&=~RCC_CR_HSION; // выключаем внутренний генератор
    RCC->CR|=RCC_CR_HSEON; // включение внешнего кварца
    while(!(RCC->CR&RCC_CR_HSERDY)){} // пока не появился флаг готовности HSE
    RCC->CFGR|=RCC_CFGR_HPRE_DIV1; // делим SYSCLK на единицу      (128MHz)
    RCC->CFGR|=RCC_CFGR_PPRE1_DIV4; // APB1 clk SYSCLK делим на 4  (32MHz)
    RCC->CFGR|=RCC_CFGR_PPRE2_DIV2; // APB2 clk SYSCLK делим на 2  (64MHz)

    RCC->CFGR|=RCC_CFGR_PLLMULL16; // 8MHz HSE * 16 = 128MHz SYSCLK
    
    RCC->CR|=RCC_CR_PLLON; // включаем тактирование с PLL
    while(!(RCC->CR&RCC_CR_PLLRDY)){} // пока не появится флаг включения PLL

    /* Enable Prefetch Buffer */
    FLASH->ACR |= FLASH_ACR_PRFTBE; // PRFTBE включает буфер превыборки команд  

    /* Flash 2 wait state */
    FLASH->ACR &=~FLASH_ACR_LATENCY; // обнуляем
    FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2; // 1:0 Для частоты 128 MHz следует ставить задержку в два такта 

    RCC->CFGR|=RCC_CFGR_SW_PLL;           // переключаемся с HSI на PLL
    while(!(RCC->CFGR&RCC_CFGR_SWS_PLL)){} // дождемся выставления бита готовности PLL
}
