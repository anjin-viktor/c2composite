//#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>

#include "../src/util.h"


int init_suite_UTIL(void)
{
	return 0;
}

int clean_suite_UTIL(void)
{
	return 0;
}


void type_c_to_composite_test(void)
{
	char *str;
	CU_ASSERT_TRUE((int)(str = (char *)malloc(sizeof(char) * 32)));
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed int", 32), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "long", 32), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed long", 32), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "int", 32), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "unsigned int", 32), "uint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "unsigned long", 32), "uint");



	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed char", 32), "schar");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "char", 32), "schar");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "unsigned char", 32), "uchar");

	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed short", 32), "sshort");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "short", 32), "sshort");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "unsigned short", 32), "ushort");

	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "incorrect_type", 32), "");

	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed int", 5), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed int", 4), "sin");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed int", 3), "si");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "char", 2), "s");

	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "void", 25), "");


	free(str);
	str = NULL;
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "signed int", 0), "sint");

	free(str);
}



void type_c_from_str_test(void)
{
	CU_ASSERT_EQUAL(type_c_from_str("char"), SIGNED_CHAR);
	CU_ASSERT_EQUAL(type_c_from_str("signed char"), SIGNED_CHAR);
	CU_ASSERT_EQUAL(type_c_from_str("unsigned char"), UNSIGNED_CHAR);
	CU_ASSERT_EQUAL(type_c_from_str("short"), SIGNED_SHORT);
	CU_ASSERT_EQUAL(type_c_from_str("unsigned short"), UNSIGNED_SHORT);
	CU_ASSERT_EQUAL(type_c_from_str("signed int"), SIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("int"), SIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("long"), SIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("signed long"), SIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("unsigned int"), UNSIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("unsigned long"), UNSIGNED_INT);
	CU_ASSERT_EQUAL(type_c_from_str("incorrect_type"), C_NO_TYPE);
}



void type_c_to_str_test(void)
{
	char *str;
	CU_ASSERT_TRUE((int)(str = (char *)malloc(sizeof(char) * 64)));

	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_CHAR, 64), "signed char");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, UNSIGNED_CHAR, 64), "unsigned char");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_SHORT, 64), "signed short");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, UNSIGNED_SHORT, 64), "unsigned short");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_INT, 64), "signed int");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, UNSIGNED_INT, 64), "unsigned int");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, C_NO_TYPE, 64), "");

	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_CHAR, 5), "sign");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_CHAR, 2), "s");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_CHAR, 1), "");
	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_CHAR, 0), "");

	free(str);
	str = NULL;

	CU_ASSERT_STRING_EQUAL(type_c_to_str(str, SIGNED_INT, 0), "signed int");

	free(str);
}



void type_composite_from_str_test(void)
{
	CU_ASSERT_EQUAL(type_composite_from_str("schar"), SCHAR);
	CU_ASSERT_EQUAL(type_composite_from_str("uchar"), UCHAR);
	CU_ASSERT_EQUAL(type_composite_from_str("sshort"), SSHORT);
	CU_ASSERT_EQUAL(type_composite_from_str("ushort"), USHORT);
	CU_ASSERT_EQUAL(type_composite_from_str("sint"), SINT);
	CU_ASSERT_EQUAL(type_composite_from_str("uint"), UINT);
	CU_ASSERT_EQUAL(type_composite_from_str("mod8"), MOD8);
	CU_ASSERT_EQUAL(type_composite_from_str("mod16"), MOD16);
	CU_ASSERT_EQUAL(type_composite_from_str("mod32"), MOD32);
	CU_ASSERT_EQUAL(type_composite_from_str("incorrect"), COMPOSITE_NO_TYPE);
}



