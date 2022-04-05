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
int seg3;

void RutAtencionTeclado ()
{
//if (ESTADO == CERRADA)
//{	
	if (TeclaPulsada()==A)
	{
		iprintf("\x1b[2;5HPrueba de escritura%d", TECLAS_DAT);						
		ESTADO=ABIERTA;
		visualizarPuertaAbierta();
		seg3=0;
		MostrarRombo(1, 5, 5);
		MostrarRomboGrande(2, 100, 100);
	}
//}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	

if (ESTADO!=ESPERA)
{
	tick++; 
	if (tick==5)
	{
		seg++;
		iprintf("\x1b[13;5HSegundos que han pasado=%d", seg);
		tick=0;
		if (ESTADO == ABIERTA)
		{
			seg3++;
			if (seg3==3)
			{
				visualizarPuerta();
				seg3=0;
				ESTADO=CERRADA;
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
	
}

