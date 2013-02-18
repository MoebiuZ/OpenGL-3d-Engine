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

#define ASEHEADER			"*3DSMAX_ASCIIEXPORT"

// Geometría de los objetos
#define GOBJECT				"*GEOMOBJECT"
#define NODENAME			"*NODE_NAME"
#define NUM_VERTEX			"*MESH_NUMVERTEX"
#define NUM_FACES			"*MESH_NUMFACES"
#define NUM_TVERTEX			"*MESH_NUMTVERTEX"
#define NUM_TFACES			"*MESH_NUMTVFACES"
#define VERTEX_LIST			"*MESH_VERTEX_LIST"
#define VERTEX				"*MESH_VERTEX"
#define FACE_LIST			"*MESH_FACE_LIST"
#define FACE				"*MESH_FACE"
#define TVERTEX_LIST		"*MESH_TVERTEX_LIST"
#define TVERTEX				"*MESH_TVERT"
#define TFACE_LIST			"*MESH_TFACE_LIST"
#define TFACE				"*MESH_TFACE"
#define ID_MATERIAL			"*MATERIAL_REF"
#define NORMALS             "*MESH_NORMALS"
#define FACE_NORMAL         "*MESH_FACENORMAL"
#define POSITION            "*INHERIT_POS"
#define GMESH				"*MESH"
#define NODE_END            "}"

// Materiales y texturas
#define NUM_MATERIALES		"*MATERIAL_COUNT"
#define GMATERIAL			"*MATERIAL"
#define MAT_NAME   		    "*MATERIAL_NAME"
#define MAT_DIFFUSE			"*MATERIAL_DIFFUSE"
#define MAT_SPECULAR        "*MATERIAL_SPECULAR"
#define MAT_SHINE           "*MATERIAL_SHINE"
#define MAT_TEXTURE			"*BITMAP"
#define MAT_UTILE           "*UVW_U_TILE"
#define MAT_VTILE           "*UVW_V_TILE"
#define MAT_UOFFSET         "*UVW_U_OFFSET"
#define MAT_VOFFSET         "*UVW_V_OFFSET" 


#include "include/CargadorASE.h"


//--------------------------------------------------------------------------------
// Nombre: Liberar
// Descripcion: Libera todo lo que hemos utilizado
// Parametros: 
//--------------------------------------------------------------------------------
void CargadorASE::Liberar()
{
	if (m_pTListaVertices)
		delete [] m_pTListaVertices;
}




//--------------------------------------------------------------------------------
// Nombre: Cargar
// Descripcion: Inicia la carga del archivo
// Parametros: 
//--------------------------------------------------------------------------------
int CargadorASE::Cargar(char *szArchivo, CEscena *pEscena)
{
	FILE *hArchivo;
	
	// Abrimos el fichero que nos pasan como parámetro
	if (!(hArchivo = fopen (szArchivo, "r")))
	{
			// Fichero no encontrado
		return 0;
	}


	m_pEscena = pEscena;
	CargarEscena(hArchivo, pEscena);

	// Cerramos el hArchivo y salimos
	fclose (hArchivo);
	
	return 1;
}




