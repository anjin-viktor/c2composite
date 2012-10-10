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
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "int", 32), "sint");
	CU_ASSERT_STRING_EQUAL(type_c_to_composite(str, "unsigned int", 32), "uint");

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
	CU_ASSERT_EQUAL(type_c_from_str("unsigned int"), UNSIGNED_INT);
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


int main(int argc, char **argv)
{
	CU_pSuite psuite = NULL;

	if (CU_initialize_registry() != CUE_SUCCESS)
		return CU_get_error();

	psuite = CU_add_suite("Suite_UTIL", init_suite_UTIL, clean_suite_UTIL);
	if (psuite == NULL) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if((CU_add_test(psuite, "test of type_c_to_composite()", type_c_to_composite_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	if((CU_add_test(psuite, "test of type_c_from_str()", type_c_from_str_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	if((CU_add_test(psuite, "test of type_c_to_str()", type_c_to_str_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}


	if((CU_add_test(psuite, "test of type_composite_from_str()", type_composite_from_str_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	if((CU_add_test(psuite, "test of type_composite_to_str()", type_composite_to_str_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
