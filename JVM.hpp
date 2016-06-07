#include <string>
#include "ClassLoader.hpp"

#ifndef JVM_HPP
#define JVM_HPP

class JVM
{
	private:
		ClassLoader classLoader;
		RuntimeDataArea runtimeDataArea;
		ExecutionEngine executionEngine;
	public:
		JVM(std::string ClassComMain, int argc, char** argv);
		JVM(std::string ClassComMain);
		
		//a descobrir
}

#endif
