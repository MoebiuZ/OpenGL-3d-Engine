#include "include/CASE.h"


#define ASEHEADER			"*3DSMAX_ASCIIEXPORT"

// Geometría de los objetos
#define GOBJECT				"*GEOMOBJECT"
#define OBJNAME				"*NODE_NAME"
#define NUM_VERTEX			"*MESH_NUMVERTEX"
#define NUM_FACES			"*MESH_NUMFACES"
#define NUM_TVERTEX			"*MESH_NUMTVERTEX"
#define NUM_TFACES			"*MESH_NUMTVFACES"
#define VERTEX_LIST			"*MESH_VERTEX_LIST"
#define VERTEX				"*MESH_VERTEX"
#define FACE_LIST			"*MESH_FACE_LIST"
#define FACE				"*MESH_FACE"
#define TVERTEX				"*MESH_TVERT"
#define TFACE				"*MESH_TFACE"
#define ID_MATERIAL			"*MATERIAL_REF"

// Materiales y texturas
#define NUM_MATERIALES		"*MATERIAL_COUNT"
#define MATERIAL			"*MATERIAL"
#define NOMBRE_MATERIAL		"*MATERIAL_NAME"
#define MAT_DIFFUSE			"*MATERIAL_DIFFUSE"
#define TEXTURE				"*BITMAP"

//------------------------------------------------------------------------------
// NOMBRE: Cargar
// DESCRIPCIÓN: Inicializa las estructuras que vamos a utilizar en la carga
//				y procede con la carga de la escena.
//------------------------------------------------------------------------------
int CASE::Cargar(char *szNombreFichero, CEscena *pEscena)
{
	FILE *hFichero;
	
	if (!(hFichero = fopen (szNombreFichero, "r")))
	{
		// hFichero no encontrado
		fprintf(stderr, "No se ha encontrado el fichero ASE \n");
		return 0;
	}
	
	// Comprobamos que se trate de un ASE correcto
	char datos[255];
	fscanf(hFichero,"%s",&datos);
	if (strcmp (datos, ASEHEADER)) {
		fprintf(stderr, "Cabecera del fichero ASE errónea \n");
		return 0;
	}

	CargarEscena(hFichero, pEscena);

	fclose (hFichero);
	
	return 1;
}

//------------------------------------------------------------------------------
// NOMBRE: CargarEscena
// DESCRIPCIÓN: Carga la información de la escena de un fichero ASE dentro de un
//				objeto CEscena.
//------------------------------------------------------------------------------
void CASE::CargarEscena	(FILE *hFichero, CEscena *pEscena)
{
	// Contamos cuantos objetos hay
	int nNumMeshes = 0;
	int nNumMateriales = 0;

	char datos[255];
	rewind (hFichero);
	while (!feof (hFichero)) {
		fscanf (hFichero, "%s", &datos);
		
		if (!strcmp (datos, GOBJECT))
			nNumMeshes++;		
	
		if (!strcmp (datos, NUM_MATERIALES))
			fscanf (hFichero, "%d", &nNumMateriales);			
	}
	
	pEscena->m_nNumMeshes = nNumMeshes;

	// Mostramos un mensaje con el número de objetos que hemos encontrado
	sprintf(datos,"Número de objetos encontrados: %d. Numero de materiales encontrados: %d", nNumMeshes, nNumMateriales);
	fprintf(stderr, datos);
	
	rewind (hFichero);
/*
	if (nNumMateriales > 0)
	{
		pEscena->m_pListaMateriales->Insertar(NumMateriales);
		CargarMateriales(hFichero, pEscena);
	}
*/	
	// Empezamos a sacar información del fichero
	CMesh	*mesh;

	int i = 0;
	fpos_t pos;

	rewind (hFichero);

	while (!feof(hFichero) && (i < nNumMeshes))
	{
		fscanf (hFichero, "%s", &datos);
		if (!strcmp (datos, GOBJECT))	
		{
			fgetpos(hFichero, &pos);			// Almacenamos la posición actual
			mesh = pEscena->NuevoMesh();		
			CargarInfoMesh(hFichero, mesh);	// Cargamos la información del objeto
			fsetpos(hFichero, &pos);			// Restauramos la posición actual
			CargarMesh(hFichero, mesh);	// Cargamos los datos del objeto
			i++;
		}
	}
}

//------------------------------------------------------------------------------
// NOMBRE: CargarInfoObjeto
// DESCRIPCIÓN: Carga información correspondiente a un objeto (NumCaras, NumVertices...)
//------------------------------------------------------------------------------
void CASE::CargarInfoMesh	(FILE *hFichero, CMesh *pMesh)
{
	int Num;
	int Mesh = false;
	char	datos[255];
	
	while (!feof (hFichero))
	{
		fscanf (hFichero, "%s", &datos);
	
		// Si nos encontramos con otro objeto salimos
		if (!strcmp (datos, GOBJECT))	
				return;
		
		if (!strcmp (datos, NUM_VERTEX))
		{
			fscanf (hFichero, "%d", &Num);
			pMesh->AddNVertices(Num);
		}
		else if (!strcmp (datos, NUM_FACES))
		{	
			fscanf (hFichero, "%d", &Num);
			pMesh->AddNCaras(Num);
			pMesh->m_nNumCaras=Num;
		}

		else if (!strcmp (datos, NUM_TVERTEX))
		{
			fscanf (hFichero, "%d", &Num);
			ListaVertices = new CVertice[Num];
			pMesh->m_nNumVertices = Num;
		}
		else fgets (datos, sizeof (datos), hFichero);

	}
}


