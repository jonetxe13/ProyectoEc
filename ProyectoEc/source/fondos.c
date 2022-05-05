
#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "fondos.h"
#include "graficos.h"
#include "Puerta.h"
#include "PuertaAbierta.h"
#include "FondoPelea.h"
#include "FondoSonic.h"
#include "FondoGoku.h"
#include "FondoKratos.h"

/* Se elige el canal de DMA que se utilizará para copiar las imágenes en memoria.*/
static const int DMA_CHANNEL = 3;

/* Para cada fondo que se quiera visualizar hay que escribir un procedimiento como el siguiente */

void visualizarPuerta() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPelea() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoPeleaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoPeleaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarSonic() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoSonicBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoSonicBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarGoku() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoGokuBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoGokuBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarKratos() {
	
	dmaCopyHalfWords(DMA_CHANNEL,
                     FondoKratosBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     FondoKratosBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void visualizarPuertaAbierta() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     PuertaAbiertaBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     PuertaAbiertaBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

