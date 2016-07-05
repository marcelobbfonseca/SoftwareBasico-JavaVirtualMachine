#ifndef OBJETO_HPP
#define OBJETO_HPP

enum TipoObjeto
{
	ARRAY,
	STRING,
	INSTANCIA
}

#define OBJETO
class Objeto
{
	public:
		virtual TipoObjeto ObterTipoObjeto(void)=0;
};

#endif
