//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  


//--------------------------------------------------------------------------------
// Clase: CControles
//--------------------------------------------------------------------------------
// Descripción: Clase para controlar teclado y raton
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CCONTROLES_H_
#define _CCONTROLES_H_

#include "general.h"
#include "3DEngine/include/CEscena.h"  // Porque lo que vamos a controlar esta 
                                       // en la escena antes de ser renderizada


class CControles
{
	public:
	
		
		CControles						();
		~CControles						();


		void	Comprobar				(bool bTeclas[256]);
		void	SetEscena				(CEscena *Escena);


	private:

			CEscena		*m_Escena;
};


#endif