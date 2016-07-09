public class numeros
{
	double AtributoDouble= -10.123;
	static float AtributoFloat= 5.456f;
	public int AtributoInteiro =10;
	long AtributoLong= 50;
	public static void main(String[] args)
	{
		double temporatioDouble= 15.123;
		float temporarioFloat= -50.456f;
		int temporarioInt =190;
		long temporarioLong= 550;
		numeros n= new numeros();
		n.incrementaEdecrementa();
	}
	public void incrementaEdecrementa()
	{
		AtributoInteiro++;
		AtributoLong--;
		AtributoFloat= AtributoFloat-2;
		AtributoDouble=AtributoDouble-2;
		for(int cont =0; cont < 50; cont++)
		{
			cont--;
			cont++;
		}
	}
}
