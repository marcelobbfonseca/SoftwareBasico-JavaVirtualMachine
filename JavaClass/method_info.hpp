#ifndef METHOD_INFO_HPP
#define METHOD_INFO_HPP

#include "attribute_info.hpp"
#include <stdint.h>
#include<stdio.h>
#include<vector>

#ifndef ATTRIBUTE_INFO
class attribute_info;
#endif
#ifndef JAVA_CLASS
class JavaClass;
#endif
#ifndef CP_INFO
class cp_info;
#endif

using namespace std;
#define METHOD_INFO
class method_info {

	private:

	uint16_t access_flags;
	uint16_t name_index;
	uint16_t descriptor_index;
	uint16_t attributes_count;
	vector<attribute_info *> attributes;

	public:

	method_info(FILE *arq, std::vector<cp_info*> const &constant_pool);
	~method_info();
	void ExibirInformacoes(string tabs, JavaClass *javaClass);
	uint16_t getNameIndex(void);
	uint16_t getDescriptorIndex(void);
	uint16_t getAccessFlags(void);
	uint16_t getAttributesCount(void);
	vector<attribute_info *> getAttributes(void);

};

#endif
