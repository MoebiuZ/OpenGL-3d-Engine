#ifndef _CLISTAENLAZADA_H_
#define _CLISTAENLAZADA_H_

// INCLUDES ////////////////////////////
#include <stdlib.h>
#include <string.h>

template<class tTipo>
class CListaEnlazada												
{
	// PRIVADO //////////////////////////
	private:
		typedef struct ElementoTipo {	tTipo * puntero; };		// Estructura que encapsula un elemento de la lista
		inline void ReservaMemoria(void);						// Reserva memoria para almacenar los elementos
		bool m_bTodoLiberado;								
	
	
	// PUBLICO //////////////////////////
	public:
		ElementoTipo * m_Zona;									// Puntero a la zona de memoria donde está almacenada la lista
																// Este miembro es publico para permitir a las clases derivadas
																// acceder a los elementos (friend?)
		
		int m_nNumElementos;									// Número de elementos. Para una lectura directa usar Contar()
		
		CListaEnlazada(void);														// Constructor
		~CListaEnlazada(void);														// Destructor

		inline void		LiberarTodo		();											// Elimina los elementos contenidos en la lista enlazada (Liberación de los recursos)
		inline void		Insertar		(const int& nNumero);						// Almacena <nNumero> elementos al final de la lista sin precisar su contenido
		
		inline void		CopiarLista		(CListaEnlazada<tTipo> * Lista);			// Copia los elementos de Lista, al final de la lista
		inline void		Anadir			(tTipo * tElemento);						// Añade un elemento al final de la lista
		inline void		AnadirUnico		(tTipo * tElemento);						// Añade un elemento, pero si tElemento está en la lista, no lo añade

		inline void		Poner			(const int& nIndice,tTipo * tElemento);		// Almacena el elemento tElemento en la nueva posición (nIndice)

		inline bool		Buscar			(tTipo * tElemento,int &nIndice);			// TRUE si el elemento está. Devuelve su indice en nIndice. (NOTA: Encuentra la primera ocurrencia)
		inline bool		Buscar			(tTipo * tElemento);						// TRUE si el elemento está. (NOTA: Encuentra la primera ocurrencia)

		inline void		Borrar			(tTipo * tElemento);						// Elimina el elemento de lista que contenga a tElemento.
		inline void		Borrar			(const int& nIndice);						// Elimina el elemento indicado por el indice
		inline void		Limite			(int m_nNumElementos);						// Pone un limite de elementos a la lista

		inline tTipo*	Obtener			(const int& nIndice);						// Devuelve el contenido del elemento de indice nIndice
		inline int		Contar			(void);										// Cuenta el número de elementos almacenados

		inline void		Resetea	(void);												// Resetea el contenido de la lista
};

//////////////////////////////////////////////////////////////////////////////////
//                    IMPLEMENTACIÓN DE LAS FUNCIONES MIEMBROS
//////////////////////////////////////////////////////////////////////////////////

//--------------------------------------------------------------------------------
// NOMBRE: (Constructor)
// DESCRIPCION: Inicializa la lista.
// PARAMETROS: Ninguno
//--------------------------------------------------------------------------------
template<class tTipo>
CListaEnlazada<tTipo>::CListaEnlazada(void)
{	
	m_bTodoLiberado = false;
	m_nNumElementos = 0;
	m_Zona = NULL;
}

//--------------------------------------------------------------------------------
// NOMBRE: (Destructor)
// DESCRIPCION: Libera la memoria reservada 
// PARAMETROS: Ninguno
//--------------------------------------------------------------------------------
template<class tTipo>
CListaEnlazada<tTipo>::~CListaEnlazada(void)
{
	free(m_Zona);
}

//--------------------------------------------------------------------------------
// NOMBRE: LiberarTodo
// DESCRIPCION: Elimina los elementos contenidos en la lista y libera los recursos consumidos.
// PARAMETROS: Ninguno
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::LiberarTodo()
{
	register int i;
	m_bTodoLiberado=true;
	for (i=0;i<m_nNumElementos;i++) delete Obtener(i);
	delete this;
}

//--------------------------------------------------------------------------------
// NOMBRE: Resetea
// DESCRIPCION: Elimina todos los elementos de la lista
// PARAMETROS: Ninguno
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Resetea(void)
{
	m_nNumElementos = 0;
	free(m_Zona);
	m_Zona = NULL;
}

//--------------------------------------------------------------------------------
// NOMBRE: ReservarMemoria
// DESCRIPCION: Se reserva memoria para almacenar los elementos
// PARAMETROS: Ninguno
// NOTA: Habría que comprobar que si m_Zona = NULL ha habido un error al reservar
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::ReservaMemoria(void)
{																							//¿?¿?
	m_Zona = (ElementoTipo*)realloc(m_Zona,m_nNumElementos<<2);		// ElementoTipo est sensé faire 4 octets...
	// si m_Zona = NULL -> error de reserva de memoria
}

//--------------------------------------------------------------------------------
// NOMBRE: Insertar
// DESCRIPCION: Inserta nNumero elementos al final de la lista sin especificar su contenido
// PARAMETROS: 
//				int &nNumero: Numero de elementos a insertar		
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Insertar(const int& nNumero)
{
	m_nNumElementos+=nNumero;
	ReservaMemoria();
}

//--------------------------------------------------------------------------------
// NOMBRE: CopiarLista
// DESCRIPCION: Copia los elementos de "Lista" al final de la lista actual
// PARAMETROS: 
//				CListaEnlazada<tTipo> *Lista: Lista desde donde copiar los elementos
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::CopiarLista(CListaEnlazada<tTipo> * Lista)
{
	if (Lista->m_nNumElementos==0)
		return;

	int last = m_nNumElementos;
	Insertar(Lista->m_nNumElementos);
	memcpy(&m_Zona[last], Lista->m_Zona, Lista->m_nNumElementos<<2);

}

