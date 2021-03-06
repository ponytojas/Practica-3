//Elemento con la función que configura los puertos GPIO

/* void configurarPuertos(void) */

#include <lpc17xx.h>

//Todos los puertos en modo GPIO
LPC_PINCON->PINSEL0 = 0x00000000;
LPC_PINCON->PINSEL1 = 0x00000000;
LPC_PINCON->PINSEL2 = 0x00000000;
LPC_PINCON->PINSEL3 = 0x00000000;
LPC_PINCON->PINSEL4 = 0x00000000;

//Pines de ENTRADA y SALIDA
LPC_GPIO0->FIODIR |= 0xf87fffff;
LPC_GPIO1->FIODIR |= 0x6007ffff;
LPC_GPIO2->FIODIR |= 0xfffffbff;
LPC_GPIO3->FIODIR |= 0xfbffffff;
LPC_GPIO4->FIODIR |= 0xffffffff;
}
