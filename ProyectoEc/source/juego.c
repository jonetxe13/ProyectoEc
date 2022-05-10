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

int tiempo;
int presionada = 0;

void juego()
{	
	//definiciones de variables
	int i=9;
	int tecla=0;
	int limpiar = 0;

	ESTADO=INICIO;

	//*******************************EN LA 2.ACTIVIDAD ********************************//
	// LLAMADAS A REALIZAR:
	// Configurar el teclado.
	//int APorInt = 0x4001;
	int ABPorInt = 0x4003;
	ConfigurarTeclado(ABPorInt);
	// Configurar el temporizador.
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
			visualizarInicio();

			//Insertar Portada y Texto(pulsa START para comenzar)
			iprintf("\x1b[4;2Hestado INICIO");
			if(TeclaPulsada()==START) {
				ESTADO = SELECCION;	
				iprintf("\x1b[2J");
			}
		}	
		else if(ESTADO == SELECCION){

			Seleccion();

			iprintf("\x1b[7;2HEl personaje es %s", personaje);
			//Rotacion de personajes
		}
		//Insertar Personajes
		else if(ESTADO == PELEA){
			visualizarPelea();
			PonerEnMarchaTempo();
			int enemigoRandom[2] = {0,1,2};
			int hecho = 0;
			if(hecho == 0){
				if( PERSONAJE == SONIC ){
					for(int i=1;i<3;i++){
						enemigoRandom[i-1] = enemigoRandom[i];
					}
					MostrarSonic(126,40,140);
				}
				else if( PERSONAJE == GOKU ){
					for(int i=2;i<3;i++){
						enemigoRandom[i-1] = enemigoRandom[i];
					}
					MostrarGoku(126,40,140);
				}
				else if( PERSONAJE == KRATOS ){
					for(int i=2;i<3;i++){
						enemigoRandom[i-1] = enemigoRandom[i];
					}
					MostrarPouAsesino(126,40,140);
				}

				int indiceEnemigoRandom = rand()%2;
				int enemigo = enemigoRandom[indiceEnemigoRandom];

				if(enemigo == SONIC){
					MostrarSonic(126,174,45);
				}
				else if(enemigo == GOKU){
					MostrarGoku(126,174,45);
				}
				else if(enemigo == KRATOS){
					MostrarPouAsesino(126,174,45);
				}
				hecho = 1;
			}

			iprintf("\x1b[5;1H%s", personaje); iprintf("\x1b[5;7H:%d", HP1);

			iprintf("\x1b[5;15Hvida2: %d", HP2);

			if(HP1 <= 0 || HP2 <= 0){
				ESTADO = FIN;
				iprintf("\x1b[2J");
			}
		}

		else if(ESTADO == FIN){
			BorrarRombo(126,70,150);

			iprintf("\x1b[2;1H Se ha acabado la partida");
			if(HP1 <= 0){
				iprintf("\x1b[15;1HGana la IA tonto que no sabes darle a la B xd");
				visualizarDerrota();
			}
			else if(HP2 <= 0){
				iprintf("\x1b[17;1HGanas tu, sabes darle a la B xd");
				visualizarVictoria();
			}
		}
	}
}
