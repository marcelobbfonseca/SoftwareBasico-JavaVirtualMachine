compilador = g++
flags = -Wall -pedantic -g
arquivoSaida = -o JVM.out
executavel:
	$(compilador) JavaClass.cpp field_info.cpp cp_info.cpp method_info.cpp attribute_info.cpp main.cpp Leitura.cpp Endian.cpp Buffer.cpp $(flags) $(arquivoSaida)
.PHONY: gcc
gcc:
	$(eval compilador = gcc)
	$(eval flags += -lstdc++)
.PHONY: windows
windows:
	$(eval arquivoSaida = -o JVM.exe)
