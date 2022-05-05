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
		if(TeclaPulsada() == A) {
			iprintf("\x1b[2J");
			ESTADO = PELEA;
		}
	}
	else if (ESTADO == PELEA){	
		if(player == 0){
			if(TeclaPulsada() == A){
				iprintf("\x1b[2J");
				HP2 -= 5;
				player = 1;
			}
			else if(TeclaPulsada() == B){
				iprintf("\x1b[2J");
				HP2 -= 20;
				player = 1;
			}
		}
	}
	else if(ESTADO == FIN){

		if(TeclaPulsada()==A){
			iprintf("\x1b[2J");
			ESTADO = SELECCION;
		}
		//Pulsa B para finalizar 
		else if(TeclaPulsada()==B){
			iprintf("\x1b[2J");
			ESTADO = INICIO;
		}
	}
}

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;


	if (ESTADO==PELEA && player == 1)
	{
		tick++; 
		if (tick==5)
		{
			seg++;
			tick=0;
				if(seg == 2){
					int aleatorio = rand()%2;
					if(aleatorio == 0){
						iprintf("\x1b[2J");
						HP1 -= 5; 
						player = 0;
					}else{ 
						iprintf("\x1b[2J");
						HP1 -= 20; 
						player = 0;
					}
					seg = 0;
				}
			seg3++;
			if (seg3==100)
			{
				iprintf("\x1b[2J");
				seg3=0;
				ESTADO=FIN;
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

