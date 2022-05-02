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
		vida2 -= 5;
		iprintf("\x1b[1;1HLa vida2 es:%d",vida2);
	}
	else if(TeclaPulsada() == B){
		vida2 -= 20;
		iprintf("\x1b[1;1HLa vida2 es:%d",vida2);
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
		//iprintf("\x1b[16;5HSegundos que han pasado=%d", seg);
		tick=0;
		if (ESTADO == SELECCION)
		{
			seg3++;
			if (seg3==3)
			{
				visualizarPuerta();
				seg3=0;
				ESTADO=PELEA;
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