//--------------------------------------------------------------------------------
// Nombre: CargarEscena
// Descripcion: Comienza la carga de la escena del archivo
// Parametros: 
//--------------------------------------------------------------------------------
void CargadorASE::CargarEscena(FILE *hArchivo, CEscena *pEscena)
{
	char szData[255];
	unsigned int nNumMeshes = 0;		// Con estas variables contamos cuantos
	unsigned int nNumMateriales = 0;    // elementos de cada tipo hay

	CMaterial	*pMaterial;
	CMesh		*pMesh;
	
	// Chequeamos la cabecera para comprobar que se trata de un ASE correcto
	fscanf(hArchivo, "%s", &szData);
	
	if (strcmp (szData, ASEHEADER)) {
		return;  // No es un archivo ASE o esta corrupto
	}
	
	// Comenzamos con la lectura
	
	while (!feof(hArchivo)) 
	{
		memset(&szData, 0, sizeof(szData));	// Nos aseguramos de la memoria
		fscanf(hArchivo, "%s", &szData);
		
		//--------------------------------
		//		Cargamos un material
		//--------------------------------
		if (!strcmp(szData, GMATERIAL)) {
			pMaterial = CargarMaterial(hArchivo);					// Cargamos la información del mismo
			m_pEscena->m_pListaMateriales->Anadir(pMaterial);		// Lo añadimos a la lista de materiales
			nNumMateriales++;									    // Incrementamos el número de mat. cargados

		
		//--------------------------------
		//		Cargamos un Mesh
		//--------------------------------
		}
		else if (!strcmp(szData, GOBJECT)) {
			pMesh = pEscena->NuevoMesh();	// Creamos un nuevo objeto
			CargarMesh(hArchivo, pMesh);
	
			nNumMeshes++;					// Incrementamos el contador de objetos
		}

		// Leemos la basura que no nos interesa
		else fgets (szData, sizeof (szData), hArchivo);
	}

	pEscena->m_pListaMeshes->m_nNumElementos = nNumMeshes;
	pEscena->m_pListaMateriales->m_nNumElementos = nNumMateriales;


}



//--------------------------------------------------------------------------------
// Nombre: CargarMesh
// Descripcion: Inicia la carga de un Mesh
// Parametros: 
//--------------------------------------------------------------------------------
void CargadorASE::CargarMesh(FILE *hArchivo, CMesh *pMesh)
{
	char	szData[255];
	bool	bTerminar = false;
	bool	bNombre = false;
	float   fX, fY, fZ;
	unsigned int	nIDMaterial;
		

	while (!bTerminar)
	{
	
		fscanf (hArchivo, "%s", &szData);		// Leemos una cadena del fichero
	
	
		//----------------------------
		//	Nombre del objeto
		//----------------------------
		if ((!strcmp (szData, NODENAME)) && (!bNombre))
		{
			memset(&szData, 0, sizeof(szData));
			fscanf(hArchivo, " \"%s", &szData);				// Leemos el nombre eliminando las comillas inicial
			szData[strlen (szData) - 1] = '\0';				// y final
			
			strcpy(pMesh->m_szNombre, szData);				// Copiamos el nombre al objeto
			bNombre = true;									// Nos aseguramos de no entrar otra vez
		}
				
		//----------------------------
		//	  Posición del objeto
		//----------------------------
		else if (!strcmp (szData, POSITION))
		{
			fscanf (hArchivo, "%f %f %f", &fX, &fZ, &fY);
			pMesh->m_vPivote->Inicializa(fX, fY, fZ);


		}

		else if (!strcmp (szData, NODE_END))
		{
			bTerminar = true;
		}
		else fgets (szData, sizeof (szData), hArchivo);

	}

	bTerminar = false;  // Ahora haremos el bucle para cargar la geometria

	while (!bTerminar)
	{
		fscanf (hArchivo, "%s", &szData);

		if (!strcmp (szData, GMESH))
		{
			CargarGeomMesh(hArchivo, pMesh);

		}
		
		//----------------------------
		//  IDENTIFICADOR DEL MATERIAL
		//----------------------------
		else if (!strcmp (szData, ID_MATERIAL))
		{
			fscanf (hArchivo, "%d", &nIDMaterial);
			pMesh->m_nIDMaterial = nIDMaterial;
		}

		//----------------------------
		// COLOR EN MODO WIREFRAME
		//----------------------------
//		else if (!strcmp (szData, MAT_WFCOLOR))
//			GetColor(hArchivo, pMesh);

		else if (!strcmp (szData, NODE_END)) 
		{
				bTerminar = true;
		}	
		
		// Leemos la basura restante
		else fgets (szData, sizeof (szData), hArchivo);
	}

}  



//--------------------------------------------------------------------------------
// Nombre: CargarGeomMesh
// Descripcion: Carga la geometría de un Mesh
// Parametros: 
//--------------------------------------------------------------------------------

