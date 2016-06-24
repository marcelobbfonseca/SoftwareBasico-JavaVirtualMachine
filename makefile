compilador = g++
flags = -Wall -pedantic -g -std=c++11
arquivoSaida = -o JVM.out
classesAuxiliares = ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Opcode.cpp
classLoader = ClassLoader.cpp
javaClass = JavaClass/field_info.cpp JavaClass/cp_info.cpp JavaClass/method_info.cpp JavaClass/attribute_info.cpp JavaClass/JavaClass.cpp
executionEngine = ExecutionEngine/ExecutionEngine.cpp
mainJVM = main.cpp JVM.cpp
INC_HPP = -IClassesAuxiliares -IClassLoader -IJavaClass
executavel: ClassesAuxiliares.o ClassLoader.o ExecutionEngine.o JavaClass.o RuntimeDataArea.o mainJVM.o
	$(compilador) ClassesAuxiliares.o ClassLoader.o ExecutionEngine.o JavaClass.o RuntimeDataArea.o mainJVM.o $(classesAuxiliares) $(classLoader) $(flags) $(arquivoSaida) $(INC_HPP)
.PHONY: gcc
gcc:
	$(eval compilador = gcc)
	$(eval flags += -lstdc++)
.PHONY: windows
windows:
	$(eval arquivoSaida = -o JVM.exe)
ClassesAuxiliares.o: ClassesAuxiliares/AnalisadorArgumentos.hpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Buffer.hpp ClassesAuxiliares/Easter.hpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Endian.hpp ClassesAuxiliares/Erro.hpp ClassesAuxiliares/JavaClass.cpp ClassesAuxiliares/JavaClass.hpp ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Leitura.hpp ClassesAuxiliares/Opcode.cpp ClassesAuxiliares/Opcode.hpp ClassesAuxiliares/UtilidadesParaString.hpp
	$(compilador) $(classesAuxiliares) $(flags) $(INC_HPP) -o ClassesAuxiliares.o
ClassLoader.o: ClassLoader.cpp ClassLoader.hpp
	$(compilador) $(classLoader) $(flags) $(INC_HPP) -o ClassLoader.o
ExecutionEngine.o: ExecutionEngine.cpp ExecutionEngine.hpp
	$(compilador) $(executionEngine) $(flags) $(INC_HPP) -o ExecutionEngine.o
JavaClass.o: atribute_info.cpp atribute_info.hpp cp_info.cpp cp_info.hpp field_info.cpp field_info.hpp JavaClass.cpp JavaClass.hpp method_info.cpp method_info.hpp
	$(compilador) $(javaClass) $(flags) $(INC_HPP) -o JavaClass.o
RuntimeDataArea.o: DadosInstancia.cpp DadosInstancia.hpp Frame.cpp  Frame.hpp RuntimeDataArea.cpp RuntimeDataArea.hpp Tipos.h 
	$(compilador) $(runtimeDataArea) $(flags) $(INC_HPP) -o RuntimeDataArea.o
mainJVM.o: JVM.hpp JVM.cpp main.cpp
	$(compilador) $(mainJVM) $(flags) $(INC_HPP) -o mainJVM.o
	


