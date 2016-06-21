#ifndef DADOS_DA_CLASSE_HPP
#define DADOS_DA_CLASSE_HPP

class DadosDaClasse
{
	private:
		string nomeDaClasse;
		vector<stributo> atributos;
		vector<metodo> metodos;
		vector<cp_info> constant_pool;
	public:
		bool MetodoExiste(string nomeDoMetodo, string descritor);
		DadosDaClasse(JavaClass *);
}

class Metodo
{
	private:
		string nomeMetodo;
		vector<uint8_t> bytecode;
		vector<Tipo> variaveisLocais;
//		Tipo tipoDeRetorno;
//		vector<Tipo> argumentos;
		string descritor;
	public:
		bool MetodoExiste(string nomeDoMetodo, string descritor);
}

#endif
