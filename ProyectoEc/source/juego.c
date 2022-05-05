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

int tiempo;

void juego()
{	
	//definiciones de variables
	int i=9;
	int tecla=0;
	int presionada = 0; 
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

			HP1 =100;
			HP2 =100;
			//Insertar Portada y Texto(pulsa START para comenzar)
			iprintf("\x1b[4;2Hestado INICIO");
			if(TeclaPulsada()==START) {
				iprintf("\x1b[2J");
				ESTADO = SELECCION;	
			}
		}	
		else if(ESTADO == SELECCION){
			HP1 =100;
			HP2 =100;
			//Insertar PERSONAJE y Texto(pulsa A para confirmar)
			iprintf("\x1b[2;2Hestado SELECCION");

			if( TeclaDetectada() && TeclaPulsada()==L && presionada ==0){
				presionada=1;
				PERSONAJE-=1;
				if(PERSONAJE<0) PERSONAJE=2;
				else if(PERSONAJE>2) PERSONAJE=0;

				iprintf("\x1b[7;2HEl personaje es%d", PERSONAJE);
			}
			else if(TeclaDetectada() && TeclaPulsada()==R && presionada==0){
				presionada=1;
				PERSONAJE+=1;
				if(PERSONAJE<0) PERSONAJE=2;
				else if(PERSONAJE>2) PERSONAJE=0;

				iprintf("\x1b[7;2HEl personaje es%d", PERSONAJE);
			}
			else if(presionada==1 && TeclaDetectada()==0) presionada=0;
			
			//Fondos Seleccion
			if(PERSONAJE == SONIC){
				visualizarSonic();
			}
			else if(PERSONAJE == GOKU){
				visualizarGoku();
			}
			else if(PERSONAJE == KRATOS){
				visualizarKratos();
			}
			iprintf("\x1b[7;2HEl personaje es%d", PERSONAJE);
			//Rotacion de personajes
		}
		//Insertar Personajes
		else if(ESTADO == PELEA){
			visualizarPelea();
			PonerEnMarchaTempo();
			int ataque;
			int defensa;
			int velocidad;

			iprintf("\x1b[5;1Hvida1: %d", HP1);
			iprintf("\x1b[5;15Hvida2: %d", HP2);

			if( PERSONAJE == SONIC ){
				iprintf("\x1b[21;5HEl personaje Sonic");
				ataque = 2;
				defensa = 3;
				velocidad = 2;
				MostrarSonic(126,70,150);
			}
			else if( PERSONAJE == GOKU ){
				iprintf("\x1b[21;5HEl personaje Goku");
				ataque = 3;
				defensa = 2;
				velocidad = 2;
			}
			else if( PERSONAJE == KRATOS ){
				iprintf("\x1b[21;5HEl personaje Kratos");
				ataque = 2;
				defensa = 2;
				velocidad = 3;
			}
			if(HP1 <= 0 || HP2 <= 0){
				iprintf("\x1b[2J");
				ESTADO = FIN;
			}
		}

		else if(ESTADO == FIN){
			BorrarRombo(126,70,150);

			iprintf("\x1b[2;1H Se ha acabado la partida");
			if(HP1 <= 0){
				iprintf("\x1b[15;1HGana la IA tonto que no sabes darle a la B xd");
			}
			else if(HP2 <= 0){
				iprintf("\x1b[17;1HGanas tu, sabes darle a la B xd");
			}
			//Pulsa A para volver a la selccion de personaje
		}
	}
}
