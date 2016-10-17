//Función que convierte de binario a bcd

#include <lpc17xx.h>

int i, resultado = 0;
for(i=1;i<=8;i++){
  resultado<<=4;
  resultado|=(n%10);
  n/=10;
