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
	int tecla=0;;

	ESTADO=INICIO;
	
	//Escribe en la fila 22 columna 5 de la pantalla	
	iprintf("\x1b[22;5HPrueba de escritura");						

/*Si se quiere visualizar el valor de una variable escribir %d dentro de las comillas y el nombre de la variable fuera de las comillas.*/
	iprintf("\x1b[23;5HPrueba de escritura con variable. Valor=%d", i);

	//*******************************EN LA 2.ACTIVIDAD ********************************//
        // LLAMADAS A REALIZAR:
	// Configurar el teclado.
	int APorInt = 0x4001;
	ConfigurarTeclado(APorInt);
	// Configurar el temporizador.
	int 	Latch=65536 - ((1/5) * (33554432/256));	
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
			iprintf("\x1b[22;5HPrueba de escritura");						
			if(TeclaPulsada()==START){
				ESTADO = SELECCION;	
			}
		}	
		else if(ESTADO == SELECCION){
			//Insertar PERSONAJE y Texto(pulsa A para confirmar)
			PERSONAJE = 0;
			//Rotacion de personajes
				if(TeclaPulsada()==L){
					PERSONAJE-=1;
				}
				else if(TeclaPulsada()=R){
					PERSONAJE+=1;
				}
				if(PERSONAJE<0){
					PERSONAJE=2;
				}
				else if(PERSONAJE>2){
					PERSONAJE=0;
				}
			
			//Insertar Personajes
			//Insertar SONIC
			//else if(PERSONAJE==SONIC){
				//Mostrar ficha de SONIC
				//if(TeclaPulsada==A){
					//ESTADO = PELEA;
				//}
			//}
			//Insertar GOKU
			//else if(PERSONAJE==GOKU){
				//Mostrar ficha de GOKU
				//if(TeclaPulsada==A){
					//ESTADO = PELEA;
				//}
			//}
			//Insertar KRATOS
			//else if(PERSONAJE==KRATOS){
				//Mostrar ficha de KRATOS
				//if(TeclaPulsada==A){
					//ESTADO = PELEA;
				//}
			//}
		}
		else if(ESTADO == PELEA){
			PonerEnMarchaTempo();
			//Pausa
			//if(TeclaPulsada()==START){
				//Se para el tiempo
					//PararTempo();
				//Se para el juego
			//}

			//Defenderse
			//else if(TeclaPulsada()==B){
				//Bloquea y no le hacen daño
			//}

			//Ataque
			//Ataque SONIC
			//else if(PERSONAJE==SONIC){
				//Insertar a SONIC en pelea
				//if(TeclaPulsada==A){
					//Mostrar ataques de sonic
					//if(TeclaPulsada==A){
						//Usar ATAQUE1
					//}	
					//else if(TeclaPulsada==B){
						//Usar ATAQUE2
					//}
				//}
			//Ataque GOKU
			//else if(PERSONAJE==GOKU){
				//Insertar a GOKU en pelea
				//if(TeclaPulsada==A){
					//Mostrar ataques de goku
					//if(TeclaPulsada==A){
						//Usar ATAQUE1
					//}	
					//else if(TeclaPulsada==B){
						//Usar ATAQUE2
					//}
				//}
			//Ataque KRATOS
			//else if(PERSONAJE==KRATOS){
				//Insertar a KRATOS en pelea
				//if(TeclaPulsada==A){
					//Mostrar ataques de kratos
					//if(TeclaPulsada==A){
						//Usar ATAQUE1
					//}	
					//else if(TeclaPulsada==B){
						//Usar ATAQUE2
					//}
				//}

			//Si se acaba la vida de alguno de los combatientes se acaba el combate
			//else if(HP2 == 0){
				//ESTADO = FIN
				//Mostrar mensaje Victoria
			//}
			//else if(HP1 == 0){
				//ESTADO = FIN
				//Mostrar mensaje Derrota
			//}

			//Si se acaba el tiempo determinado para el combate se acab el combate
			//else if(Timer = (tiempo maximo de pelea)){
				//ESTADO = FIN
				//Mostrar mensaje victoria para HP maximo
				//if(HP1>HP2){
					//Mostrar imagen victoria
				//}
				//else if(HP1==HP2)
					//Mostrar imagen empate
				//}
				//else{
					//Mostrar imagen derrota
				//}
			//}

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
