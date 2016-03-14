    //************************************//
   /* Práctica 3---EntradaSalida		 */
  /*  Francisco Jesús Gimenez Hidalgo   */
 /*   Daniel Villalobos del Baño       */
//************************************//

#include <lpc17xx.h>

/*DECLARACIÓN DE LAS VARIABLES*/
int valorBCD;																				//Valor del número codificado en BCD
int valorBIN;																				//Valor del número codificado en BINARIO
int esPrimerNoCero = 0;

/*DEFINICIÓN DE LAS CONSTANTES*/
#define NUM_MAX 65535


/***********/
/*FUNCIONES*/
/***********/

/*FUNCIÓN QUE CONTROLA EL DELAY*/
void delay(uint32_t n){															//Introducimos direcctamente el valor de los ms de retraso
  int32_t i;
  n*=20000;
  for(i=0;i<n;i++);
}

int getBinToBCD(int n){
  int i, resultado = 0;
  for(i=1;i<=8;i++){
    resultado<<=4;
    resultado|=(n%10);
    n/=10;
  }
  return resultado;
}

/*CONFIGURACIÓN DE PUERTOS*/
void configurarPuertos(){
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

/*PONEMOS TODOS LOS PINES A 0*/
void limpiarPuertos(){
  LPC_GPIO0->FIOCLR = 0xffffffff;
  LPC_GPIO1->FIOCLR = 0xffffffff;
  LPC_GPIO2->FIOCLR = 0xffffffff;
  LPC_GPIO3->FIOCLR = 0xffffffff;
  LPC_GPIO4->FIOCLR = 0xffffffff;
}

/*EVALÚA SI ES PRIMO O NO*/
int getEsPrimo(int n){
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
}

/*MOSTRAMOS EL NÚMERO EN EL DISPLAY */
void setDisplayLooser(int n){
//Pues aquí va el muestreo del display de 7-seg//Es necesario ver los segmentos que se encienden para cada numero//
//Pines: a(P0.18) b(p0.17) c(p0.15) d(p0.16) e(p0.9) f(p0.8) g(p0.7)//
  LPC_GPIO0->FIOSET = 0x00078380;
	delay(50);
  //pos++;  Falta la parte donde se va dividiendo los números en partes que hice
  switch (n){
    case 0:
    //El 0//a + b + c + d + e + f
    LPC_GPIO0->FIOCLR = 0x00078300;
    break;

    case 1:
    //El 1//b + c//
    LPC_GPIO0->FIOCLR = 0x00028000;
    break;

    case 2:
    //El 2//a + b + d + e +g//
    LPC_GPIO0->FIOCLR = 0x00070280;
    break;

    case 3:
    //El 3 //a + b + c + d + g/
    LPC_GPIO0->FIOCLR = 0x00078080;
    break;

    case 4:
    //El 4//b + c + f + g//
    LPC_GPIO0->FIOCLR = 0x00028180;
    break;

    case 5:
    //El 5//a + c + d + f + g//
    LPC_GPIO0->FIOCLR = 0x00058180;
    break;

    case 6:
    //El 6//a + c + d + e + f + g
    LPC_GPIO0->FIOCLR = 0x00058380;
    break;

    case 7:
    //El 7//a + b + c//
    LPC_GPIO0->FIOCLR = 0x00068000;
    break;

    case 8:
    //El 8//a + b + c + d + e + f + g//
    LPC_GPIO0->FIOCLR = 0x00078380;
    break;

    case 9:
    //El 9//a + b + c + d + f + g//
    LPC_GPIO0->FIOCLR = 0x00078180;
    break;
  }
}


/*OBTENCIÓN DEL VALOR INICIAL*/
int getValorInicial(){
  int valorInicial = 0;
  //El primer pin corresponde con 1
  valorInicial = !(((LPC_GPIO1->FIOPIN>>31) & 0x01));
  //El segundo con 2 y así sucesivamente en potencias de 2, por lo que iremos multiplicando por 2 sucesivamente
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>26) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>25) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>24) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>23) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>28) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>27) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>26) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>25) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>24) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>23) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>22) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>21) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>20) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>19) & 0x01));
  valorInicial = (valorInicial<<1) + !((LPC_GPIO3->FIOPIN>>26) & 0x01);

	if(!valorInicial)
		valorInicial = 1;
  //Devolvemos el valor inicial introducido
  return valorInicial;
}

/*MOSTRAR VALORES BINARIOS*/
void setNumeroBinario(int n){
  int estado;
  estado = n&0x01;
  LPC_GPIO1->FIOPIN |= (estado<<0);
  estado = ((n&0x02)>>1);
  LPC_GPIO1->FIOPIN |= (estado<<1);
  estado = ((n&0x04)>>2);
  LPC_GPIO1->FIOPIN |= (estado<<4);
  estado = ((n&0x08)>>3);
  LPC_GPIO1->FIOPIN |= (estado<<8);
  estado = ((n&0x010)>>4);
  LPC_GPIO1->FIOPIN |= (estado<<9);
  estado = ((n&0x020)>>5);
  LPC_GPIO1->FIOPIN |= (estado<<10);
  estado = ((n&0x040)>>6);
  LPC_GPIO1->FIOPIN |= (estado<<14);
  estado = ((n&0x080)>>7);
  LPC_GPIO0->FIOPIN |= (estado<<2);
  estado = ((n&0x0100)>>8);
  LPC_GPIO1->FIOPIN |= (estado<<16);
  estado = ((n&0x0200)>>9);
  LPC_GPIO1->FIOPIN |= (estado<<17);
  estado = ((n&0x0400)>>10);
  LPC_GPIO4->FIOPIN |= (estado<<29);
  estado = ((n&0x0800)>>11);
  LPC_GPIO4->FIOPIN |= (estado<<28);
  estado = ((n&0x01000)>>12);
  LPC_GPIO2->FIOPIN |= (estado<<6);
  estado = ((n&0x02000)>>13);
  LPC_GPIO2->FIOPIN |= (estado<<7);
  estado = ((n&0x04000)>>14);
  LPC_GPIO2->FIOPIN |= (estado<<8);
  estado = ((n&0x08000)>>15);
  LPC_GPIO0->FIOPIN |= (estado<<19);
}

