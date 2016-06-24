compilador = g++
flags = -Wall -pedantic -g -std=c++11
arquivoSaida = -o JVM.out
INC_HPP = -IClassesAuxiliares -IClassLoader -IJavaClass -IExecutionEngine -IRuntimeDataAreas
executavel: ClassesAuxiliares.o ClassLoader.o ExecutionEngine.o JavaClass.o RuntimeDataArea.o mainJVM.o
	$(compilador) ClassesAuxiliares.o ClassLoader.o ExecutionEngine.o JavaClass.o RuntimeDataArea.o mainJVM.o $(arquivoSaida) $(INC_HPP)
.PHONY: gcc
gcc:
	$(eval compilador = gcc)
	$(eval flags += -lstdc++)
.PHONY: windows
windows:
	$(eval arquivoSaida = -o JVM.exe)
ClassesAuxiliares.o: ClassesAuxiliares/AnalisadorArgumentos.hpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Buffer.hpp ClassesAuxiliares/Easter.hpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Endian.hpp ClassesAuxiliares/Erro.hpp ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Leitura.hpp ClassesAuxiliares/Opcode.cpp ClassesAuxiliares/Opcode.hpp ClassesAuxiliares/UtilidadesParaString.hpp
	$(compilador) ClassesAuxiliares/uniao.cpp $(flags) $(INC_HPP) -o ClassesAuxiliares.o -c
ClassLoader.o: ClassLoader/ClassLoader.cpp ClassLoader/ClassLoader.hpp
	$(compilador) ClassLoader/uniao.cpp $(flags) $(INC_HPP) -o ClassLoader.o -c
ExecutionEngine.o: ExecutionEngine.cpp ExecutionEngine.hpp
	$(compilador) ExecutionEngine/uniao.cpp $(flags) $(INC_HPP) -o ExecutionEngine.o -c
JavaClass.o: atribute_info.cpp atribute_info.hpp cp_info.cpp cp_info.hpp field_info.cpp field_info.hpp JavaClass.cpp JavaClass.hpp method_info.cpp method_info.hpp
	$(compilador) JavaClass/uniao.cpp $(flags) $(INC_HPP) -o JavaClass.o -c
RuntimeDataArea.o: DadosInstancia.cpp DadosInstancia.hpp Frame.cpp  Frame.hpp RuntimeDataArea.cpp RuntimeDataArea.hpp Tipos.h 
	$(compilador) RuntimeDataAreas/uniao.cpp $(flags) $(INC_HPP) -o RuntimeDataArea.o -c
mainJVM.o: JVM.hpp JVM.cpp main.cpp
	$(compilador) main.cpp JVM.cpp $(flags) $(INC_HPP) -o mainJVM.o -c
	


