#include<string>

#ifndef ERRO
#define ERRO
using namespace std;


class Erro{

	private:
		string mensagem;
	public:
		string GetMensagem()
		{
			return mensagem;
		}
		
		Erro()
		{
			mensagem= "[ERRO]";
		}
		Erro(string errMsg)
		{
			mensagem= "[ERRO]"+ errMsg;
		}
		Erro(char const * errMsg)
		{
			string temp= "[ERRO]";
			mensagem= temp + errMsg;
		}
};

#endif