void type_composite_to_str_test(void)
{
	char *dst;
	CU_ASSERT_TRUE((int)(dst = (char *)malloc(sizeof(char) * 16)));

	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, SCHAR, 16), "schar");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, UCHAR, 16), "uchar");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD8, 16), "mod8");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, SSHORT, 16), "sshort");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, USHORT, 16), "ushort");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD16, 16), "mod16");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, SINT, 16), "sint");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, UINT, 16), "uint");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 16), "mod32");

	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 5), "mod3");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 2), "m");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 0), "");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 1), "");
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 2), "m");

	free(dst);
	dst = NULL;
	CU_ASSERT_STRING_EQUAL(type_composite_to_str(dst, MOD32, 16), "mod32");
	free(dst);
}



void function_header_test(void)
{
	char *dst;
	char *dst_;
	CompositeType param_types[4] = {MOD32, UCHAR, SSHORT, SINT};
	char *param_names[4] = {"param1", "param2", "param3", "param4"};
	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, NULL, 0};

	CU_ASSERT_TRUE((int)(dst = (char *)malloc(sizeof(char) * 1024)));

	dst = function_header(dst, &func, 1024);
	dst_ = function_header(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, ".name name");	
	CU_ASSERT_STRING_EQUAL(dst_, ".name name");	
	free(dst_);

	function_header(dst, &func, 8);
	CU_ASSERT_STRING_EQUAL(dst, ".name n");	
	function_header(dst, &func, 4);
	CU_ASSERT_STRING_EQUAL(dst, ".na");	

	function_header(dst, &func, 1);
	CU_ASSERT_STRING_EQUAL(dst, "");	

	dst_ = function_header(dst, &func, 0);
	CU_ASSERT_EQUAL(dst_, NULL);

	func.rettype = UINT;
	dst = function_header(dst, &func, 1024);
	dst_ = function_header(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, ".name name uint &__ret_val__");	
	CU_ASSERT_STRING_EQUAL(dst_, ".name name uint &__ret_val__");
	free(dst_);

	function_header(dst, &func, 8);
	CU_ASSERT_STRING_EQUAL(dst, ".name n");	

	function_header(dst, &func, 15);
	CU_ASSERT_STRING_EQUAL(dst, ".name name uin");	

	function_header(dst, &func, 18);
	CU_ASSERT_STRING_EQUAL(dst, ".name name uint &");	

	function_header(dst, &func, 24);
	CU_ASSERT_STRING_EQUAL(dst, ".name name uint &__ret_");	

	func.name = "__name__";
	func.param_types = param_types;
	func.param_names = param_names;
	func.nparams = 1;
	func.rettype = COMPOSITE_NO_TYPE;

	dst = function_header(dst, &func, 1024);
	dst_ = function_header(NULL, &func, 0);


	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1");	
	CU_ASSERT_STRING_EQUAL(dst_, ".name __name__ mod32 param1");
	free(dst_);

	function_header(dst, &func, 16);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ ");	

	function_header(dst, &func, 20);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod3");	

	function_header(dst, &func, 21);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32");	

	function_header(dst, &func, 22);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 ");	

	function_header(dst, &func, 24);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 pa");	

	function_header(dst, &func, 28);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1");	

	func.nparams = 4;

	dst = function_header(dst, &func, 1024);
	dst_ = function_header(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1, uchar param2, sshort param3, sint param4");	
	CU_ASSERT_STRING_EQUAL(dst_, ".name __name__ mod32 param1, uchar param2, sshort param3, sint param4");
	free(dst_);

	function_header(dst, &func, 28);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1");	

	function_header(dst, &func, 29);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1,");	

	function_header(dst, &func, 30);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1, ");	

	function_header(dst, &func, 31);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1, u");	

	function_header(dst, &func, 50);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1, uchar param2, sshort");

	function_header(dst, &func, 51);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ mod32 param1, uchar param2, sshort ");

	func.rettype = SINT;

	dst = function_header(dst, &func, 1024);
	dst_ = function_header(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, mod32 param1, uchar param2, sshort param3, sint param4");	
	CU_ASSERT_STRING_EQUAL(dst_, ".name __name__ sint &__ret_val__, mod32 param1, uchar param2, sshort param3, sint param4");

	function_header(dst, &func, 32);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val_");

	function_header(dst, &func, 33);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__");

	function_header(dst, &func, 34);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__,");

	function_header(dst, &func, 35);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, ");

	function_header(dst, &func, 37);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, mo");

	function_header(dst, &func, 40);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, mod32");

	function_header(dst, &func, 41);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, mod32 ");

	function_header(dst, &func, 46);
	CU_ASSERT_STRING_EQUAL(dst, ".name __name__ sint &__ret_val__, mod32 param");

	free(dst_);
	free(dst);
}



void function_set_name_test(void)
{
	function func;

	CU_ASSERT_EQUAL(function_set_name(NULL, ""), -1);
	CU_ASSERT_EQUAL(function_set_name(&func, NULL), -1);

	CU_ASSERT_EQUAL(function_set_name(&func, "name"), 0);
	CU_ASSERT_STRING_EQUAL(func.name, "name");

	free(func.name);
}



void parameter_declaration_set_test(void)
{
	parameter_declaration pd;
	CU_ASSERT_EQUAL(parameter_declaration_set(NULL, "", "", ""), -1);
	CU_ASSERT_EQUAL(parameter_declaration_set(&pd, NULL, "", ""), -1);
	CU_ASSERT_EQUAL(parameter_declaration_set(NULL, "", NULL, ""), -1);
	CU_ASSERT_EQUAL(parameter_declaration_set(&pd, "", "", NULL), -1);

	CU_ASSERT_EQUAL(parameter_declaration_set(&pd, "type", "name", "init_str"), 0);
	CU_ASSERT_STRING_EQUAL(pd.type, "type");
	CU_ASSERT_STRING_EQUAL(pd.name, "name");
	CU_ASSERT_STRING_EQUAL(pd.init_str, "init_str");

	free(pd.type);
	free(pd.name);
	free(pd.init_str);
}



void function_var_test(void)
{
	char *dst;
	char *dst_;
	parameter_declaration pdl[] = { {"name1", "type1", NULL}, {"name2", "type2", "init2"} };
	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, NULL, 0};

	CU_ASSERT_TRUE((int)(dst = (char *)malloc(sizeof(char) * 1024)));

	dst = function_var(dst, &func, 1024);
	dst_ = function_var(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, "");
	CU_ASSERT_STRING_EQUAL(dst_, "");
	free(dst_);

	func.vars = pdl;
	func.nvars = 1;

	dst = function_var(dst, &func, 1024);
	dst_ = function_var(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n");
	CU_ASSERT_STRING_EQUAL(dst_, "\ttype1 name1\n");
	free(dst_);

	dst = function_var(dst, &func, 1);
	CU_ASSERT_STRING_EQUAL(dst, "");

	dst = function_var(dst, &func, 2);
	CU_ASSERT_STRING_EQUAL(dst, "\t");

	dst = function_var(dst, &func, 4);
	CU_ASSERT_STRING_EQUAL(dst, "\tty");

	dst = function_var(dst, &func, 7);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1");

	dst = function_var(dst, &func, 8);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 ");

	dst = function_var(dst, &func, 10);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 na");

	dst = function_var(dst, &func, 13);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1");

	dst = function_var(dst, &func, 14);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n");

	func.nvars = 2;

	dst = function_var(dst, &func, 1024);
	dst_ = function_var(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\ttype2 name2 init2\n");
	CU_ASSERT_STRING_EQUAL(dst_, "\ttype1 name1\n\ttype2 name2 init2\n");

	free(dst_);

	dst = function_var(dst, &func, 15);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\t");

	dst = function_var(dst, &func, 27);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\ttype2 name2 ");

	dst = function_var(dst, &func, 28);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\ttype2 name2 i");

	dst = function_var(dst, &func, 32);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\ttype2 name2 init2");

	dst = function_var(dst, &func, 33);
	CU_ASSERT_STRING_EQUAL(dst, "\ttype1 name1\n\ttype2 name2 init2\n");

	free(dst);
}



void init_declarator_set_test(void)
{
	init_declarator id;
	CU_ASSERT_EQUAL(init_declarator_set(&id, "name", "init_val"), 0);

	CU_ASSERT_STRING_EQUAL(id.name, "name");
	CU_ASSERT_STRING_EQUAL(id.init_val, "init_val");

	free(id.name);
	free(id.init_val);

	CU_ASSERT_EQUAL(init_declarator_set(&id, NULL, ""), -1);
	CU_ASSERT_EQUAL(init_declarator_set(NULL, "", ""), -1);

	CU_ASSERT_EQUAL(init_declarator_set(&id, "name", NULL), 0);

	CU_ASSERT_STRING_EQUAL(id.name, "name");
	CU_ASSERT_EQUAL(id.init_val, NULL);

	free(id.name);
}



void function_add_command_test(void)
{
 	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, NULL, 0};

	function_set_name(&func, "name");

	CU_ASSERT_EQUAL(func.ncommands, 0);

	CU_ASSERT_EQUAL(function_add_command(&func, "add s, 1"), 0);
	CU_ASSERT_EQUAL(func.ncommands, 1);
	CU_ASSERT_STRING_EQUAL(func.code[0], "add s, 1");

	CU_ASSERT_EQUAL(function_add_command(&func, "label: mul s1, 2"), 0);
	CU_ASSERT_EQUAL(function_add_command(&func, "label1:"), 0);
	CU_ASSERT_EQUAL(function_add_command(&func,  NULL), -1);
	CU_ASSERT_EQUAL(function_add_command(NULL,  ""), -1);

	CU_ASSERT_STRING_EQUAL(func.code[0], "add s, 1");
	CU_ASSERT_STRING_EQUAL(func.code[1], "label: mul s1, 2");
	CU_ASSERT_STRING_EQUAL(func.code[2], "label1:");
	CU_ASSERT_EQUAL(func.ncommands, 3);

	function_free(&func);
}




void function_code_test(void)
{
	char *dst;
	char *dst_;

	char *strs[] = {"l1: mov a, b", "l2: ", "ret", "call function"};

	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, strs, 0};

	CU_ASSERT_TRUE((int)(dst = (char *)malloc(sizeof(char) * 1024)));

	dst = function_code(dst, &func, 1024);
	dst_ = function_code(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, "");
	CU_ASSERT_STRING_EQUAL(dst_, "");
	free(dst_);

	func.ncommands = 1;

	dst = function_code(dst, &func, 1);
	CU_ASSERT_STRING_EQUAL(dst, "");

	dst_ = function_code(dst, &func, 0);
	CU_ASSERT_EQUAL(dst_, NULL);


	dst = function_code(dst, &func, 1024);
	dst_ = function_code(NULL, &func, 0);

	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\n");
	CU_ASSERT_STRING_EQUAL(dst_, "l1: mov a, b\n");
	free(dst_);

	dst = function_code(dst, &func, 2);
	CU_ASSERT_STRING_EQUAL(dst, "l");

	dst = function_code(dst, &func, 13);
	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b");

	dst = function_code(dst, &func, 14);
	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\n");


	func.ncommands = 4;

	dst = function_code(dst, &func, 1024);
	dst_ = function_code(NULL, &func, 1024);

	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\nl2: \nret\ncall function\n");
	CU_ASSERT_STRING_EQUAL(dst_, "l1: mov a, b\nl2: \nret\ncall function\n");
	free(dst_);

	dst = function_code(dst, &func, 14);
	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\n");

	dst = function_code(dst, &func, 15);
	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\nl");

	dst = function_code(dst, &func, 23);
	CU_ASSERT_STRING_EQUAL(dst, "l1: mov a, b\nl2: \nret\n");

	free(dst);
}





