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

	ESTADO=INICIO;
	
	//*******************************EN LA 2.ACTIVIDAD ********************************//
        // LLAMADAS A REALIZAR:
	// Configurar el teclado.
	//int APorInt = 0x4001;
	int ALRPorInt = 0x4301;
	ConfigurarTeclado(ALRPorInt);
	// Configurar el temporizador.
	int Latch=65536 - ((1/5) * (33554432/256));	
	// ConfigurarTemporizador(int Latch, int Conf_Tempo);
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
			//Insertar Portada y Texto(pulsa START para comenzar)
			iprintf("\x1b[2;2HEstamos en el estado INICIO");
			if(TeclaPulsada()==START){
				ESTADO = SELECCION;	
			}
		}	
		else if(ESTADO == SELECCION){
			//Insertar PERSONAJE y Texto(pulsa A para confirmar)
			iprintf("\x1b[2;2HEstamos en el estado SELECCION");

				if( TeclaDetectada() && TeclaPulsada()==L && presionada ==0){
					presionada=1;
					PERSONAJE-=1;
					if(PERSONAJE<0){
						PERSONAJE=2;
					}
					else if(PERSONAJE>2){
						PERSONAJE=0;
					}
					iprintf("\x1b[7;2HEl personaje es el numero %d", PERSONAJE);
				}
				else if(TeclaDetectada() && TeclaPulsada()==R && presionada==0){
					presionada=1;
					PERSONAJE+=1;
					if(PERSONAJE<0){
						PERSONAJE=2;
					}
					else if(PERSONAJE>2){
						PERSONAJE=0;
					}
					iprintf("\x1b[7;2HEl personaje es el numero %d", PERSONAJE);
				}
				else if(presionada==1 && TeclaDetectada()==0){
					presionada=0;
				}
			iprintf("\x1b[7;2HEl personaje es el numero %d", PERSONAJE);
			//Rotacion de personajes
		}
			//Insertar Personajes
		else if(ESTADO == PELEA){
			PonerEnMarchaTempo();

			iprintf("\x1b[2;2HEstamos en el estado PELEA");
				int ataque;
				int defensa;
				int velocidad;
					if( PERSONAJE == SONIC ){
						iprintf("\x1b[21;5HEl personaje seleccionado es Sonic");
						ataque = 2;
						defensa = 3;
						velocidad = 2;
						MostrarRombo();
					}
					else if( PERSONAJE == GOKU ){
						iprintf("\x1b[21;5HEl personaje seleccionado es Goku");
						ataque = 3;
						defensa = 2;
						velocidad = 2;
					}
					else if( PERSONAJE == KRATOS ){
						iprintf("\x1b[21;5HEl personaje seleccionado es Kratos");
						ataque = 2;
						defensa = 2;
						velocidad = 3;
					}

					iprintf("\x1b[16;5HLa vida1: %d", vida1);
					iprintf("\x1b[17;5HLa vida2: %d", vida2);
			}
		
		else if(ESTADO == FIN){
			//Pulsa A para volver a la selccion de personaje
			if(TeclaPulsada()==A){
				ESTADO = SELECCION;
			}
			//Pulsa B para finalizar 
			else if(TeclaPulsada()==B){
				ESTADO = INICIO;
			}
		}
	}
}
