//Función que evalua si el número es primo o no

#include <lpc17xx.h>

int i, esPrimo = 1;
for (i=2;i<=n/2;i++){
  if (i%2==0 && i!=2)
  i++;
  if(n%i == 0){
    esPrimo = 0;
    break;
  }
}
return esPrimo;
