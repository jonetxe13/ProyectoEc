/*-------------------------------------
rutinasAtencion.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO;
int PERSONAJE;
int ATAQUES;
int seg3;
int HP1 = vida;
int HP2 = vida;

void RutAtencionTeclado ()
{
if (ESTADO == SELECCION)
{		
	if(TeclaPulsada() == A){
		ESTADO = PELEA;
	}
}
else if (ESTADO == PELEA)
{
	if(TeclaPulsada() == A){
		HP2 -= 5;
	}
	else if(TeclaPulsada() == B){
		HP2 -= 20;
	}
	if(HP1 <= 0 || HP2 <= 0){
		ESTADO == FIN;
	}
}
else if(ESTADO == FIN){

			if(TeclaPulsada()==A){
				ESTADO = SELECCION;
			}
			//Pulsa B para finalizar 
			else if(TeclaPulsada()==B){
				ESTADO = INICIO;
			}
}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	

if (ESTADO!=INICIO)
{
	tick++; 
	if (tick==5)
	{
		seg++;
		tick=0;
		if (ESTADO == PELEA)
		{
			seg3++;
			iprintf("\x1b[6;5HSegundos=%d", seg3);
			if (seg3==10)
			{
				visualizarPuerta();
				seg3=0;
				ESTADO=FIN;
				BorrarRombo(1, 5, 5);
				BorrarRomboGrande(2, 100, 100);
			}
		}
				
	}
}
	
}

void EstablecerVectorInt()
{
// A COMPLETAR
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

