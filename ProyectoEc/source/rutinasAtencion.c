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
if (ESTADO == INICIO)
{		
	if(TeclaPulsada()==ARRIBA){
		ESTADO=SELECCION;
		visualizarPuertaAbierta();
		seg3=0;
		MostrarRombo(1, 5, 5);
		MostrarRomboGrande(2, 100, 100);
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
		iprintf("\x1b[13;5HSegundos que han pasado=%d", seg);
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

