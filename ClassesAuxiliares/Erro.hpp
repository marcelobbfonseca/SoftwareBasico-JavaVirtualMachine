#include<string>
#include<list>

#ifndef ERRO
#define ERRO
using namespace std;

#define ENDL \n
//#define ENDL \r\n

class Erro{

	private:
		string mensagem;
		list<string> contexto;
	public:
		string GetMensagem()
		{
			string saida = "----------------------------------------------------------ENDL";
			saida += "[ERRO]";
			saida += "ENDL";
			while(contexto.size()>0)
//			for(int cont  =0; cont < contexto.size() ; cont++)
			{
				saida+= "\t";
				saida+= contexto.front();
				saida+= "ENDL";
				contexto.pop_front();
			};
			saida += "ENDL\t\t" + mensagem + "ENDL";
			return saida;
		}
		void AdicionarContexto(char const * nomeClasse, char const * nomeMetodo)
		{
			string temp = "Na classe '";
			temp += nomeClasse;
			temp += "' metodo '";
			temp += nomeMetodo;
			temp += "'";
			contexto.push_front(temp);
		}
		Erro()
		{
			mensagem= "";
		}
		Erro(string errMsg)
		{
			mensagem= errMsg;
		}
		Erro(char const * errMsg)
		{
			string temp= "";
			mensagem= temp + errMsg;
		}
		Erro(char const * errMsg, char const * classeOuNameSpaceQueLancou, char const * metodoOuFucaoQueLancou)
		{
			string temp= "";
			mensagem= temp + errMsg;
			AdicionarContexto(classeOuNameSpaceQueLancou, metodoOuFucaoQueLancou);
		}
		Erro(string const &errMsg, char const * classeOuNameSpaceQueLancou, char const * metodoOuFucaoQueLancou)
		{
			mensagem= errMsg;
			AdicionarContexto(classeOuNameSpaceQueLancou, metodoOuFucaoQueLancou);
		}
};

#endif
