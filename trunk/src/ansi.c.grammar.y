%{
#include <stdio.h>
#include <string.h>

#include "util.h"

FILE *fp_out;

#define YYSTYPE_IS_DECLARED

typedef union{
	int i;
	char *s;
	parameter_declaration pd;
	init_declarator id;
	init_declarator_list lid;
	expression expr;
	COperator cop;
} YYSTYPE;



YYSTYPE yylval;


/*ANSI C требует длинны идентификатора до 63 символов*/
static char current_identifier[64];
static function current_function;
static char declaration_specifiers_buffer[1024];

%}



%union
{
	int n;
	char *s;
}



%token<s> IDENTIFIER
%token CONSTANT STRING_LITERAL SIZEOF
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type<s> declarator direct_declarator declaration_specifiers type_specifier specifier_qualifier_list type_name
%type<pd> parameter_declaration
%type<id> init_declarator
%type<lid> init_declarator_list

%type<cop> unary_operator;

%type<expr> primary_expression postfix_expression unary_expression assignment_expression cast_expression multiplicative_expression
%type<expr> additive_expression shift_expression relational_expression equality_expression conditional_expression
%type<expr> and_expression  exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression 


%start translation_unit 
%%

primary_expression
	: IDENTIFIER 
	{
		$$.result_name = $1;
	}
	| CONSTANT
	| STRING_LITERAL
	| '(' expression ')'
	;