//--------------------------------------------------------------------------------
// NOMBRE: Anadir
// DESCRIPCION: Añade el elemento tElemento al final de la lista.
// PARAMETROS: 
//				tTipo *tElemento: Elemento que queremos añadir
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Anadir(tTipo * tElemento)
{
	m_nNumElementos++;
	ReservaMemoria();
	m_Zona[m_nNumElementos-1].puntero = tElemento;
}

//--------------------------------------------------------------------------------
// NOMBRE: 
// DESCRIPCION: Añade el elemento tElemento si este no está en la lista
// PARAMETROS: 
//				tTipo *tElemento: Elemento que queremos añadir
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::AnadirUnico(tTipo * tElemento)
{
	if (!Buscar(tElemento)) Anadir(tElemento);
}


//--------------------------------------------------------------------------------
// NOMBRE: Poner
// DESCRIPCION: Pone el elemento tElemento en la posición indicada por nIndice
// PARAMETROS: 
//				int &nIndice: Posición donde almacenar el elemento
//				tTipo *tElemento: Elemento que queremos almacenar
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Poner(const int& nIndice,tTipo * tElemento)
{
	m_Zona[nIndice].puntero = tElemento; 
}

// Retourne le nombre d'elements dans la Lista
//--------------------------------------------------------------------------------
// NOMBRE: Contar
// DESCRIPCION: Devuelve el número de elemntos que contiene la lista
// PARAMETROS: 
//			(RETORNO) int: Indica el número de elementos
//--------------------------------------------------------------------------------
template<class tTipo>
inline int CListaEnlazada<tTipo>::Contar(void)
{
	return m_nNumElementos;
}

// Retourne le nieme element de la Lista
//--------------------------------------------------------------------------------
// NOMBRE: Obtener
// DESCRIPCION: Devuelve el elemento almacenado en la posición nIndice
// PARAMETROS: 
//		tTipo*: Elemento contenido en la posición nIndice
//--------------------------------------------------------------------------------
template<class tTipo>
inline tTipo * CListaEnlazada<tTipo>::Obtener(const int& nIndice)
{
	return m_Zona[nIndice].puntero;
}

//--------------------------------------------------------------------------------
// NOMBRE: Buscar
// DESCRIPCION: Devuelve TRUE si el elemento está en la lista y además devuelve en
//				nIndice el índice que le corresponde.
// PARAMETROS: 
//		tTipo	*tElemento: Elemento que buscamos
//		int		&nIndice:   Devuelve el índice donde se encuentra
//		bool		(RETORNO):  Devuelve TRUE si está en la lista.
// NOTA: Encuentra la primera ocurrencia
//--------------------------------------------------------------------------------
template<class tTipo>
inline bool CListaEnlazada<tTipo>::Buscar(tTipo * tElemento,int &nIndice)
{
	if (m_nNumElementos==0)
		return false;

	register int contador=0;
	register ElementoTipo * acceso;
	
	for (acceso=m_Zona;acceso<m_Zona+m_nNumElementos;acceso++)
	{
		if (acceso->puntero == tElemento )
		{
			nIndice = contador;
			return true;
		}
		contador++;
	}
	return false;
}

//--------------------------------------------------------------------------------
// NOMBRE: Buscar
// DESCRIPCION: Devuelve TRUE si el elemento está en la lista
// PARAMETROS: 
//		tTipo	*tElemento: Elemento que queremos buscar
//		bool	(RETORNO):  Devuelve TRUE si está en la lista
// NOTA: Encuentra la primera ocurrencia
//--------------------------------------------------------------------------------
template<class tTipo>
inline bool CListaEnlazada<tTipo>::Buscar(tTipo * tElemento)
{
	if (m_nNumElementos==0)
		return false;

	register ElementoTipo * acceso;
	
	for (acceso=m_Zona;acceso<m_Zona+m_nNumElementos;acceso++)
		if (acceso->pointeur == tElemento )
			return true;

	return false;
}

//--------------------------------------------------------------------------------
// NOMBRE: Borrar
// DESCRIPCION: Elimina el primer elemento de la lista que contenga tElemento
// PARAMETROS: 
//		tTipo	*tElemento: Elemento que queremos borrar
// NOTA: Encuentra la primera ocurrencia
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Borrar(tTipo * tElemento)
{
	if (m_bTodoLiberado)	return;

	int nIndice;
	if ( Buscar(tElemento,nIndice) )	Borrar(nIndice);
}

//--------------------------------------------------------------------------------
// NOMBRE: Borrar
// DESCRIPCION: Elimina el elemento de la lista que esté en la posición nIndice
// PARAMETROS: 
//		int &nIndice: Indice del elemento a borrar
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Borrar(const int& nIndice)
{
	if (m_bTodoLiberado)	return;

	if (m_nNumElementos<2)
	{
		m_nNumElementos=0;
		free(m_Zona);
		m_Zona=NULL;
		return;
	}

	if (nIndice<m_nNumElementos-1)
		memmove(&m_Zona[nIndice],&m_Zona[nIndice+1], (m_nNumElementos-(nIndice+1))*4 );

	--m_nNumElementos;

	ReservaMemoria();
}

//--------------------------------------------------------------------------------
// NOMBRE: Limite
// DESCRIPCION: Limita el número de elemento que se pueden almacenar en la lista
//				a nNumElementos
// PARAMETROS: 
//		int	    nNumElementos: Número de elementos que se pueden almacenar
//--------------------------------------------------------------------------------
template<class tTipo>
inline void CListaEnlazada<tTipo>::Limite(int nNumElementos)
{
	this->m_nNumElementos=nNumElementos;
	ReservaMemoria();
}

#endif