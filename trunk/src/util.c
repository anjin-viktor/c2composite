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




CType type_c_from_str(const char *str)
{
	if(strcmp(str, "signed char") == 0 || strcmp(str, "char") == 0)
		return SIGNED_CHAR;
	else if(strcmp(str, "unsigned char") == 0)
		return UNSIGNED_CHAR;
	else if(strcmp(str, "signed short") == 0 || strcmp(str, "short") == 0)
		return SIGNED_SHORT;
	else if(strcmp(str, "unsigned short") == 0)
		return UNSIGNED_SHORT;
	else if(strcmp(str, "signed int") == 0 || strcmp(str, "int") == 0)
		return SIGNED_INT;
	else if(strcmp(str, "unsigned int") == 0)
		return UNSIGNED_INT;
	else 
		return C_NO_TYPE;
}



char *type_c_to_str(char *dst, CType type, size_t n)
{
	switch(type)
	{
		case SIGNED_CHAR:
			if(dst == NULL)
			{
		 		n = strlen("signed char") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "signed char", n);

			break;

		case UNSIGNED_CHAR:
			if(dst == NULL)
			{
		 		n = strlen("unsigned char") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "unsigned char", n);

			break;

		case SIGNED_SHORT:
			if(dst == NULL)
			{
		 		n = strlen("signed short") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "signed short", n);

			break;

		case UNSIGNED_SHORT:
			if(dst == NULL)
			{
		 		n = strlen("unsigned short") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "unsigned short", n);

			break;

		case SIGNED_INT:
			if(dst == NULL)
			{
		 		n = strlen("signed int") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "signed int", n);

			break;

		case UNSIGNED_INT:
			if(dst == NULL)
			{
		 		n = strlen("unsigned int") + 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "unsigned int", n);

			break;

		case C_NO_TYPE:
			if(dst == NULL)
			{
		 		n = 1;
				if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			dst[0] = '\0';
			break;
	};

	if(n > 0)
		dst[n-1] = '\0';
	else 
		dst[0] = '\0';

	return dst;
}




CompositeType type_composite_from_str(const char *str)
{
	CompositeType type = COMPOSITE_NO_TYPE;
	if(strcmp(str, "schar") == 0)
		type = SCHAR;
	else if(strcmp(str, "uchar") == 0)
		type = UCHAR;
	else if(strcmp(str, "mod8") == 0)
		type = MOD8;
	else if(strcmp(str, "sshort") == 0)
		type = SSHORT;
	else if(strcmp(str, "ushort") == 0)
		type = USHORT;
	else if(strcmp(str, "mod16") == 0)
		type = MOD16;
	else if(strcmp(str, "sint") == 0)
		type = SINT;
	else if(strcmp(str, "uint") == 0)
		type = UINT;
	else if(strcmp(str, "mod32") == 0)
		type = MOD32;

	return type;
}




char *type_composite_to_str(char *dst, CompositeType type, size_t n)
{
	switch(type)
	{
		case UCHAR:
			if(dst == NULL)
			{
				n = strlen("uchar") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "uchar", n);
			break;

		case SCHAR:
			if(dst == NULL)
			{
				n = strlen("schar") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "schar", n);
			break;

		case MOD8:
			if(dst == NULL)
			{
				n = strlen("mod8") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "mod8", n);
			break;

		case USHORT:
			if(dst == NULL)
			{
				n = strlen("ushort") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "ushort", n);
			break;

		case SSHORT:
			if(dst == NULL)
			{
				n = strlen("sshort") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "sshort", n);
			break;

		case MOD16:
			if(dst == NULL)
			{
				n = strlen("mod16") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "mod16", n);
			break;
		case UINT:
			if(dst == NULL)
			{
				n = strlen("uint") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "uint", n);
			break;

		case SINT:
			if(dst == NULL)
			{
				n = strlen("sint") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "sint", n);
			break;

		case MOD32:
			if(dst == NULL)
			{
				n = strlen("mod32") + 1;
				if((dst = (char *)malloc(sizeof(char) * n)) == NULL)
					return NULL;
			}
			strncpy(dst, "mod32", n);
			break;

		case COMPOSITE_NO_TYPE:
			if(dst == NULL)
			{
				if((dst = (char *)malloc(sizeof(char))) == NULL)
					return NULL;
			}
			dst[0] = '\0';
			break;
	};

	if(n > 0)
		dst[n-1] = '\0';
	else
		dst[0] = '\0';

	return dst;
}
