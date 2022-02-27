#ifndef TEXT_H
#define TEXT_H

#include"strings.h"
#include"point.h"

/*
    - Esse módulo tem por objetivo definir um texto svg

    - Todas as funções que tem text como entrada assumem text != NULL
*/

typedef void *text;

/*
    # Entrada:
        - instruction: Instrução do .geo para criar um texto
    
    # Saída:
        - text: Struct
    
    # Descrição:
        - Retorna um text com base nas instruções em instruction
*/
text newText(string instruction);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna o id de txt
*/
int getTextID(text txt);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - point: Ponto
    
    # Descrição:
        - Retorna o ponto de ancoragem de txt
*/
point getTextAnchor(text txt);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor da borda de txt
*/
string getTextBorderColor(text txt);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor de preenchimento de txt
*/
string getTextBodyColor(text txt);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a propriedade a de txt
*/
string getTextA(text txt);

/*
    # Entrada:
        - txt: Texto
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna o texto de txt
*/
string getTextTxto(text txt);

/*
    # Entrada:
        - txt: Texto
      
    # Descrição:
        - Libera a memória utilizada pro txt
*/
void destroyText(text txt);

#endif