void CargadorASE::CargarGeomMesh (FILE *hArchivo, CMesh *pMesh)
{
	char			szData[255];
	bool			bTerminar = false;
	int			    nNum;

	
	while (!bTerminar)
	{
		memset(&szData, 0, sizeof(szData));	
		fscanf (hArchivo, "%s", &szData);		// Leemos una cadena del fichero

		
		//----------------------------
		//		Número de vertices
		//----------------------------
		if (!strcmp (szData, NUM_VERTEX))
		{
			fscanf (hArchivo, "%d", &nNum);					// Leemos el número de vértices
			
			pMesh->AddNVertices(nNum);					    // Reservamos memoria para ellos
		
		}
		
		//----------------------------
		//		Número de caras
		//----------------------------
		else if (!strcmp (szData, NUM_FACES))
		{	
			fscanf (hArchivo, "%d", &nNum);					// Leemos el número de caras
			
			pMesh->AddNCaras(nNum);  						// Reservamos memoria para las caras
			
		}

		//----------------------------
		// Número de vértices texturizados
		//----------------------------
		else if (!strcmp (szData, NUM_TVERTEX))
		{
			fscanf (hArchivo, "%d", &nNum);					// Leemos el número de vértices texturizados
			
			m_pTListaVertices = new CVertice[nNum];			// Reservamos memoria para la lista
		}
		
		//----------------------------
		// Un vertice
		//----------------------------
		else if (!strcmp (szData, VERTEX_LIST))
		{
			
			fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
			fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente

			while (strcmp(szData, NODE_END))
			{
				GetVertice(hArchivo, pMesh);
				fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
				fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente
			}
		}

		
		
		//----------------------------
		// Un vertice texturizado
		//----------------------------
		else if (!strcmp (szData, TVERTEX_LIST))
		{
			fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
			fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente

			
			while (strcmp(szData, NODE_END))
			{
				GetTVertice(hArchivo, pMesh);
				fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
				fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente
			}
		}

		//----------------------------
		// Una cara
		//----------------------------
		else if (!strcmp (szData, FACE_LIST))
		{
			fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
			fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente

			
			while (strcmp(szData, NODE_END))
			{
				GetCara(hArchivo, pMesh);
				fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
				fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente
			}
		}

		//----------------------------
		// Una cara texturizada
		//----------------------------
		else if (!strcmp (szData, TFACE_LIST))
		{
			fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
			fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente

			
			while (strcmp(szData, NODE_END))
			{
				GetTCara(hArchivo, pMesh);
				fgets (szData, sizeof (szData), hArchivo);  // Leemos la basura que queda en la linea actual
				fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente
			}
		}

		
		//----------------------------
		// Normales de vertice y cara
		//----------------------------
		else if (!strcmp (szData, NORMALS))
		{
			fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
			fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente

			while (strcmp(szData, NODE_END))
			{
				if (!strcmp(szData, FACE_NORMAL))
					GetNCara(hArchivo, pMesh);
				else
					GetNVertice(hArchivo, pMesh);
				fgets (szData, sizeof (szData), hArchivo);    // Leemos la basura que queda en la linea actual
				fscanf (hArchivo, "%s", &szData);			  // Leemos la linea siguiente
			}
			float a = 0;
		} 

		//----------------------------
		//		Si no queda nada
		//----------------------------
		else if (!strcmp (szData, NODE_END)) 
		{
				bTerminar = true;

		}
		
		else 
		{
			// Leer la basura que queda
			fgets (szData, sizeof (szData), hArchivo);
		
		}
	}
	
}



