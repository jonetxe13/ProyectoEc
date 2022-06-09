/*-------------------------------------
	rutinasAtencion.c
	-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "stdlib.h"
#include "definiciones.h"
#include "juego.h"
#include "perifericos.h"
#include "fondos.h"
#include "sprites.h"
int ESTADO;
int PERSONAJE;
int ATAQUES;
int seg3;
int player;
int HP1 = vida;
int HP2 = vida;

int posx= 50;
int posy= 155;
int pos2x= 180;
int pos2y= 105;

int contar = 0;
char teclaDanno;

void RutAtencionTeclado (){
  //si estas en seleccion y pulsas A se interrumpe y cambia el estado a pelea
	if (ESTADO == SELECCION){		
		if(TeclaPulsada() == A) {
			iprintf("\x1b[2J");
			ESTADO = PELEA;
		}
	}
	else if (ESTADO == PELEA){
    //si es tu turno
		if(player == 0){
        //si se pulsa A y contar es 0 entonces empieza a contar en RutAtencionTempo para hacer la animacion y se guarda la tecla pulsada en teclaDanno para RutAtencionTempo
				if(TeclaPulsada() == A && contar == 0){
					contar = 1;
          teclaDanno = 'a';
				}
				else if(TeclaPulsada() == B && contar == 0){
					contar = 1;
          teclaDanno = 'b';
				}
		}
	}
	else if(ESTADO == FIN){
    //devolvemos el turno a ti
		player = 0;
    //si se pulsa la A se vuelve al estado de seleccion
		if(TeclaPulsada()==A){
			ESTADO = SELECCION;
			iprintf("\x1b[2J");
		}
    //si se pulsa la B se vuelve al estado de inicio 
		else if(TeclaPulsada()==B){
			ESTADO = INICIO;
			iprintf("\x1b[2J");
		}
	}
}


void RutAtencionTempo()
{
	static int tick=0;
	static int seg=0;
	static int tickAnimaciones1 = 0;
	static int tickAnimaciones2 = 0;
  //solo usamos el timer para el estado pelea
	if (ESTADO==PELEA)
	{
		tick++; 
		//animacion para MostrarAtaque en diagonal
		if(player == 0 && contar == 1){
        //si se cumple empieza a contar 
		    tickAnimaciones1++;
				int Nataques;	
        //mientras no llegue a 10 el sprite del ataque se actualiza cada tick para hacer la animacion 
				if(tickAnimaciones1 < 10){
					MostrarAtaque(12,posx,posy);
					posx += 14;
					posy -= 6;
				}
				else if(tickAnimaciones1 >= 10){
          //cuando llega a 10 o mas se borra el sprite del ataque 
					BorrarAtaque(12,posx,posy);
          //se devuelve a 0 los ticks para que pueda empezar de cero despues
					tickAnimaciones1 = 0;
          //se devuelve a 0 para que pare de hacer la animacion
					contar = 0;
          //se cambia de turno
					player = 1;
          //se devuelve al valor inicial la posicion del sprite de ataque
					posx = 50;
					posy = 155;
          //si la tecla que habiamos pulsado antes era A entonces ataca random entre 5, 10 y 20
					if(teclaDanno == 'a'){
						Nataques = rand()%3;
            if(Nataques == 0){
            HP2 -= 5;
            }
            else{
              HP2 -= 10*Nataques;
              iprintf("\x1b[13;2HHas atacado %d", Nataques);iprintf("\x1b[13;15H veces.");
            }
					}
					else if(teclaDanno == 'b'){
            //si la tecla era la B quita 10 siempre
						HP2 -= 10;
					}
				}
		}
		else if(player == 1){
      //empieza a contar para hacer la animacion
		  tickAnimaciones2++;
			if(tickAnimaciones2 >= 10){
          //el enemigo ataca aleatoriamente entre 10 y 15
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
          //se borra el sprite de ataque y se reinician las variables para que se pueda repetir
          BorrarAtaque(12,pos2x,pos2y);
          pos2x = 180;
          pos2y = 105;
          tickAnimaciones2 = 0;
			}
      else if(tickAnimaciones2 < 10){
        //se muestra el ataque y se cambia la posicion a cada tick haciendo asi la animacion
        MostrarAtaque(12,pos2x,pos2y);
        pos2x -= 14;
        pos2y += 6;
      }
		}

		if (tick==5){
      //si los ticks normales llegan a 5 se suma 1 a seg3 que cuenta los segundos
			tick=0;
			seg3++;
			if (seg3==150){
        //si la variable con la que contamos segundos llega a 150 segundos, es decir 2 minutos y medio se cambia de estado y se reinicia seg3
				seg3=0;
				ESTADO=FIN;
				iprintf("\x1b[2J");
			}
		}
	}
}

void EstablecerVectorInt()
{
	//ponemos en marcha las rutinas de atencion 
	irqSet(IRQ_KEYS, RutAtencionTeclado);
	irqSet(IRQ_TIMER0, RutAtencionTempo);
}

