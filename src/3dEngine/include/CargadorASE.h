//--------------------------------------------------------------------------------
//								 Void of Mercy          							  
//							  www.voidofmercy.org        						  



//--------------------------------------------------------------------------------
// Clase: CargadorASE
//--------------------------------------------------------------------------------
// Descripción: Carga ficheros ASE (Exportados de 3D MAX)
// Autor: Antonio Rodriguez Fernandez "MoebiuZ"      <moebiuz@voidofmercy.org>
// Fecha: 06/04/2005														
//--------------------------------------------------------------------------------

#ifndef _CARGADORASE_H
#define _CARGADORASE_H_

#include "general.h"
#include "CVector.h"
#include "CMaterial.h"
#include "CEscena.h"
#include "CMesh.h"
#include "CCara.h"
#include "CVertice.h"


class CargadorASE
{

	public:
		// Carga una escena desde un fichero ASE
		int		Cargar				(char *szArchivo, CEscena *pEscena);
		void	Liberar				();
				
				CargadorASE			() { 
										m_pTListaVertices = NULL; 
										m_pEscena = NULL;
										};

				~CargadorASE		() { 
										Liberar(); 
										};
		

	private:
		void	CargarEscena 		(FILE *hArchivo, CEscena *Escena);

		// Funciones para la carga de la geometría de un objeto
		void	CargarMesh			(FILE *hArchivo, CMesh *pMesh);
		void	CargarGeomMesh		(FILE *hArchivo, CMesh *pMesh);
		

		void	GetVertice			(FILE *hArchivo, CMesh *pMesh);
		void	GetTVertice			(FILE *hArchivo, CMesh *pMesh);
		void	GetNVertice			(FILE *hArchivo, CMesh *pMesh);
		void	GetCara				(FILE *hArchivo, CMesh *pMesh);
		void	GetTCara			(FILE *hArchivo, CMesh *pMesh);
		void	GetNCara			(FILE *hArchivo, CMesh *pMesh);
		void	GetColor			(FILE *hArchivo, CMesh *pMesh);

		CMaterial	*CargarMaterial	(FILE *hArchivo);

		// Variables de miembro
	
		CVertice	*m_pTListaVertices;
		CEscena		*m_pEscena;

};

#endif _CARGDORASE_H_