//--------------------------------------------------------------------------------
// Nombre: CargarMaterial
// Descripcion: Extrae información de un material contenido en el fichero
// Parametros: 
//--------------------------------------------------------------------------------
CMaterial * CargadorASE::CargarMaterial(FILE *hArchivo)
{
	
	CMaterial *pMaterial = new CMaterial();
	
	bool bTerminar = false;
	char szData[255];
	float fX, fY, fZ;


	while (!bTerminar)
	{
		fscanf (hArchivo, "%s", szData);	// Leemos una cadena del fichero
		

		// El nombre del material
		if (!strcmp (szData, MAT_NAME))
		{			
			fscanf(hArchivo, " \"%s",&szData);			// Leemos el nombre excluyendo las comillas iniciales
			szData[strlen (szData) - 1] = '\0';			// y finales
			strcpy(pMaterial->m_szNombre, szData);      // Copiamos el nombre en el material
		}
		
		// El color difuso
		else if (!strcmp (szData, MAT_DIFFUSE))
		{
			fscanf(hArchivo, "%f %f %f", &fX, &fY, &fZ);		// Leemos el color
			pMaterial->m_fDifuso[0] = fX;				        // Asignamos el color al material
			pMaterial->m_fDifuso[1] = fY;
			pMaterial->m_fDifuso[2] = fZ;
		}
		
		// Color especular
		else if (!strcmp (szData, MAT_SPECULAR))
		{
			fscanf(hArchivo, "%f %f %f", &fX, &fY, &fZ);		// Leemos el color
			pMaterial->m_fEspecular[0] = fX;			       // Asignamos el color al material
			pMaterial->m_fEspecular[1] = fY;
			pMaterial->m_fEspecular[2] = fZ;
		}

		// Brillo
		else if (!strcmp (szData, MAT_SHINE))
		{
			fscanf(hArchivo, "%f", &fX);					// Leemos el valor del brillo
			pMaterial->m_fBrillo = fX;				        // y lo asignamos al material
		}
		
		// Textura
		else if (!strcmp (szData, MAT_TEXTURE))
		{

			fscanf(hArchivo, " \"%s",&szData);						// Leemos el nombre de la textura excluyendo 
			szData[strlen (szData) - 1] = '\0';						// las comillas iniciales fY finales.
			pMaterial->m_pTextura = new CTextura;					// Reservamos memoria para la textura	

			strcpy(pMaterial->m_pTextura->m_szNombre, szData);		// Copiamos el nombre al material
			
			pMaterial->m_pTextura->CargarBMP(szData);		  	    // Cargamos la textura
		}
		
		// U Tile
		else if (!strcmp (szData, MAT_UTILE))
		{
			fscanf(hArchivo, "%f", &fX);				// Leemos el valor
			pMaterial->m_pTextura->m_uTile = fX;	    // y lo asignamos a la textura
		}
		
		// V Tile
		else if (!strcmp (szData, MAT_VTILE))
		{
			fscanf(hArchivo, "%f",&fX);				// Leemos el valor
			pMaterial->m_pTextura->m_vTile = fX;	// y lo asignamos a la textura
		}

		// U Offset
		else if (!strcmp (szData, MAT_UOFFSET))	
		{
			fscanf(hArchivo, "%f", &fX);				// Leemos el valor
			pMaterial->m_pTextura->m_uOffset = fX;	    // y lo asignamos a la textura
		}

		// V Offset
		else if (!strcmp (szData, MAT_VOFFSET))
		{
			fscanf(hArchivo, "%f",&fX);				// Leemos el valor
			pMaterial->m_pTextura->m_vOffset = fX;	// y lo asignamos a la textura
		}
		
		// No hay textura
		else if (!strcmp (szData, NODE_END))
		{
			bTerminar = true;
		}
		// Basura restante
		else fgets (szData, sizeof (szData), hArchivo);
	}


	return pMaterial;
}


//================================================================================
//			FUNCIONES DE CARGA DE LA GEOMETRIA DE LOS OBJETOS
//================================================================================

//--------------------------------------------------------------------------------
// Nombre: GetVertice
// Descripcion: Carga un vertice desde el hArchivo
//--------------------------------------------------------------------------------
void CargadorASE::GetVertice (FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	float fX, fY, fZ;


	fscanf (hArchivo, "%d", &nIndice);
	// Cambiamos el valor de Y y Z ya que 3DStudio trabaja así
	fscanf (hArchivo, "%f %f %f", &fX, &fY, &fZ);
	
	// En 3DSMax el valor negativo de Z significa salir de la pantalla, nosotros lo necesitamos
	// al reves
	CVector vect; // = new CVector;
	vect.Inicializa(fX, fZ, fY); // fX,-fZ,fY

	CVertice *vert = new CVertice;

	vert->m_cPunto = vect;

	pMesh->ModVertice(nIndice, vert);
    	
}

