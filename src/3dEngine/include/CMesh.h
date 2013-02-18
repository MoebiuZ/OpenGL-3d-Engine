//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CMesh																	  
//--------------------------------------------------------------------------------
// Descripción: Clase para almacenar Meshes inanimados			  
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CMESH_H_
#define _CMESH_H_

#include "general.h"

#include "CCara.h"
#include "CVertice.h"
#include "CVector.h"


class CMesh
{
	public:

		CListaEnlazada<CVertice>		*m_pListaVertices;
		unsigned int					m_nNumVertices;
		CListaEnlazada<CCara>			*m_pListaCaras;
		unsigned int					m_nNumCaras;
		
		float			m_fColor[3];
		char			m_szNombre[12];
		unsigned int	m_nIDMaterial;

		CMesh			*m_pSubMesh;		 // Mas adelante quiza lo use para enlazar 
                                             // varios Meshes relacionados

        CVector         *m_vPivote;          // Posicion del mesh

						CMesh					();
		virtual			~CMesh			    	();
		
		void			AddNCaras	 	        (int nNumCaras);
		void			ModCara					(int nNumeroCara, CCara *pCara);
        void			ModCara					(int nNumCara, long Vertices[3]);
		void			AddNVertices			(int nNumeroVertices);
		void			ModVertice				(int nNumeroVertice, CVertice *pVertice);


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

		float			m_fRotX;         // Angulo para rotar el mesh en el eje X
		float			m_fRotY;         // Angulo para rotar el mesh en el eje Y
		float           m_fRotZ;         // Angulo para rotar al mesh en el eje Z

		float			m_fTransX;       // Variable para trasladar el mesh en el eje X
		float			m_fTransY;       // Variable para trasladar el mesh en el eje Y
		float			m_fTransZ;       // Variable para trasladar el mesh en el eje Z
};

#endif