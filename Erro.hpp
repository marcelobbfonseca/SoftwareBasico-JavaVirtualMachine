#ifndef ERRO

#define ERRO

class Erro{
	private:
		string mensagem;
	public:
		string GetMensagem();
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