void function_get_var_test(void)
{
 	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, NULL, 0};
	parameter_declaration pdl[] = { {"name1", "type1", NULL}, {"name2", "type2", "init2"} };

	func.vars = pdl;
	func.nvars = 2;

	CU_ASSERT_EQUAL(function_get_var(&func, "name1"), &pdl[0]);
	CU_ASSERT_EQUAL(function_get_var(&func, "name2"), &pdl[1]);
	CU_ASSERT_EQUAL(function_get_var(&func, "name3"), NULL);
	CU_ASSERT_EQUAL(function_get_var(&func, NULL), NULL);
	CU_ASSERT_EQUAL(function_get_var(NULL, "name2"), NULL);
}




void  function_copy_var_test(void)
{
	CompositeType param_types[4] = {MOD32, UCHAR, SSHORT, SINT};
	char *param_names[4] = {"param1", "param2", "param3", "param4"};
 	function func = {"name", COMPOSITE_NO_TYPE, NULL, NULL, 0, NULL, 0, NULL, 0};
	parameter_declaration *pdl = malloc(2 * sizeof(parameter_declaration));
	CU_ASSERT_TRUE(pdl != NULL);

	pdl[0].name = malloc((strlen("name1") + 1) * sizeof(char));
	CU_ASSERT_TRUE(pdl[0].name != NULL);
	pdl[0].type = malloc((strlen("type1") + 1) * sizeof(char));
	CU_ASSERT_TRUE(pdl[0].type != NULL);
	pdl[0].init_str = NULL;

	pdl[1].name = malloc((strlen("name2") + 1) * sizeof(char));
	CU_ASSERT_TRUE(pdl[1].name != NULL);
	pdl[1].type = malloc((strlen("type2") + 1) * sizeof(char));
	CU_ASSERT_TRUE(pdl[1].type != NULL);
	pdl[1].init_str = malloc((strlen("init2") + 1) * sizeof(char));
	CU_ASSERT_TRUE(pdl[1].init_str != NULL);

	strcpy(pdl[0].name, "name1");
	strcpy(pdl[1].name, "name2");
	strcpy(pdl[0].type, "type1");
	strcpy(pdl[1].type, "type2");
	strcpy(pdl[1].init_str, "init2");


	func.vars = pdl;
	func.nvars = 2;

	const char * p = function_copy_var(&func, "name1"); 
	CU_ASSERT_TRUE(p != NULL);
	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "type1");


	p = function_copy_var(&func, "name2"); 
	CU_ASSERT_TRUE(p != NULL);
	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "type2");

	func.param_types = param_types;
	func.param_names = param_names;
	func.nparams = 4;

	p = function_copy_var(&func, "name1"); 
	CU_ASSERT_TRUE(p != NULL);
	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "type1");


	p = function_copy_var(&func, "name2"); 
	CU_ASSERT_TRUE(p != NULL);
	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "type2");

	p = function_copy_var(&func, "param1"); 
	CU_ASSERT_TRUE(p != NULL);

	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "mod32");


	p = function_copy_var(&func, "param4"); 
	CU_ASSERT_TRUE(p != NULL);
	CU_ASSERT_STRING_EQUAL(function_get_var(&func, p) -> type, "sint");

	p = function_copy_var(&func, "param5"); 
	CU_ASSERT_TRUE(p == NULL);

	p = function_copy_var(&func, "var"); 
	CU_ASSERT_TRUE(p == NULL);

	func.param_types = NULL;
	func.param_names = NULL;
	func.nparams = 0;

	p = function_copy_var(&func, "param1"); 
	CU_ASSERT_TRUE(p == NULL);

	func.vars = NULL;
	func.nvars = 0;

	p = function_copy_var(&func, "name1"); 
	CU_ASSERT_TRUE(p == NULL);
}




void unique_label_name_test(void)
{
	char str[32];
	char *p;

	CU_ASSERT_TRUE(unique_label_name(str, 32) != NULL);
	CU_ASSERT_TRUE((p = unique_label_name(NULL, 1)) != NULL);

	free(p);

	CU_ASSERT_EQUAL(unique_label_name(str, 10), NULL);
}
