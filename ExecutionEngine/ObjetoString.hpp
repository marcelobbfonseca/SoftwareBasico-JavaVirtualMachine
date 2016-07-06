#ifndef OBJETO_STRING_HPP
#define OBJETO_STRING_HPP
#include "Objeto.hpp"
#include <string>

using namespace std;

class ObjetoString: public Objeto
{
	public:
		ObjetoString(string s = "");
		~ObjetoString();
		string ObterString(void);
		void SetString(string s);
		TipoObjeto ObterTipoObjeto(void);
	private:
		string stringInterna;
};

#endif
