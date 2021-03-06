#ifndef OBJETO_INSTANCIA_HPP
#define OBJETO_INSTANCIA_HPP

#include "Objeto.hpp"
#include "JavaClass.hpp"
#include "Tipos.hpp"
#include "Erro.hpp"

#define OBJETO_INSTANCIA
class ObjetoInstancia: public Objeto
{
	public:
		TipoObjeto ObterTipoObjeto(void);
		ObjetoInstancia(JavaClass *classe);
		~ObjetoInstancia();
		JavaClass *ObterJavaClass(void);//necessário?
		void ColocarValorNoCampo(string nomeDoCampo, Valor valor);
		Valor ObterValorDoCampo(string nomeDoCampo);
		bool CampoExiste(string nomeDoCampo);
	private:
		JavaClass *javaClass;//informações de qual classe esse objeto é
		map<string, Valor> atributosDeInstancia;
};

#endif
