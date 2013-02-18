//--------------------------------------------------------------------------------
// 							     Void of Mercy           							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CEscenaRender																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para renderizar una escena completa		  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CESCENARENDER_H_
#define _CESCENARENDER_H_

#include "general.h"
#include "CEscena.h"    // Clase CEscena a renderizar
#include "CMesh.h"

#include "CCamara.h"

class CEscenaRender
{
	public:
						CEscenaRender			();
		virtual			~CEscenaRender			();

		void			SetEscena               (CEscena *Escena);
		void            Renderizar              ();




	private:

		CEscena			*m_Escena;
		

		int             RenderEscena            ();
		int             RenderMesh              (int nIndice, CMesh *pMesh);
};

#endif