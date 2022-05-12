/*-------------------------------------
	rutinasAtencion.c
	-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"
#include "juego.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"

int ESTADO;
int PERSONAJE;
int ATAQUES;
int seg3;
int player = 0;
int HP1 = vida;
int HP2 = vida;

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
				HP2 -= 5;
				player = 1;
				iprintf("\x1b[2J");
			}
			else if(TeclaPulsada() == B){
				HP2 -= 20;
				player = 1;
				iprintf("\x1b[2J");
			}
		}
	}
	else if(ESTADO == FIN){
		player = 0;

		if(TeclaPulsada()==A){
			ESTADO = SELECCION;
			iprintf("\x1b[2J");
		}
		//Pulsa B para finalizar 
		else if(TeclaPulsada()==B){
			ESTADO = INICIO;
			iprintf("\x1b[2J");
		}
	}
}
int posx= 10;
int posy= 170;

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;

	if (ESTADO==PELEA)
	{
		tick++; 
		if(tick == 1){
			tick = 0;
			posx += 5;
			posy -= 5;

			MostrarAtaque(1,posx,posy);
		}
		if (tick==5)
		{
			tick=0;
			
			if(player == 1){

				seg++;
				if(seg == 2){
					int aleatorio = rand()%2;
					if(aleatorio == 0){
						HP1 -= 5; 
						player = 0;
						iprintf("\x1b[2J");
					}else{ 
						HP1 -= 20; 
						player = 0;
						iprintf("\x1b[2J");
					}
					seg = 0;
				}
			}
			seg3++;
			if (seg3==50)
			{
				seg3=0;
				ESTADO=FIN;
				iprintf("\x1b[2J");
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

