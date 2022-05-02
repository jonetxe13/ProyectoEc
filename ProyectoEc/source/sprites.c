/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "sprites.h"
#include "definiciones.h"

u16* gfxsonic;
u16* gfxromboGrande;


/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void memoriaReserba()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxrombo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxromboGrande=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(255,0,0); // 1 = Rojo
	SPRITE_PALETTE[2] = RGB15(0,31,0); // los píxeles con valor 2 serán verdes.
	SPRITE_PALETTE[5] = RGB15(0,0,255); // 5 = Azul
	SPRITE_PALETTE[6]; // 6 = Negro
	SPRITE_PALETTE[3] =	RGB(255,255,255); // 3 = Blanco
	SPRITE_PALETTE[24] = RGB(255,215,126); //24 = Carne
}	


/* definición de un sprite de 16x16 píxeles para dibujar un rombo */
/* Por la forma que tienen de trabajar los bancos de memoria, la imagen del sprite se divide en bloques de 8x8 píxeles. Los primeros 64 (8x8) píxeles que indicamos
aparecerán en el cuadrante superior izquierdo de la imagen del sprite, los siguientes 64 en el cuadrante superior derecho, los siguientes en el cuadrante inferior izquierdo y los
últimos en el cuadrante inferior derecho. */

u8 sonic[256] = 
{
	0,0,0,6,6,6,6,6,
        6,6,0,0,6,6,0,0,	//	0,0,0,6,6,6,6,6, 6,6,0,0,6,6,0,0,
	0,0,6,6,5,5,5,5,
        5,5,6,6,5,5,6,0,	//	0,0,6,6,5,5,5,5, 5,5,6,6,5,5,6,0,
	0,0,0,0,6,5,6,24,
        5,5,5,5,5,5,5,6,	//	0,0,0,0,6,5,6,24, 5,5,5,5,5,5,5,6,
	0,0,0,6,5,5,6,24,
        5,3,3,5,5,5,5,6,	//	0,0,0,6,5,5,6,24, 5,3,3,5,5,5,5,6,
 
	0,0,6,5,5,5,5,5,
        3,3,3,3,5,3,6,0,	//	0,0,6,5,5,5,5,5, 3,3,3,3,5,3,6,0,
	0,6,6,6,6,6,5,5,
        3,3,3,6,5,3,6,0,	//	0,6,6,6,6,6,5,5, 3,3,3,6,5,3,6,0,
	0,0,0,0,6,5,5,3,
        3,3,6,3,6,6,6,0,	//	0,0,0,0,6,5,5,3, 3,3,6,3,6,6,6,0,
	0,0,0,6,5,5,5,5,
        24,3,3,3,24,24,6,2,	//	0,0,0,6,5,5,5,5, 24,3,3,3,24,24,6,2,

	0,0,6,6,6,6,6,6,
        24,24,24,24,24,24,6,0,	//	0,0,6,6,6,6,6,6, 24,24,24,24,24,24,6,0,
	0,0,0,0,0,0,6,5,
        6,6,6,6,6,6,6,6,	//	0,0,0,0,0,0,6,5, 6,6,6,6,6,6,6,6,
	0,0,0,0,0,6,5,6,
        6,5,24,24,6,3,3,6,	//	0,0,0,0,0,6,5,6, 6,5,24,24,6,3,3,6,
	0,0,0,0,0,6,6,3,
        3,6,24,24,6,3,3,6,	//	0,0,0,0,0,6,6,3, 3,6,24,24,6,3,3,6,

	0,0,0,0,0,0,6,3,
        3,6,5,24,6,3,6,0,	//	0,0,0,0,0,0,6,3, 3,6,5,24,6,3,6,0,
	0,0,0,0,0,0,6,6,
        6,6,6,6,6,6,0,0,	//	0,0,0,0,0,0,6,6, 6,6,6,6,6,6,0,0,
	0,0,0,0,0,6,1,1,
        1,3,6,1,1,3,6,0,	//	0,0,0,0,0,6,1,1, 1,3,6,1,1,3,6,0,
	0,0,0,0,0,6,1,1,
        3,1,1,6,3,1,1,6,	//	0,0,0,0,0,6,1,1, 3,1,1,6,3,1,1,6,
};

u8 romboGrande[1024] = 
{
	0,0,0,0,0,0,2,2,0,0,0,0,0,2,2,2,0,0,0,0,2,2,2,2,0,0,0,2,2,2,2,2,0,0,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	
 
	2,2,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2,2,2,2,0,0,0,0,2,2,2,2,2,0,0,0,2,2,2,2,2,2,0,0,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,2,0,0,2,2,2,2,2,2,0,0,0,2,2,2,2,2,0,0,0,0,2,2,2,2,0,0,0,0,0,2,2,2,0,0,0,0,0,0,2,2,	

	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,0,2,2,2,2,2,2,0,0,2,2,2,2,2,0,0,0,2,2,2,2,0,0,0,0,2,2,2,0,0,0,0,0,2,2,0,0,0,0,0,0,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,	

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,	
};

/* Carga en memoria cada uno de los sprites que hemos dibujado. */

void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxsonic[i] = sonic[i*2] | (sonic[(i*2)+1]<<8);				
	}
	//sprite de 32x32
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxromboGrande[i] = romboGrande[i*2] | (romboGrande[(i*2)+1]<<8);				
	}
}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un indice distinto, un valor entre 0 y 126. */

void MostrarRombo(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/*Esta función borra de la pantalla el Rombo con el índice indicado*/
void BorrarRombo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarRomboGrande(int indice, int x, int y)
{ 
 
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}
