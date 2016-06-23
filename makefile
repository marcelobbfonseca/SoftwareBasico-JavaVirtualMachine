compilador = g++
flags = -Wall -pedantic -g -std=c++11
arquivoSaida = -o JVM.out
classesAuxiliares = ClassesAuxiliares/JavaClass.cpp ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Opcode.cpp
classLoader = ClassLoader/field_info.cpp ClassLoader/cp_info.cpp ClassLoader/method_info.cpp ClassLoader/attribute_info.cpp
INC_HPP = -IClassesAuxiliares -IClassLoader
executavel:
	$(compilador)  main.cpp $(classesAuxiliares) $(classLoader) $(flags) $(arquivoSaida) $(INC_HPP)
.PHONY: gcc
gcc:
	$(eval compilador = gcc)
	$(eval flags += -lstdc++)
.PHONY: windows
windows:
	$(eval arquivoSaida = -o JVM.exe)
