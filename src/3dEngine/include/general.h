//--------------------------------------------------------------------------------
//						 		   Void of Mercy          							  
//				   		        www.voidofmercy.org        					  


//--------------------------------------------------------------------------------
// Nombre: GENERAL.H																  	
// Descripci�n: Includes y defines basicos										  
// Autor: Antonio Rodriguez Fernandez  "MoebiuZ"      <moebiuz@voidofmercy.org>  
// Fecha: 06/04/2005																  
//--------------------------------------------------------------------------------

#include "windows.h"		// Archivo cabecera para Windows 
#include "gl\gl.h"			// Librer�a OpenGL32 
#include "gl\glu.h"			// Librer�a GLu32
#include "gl\glaux.h"		// Librer�a Glaux
#include "stdio.h"

#include "CListaEnlazada.h"   // Clase para crear listas enlazadas

#define nBitsColor 32                    // bits de colores para el formato de pixel OpenGL que usaremos
#define fovyAnguloPerspectiva 45.0f
#define zNearPerspectiva 0.1f
#define zFarPerspectiva 4000.0f
