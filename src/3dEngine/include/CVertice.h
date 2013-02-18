//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CVertice																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Vertices			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CVERTICE_H_
#define _CVERTICE_H_

#include "CVector.h"

class CVertice
{
	public:
		CVector		m_cPunto;
		CVector		m_cNormal;
		float		m_fColor[3];
		float		m_fU, m_fV, m_fW; // Coordenadas de las texturas

		inline void SetColor (float r, float g, float b) 
		{
			m_fColor[0] = r; 
			m_fColor[1] = g; 
			m_fColor[2] = b;
		};


		inline void SetCoordText (float u, float v, float w)
		{ 
			m_fU = u; 
			m_fV = v;
			m_fW = w;
		};


		inline void Set (CVertice *pVertice)
		{
			m_cPunto = pVertice->m_cPunto;
			m_cNormal = pVertice->m_cNormal; 
			m_fColor[0] = pVertice->m_fColor[0]; 
			m_fColor[0] = pVertice->m_fColor[1]; 
			m_fColor[0] = pVertice->m_fColor[2];
			m_fU = pVertice->m_fU; 
			m_fV = pVertice->m_fV;
			m_fW = pVertice->m_fW;
		};


		inline void Set	(CVertice pVertice)
		{
			m_cPunto = pVertice.m_cPunto; 
			m_cNormal = pVertice.m_cNormal; 
			m_fColor[0] = pVertice.m_fColor[0]; 
			m_fColor[0] = pVertice.m_fColor[1]; 
			m_fColor[0] = pVertice.m_fColor[2];
			m_fU = pVertice.m_fU; 
			m_fV = pVertice.m_fV;
			m_fW = pVertice.m_fW;
		};


};


#endif