//--------------------------------------------------------------------------------
// Nombre: GetTVertice
// Descripcion: Cargamos un vertice texturizado de la pEscena
//--------------------------------------------------------------------------------
void CargadorASE::GetTVertice (FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	float fU, fV, fW;
	
	fscanf (hArchivo, "%d", &nIndice);
	fscanf (hArchivo, "%f %f %f", &fU, &fV, &fW);

	m_pTListaVertices[nIndice].m_fU = fU;
	m_pTListaVertices[nIndice].m_fV = fV;
	m_pTListaVertices[nIndice].m_fW = fW;

}

//--------------------------------------------------------------------------------
// Nombre: GetNVertice
// Descripcion: Cargamos la normal de un vertice
//--------------------------------------------------------------------------------
void CargadorASE::GetNVertice(FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	float fX, fY, fZ;
	CVector  vect;
	CVertice *vert = new CVertice;
	
	fscanf (hArchivo, "%d", &nIndice);
	fscanf (hArchivo, "%f %f %f", &fX, &fY, &fZ);
	vect.Inicializa(fX, fZ, fY); //X,-Z,Y

	// En 3DSMax el valor negativo de Z significa salir de la pantalla, nosotros lo necesitamos
	// al reves
	
	vert->Set(pMesh->m_pListaVertices->Obtener(nIndice));
	vert->m_cNormal = vect;
	pMesh->ModVertice(nIndice, vert);
}


//--------------------------------------------------------------------------------
// Nombre: GetCara
// Descripcion: Cargamos las especificaciones de una cara
//--------------------------------------------------------------------------------
void CargadorASE::GetCara (FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	long lVert[3];

	fscanf (hArchivo, "%d:", &nIndice);

	fscanf (hArchivo, "\tA:\t%d B:\t%d C:\t%d", &lVert[0], &lVert[1], &lVert[2]); 
		
	pMesh->ModCara(nIndice, lVert);


}


//--------------------------------------------------------------------------------
// Nombre: GetTCara
// Descripcion: Cargamos una cara texturizada
//--------------------------------------------------------------------------------
void CargadorASE::GetTCara(FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	int nX, nY, nZ;
	
	fscanf(hArchivo,"%d:",&nIndice);

	fscanf(hArchivo,"%d %d %d", &nX, &nY, &nZ); 
	
	CVertice vert[3];
	vert[0].Set(m_pTListaVertices[nX]);
	vert[1].Set(m_pTListaVertices[nY]);
	vert[2].Set(m_pTListaVertices[nZ]);

	// Cargamos la cara que vamos a modificar
	CCara *cara = pMesh->m_pListaCaras->Obtener(nIndice);
	
	for (int i = 0; i < 3; i++)
	{
		cara->m_kCoordText[i][0] = vert[i].m_fU;
		cara->m_kCoordText[i][1] = vert[i].m_fV;
		cara->m_kCoordText[i][2] = vert[i].m_fW;
	}

}


//--------------------------------------------------------------------------------
// Nombre: GetNFace
// Descripcion: Cargamos la normal de una cara
//--------------------------------------------------------------------------------
void CargadorASE::GetNCara (FILE *hArchivo, CMesh *pMesh)
{
	int nIndice;
	float fX, fY, fZ;

	fscanf (hArchivo, "%d", &nIndice);
	fscanf (hArchivo, "%f %f %f", &fX, &fY,	&fZ);
	
	CCara *pCara = pMesh->m_pListaCaras->Obtener(nIndice);
	pCara->m_Normal.Inicializa(fX, fZ, fY);
}

//--------------------------------------------------------------------------------
// Nombre: GetColor
// Descripcion: Cargamos el color de un objeto (Wireframe)
//--------------------------------------------------------------------------------
void CargadorASE::GetColor (FILE *hArchivo, CMesh *pMesh)
{
	float fR, fG, fB;
	fscanf (hArchivo, "%f %f %f", &fR, &fG, &fB);
	
	pMesh->m_fColor[0] = fR;
	pMesh->m_fColor[1] = fG;
	pMesh->m_fColor[2] = fB;
}
