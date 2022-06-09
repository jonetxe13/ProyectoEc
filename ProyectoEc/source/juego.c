/*---------------------------------------------------------------------------------
	Este código se ha desarrollado basándose en el código de dovoto "Simple sprite demo" 
	y en otro ejemplo de Jaeden Ameronen
	---------------------------------------------------------------------------------*/

#include <nds.h> 		//librería de la nds
#include <stdio.h>		//librería de entrada/salida estándar de C
#include <stdlib.h>		//librería estándar de C para reserva de memoria y conversiones númericas
#include <unistd.h>		//librería para asegurar la compatibilidad entre sistemas operativos

//librerías desarrolladas por nosotros para el proyecto

#include "definiciones.h"
#include "perifericos.h"
#include "rutinasAtencion.h"
#include "fondos.h"
#include "EstadoSeleccion.h"

//esta variable actua como un bool en el archivo de EstadoSeleccion
int presionada = 0;
void juego()
{	
	//definiciones de variables
	ESTADO = INICIO;
	int random;
	int Mapa;
	int indiceEnemigoRandom;


	//*******************************EN LA 2.ACTIVIDAD ********************************//
	// LLAMADAS A REALIZAR:
	// Configurar el teclado.
	int ABPorInt = 0x4003;
	ConfigurarTeclado(ABPorInt);
	// Configurar el temporizador.
  //
  // el temporizador interrumpe 5 veces por segundo al estar con este latch
	int Latch=39321;	
	ConfigurarTemporizador(Latch,0x0002);
	// Habilitar las interrupciones del teclado.
	HabilitarIntTeclado();
	// Habilitar las interrupciones del temporizador.
	HabilitarIntTempo();
	// Establecer las rutinas de atención a interrupciones
	EstablecerVectorInt();
	//******************************************************************************//
	while(1)
	{	
		/*******************************PROYECTO*****************************************/
		
		if(ESTADO == INICIO){
      //pone el fondo de inicio y borra todos los sprites de partidas anteriores
			visualizarInicio();
			BorrarTodos();
			iprintf("\x1b[4;2Hestado INICIO");
      //si se pulsa START se cambia al estado seleccion por encuesta
			if(TeclaPulsada()==START) {
				ESTADO = SELECCION;	
				iprintf("\x1b[2J");
			}
		}	
		else if(ESTADO == SELECCION){
      //se ejecuta la funcion que esta en otro archivo por cuestiones de limpieza y de que se vea menos codigo repetitivo
			Seleccion();
      //se inicializa random en 0 para que solo se ejecute una vez y player para que empiece tu personaje
			random = 0;
			player = 0;

			iprintf("\x1b[7;2HEl personaje es %s", personaje);
			//Rotacion de personajes
		}
			
		else if(ESTADO == PELEA){
			//se ejecuta una sola vez por la variable random, y crea dos variables random una entre 0 y 1 y la otra entre 0 y 2
			if(random == 0){
				BorrarTodos();
				random = 1;
				srand(time(NULL));
				indiceEnemigoRandom = rand()%2;
				Mapa = rand()%3;
			}
			//se pone un fondo random el cual depende de un int random entre 0 y 2 y se le pasa a una funcion para que lo muestre
			FondoPelea(Mapa);
			PonerEnMarchaTempo();
      //si se pulsa START se cambia al estado pausa por encuesta
			if(TeclaPulsada() == START){
				ESTADO = PAUSA;
			}
      //lista de enemigos posibles
			int enemigoRandom[3] = {0,1,2};

			//cambiar las opciones que hay de enemigos dependiendo de que personaje hayas elegido quitando del vector el personaje elegido para que asi no pueda salir como enemigo
      if( PERSONAJE == SONIC ){
				MostrarSonic(1,50,155);
				for(int i=1;i<3;i++){
					enemigoRandom[i-1] = enemigoRandom[i];
				}
			}
			else if( PERSONAJE == GOKU ){
				enemigoRandom[1] = enemigoRandom[2];
				
				MostrarGoku(1,50,155);
			}
			else if( PERSONAJE == KRATOS ){
				MostrarPouAsesino(1,50,155);
			}
      //elegir el enemigo con un indice elegido aleatoriamente
			const int enemigo = enemigoRandom[indiceEnemigoRandom];
      
      //mostrar el enemigo dependiendo del valor de la variable enemigo
			if(enemigo == SONIC){
				MostrarSonic(2,180,105);
			}
			else if(enemigo == GOKU){
				MostrarGoku(2,180,105);
			}
			else if(enemigo == KRATOS){
				MostrarPouAsesino(2,180,105);
			}
      //mostrar la vida de los personajes
			iprintf("\x1b[5;1H%s", personaje); iprintf("\x1b[5;7H:%d", HP1);

			iprintf("\x1b[5;15Hvida2: %d", HP2);
      //si la vida de uno de los dos jugadores es menor o igual que 0 se pasa al estado FIN
			if(HP1 <= 0 || HP2 <= 0){
				ESTADO = FIN;
				iprintf("\x1b[2J");
			}
		}

		else if(ESTADO == FIN){
      //se borran los sprites de los personajes y se compara las vidas para ver quien ha ganado
			BorrarTodos();
			iprintf("\x1b[2;1H Se ha acabado la partida");
			if(HP1 <= 0 || HP1 < HP2){
				iprintf("\x1b[15;1HGana la IA");
				visualizarDerrota();
			}
			else if(HP2 <= 0 || HP2 < HP1){
				iprintf("\x1b[17;1HGanas tu");
				visualizarVictoria();
			}
		}

		else if(ESTADO == PAUSA){
      //se borran los sprites en pantalla, se para el tiempo y se visualiza el fondo de pausa
			BorrarTodos();
			PararTempo();
			iprintf("\x1b[17;1HEl juego esta detenido");
			visualizarPausa();
      //si se pulsa A se vuelve a la pelea sin reiniciar el tiempo
			if(TeclaPulsada() == A){
				ESTADO = PELEA;
			}
      //si se pulsa B se vuelve a inicio , reiniciando asi todo
			else if(TeclaPulsada() == B){
				iprintf("\x1b[2J");
				ESTADO = INICIO;
			}
		}
	}
}
