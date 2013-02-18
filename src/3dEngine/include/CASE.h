#ifndef _CASE_H_
#define _CASE_H_

#include "CEscena.h"
#include <stdio.h>

class CASE
{
	public:
		int		Cargar			(char *szNombreFichero, CEscena *pEscena);
	
	private:
		void	CargarEscena	(FILE *hFichero, CEscena *pEscena);
		void	CargarMesh  	(FILE *hFichero, CMesh *pMesh);
		void	CargarInfoMesh   (FILE *hFichero, CMesh *pMesh);
		void	GetVertice		(FILE *hFichero, CMesh *pMesh);
		void	GetTVertice		(FILE *hFichero, CMesh *pMesh);
		void    GetCara			(FILE *hFichero, CMesh *pMesh);
		void	GetTCara		(FILE *hFichero, CMesh *pMesh);
//		void	CargarMateriales	(FILE *hFichero, CEscena *pEscena);
//		CMaterial	*CargarMaterial(FILE *hFichero);
		
		CVertice	*ListaVertices;	
};

#endif