//------------------------------------------------------------------------------
// NOMBRE: CargarObjeto
// DESCRIPCIÓN: Carga todos los datos de un objeto dentro de la estructura pObjeto
//------------------------------------------------------------------------------
void CASE::CargarMesh	(FILE *hFichero, CMesh *pMesh)
{
	char datos[255];
	bool Mesh = false;
	unsigned int	IDMat;
	while (!feof (hFichero))
	{
		fscanf (hFichero, "%s", &datos);

		if (!strcmp (datos, GOBJECT))	
				return;

		if (!strcmp (datos, VERTEX))
			GetVertice(hFichero,pMesh);
		else if (!strcmp (datos, TVERTEX))
			GetTVertice(hFichero,pMesh);
		else if (!strcmp (datos, FACE))
			GetCara(hFichero, pMesh);
		else if (!strcmp (datos, TFACE))
			GetTCara(hFichero, pMesh);
		else if (!strcmp (datos, ID_MATERIAL))
		{
			fscanf (hFichero, "%d", &IDMat);
			pMesh->m_nIDMaterial = IDMat;
		}
		else fgets (datos, sizeof (datos), hFichero);
	}
}


void CASE::GetVertice (FILE *hFichero, CMesh *pMesh)
{
	int indice;

	fscanf (hFichero, "%d", &indice);

	float x, y, z;
	fscanf (hFichero, "%f %f %f", &x, &y, &z);
	
	// Cambiamos el valor de Y y Z ya que 3DStudio trabaja así
	CVector vect;
	vect.Inicializa(x, z, y);
	
	CVertice *vert = new CVertice;

	vert->m_cPunto = vect;
	vert->m_fU = 0.0f;
	vert->m_fV = 0.0f;
	vert->m_fW = 0.0f;
	
	pMesh->ModVertice(indice, vert);
}

void CASE::GetTVertice	(FILE *hFichero, CMesh *pMesh)
{
	int indice;

	fscanf (hFichero, "%d", &indice);
	float u, v, w;
	fscanf (hFichero, "%f %f", &u, &v, &w);
	ListaVertices[indice].m_fU = u;
	ListaVertices[indice].m_fV = v;
	ListaVertices[indice].m_fW = w;

}

void CASE::GetCara (FILE *hFichero, CMesh *pMesh)
{

	int indice;
	fscanf (hFichero, "%d:", &indice);

	long vert[3];
	fscanf (hFichero, "\tA:\t%d B:\t%d C:\t%d", &vert[0], &vert[1], &vert[2]); 
	
	pMesh->ModCara(indice, vert);
}

void CASE::GetTCara	(FILE *hFichero, CMesh *pMesh)
{
	int indice;

	fscanf(hFichero, "%d:", &indice);

	int x, y, z;
	fscanf(hFichero, "%d %d %d", &x, &y, &z); 
	
	CVertice vert[3];

	vert[0].Set(ListaVertices[x]);
	vert[1].Set(ListaVertices[y]);
	vert[2].Set(ListaVertices[z]);

	CCara *cara = pMesh->m_pListaCaras->Obtener(indice);
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[0])->m_fU = vert[0].m_fU;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[1])->m_fU = vert[1].m_fU;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[2])->m_fU = vert[2].m_fU;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[0])->m_fV = vert[0].m_fV;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[1])->m_fV = vert[1].m_fV;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[2])->m_fV = vert[2].m_fV;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[0])->m_fW = vert[0].m_fW;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[1])->m_fW = vert[1].m_fW;
	pMesh->m_pListaVertices->Obtener(cara->m_Vertices[2])->m_fW = vert[2].m_fW;
}
/*
void CASE::CargarMateriales	(FILE *hFichero, CEscena *pEscena)
{
	char datos[255];
	unsigned int nummaterial;
	CMaterial	*material;
	
	while (!feof (hFichero))
	{
		fscanf (hFichero, "%s", &datos);
		
		if (!strcmp (datos,GOBJECT))	
				return;
		
		else if (!strcmp (datos,MATERIAL))	
		{
			fscanf(hFichero, "%d",&nummaterial);
			material=CargarMaterial(hFichero);
			pEscena->m_pListaMateriales->Poner(nummaterial,material);
		}
		else fgets (datos, sizeof (datos), hFichero);
	}
}

CMaterial *CASE::CargarMaterial(FILE *hFichero)
{
	
	CMaterial *nuevo_material = new CMaterial;
	
	bool finalizado=false;
	char datos[255];
	float x,y,z;


	while (!finalizado)
	{
		fscanf (hFichero, "%s", datos);
		
		if (!strcmp (datos, NOMBRE_MATERIAL))
		{			
			fscanf(hFichero, "%s", &datos);
			strcpy(nuevo_material->m_szNombre,datos);
		}
		
		else if (!strcmp (datos, MAT_DIFFUSE))
		{
			fscanf(hFichero, "%f %f %f",&x,&y,&z);
			nuevo_material->m_fDifuso[0]=x;
			nuevo_material->m_fDifuso[1]=y;
			nuevo_material->m_fDifuso[2]=z;
		}

		else if (!strcmp (datos, TEXTURE))
		{
			fscanf(hFichero, "%s",&datos);
			nuevo_material->m_pTextura=new CTextura;
			nuevo_material->m_pTextura->CargarBMP(datos);
		}
		
		else if (!strcmp (datos,GOBJECT))	
				return nuevo_material;

		else fgets (datos, sizeof (datos), hFichero);

	}

	return nuevo_material;
}
*/