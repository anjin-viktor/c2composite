#ifndef UTIL_H_
#define UTIL_H_

/**
@file util.h
*/


#include <string.h>
#include <stdlib.h>
#include <assert.h>

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
} function;


/**
Построение строки - описания функции(.name name params). Если dst == NULL то выделяется необходимая область
памяти, в которую осуществляется копирование. В этом случае переметр n игнорируется.
@param dst - указатель на буфер для результата
@param func - указатель на обрабатываемую функцию
@param n - размер буфера
@return указатель на буфер
*/

char *function_header(char *dst, function *func, size_t n);


/**
Построение строки, описывающей секцию .var функции. Если dst == NULL то выделяется необходимая область памяти, 
в которую осуществляется копирование. В этом случае параметр n игнорируется.
@param dst - указатель на буфер для результат
@param func - указатель на функцию, для которой осуществляется построение
@param n - размер целевого буфера
@return указатель на целевой буфер
*/

char *function_var(char *dst, function *func, size_t n);



/**
Установка имени в структуру function.
@param name - устанавливаемое имя
@param func - структура для установки имени
@retval 0: успешное завершение, -1: некорректные входные значения, -2: отказ в выделении памяти
*/

int function_set_name(function *func, const char *name);



/**
Освобождение занимаемой структорой памяти
@param func - указатель на структуру, освобождение полей которой осуществляется
*/

void function_free(function *func);



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
Структура для преставления элемента списка инициализации
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
Структура для преставления списка инициализации
*/


struct init_declarator_list_element
{
	init_declarator *node;
	struct init_declarator_list_element *next;
};

typedef struct
{
	struct init_declarator_list_element *head;
} init_declarator_list;



#endif
