//--------------------------------------------------------------------------------
//   							 Void of Mercy           							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CCara																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Caras			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CCARA_H_
#define _CCARA_H_

#include "CVector.h"
#include "CVertice.h"

class CCara
{
	public:
		long			m_Vertices[3];

		float			m_kCoordText[3][3];

		CVector			m_Normal;

		void Set (CCara	*pCara)
		{	
			m_Vertices[0] = pCara->m_Vertices[0];
			m_Vertices[1] = pCara->m_Vertices[1];
			m_Vertices[2] = pCara->m_Vertices[2];
			m_Normal = pCara->m_Normal;
		};
		
		void SetVertice (int nNum, long lVert)
		{	
			m_Vertices[nNum] = lVert;
		};

};		


#endif