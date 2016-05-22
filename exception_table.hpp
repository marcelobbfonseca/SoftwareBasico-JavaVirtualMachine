#include<stdint.h>
#include<stdio.h>
//#include<vector>

#ifndef EXCEPTION_TABLE_HPP
#define EXCEPTION_TABLE_HPP

class exception_table {

    uint16_t start_pc;
    uint16_t end_pc;
    uint16_t handler_pc;
    uint16_t catch_type;

        public:

	exception_table (FILE *arq);
	~exception_table ();
	void ExibirInformacoes(void);
}

#endif
