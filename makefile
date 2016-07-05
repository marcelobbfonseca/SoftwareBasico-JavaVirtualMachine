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
ClassesAuxiliares.o: ClassesAuxiliares/AnalisadorArgumentos.hpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Buffer.hpp ClassesAuxiliares/Easter.hpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Endian.hpp ClassesAuxiliares/Erro.hpp ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Leitura.hpp ClassesAuxiliares/Opcode.cpp ClassesAuxiliares/Opcode.hpp ClassesAuxiliares/UtilidadesParaString.hpp ClassesAuxiliares/UtilidadesParaString.cpp
	$(compilador) ClassesAuxiliares/uniao.cpp $(flags) $(INC_HPP) -o ClassesAuxiliares.o -c
ClassLoader.o: ClassLoader/ClassLoader.cpp ClassLoader/ClassLoader.hpp
	$(compilador) ClassLoader/uniao.cpp $(flags) $(INC_HPP) -o ClassLoader.o -c
ExecutionEngine.o: ExecutionEngine/ExecutionEngine.cpp ExecutionEngine/ExecutionEngine.hpp ExecutionEngine/ObjetoArray.hpp ExecutionEngine/ObjetoArray.cpp ExecutionEngine/ObjetoInstancia.cpp ExecutionEngine/ObjetoInstancia.hpp ExecutionEngine/ObjetoString.cpp ExecutionEngine/ObjetoString.hpp
	$(compilador) ExecutionEngine/uniao.cpp $(flags) $(INC_HPP) -o ExecutionEngine.o -c
JavaClass.o: JavaClass/attribute_info.cpp JavaClass/attribute_info.hpp JavaClass/cp_info.cpp JavaClass/cp_info.hpp JavaClass/field_info.cpp JavaClass/field_info.hpp JavaClass/JavaClass.cpp JavaClass/JavaClass.hpp JavaClass/method_info.cpp JavaClass/method_info.hpp
	$(compilador) JavaClass/uniao.cpp $(flags) $(INC_HPP) -o JavaClass.o -c
RuntimeDataArea.o: RuntimeDataAreas/DadosDaInstancia.cpp RuntimeDataAreas/DadosDaInstancia.hpp RuntimeDataAreas/Frame.cpp RuntimeDataAreas/Frame.hpp RuntimeDataAreas/RuntimeDataArea.cpp RuntimeDataAreas/RuntimeDataArea.hpp RuntimeDataAreas/Tipos.h
	$(compilador) RuntimeDataAreas/uniao.cpp $(flags) $(INC_HPP) -o RuntimeDataArea.o -c
mainJVM.o: JVM.hpp JVM.cpp main.cpp
	$(compilador) uniao.cpp $(flags) $(INC_HPP) -o mainJVM.o -c
clear:
	rm -r *.o
