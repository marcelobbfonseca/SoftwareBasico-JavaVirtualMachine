#include<string>
#include"ClassLoader.hpp"

#ifndef JVM_HPP
#define JVM_HPP

class JVM
{
	private:
		ClassLoader classLoader;
		RuntimeDataArea runtimeDataArea;
		ExecutionEngine executionEngine;
	public:
		JVM(std::string ClassComMain, int arg, char** argv);
		//a descobrir
}

#endif
