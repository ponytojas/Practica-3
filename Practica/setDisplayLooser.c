
/*MOSTRAMOS EL NÚMERO EN EL DISPLAY */
#include <lpc17xx.h>

//Pues aquí va el muestreo del display de 7-seg//
//Pines: a(P0.18) b(p0.17) c(p0.15) d(p0.16) e(p0.9) f(p0.8) g(p0.7)//

  LPC_GPIO0->FIOSET = 0x00078380; //Se pone a 1 el display (Es nivel bajo)
	delay(50); //Sin el retraso el display se vuelve loco y no muestra correctamente
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
