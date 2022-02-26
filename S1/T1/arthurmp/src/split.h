#ifndef SPLIT_H
#define SPLIT_H

/*
    - Este módulo tem por objetivo a implementação de uma função split

    - Split -> Tem por objetivo separar uma string em 1 ou mais substrings com base em
               uma outra string, que pode ou não estar presente na string a ser separada
*/

typedef void* Splited;

/*
    # Entradas:
        - String, Separator: Strings
    
    # Saídas:
        - Splited: Struct
        - NULL
    
    # Descrição:
        - string será separado em sub-strings tendo como separator como
          elemento separador de string

        - As substrings serão armazenadas em Splited, bem como a sua quantidade
        
        - string e separator devem ser != NULL e devem possuir strlen() > 0, caso
          sejam, será retornado NULL

        - É necessário desalocar a memória que será utilizada por Splited
          utilizando a função freeSplited
*/
Splited split(char *string, char *separator);

/*
	# Entradas:
		- splt: Struct
	
	# Descrição:
		- Imprime todas as substrings geradas e suas posições na matriz
*/
void printAllSubstrings(Splited splt);

/*
	# Entrada:
		- splt: Struct
	
	# Saída:
		- int: Quantidade de substrings
	
	# Descrição:
		- Retorna a quantidade de substrings armazenadas em splt
*/
int getNumSubstrings(Splited splt);

/*
	# Entradas:
		- splt: Struct
		- position: Posição da substring
	
	# Saída:
		- char *: String
	
	# Descrição:
		- Retorna a substring armazenada na posição position
*/
char *getSubstring(Splited splt, int position);

/*
	# Entrada:
		- splt: Struct
	
	# Saída:
		- char **: Array
	
	# Descrição:
		- Retorna um array contedo todas as sunstrings em splt
*/
char **getAllSubstrings(Splited splt);

/*
	# Entrada:
		- splt: Struct
	
	# Descrição:
		- Libera a memória utilizada por splt
*/
void destroySplited(Splited splt);

#endif