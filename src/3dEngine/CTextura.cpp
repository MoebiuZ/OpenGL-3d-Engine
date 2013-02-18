#include "include/CTextura.h"

//---------------------------------------------------------------
// Nombre: Constructor
// Descripcion: Constructor de la clase. Inicializa las variables
// Parametros: Ninguno
//---------------------------------------------------------------
CTextura::CTextura()
{
	m_nID = 0;
}

//---------------------------------------------------------------
// Nombre: Destructor
// Descripcion: Destructor de la clase. Elimina la textura
// Parametros: Ninguno
//---------------------------------------------------------------
CTextura::~CTextura()
{
	Eliminar();
}

//---------------------------------------------------------------
// Nombre: Crear
// Descripcion: Establece los parámetros GL para cargar
// Parametros: 
//				char* szNombreFichero: Nombre del fichero a cargar
//---------------------------------------------------------------
bool CTextura::Crear(char* szNombreFichero)
{
	Eliminar();

	// Copiamos el nombre de fichero
	unsigned long int nszLon = strlen(szNombreFichero);
	
	// Generamos la ID de la textura
	glGenTextures(1, &m_nID);
	m_nID++; // Usamos un offset de +1 para diferenciar del estado no-inicializado
	
	glBindTexture(GL_TEXTURE_2D, m_nID-1);

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

	return true;
}

//---------------------------------------------------------------
// Nombre: Elimina
// Descripcion: Elimina la textura
// Parametros: Ninguno
//---------------------------------------------------------------
void CTextura::Eliminar()
{
	if( m_nID )
	{
		m_nID--;
		glDeleteTextures(1, &m_nID);
		m_nID=0;
	}
}

//---------------------------------------------------------------
// Nombre: Usa
// Descripcion: Usa la textura actual
// Parametros: Ninguno
//---------------------------------------------------------------
void CTextura::Usar()
{
	glBindTexture(GL_TEXTURE_2D, m_nID-1);
}

//---------------------------------------------------------------
// Nombre: CargarBMP
// Descripcion: Carga un fichero BMP y almacena los datos
// Parametros: Ninguno
//---------------------------------------------------------------
bool CTextura::CargarBMP(char *szNombreFichero)
{
    FILE *hFichero;
	AUX_RGBImageRec *Imagen;
	bool bResultado = false;


    if (szNombreFichero)          // Comprobamos que el nombre de fichero sea correcto 
	{
		hFichero = fopen(szNombreFichero, "r");            // Comprobamos si el fichero existe (Si podemos abrirlo)

		if (hFichero)                                   // ¿Existe el fichero?
		{
			fclose(hFichero);                          // Cerramos el handle
			Crear(szNombreFichero);
        
			Imagen = auxDIBImageLoad(szNombreFichero);   // Cargamos el BMP
			m_nAncho = Imagen->sizeX;
			m_nAlto = Imagen->sizeY;
		
			glTexImage2D(GL_TEXTURE_2D, 0, 3, m_nAncho, m_nAlto, 0, GL_RGB, GL_UNSIGNED_BYTE, Imagen->data);
		
			bResultado = true;
		}
	}
	delete Imagen->data;
	delete Imagen;
	return bResultado;
}


