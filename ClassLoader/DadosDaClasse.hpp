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
		
}

class Metodo
{
	private:
		string nomeMetodo;
		vector<uint8_t> bytecode;
		vector<atributo> variaveisLocais;
		TipoDeRetorno tipoDeRetorno;
		vector<atributo> argumentos;
	public:
		
}

#endif
