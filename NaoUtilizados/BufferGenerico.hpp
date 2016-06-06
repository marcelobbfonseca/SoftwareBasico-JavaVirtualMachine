class BufferGenerico
{
	private:
	public:
		virtual void Ler(&alvo, int quantidade de bytes, bool inverterEndian = true)=0;
};

class FileBuffer : public BufferGenerico
{
	private:
		FILE *arq;
	public:
		FileBuffer(string NomeArquivo);
		~FileBuffer();
		void Ler(&alvo, int quantidade de bytes, bool inverterEndian = true);
};
