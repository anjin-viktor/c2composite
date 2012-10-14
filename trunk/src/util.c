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
	else if(strcmp(src, "int") == 0 || strcmp(src, "signed int") == 0 || strcmp(src, "signed long") == 0 || strcmp(src, "long") == 0)
	{
		if(dst == NULL)
		{

		 	n = strlen("sint") + 1;
			if((dst = (char *) malloc(sizeof(char) * n)) == NULL)
				return NULL;
		}

		strncpy(dst, "sint", n);
	}
	else if(strcmp(src, "unsigned int") == 0 || strcmp(src, "unsigned long") == 0)
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
	else if(strcmp(str, "signed int") == 0 || strcmp(str, "int") == 0 || strcmp(str, "signed long") == 0 || strcmp(str, "long") == 0)
		return SIGNED_INT;
	else if(strcmp(str, "unsigned int") == 0 || strcmp(str, "unsigned long") == 0)
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


static size_t size_of_function_header(function *func)
{
	char *type_buff;
	int i;
	size_t n = 0;
	n += strlen(".name ");
	n += strlen(func -> name);
	n += 2;

	for(i=0; i<func -> nparams; i++)
	{
		type_buff = type_composite_to_str(NULL, func -> param_types[i], 0);
		n += strlen(type_buff);
		free(type_buff);

		n += strlen(func -> param_names[i]);
		n += strlen(", ");
		n += 8;
	}

	if(func -> rettype != COMPOSITE_NO_TYPE)
	{
		type_buff = type_composite_to_str(NULL, func -> rettype, 0);
		n += strlen(type_buff);
		n += 4;
		free(type_buff);
		n += strlen("&__ret_val__");
	}

	n += 16;
	return n;
}


char *function_header(char *dst, function *func, size_t n)
{
	size_t len;
	size_t cur_len;
	char *type_buff;
	char flag = 0;
	int i=0;

	if(dst == NULL)
	{
		n = size_of_function_header(func);
		if((dst = malloc(sizeof(char) * n)) == NULL)
			return NULL;
	}
	else if(n == 1)
	{
		dst[0] = '\0';
		return dst;
	}
	else if(n == 0)
		return NULL;


	dst[0] = '\0';
	len = 0;

	strncpy(dst, ".name ", n);
	cur_len = strlen(".name ");


	if(cur_len > n)
	{
		dst[len+n-1] = '\0';
		return dst;
	}

	len += cur_len;
	n -= cur_len;

	strncpy(dst + len, func -> name, n);
	cur_len = strlen(func -> name);

	if(cur_len > n)
	{
		dst[len+n-1] = '\0';
		return dst;
	}

	len += cur_len;
	n -= cur_len;

	flag = 0;

	if(func -> rettype != COMPOSITE_NO_TYPE)
	{
		strncpy(dst + len, " ", n);
		cur_len = strlen(" ");
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;

		type_buff = type_composite_to_str(NULL, func -> rettype, 0);

		strncpy(dst + len, type_buff, n);
		cur_len = strlen(type_buff);
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;
	
		free(type_buff);

		strncpy(dst + len, " &__ret_val__", n);
		cur_len = strlen(" &__ret_val__");
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;
		flag = 1;
	}


	for(i=0; i<func -> nparams; i++, flag=1)
	{
		if(flag)
		{
			strncpy(dst + len, ", ", n);
			cur_len = strlen(", ");
			if(cur_len > n)
			{
				dst[len+n-1] = '\0';
				return dst;
			}
			n -= cur_len;
			len += cur_len;
		}
		else
		{
			strncpy(dst + len, " ", n);
			cur_len = strlen(" ");
			if(cur_len > n)
			{
				dst[len+n-1] = '\0';
				return dst;
			}
			n -= cur_len;
			len += cur_len;

		}

		type_buff = type_composite_to_str(NULL, func -> param_types[i], 0);

		strncpy(dst + len, type_buff, n);		
		cur_len = strlen(type_buff);
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;

		free(type_buff);

		strncpy(dst + len, " ", n);
		cur_len = strlen(" ");
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;

		strncpy(dst + len, func -> param_names[i], n);
		cur_len = strlen(func -> param_names[i]);
		if(cur_len > n)
		{
			dst[len+n-1] = '\0';
			return dst;
		}
		len += cur_len;
		n -= cur_len;

		flag = 1;
	}

	return dst;
}




