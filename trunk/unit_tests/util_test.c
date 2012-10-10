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

	CU_ASSERT_STRING_EQUAL(type_c_to_composite(NULL, "signed int", 0), "sint");

	free(str);
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

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
