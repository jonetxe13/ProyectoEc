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
int player = 0;

void RutAtencionTeclado (){

if (ESTADO == SELECCION){		
	if(TeclaPulsada() == A) ESTADO = PELEA;
}
else if (ESTADO == PELEA){	
	if(player == 0){
		if(TeclaPulsada() == A){
			HP2 -= 5;
			player = 1;
		}
		else if(TeclaPulsada() == B){
			HP2 -= 20;
			player = 1;
		}
	}
	else{
		int aleatorio = rand()%2;
		if(aleatorio == 0){
			HP1 -= 5;
			player = 0;
		}
		else if(aleatorio == 1){
			HP1 -= 20;
			player = 0;
		}
	}
}
else if(ESTADO == FIN){

			if(TeclaPulsada()==A) ESTADO = SELECCION;
			//Pulsa B para finalizar 
			else if(TeclaPulsada()==B) ESTADO = INICIO;
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
			iprintf("\x1b[9;5HSegundos=%d", seg3);
			if (seg3==100)
			{
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