postfix_expression
	: primary_expression
	{
		$$.result_name = $1.result_name;
	}
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')'
	| postfix_expression '(' argument_expression_list ')'
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	{
		const char *const new_name = function_copy_var(&current_function, $1.result_name);
		char *tmp;

		if(new_name == NULL)
		{
			//обдумать поведение в данном случае
			yyerror("error: variable not exists");
		}
	
		if((tmp = (char *)malloc(sizeof(char) * (strlen($1.result_name) + strlen(new_name) + 16))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "mov %s, %s", new_name, $1.result_name);
		function_add_command(&current_function, tmp);

		sprintf(tmp, "add %s, 1", $1.result_name);
		function_add_command(&current_function, tmp);
		free(tmp);

		$$.result_name = $1.result_name;

		if(($$.result_name = (char *) realloc($1.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$.result_name, new_name);			
	}
	| postfix_expression DEC_OP
	{
		const char *const new_name = function_copy_var(&current_function, $1.result_name);
		char *tmp;

		if(new_name == NULL)
		{
			//обдумать поведение в данном случае
			yyerror("error: variable not exists");
		}
	
		if((tmp = (char *)malloc(sizeof(char) * (strlen($1.result_name) + strlen(new_name) + 16))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "mov %s, %s", new_name, $1.result_name);
		function_add_command(&current_function, tmp);

		sprintf(tmp, "sub %s, 1", $1.result_name);
		function_add_command(&current_function, tmp);
		free(tmp);

		$$.result_name = $1.result_name;

		if(($$.result_name = (char *) realloc($1.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$.result_name, new_name);	
	}
	;

argument_expression_list
	: assignment_expression
	| argument_expression_list ',' assignment_expression
	;

unary_expression
	: postfix_expression
	{
		$$.result_name = $1.result_name;
	}
	| INC_OP unary_expression
	{
		char *tmp;

		if((tmp = (char *)malloc(sizeof(char) * (strlen($2.result_name) + 16))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "add %s, 1", $2.result_name);
		function_add_command(&current_function, tmp);
		free(tmp);

		$$.result_name = $2.result_name;
	}
	| DEC_OP unary_expression
	{
		char *tmp;

		if((tmp = (char *)malloc(sizeof(char) * (strlen($2.result_name) + 16))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "sub %s, 1", $2.result_name);
		function_add_command(&current_function, tmp);
		free(tmp);

		$$.result_name = $2.result_name;		
	}
	| unary_operator cast_expression
	{
		const char *const new_name = function_copy_var(&current_function, $2.result_name);
		char *tmp;

		if(new_name == NULL)
		{
			//обдумать поведение в данном случае
			yyerror("error: variable not exists");
		}
	
		if((tmp = (char *)malloc(sizeof(char) * (strlen($2.result_name) + strlen(new_name) + 64))) == NULL)
			yyerror("internal error: memory allocation failed");

		switch($1)
		{
			case OP_MIN:
			{
				sprintf(tmp, "mov %s, 0", new_name);
				function_add_command(&current_function, tmp);

				sprintf(tmp, "sub %s, %s", new_name, $2.result_name);
				function_add_command(&current_function, tmp);
			
				break;
			}

			case OP_PLUS:
			{
				sprintf(tmp, "mov %s, %s", new_name, $2.result_name);
				function_add_command(&current_function, tmp);
			
				break;				
			}

			case OP_LOG_COMPL:
			{
				char *label_zero;
				char *label_end;

				if((label_zero = unique_label_name(NULL, 0)) == NULL)
					yyerror("internal error: memory allocation failed");

				if((label_end = unique_label_name(NULL, 0)) == NULL)
					yyerror("internal error: memory allocation failed");

				sprintf(tmp, "cmp 0, %s", $2.result_name);
				function_add_command(&current_function, tmp);
				sprintf(tmp, "je %s", label_zero);
				function_add_command(&current_function, tmp);
				sprintf(tmp, "mov %s, 0", new_name);
				function_add_command(&current_function, tmp);
				sprintf(tmp, "jmp %s", label_end);
				function_add_command(&current_function, tmp);

				sprintf(tmp, "%s: mov %s, 1", label_zero, new_name);
				function_add_command(&current_function, tmp);

				sprintf(tmp, "%s:", label_end);
				function_add_command(&current_function, tmp);

				free(label_zero);
				free(label_end);

				break;
			}

			case OP_NOT:
			{
				sprintf(tmp, "mov %s, %s", new_name, $2.result_name);
				function_add_command(&current_function, tmp);

				sprintf(tmp, "not %s", new_name);
				function_add_command(&current_function, tmp);
			}

			default:
				break;
		};

		free(tmp);

		if(($$.result_name = (char *) realloc($2.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");


		strcpy($$.result_name, new_name);
	}
	| SIZEOF unary_expression
	| SIZEOF '(' type_name ')'
	;

unary_operator
	: '&'
	{
	}
	| '*'
	| '+'
	{
		$$ = OP_PLUS;
	}
	| '-'
	{
		$$ = OP_MIN;
	}
	| '~'
	{
		$$ = OP_NOT;
	}
	| '!'
	{
		$$ = OP_LOG_COMPL;
	}
	;

cast_expression
	: unary_expression
	| '(' type_name ')' cast_expression
	{
		parameter_declaration pd;
		char *tmp;

		pd.init_str = NULL;

		if((pd.type = type_c_to_composite(NULL, $2, 0) )== NULL)
			yyerror("internal error: memory allocation failed");


		pd.name = unique_var_name(&current_function, pd.type);

		if(pd.name == NULL)
		{
			free(pd.type);
			yyerror("internal error: memory allocation failed");
		}
	
		if((current_function.vars = realloc(current_function.vars, 
			(current_function.nvars + 1) * sizeof(parameter_declaration))) == NULL)
		{
			free(pd.type);
			yyerror("internal error: memory allocation failed");
		}


		if((tmp = malloc(strlen(pd.name) + strlen($4.result_name) + strlen(pd.type) + strlen("mov")+ 16)) == NULL)
		{
			free(pd.type);
			yyerror("internal error: memory allocation failed");
		}

		sprintf(tmp, "mov %s, (%s)%s", pd.name, pd.type, $4.result_name);
		function_add_command(&current_function, tmp);

		free(tmp);
		free(pd.type);
		free($2);
	}
	;

multiplicative_expression
	: cast_expression
	{
		$$ = $1;
	}
	| multiplicative_expression '*' cast_expression
	{
		char *type1 = function_get_type(&current_function, $1.result_name, NULL, 0);
		char *type2 = function_get_type(&current_function, $3.result_name, NULL, 0);
		char *type = implicit_cast_type(type1, type2, NULL, 0);
		char *new_name = unique_var_name(&current_function, type);


		char *tmp;

		size_t size, size_;

		size = strlen($1.result_name);
		size_ = strlen($3.result_name);

		if(size_ > size)
			size = size_;

		if(new_name == NULL)
			yyerror("error: variable not exists");
	
		if((tmp = (char *)malloc(sizeof(char) * (size + strlen(new_name) + 64))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "mov %s, %s", new_name, $1.result_name);
		function_add_command(&current_function, tmp);

		sprintf(tmp, "mul %s, %s", new_name, $3.result_name);
		function_add_command(&current_function, tmp);

		free(tmp);
		free($3.result_name);

		if(($$.result_name = (char *) realloc($1.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$.result_name, new_name);

		free(type);
		free(type1);
		free(type2);
	}
	| multiplicative_expression '/' cast_expression
	{
		char *type1 = function_get_type(&current_function, $1.result_name, NULL, 0);
		char *type2 = function_get_type(&current_function, $3.result_name, NULL, 0);
		char *type = implicit_cast_type(type1, type2, NULL, 0);
		char *new_name = unique_var_name(&current_function, type);

		char *tmp;

		size_t size, size_;

		size = strlen($1.result_name);
		size_ = strlen($3.result_name);

		if(size_ > size)
			size = size_;

		if(new_name == NULL)
			yyerror("error: variable not exists");
	
		if((tmp = (char *)malloc(sizeof(char) * (size + strlen(new_name) + 64))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "mov %s, %s", new_name, $1.result_name);
		function_add_command(&current_function, tmp);

		sprintf(tmp, "div %s, %s", new_name, $3.result_name);
		function_add_command(&current_function, tmp);

		free(tmp);
		free($3.result_name);

		if(($$.result_name = (char *) realloc($1.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$.result_name, new_name);

		free(type);
		free(type1);
		free(type2);
	}
	| multiplicative_expression '%' cast_expression
	{
		char *type1 = function_get_type(&current_function, $1.result_name, NULL, 0);
		char *type2 = function_get_type(&current_function, $3.result_name, NULL, 0);
		char *type = implicit_cast_type(type1, type2, NULL, 0);
		char *new_name = unique_var_name(&current_function, type);

		char *tmp;

		size_t size, size_;

		size = strlen($1.result_name);
		size_ = strlen($3.result_name);

		if(size_ > size)
			size = size_;

		if(new_name == NULL)
			yyerror("error: variable not exists");
	
		if((tmp = (char *)malloc(sizeof(char) * (size + strlen(new_name) + 64))) == NULL)
			yyerror("internal error: memory allocation failed");

		sprintf(tmp, "mov %s, %s", new_name, $1.result_name);
		function_add_command(&current_function, tmp);

		sprintf(tmp, "mod %s, %s", new_name, $3.result_name);
		function_add_command(&current_function, tmp);

		free(tmp);
		free($3.result_name);

		if(($$.result_name = (char *) realloc($1.result_name, sizeof(char) * (strlen(new_name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$.result_name, new_name);

		free(type);
		free(type1);
		free(type2);
	}
	;

additive_expression
	: multiplicative_expression
	| additive_expression '+' multiplicative_expression
	| additive_expression '-' multiplicative_expression
	;

shift_expression
	: additive_expression
	| shift_expression LEFT_OP additive_expression
	| shift_expression RIGHT_OP additive_expression
	;

relational_expression
	: shift_expression
	| relational_expression '<' shift_expression
	| relational_expression '>' shift_expression
	| relational_expression LE_OP shift_expression
	| relational_expression GE_OP shift_expression
	;

equality_expression
	: relational_expression
	| equality_expression EQ_OP relational_expression
	| equality_expression NE_OP relational_expression
	;


and_expression
	: equality_expression
	| and_expression '&' equality_expression
	;

exclusive_or_expression
	: and_expression
	| exclusive_or_expression '^' and_expression
	;

inclusive_or_expression
	: exclusive_or_expression
	| inclusive_or_expression '|' exclusive_or_expression
	;

logical_and_expression
	: inclusive_or_expression
	| logical_and_expression AND_OP inclusive_or_expression
	;

logical_or_expression
	: logical_and_expression
	| logical_or_expression OR_OP logical_and_expression
	;

conditional_expression
	: logical_or_expression
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression
	| unary_expression assignment_operator assignment_expression
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression
	{
		free($1.result_name);
	}
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';'
	{
		struct init_declarator_list_element *p = $2.head;
		for(;p != NULL; p = p -> next)
		{
			char *tmp;
			if((current_function.vars = realloc(current_function.vars, 
				(current_function.nvars + 1) * sizeof(parameter_declaration))) == NULL)
				yyerror("internal error: memory allocation failed");

			parameter_declaration pd;

			if((pd.name = malloc(sizeof(char) * (strlen(p -> node -> name) + 1))) == NULL)
				yyerror("internal error: memory allocation failed");

			strcpy(pd.name, p -> node -> name);

			pd.type = type_c_to_composite(NULL, $1, 0);

			if(pd.type == NULL)
				yyerror("internal error: memory allocation failed");


			pd.init_str = NULL;

			current_function.vars[current_function.nvars] = pd;
			current_function.nvars++;
		}

		free($1);
		p = $2.head;

		for(;p != NULL; )
		{
			struct init_declarator_list_element *tmp = p;

			free(p -> node -> name);
			if(p -> node -> init_val)
				free(p -> node -> init_val);

			p = p -> next;
			free(tmp -> node);
			free(tmp);
		}

	}
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier
	{
		size_t length = strlen($1);
		length += 1;

		if(($$ = malloc(length)) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$, $1);
	}
	| type_specifier declaration_specifiers
	{
		size_t length = strlen($1);
		length += 2;
		length += strlen($2);

		if(($$ = malloc(length)) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$, $1);
		strcat($$, " ");
		strcat($$, $2);

		free($2);
	}
	| type_qualifier
	| type_qualifier declaration_specifiers
	;

init_declarator_list
	: init_declarator
	{
		struct init_declarator_list_element *tmp;
		if((tmp = malloc(sizeof(struct init_declarator_list_element))) == NULL)
			yyerror("internal error: memory allocation failed");

		if((tmp -> node = malloc(sizeof(init_declarator))) == NULL)
			yyerror("internal error: memory allocation failed");

		tmp -> node -> name = $1.name;
		tmp -> node -> init_val = $1.init_val;

		tmp -> next = NULL;
		$$.head = tmp;
	}
	| init_declarator_list ',' init_declarator
	{
		struct init_declarator_list_element *p = $1.head;
		for(;p -> next; p = p -> next);


		if((p -> next = malloc(sizeof(struct init_declarator_list_element))) == NULL)
			yyerror("internal error: memory allocation failed");

		if((p -> next -> node = malloc(sizeof(init_declarator))) == NULL)
			yyerror("internal error: memory allocation failed");

		p -> next -> node -> name = $3.name;
		p -> next -> node -> init_val = $3.init_val;

		p -> next -> next = NULL;

		$$ = $1;
	}
	;

init_declarator
	: declarator
	{
		init_declarator_set(&$$, $1, NULL);
		free($1);
	}
	| declarator '=' initializer
	{
//todo: добавить инициализацию
		init_declarator_set(&$$, $1, NULL);		
		free($1);
	}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID
	{
		$$ = "void";
	}
	| CHAR
	{
		$$ = "char";
	}
	| SHORT
	{
		$$ = "short";
	}
	| INT
	{
		$$ = "int";
	}
	| LONG
	{
		$$ = "long";
	}
//	| FLOAT
//	| DOUBLE
	| SIGNED
	{
		$$ = "signed";
	}
	| UNSIGNED
	{
		$$ = "unsigned";
	}
	| struct_or_union_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'
	| struct_or_union '{' struct_declaration_list '}'
	| struct_or_union IDENTIFIER
	;

struct_or_union
	: STRUCT
	| UNION
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	{
		if(($$ = malloc(sizeof(char) * (strlen($1) + 8 + strlen($2)))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$, $1);
		strcat($$, " ");
		strcat($$, $2);

		free($2);
	}
	| type_specifier
	{
		if(($$ = malloc(sizeof(char) * (strlen($1) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$, $1);
	}
	| type_qualifier specifier_qualifier_list
	| type_qualifier
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

type_qualifier
	: CONST
	| VOLATILE
	;

declarator
	: pointer direct_declarator
	| direct_declarator
	;

direct_declarator
	: IDENTIFIER 
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']'
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_type_list ')'
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')'
	;

pointer
	: '*'
	| '*' type_qualifier_list
	| '*' pointer
	| '*' type_qualifier_list pointer
	;

type_qualifier_list
	: type_qualifier
	| type_qualifier_list type_qualifier
	;


parameter_type_list
	: parameter_list
	| parameter_list ',' ELLIPSIS
	;

parameter_list
	: parameter_declaration
	{
		if(strcmp($1.type, ""))
		{
			if((current_function.param_types = realloc(current_function.param_types,
				(current_function.nparams + 1) * sizeof(CompositeType))) == NULL)
				yyerror("internal error: memory allocation failed");

			current_function.param_types[current_function.nparams] = type_composite_from_str($1.type);

			if((current_function.param_names = realloc(current_function.param_names,
				(current_function.nparams + 1) * sizeof(char *))) == NULL)
				yyerror("internal error: memory allocation failed");

			if((current_function.param_names[current_function.nparams] = malloc(sizeof(char) * (strlen($1.name) + 1))) == NULL)
				yyerror("internal error: memory allocation failed");

			strcpy(current_function.param_names[current_function.nparams], $1.name);

			current_function.nparams++;
		}
		free($1.type);
		free($1.name);
		free($1.init_str);

	}
	| parameter_list ',' parameter_declaration
	{
		if((current_function.param_types = realloc(current_function.param_types,
			(current_function.nparams + 1) * sizeof(CompositeType))) == NULL)
			yyerror("internal error: memory allocation failed");

		current_function.param_types[current_function.nparams] = type_composite_from_str($3.type);

		if((current_function.param_names = realloc(current_function.param_names,
			(current_function.nparams + 1) * sizeof(char *))) == NULL)
			yyerror("internal error: memory allocation failed");

		if((current_function.param_names[current_function.nparams] = malloc(sizeof(char) * (strlen($3.name) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy(current_function.param_names[current_function.nparams], $3.name);

		free($3.type);
		free($3.name);
		free($3.init_str);

		current_function.nparams++;
	}
	;

parameter_declaration
	: declaration_specifiers declarator
	{
		char *tmp;
		tmp = type_c_to_composite(NULL, $1, 0);
		parameter_declaration_set(&$$, tmp, $2, "");
		free(tmp);
		free($1);
		free($2);
	}
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	{
		char *tmp;
		tmp = type_c_to_composite(NULL, $1, 0);
		parameter_declaration_set(&$$, tmp, "", "");
		free(tmp);		
		free($1);
	}
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list
	{
		$$ = $1;
		if(($$ = malloc(sizeof(char) * (strlen($1) + 1))) == NULL)
			yyerror("internal error: memory allocation failed");

		strcpy($$, $1);
		free($1);
	}
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_type_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_type_list ')'
	;

initializer
	: assignment_expression
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement
	| expression_statement
	| selection_statement
	| iteration_statement
	| jump_statement
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}'
	| '{' statement_list '}'
	| '{' declaration_list '}'
	| '{' declaration_list statement_list '}'
	;

declaration_list
	: declaration
	| declaration_list declaration
	;

statement_list
	: statement
	| statement_list statement
	;

expression_statement
	: ';'
	| expression ';'
	;

selection_statement
	: IF '(' expression ')' statement
	| IF '(' expression ')' statement ELSE statement
	| SWITCH '(' expression ')' statement
	;

iteration_statement
	: WHILE '(' expression ')' statement
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';'
	| RETURN expression ';'
	;

translation_unit
	: external_declaration
	| translation_unit external_declaration
	;

external_declaration
	: function_definition
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement

	| declaration_specifiers declarator compound_statement
	{
		char *str;

		function_set_name(&current_function, $2);

		if(type_c_from_str($1) != C_NO_TYPE)
		{
			char buff[128];

			type_c_to_composite(buff, $1, 128);

			current_function.rettype = type_composite_from_str(buff);
		}
		else
		{
			current_function.rettype = COMPOSITE_NO_TYPE;
		}
		free($2);
		free($1);

		str = function_header(NULL, &current_function, 0);

		fprintf(fp_out, "%s\n", str);
		free(str);

		fprintf(fp_out, ".var\n");


		str = function_var(NULL, &current_function, 0);
		fprintf(fp_out, "%s", str);
		free(str);

		fprintf(fp_out, ".begin\n");
		str = function_code(NULL, &current_function, 0);
		fprintf(fp_out, "%s", str);
		free(str);
		fprintf(fp_out, ".end\n\n");

		function_free(&current_function);
		bzero(&current_function, sizeof(function));
	}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	;

%%


extern char yytext[];
extern int column;

yyerror(s)
char *s;
{
	fflush(stdout);
	printf("\n%*s\n%*s\n", column, "^", column, s);
}


int main(int argc, char **argv)
{
	FILE *fp_in;

	if(argc != 3)
	{
		fprintf(stderr, "Wrong usage. Use `%s source destination`.\n\n", argv[0]);
		return 1;
	}

	if((fp_in = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Error at opening file `%s` for reading.\n\n", argv[1]);
		return 1;
	}

	if((fp_out = fopen(argv[2], "w")) == NULL)
	{
		fprintf(stderr, "Error at opening file `%s` for writing.\n\n", argv[2]);
		return 1;
	}

	stdin = fp_in;

	bzero(&current_function, sizeof(function));

	yyparse();
	return 0;
}
