//--------------------------------------------------------------------------------
//								   MoebiuZ           							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: Camara																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para el control de la camara			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CCAMARA_H_
#define _CCAMARA_H_

#include "general.h"


class CCamara
{
	public:

						CCamara					();
		virtual			~CCamara	    		();
	
		float           GetRotX					();	
		float           GetRotY					();	
		float           GetRotZ					();	

		float           GetTransX				();	
		float           GetTransY				();	
		float           GetTransZ				();	

		void			SetRotX					(float fValor);
		void			SetRotY					(float fValor);
		void			SetRotZ					(float fValor);

		void			SetTransX				(float fValor);
		void			SetTransY				(float fValor);
		void			SetTransZ				(float fValor);

		void			AddRotX					(float fValor);
		void			AddRotY					(float fValor);
		void			AddRotZ					(float fValor);

		void			AddTransX				(float fValor);
		void			AddTransY				(float fValor);
		void			AddTransZ				(float fValor);



	private:

		float			m_fRotX;         // Angulo para rotar la camara en el eje X		
		float			m_fRotY;         // Angulo para rotar la camara en el eje Y
		float           m_fRotZ;         // Angulo para rotar al camara en el eje Z

		float			m_fTransX;       // Variable para trasladar la camara en el eje X
		float			m_fTransY;       // Variable para trasladar la camara en el eje Y
		float			m_fTransZ;       // Variable para trasladar la camara en el eje Z
};



#endif