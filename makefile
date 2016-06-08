compilador = g++
flags = -Wall -pedantic -g
arquivoSaida = -o JVM.out
classesAuxiliares = ClassesAuxiliares/Leitura.cpp ClassesAuxiliares/Endian.cpp ClassesAuxiliares/Buffer.cpp ClassesAuxiliares/Opcode.cpp
classLoader = ClassLoader/JavaClass.cpp ClassLoader/field_info.cpp ClassLoader/cp_info.cpp ClassLoader/method_info.cpp ClassLoader/attribute_info.cpp
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
