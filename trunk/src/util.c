#include "util.h"


char *type_c_to_composite(char *dst, const char *src, size_t n)
{
	if(strcmp(src, "char") == 0 || strcmp(src, "signed char") == 0)
	{
		if(dst == NULL)
		{
		 	n = strlen("schar") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "schar", n);
	}
	else if(strcmp(src, "unsigned char") == 0)
	{
		if(dst == NULL)
		{
		 	n = strlen("uchar") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "uchar", n);
	}
	else if(strcmp(src, "short") == 0 || strcmp(src, "signed short") == 0)
	{
		if(dst == NULL)
		{
		 	n = strlen("sshort") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "sshort", n);
	}
	else if(strcmp(src, "unsigned short") == 0)
	{
		if(dst == NULL)
		{
		 	n = strlen("ushort") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "ushort", n);
	}
	else if(strcmp(src, "int") == 0 || strcmp(src, "signed int") == 0)
	{
		if(dst == NULL)
		{

		 	n = strlen("sint") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "sint", n);
	}
	else if(strcmp(src, "unsigned int") == 0)
	{
		if(dst == NULL)
		{
		 	n = strlen("uint") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "uint", n);		
	}
	else 
	{
		if(dst == NULL)
		{
		 	n = 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}
		strncpy(dst, "", n);
	}

	if(strlen(src) >= n)
		dst[n-1] = '\0';


	return dst;
}
