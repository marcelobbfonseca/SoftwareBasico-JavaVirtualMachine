
#include "Objeto.hpp"

class ObjetoString: public Objeto
{
	public:
		ObjetoString(string s = "");
		~ObjetoString();
		string ObterString;
		void setString(string s);
		TipoObjeto ObterTipoObjeto(void);
	private:
		string stringInterna;
}
