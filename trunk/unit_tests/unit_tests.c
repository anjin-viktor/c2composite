#include <CUnit/Basic.h>
#include <stdio.h>


int init_suite_UTIL(void);
int clean_suite_UTIL(void);
void type_c_to_composite_test(void);
void type_c_from_str_test(void);
void type_c_to_str_test(void);
void type_composite_from_str_test(void);
void type_composite_to_str_test(void);
void function_header_test(void);
void function_set_name_test(void);
void parameter_declaration_set_test(void);



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

	if((CU_add_test(psuite, "test of function_header()", function_header_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	if((CU_add_test(psuite, "test of function_set_name()", function_set_name_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}

	if((CU_add_test(psuite, "test of  parameter_declaration_set()",  parameter_declaration_set_test) == NULL))
	{
		CU_cleanup_registry();
		return CU_get_error();		
	}
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