/*MUESTRA EL NÚMERO BCD A TRAVÉS DE LOS LEDS*/
void setNumeroBCD(int n){
  //int resultado = 0;
  //int i=0;
  int estado = 0;

  //Convierto el número a BCD
  n = getBinToBCD(n);

  //Muestro n (ya en formato BCD en los LEDs)
  estado = ((n&0x010000000)>>28);
  LPC_GPIO1->FIOPIN |= (estado<<0);
  estado = ((n&0x020000000)>>29);
  LPC_GPIO1->FIOPIN |= (estado<<1);
  estado = ((n&0x040000000)>>30);
  LPC_GPIO1->FIOPIN |= (estado<<4);
  estado = ((n&0x080000000)>>31);
  LPC_GPIO1->FIOPIN |= (estado<<8);
  estado = ((n&0x01000000)>>24);
  LPC_GPIO1->FIOPIN |= (estado<<9);
  estado = ((n&0x02000000)>>25);
  LPC_GPIO1->FIOPIN |= (estado<<10);
  estado = ((n&0x04000000)>>26);
  LPC_GPIO1->FIOPIN |= (estado<<14);
  estado = ((n&0x08000000)>>27);
  LPC_GPIO0->FIOPIN |= (estado<<2);
  estado = ((n&0x0100000)>>20);
  LPC_GPIO1->FIOPIN |= (estado<<16);
  estado = ((n&0x0200000)>>21);
  LPC_GPIO1->FIOPIN |= (estado<<17);
  estado = ((n&0x0400000)>>22);
  LPC_GPIO4->FIOPIN |= (estado<<29);
  estado = ((n&0x0800000)>>23);
  LPC_GPIO4->FIOPIN |= (estado<<28);
  estado = ((n&0x010000)>>16);
  LPC_GPIO2->FIOPIN |= (estado<<6);
  estado = ((n&0x020000)>>17);
  LPC_GPIO2->FIOPIN |= (estado<<7);
  estado = ((n&0x040000)>>18);
  LPC_GPIO2->FIOPIN |= (estado<<8);
  estado = ((n&0x080000)>>19);
  LPC_GPIO0->FIOPIN |= (estado<<19);
  estado = ((n&0x01000)>>12);
  LPC_GPIO0->FIOPIN |= (estado<<20);
  estado = ((n&0x02000)>>13);
  LPC_GPIO0->FIOPIN |= (estado<<21);
  estado = ((n&0x04000)>>14);
  LPC_GPIO0->FIOPIN |= (estado<<22);
}

/*FUNCIÓN PRINCIPAL*/
int main(){
  int i = 0, valor = 0, ledTonto, ledEncendido, pos = 0, numeroDisplay = 0;
  int32_t tiempoTranscurrido;
				int test = 0;

  //Llamadas a funciones de inicialización
  configurarPuertos();
  limpiarPuertos();

  while(1){

    valor = getValorInicial();															//Leo valor inicial y lo guardo
    for(i=valor;i<=NUM_MAX;i++){														//Incrementamos el número desde el valor inicial al máximo

      while(!getEsPrimo(i) && i<=NUM_MAX)
      i++;

      if(i>NUM_MAX)
      break;

      if((LPC_GPIO2->FIOPIN>>10 & 0x01)){									//Si pulsamos SW2 Binario, si no BCD
        setNumeroBinario(i);
      }
      else{
        setNumeroBCD(i);
      }

      ledEncendido = 0;
      ledTonto = i;

      for(tiempoTranscurrido=0;tiempoTranscurrido<6000000;tiempoTranscurrido++){
        if(tiempoTranscurrido%375000 == 0){
					test++;
					
          if(ledEncendido == 0){
            LPC_GPIO1->FIOPIN |= (1<<18);  //Encendemos LED
            ledEncendido = 1;
          }
          else{
            LPC_GPIO1->FIOPIN &= ~(1<<18);  //Apagamos LED
            ledEncendido = 0;
          }

          if(ledTonto & 0x01)
            LPC_GPIO1->FIOPIN |= (1<<29);  //Encendemos LED
          else
            LPC_GPIO1->FIOPIN &= ~(1<<29);  //Encendemos LED

          ledTonto>>=1;
        }
        if(tiempoTranscurrido%1200000 == 0){
					numeroDisplay = getBinToBCD(i);
					setDisplayLooser((numeroDisplay>>(pos+12)) & 0x0F);
					pos+=4;
        }
      }
			LPC_GPIO0->FIOSET = 0x00078380;
			delay(500);
			pos = 0;
      limpiarPuertos();
    }
    limpiarPuertos();
  }
}