int function_set_name(function *func, const char *name)
{
	if(name == NULL || func == NULL)
		return -1;

	if((func -> name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
		return -2;

	strcpy(func -> name, name);

	return 0;
}



int parameter_declaration_set(parameter_declaration *pd, const char *type, const char *name, const char *init_str)
{
	if(pd == NULL || type == NULL || name == NULL || init_str == NULL)
		return -1;

	if((pd -> name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
		return -2;

	if((pd -> type = malloc((strlen(type) + 1) * sizeof(char))) == NULL)
	{
		free(pd -> name);
		return -2;
	}

	if((pd -> init_str = malloc((strlen(init_str) + 1) * sizeof(char))) == NULL)
	{
		free(pd -> name);
		free(pd -> type);
		return -2;
	}

	strcpy(pd -> name, name);
	strcpy(pd -> type, type);
	strcpy(pd -> init_str, init_str);

	return 0;
}




void function_free(function *func)
{
	int i;

	if(func -> name)
		free(func -> name);

	if(func -> param_types)
		free(func -> param_types);

	for(i=0; i<func -> nparams; i++)
		free(func -> param_names[i]);

	if(func -> param_names)
		free(func -> param_names);

	for(i=0; i<func -> nvars; i++)
	{
		if(func -> vars[i].name)
			free(func -> vars[i].name);

		if(func -> vars[i].type)
			free(func -> vars[i].type);

		if(func -> vars[i].init_str)
			free(func -> vars[i].init_str);
	}

	free(func -> vars);

	bzero(func, sizeof(function));
}





static size_t size_of_function_var(function *func)
{
	int i;
	size_t res = 0;
	for(i=0; i<func -> nvars; i++)
	{
		assert(func -> vars[i].type);

		res += strlen(func -> vars[i].type) + 1;

		if(func -> vars[i].name)
			res += strlen(func -> vars[i].name) + 1;
	
		if(func -> vars[i].init_str)
			res += strlen(func -> vars[i].init_str) + 1;

		res += 1;
	}
	res += 1;
	return res;
}



char *function_var(char *dst, function *func, size_t n)
{
	int i;
	size_t pos = 0, len;

	if(dst == NULL)
	{
		n =  size_of_function_var(func);
		if((dst = malloc(sizeof(char) * n)) == NULL)
			return NULL;
	}
	else if(n == 1)
	{
		dst[0] = '\0';
		return dst;
	}
	else if(n == 0)
		return NULL;

	for(i=0; i<func -> nvars; i++)
	{
		strcpy(dst + pos++, "\t");

		if(pos == n)
		{
			*(dst + n - 1) = '\0';			
			return dst;
		}

		assert(func -> vars[i].type);

		strncpy(dst + pos, func -> vars[i].type, n - pos);

		pos += strlen(func -> vars[i].type);

		if(pos >= n)
		{
			*(dst + n - 1) = '\0';
			return dst;
		}

		if(func -> vars[i].name)
		{
			strcpy(dst + pos++, " ");

			if(pos == n)
			{
				*(dst + n - 1) = '\0';
				return dst;
			}

			strncpy(dst + pos, func -> vars[i].name, n - pos);

			pos += strlen(func -> vars[i].name);

			if(pos >= n)
			{
				*(dst + n - 1) = '\0';
				return dst;
			}
		}

		if(func -> vars[i].init_str)
		{
			strcpy(dst + pos++, " ");

			if(pos == n)
			{
				*(dst + n - 1) = '\0';
				return dst;
			}

			strncpy(dst + pos, func -> vars[i].init_str, n - pos);

			pos += strlen(func -> vars[i].init_str);

			if(pos >= n)
			{
				*(dst + n - 1) = '\0';
				return dst;
			}
		}

		strcpy(dst + pos++, "\n");

		if(pos == n)
		{
			*(dst + n - 1) = '\0';
			return dst;
		}
	}

	if(func -> nvars == 0)
		dst[0] = '\0';

	return dst;
}
