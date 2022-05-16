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
int posx= 50;
int posy= 155;
int pos2x= 180;
int pos2y= 105;

void RutAtencionTeclado (){

	if (ESTADO == SELECCION){		
		if(TeclaPulsada() == A) {
			iprintf("\x1b[2J");
			ESTADO = PELEA;
		}
	}
	else if (ESTADO == PELEA){
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

int contar = 0;

void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	static int tickAnimaciones = 0;
	static int tickAnimaciones2 = 0;

	if (ESTADO==PELEA)
	{
		tick++; 
		tickAnimaciones++;
		tickAnimaciones2++;
		//animation for MostrarAtaque in diagonal
		if(player == 0){
				int Nataques;	
				char tecla;
				if(TeclaPulsada() == A && contar == 0){
					contar = 1;
					tickAnimaciones = 0;
					tecla = 'a';
					/* Nataques = rand()%3; */
					/* HP2 -= 10*Nataques; */
					/* iprintf("\x1b[13;2HHa atacado %d",Nataques," nº de veces"); */
				}
				else if(TeclaPulsada() == B && contar == 0){
					contar = 1;
					tickAnimaciones = 0;
					tecla = 'b';
					/* HP2 -= 10; */
					/* iprintf("\x1b[2J"); */
				}
				if(tickAnimaciones < 10 && contar == 1){
					MostrarAtaque(12,posx,posy);
					posx += 16;
					posy -= 6;
				}
				else if(tickAnimaciones >= 10 && contar == 1){
					tickAnimaciones = 0;
					contar = 0;
					player = 1;
					posx = 50;
					posy = 155;
					if(tecla == 'a'){
					Nataques = rand()%3;
					HP2 -= 10*Nataques;
					iprintf("\x1b[13;2HHa atacado %d",Nataques," nº de veces");
					}
					else if(tecla == 'b'){
					HP2 -= 10;
					}
				}
		}
		else if(player == 1){
			if(tickAnimaciones == 10){
					int aleatorio = rand()%2;
					if(aleatorio == 0){
						HP1 -= 10; 
						player = 0;
						iprintf("\x1b[2J");
					}else{ 
						HP1 -= 15; 
						player = 0;
						iprintf("\x1b[2J");
					}
					tickAnimaciones = 0;
					contar = 0;
				}
				if(tickAnimaciones2 < 10){
					MostrarAtaque(12,pos2x,pos2y);
					pos2x -= 16;
					pos2y += 6;
				}
				else if(tickAnimaciones2 >= 10){
					tickAnimaciones2 = 0;
					contar = 0;
					player = 1;
					pos2x = 180;
					pos2y = 105;
				}
		}

		if (tick==5)
		{
			tick=0;

			seg3++;
			if (seg3==150)
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

