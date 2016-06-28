 #include "JVM.hpp"
JVM::JVM(std::string classComMain)
{
	this->classLoader.SetRuntimeDataArea(&runtimeDataArea);
	
	this->runtimeDataArea.SetClassLoader(&classLoader);
	this->runtimeDataArea.SetExecutionEngine(&executionEngine);

	this->executionEngine.SetRuntimeDataArea(&runtimeDataArea);

	executionEngine.Play(classComMain);
}

