#ifndef UTIL_H_
#define UTIL_H_

/**
@file util.h
*/


#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include <stdio.h>


static size_t unique_val;


/**
Переобразовываем строки с типом языка СИ в строку с типом архитектуры "Композит".
Если dst == NULL то выделяется буфер подходящего размера и возвращается указатель на него. В этом случае 
параметр n не рассматривается. В случае, если входная строка не является корректным значением, в dst 
занисывается строка нулевой длинны. Если не удается выделить память для результата dst устанавливается 
(и возврадается) NULL.

@param src - указатель на тип СИ
@param dst - указатель для записи результата
@param n - размер буфера для результата
@return указатель на результат
*/
 

char *type_c_to_composite(char *dst, const char *src, size_t n);


/**
Перечисление поддерживаемых типов языка СИ
*/

typedef enum  
{  
	SIGNED_CHAR,
	UNSIGNED_CHAR,
	SIGNED_SHORT,
	UNSIGNED_SHORT,
	SIGNED_INT,
	UNSIGNED_INT,
	C_NO_TYPE
} CType;


/**
Перечисление поддерживаемых типов архитектуры "Композит"
*/

typedef enum  
{  
	SCHAR,
	UCHAR,
	SSHORT,
	USHORT,
	SINT,
	UINT,
	MOD8,
	MOD16,
	MOD32,
	COMPOSITE_NO_TYPE
} CompositeType;


/**
Переобразование строки с типом языка СИ в нумерованую константу из CType.
@param src - указатель строку с СИ-типом
@return соответствующее значение CType
*/

CType type_c_from_str(const char *str);


/**
Переобразовывание значения CType в соответствующее строковое представление.
Если dst == NULL то выделяется буфер подходящего размера и возвращается указатель на него. В этом случае 
параметр n не рассматривается. Если не удается выделить память для результата dst устанавливается 
(и возвращается) NULL.


@param type - тип
@param dst - указатель для записи результата
@param type - СИ-тип
@param n - размер буфера для результата
@return указатель на результат
*/

char *type_c_to_str(char *dst, CType type, size_t n);


/**
Переобразование строки с типом архитеутуры Композит в нумерованую константу из CopositeType.
@param src - указатель строку с типом архитектуры Композит.
@return соответствующее значение CompositeType
*/

CompositeType type_composite_from_str(const char *str);


/**
Переобразовывание значения CompositeType в соответствующее строковое представление.
Если dst == NULL то выделяется буфер подходящего размера и возвращается указатель на него. В этом случае 
параметр n не рассматривается. Если не удается выделить память для результата dst устанавливается 
(и возвращается) NULL.


@param type - тип
@param dst - указатель для записи результата
@param type - тип архитектуры Композит
@param n - размер буфера для результата
@return указатель на результат
*/

char *type_composite_to_str(char *dst, CompositeType type, size_t n);

/**
Структура для представления определения переменной
*/

typedef struct 
{
	char *name;
	char *type;
	char *init_str;
} parameter_declaration;

/**
Структура для представления функций
*/

typedef struct 
{
	char *name;
	CompositeType rettype;
	CompositeType *param_types;
	char **param_names;
	size_t nparams;
	parameter_declaration *vars;
	size_t nvars;
	char **code;
	size_t ncommands;
} function;


/**
Построение строки - описания функции(.name name params). Если dst == NULL то выделяется необходимая область
памяти, в которую осуществляется копирование. В этом случае переметр n игнорируется.
@param dst - указатель на буфер для результата
@param func - указатель на обрабатываемую функцию
@param n - размер буфера
@return указатель на буфер
*/

char *function_header(char *dst, const function *func, size_t n);


/**
Построение строки, описывающей секцию .var функции. Если dst == NULL то выделяется необходимая область памяти, 
в которую осуществляется копирование. В этом случае параметр n игнорируется.
@param dst - указатель на буфер для результат
@param func - указатель на функцию, для которой осуществляется построение
@param n - размер целевого буфера
@return указатель на целевой буфер
*/

char *function_var(char *dst, const function *func, size_t n);



/**
Построение строки, описывающей секцию .code функции. Если dst == NULL то выделяется необходимая область памяти, 
в которую осуществляется копирование. В этом случае параметр n игнорируется.
@param dst - указатель на буфер для результат
@param func - указатель на функцию, для которой осуществляется построение
@param n - размер целевого буфера
@return указатель на целевой буфер
*/

char *function_code(char *dst, const function *func, size_t n);



/**
Установка имени в структуру function.
@param name - устанавливаемое имя
@param func - структура для установки имени
@retval 0: успешное завершение, -1: некорректные входные значения, -2: отказ в выделении памяти
*/

int function_set_name(function *func, const char *name);




/**
Получение указателя на переменную с требуемым именем. Если такой переменной нет возвращается NULL.
@param func - функций, для которой осуществляется поиск
@param name - имя искомой переменной
@return указатель на переменную, NULL, если она не найдена
*/

parameter_declaration *function_get_var(const function *func, const char *name);



/**
Копирование переменной с именем name в функции func во временное значение и возврат строки с именем копии. Если
переменной с требуемым именем не существует возвращается NULL.
@param func - функция, в которой осуществляется копирование
@param name - имя копируемой переменной
return указатель на имя скопированной переменной
*/

const char * const function_copy_var(function *func, const char *name);




/**
Освобождение занимаемой структорой памяти
@param func - указатель на структуру, освобождение полей которой осуществляется
*/

void function_free(function *func);


/**
Добавление строки с описанием команды к структуре function
@param func - указатель на функцию, в которую осуществляется добавление
@param str - добавляемая строка
@retval 0: успешное завершение, -1: некорректные входные значения, -2: отказ в выделении памяти
*/

int function_add_command(function *func, const char *str);



/**
Заполнение структуры parameter_declaration значениями
@param pd - указатель на заполяемую структуру
@param type - строковое представление типа
@param name - имя переменной
@param init_str - строка инициализации
@retval 0: успешное завершение, -1: некорректные входные значения, -2: отказ в выделении памяти
*/

int parameter_declaration_set(parameter_declaration *pd, const char *type, const char *name, const char *init_str);



/**
Структура для преставления узла элемента списка инициализации
*/
typedef struct 
{
	char *name;
	char *init_val;
} init_declarator;


/**
Заполнение структуры inid_declarator значениями
@param id - указатель на запалняемую структуру
@param name - строка с именем
@param init_val - строка со значением инициализации. Может принимать значение NULL
@retval 0: успешное завершение, -1: некорректные входные значения, -2: отказ в выделении памяти
*/

int init_declarator_set(init_declarator *id, const char *name, const char *init_val);


/**
Структура для преставления элемента списка инициализации
*/

struct init_declarator_list_element
{
	init_declarator *node;
	struct init_declarator_list_element *next;
};


/**
Структура для преставления списка инициализации
*/

typedef struct
{
	struct init_declarator_list_element *head;
} init_declarator_list;


/**
Структура для представления результата выражения
*/

typedef struct 
{
	char *result_name;
} expression;




/**
Перечисление операторов языка СИ
*/

typedef enum  
{  
	OP_PLUS,
	OP_MIN,
	OP_LOG_COMPL,
	OP_NOT
//....
} COperator;



/**
Получение уникального имени метки. Если buff == NULL то результат записывается в создаваемый буфер. При этом
значение n не рассматривается.
@param buff - буфер для результата
@param n - размер буфера
@return указатель на буфер, NULL в случае отказа (если буфер слишком мал для имени)
*/

char *unique_label_name(char *buff, size_t n);



#endif
