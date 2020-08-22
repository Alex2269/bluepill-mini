#include "main.h"
#include "PhotonPWM.h"

void delay(volatile uint32_t x)
{
	// while(x>0)
	// {x--;}
	for(uint32_t i=0;i<x;i++){}
}

void gpioc_ini()
{
	RCC->APB2ENR|=RCC_APB2ENR_IOPCEN;
	GPIOC->CRH&=~GPIO_CRH_CNF13;
	GPIOC->CRH|=GPIO_CRH_MODE13; // 50MHz
	// GPIOC->ODR=0;//GPIO_ODR_ODR13;	
}

void led_off()
{
  GPIOC->BSRR = GPIO_BSRR_BS13;
}

void led_on()
{
  GPIOC->BSRR = GPIO_BSRR_BR13;
}

void led_toggle()
{
  GPIOC->ODR ^= GPIO_ODR_ODR13;
}

int main()
{
  rcc_ini();
  gpioc_ini();
  led_off();

  while(1)
  {
    led_off();
    delay(1500000);
    led_on();
    delay(30000);
  }
  return 0;
}

