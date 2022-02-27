#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"forms.h"
#include"circle.h"
#include"rectangle.h"
#include"line.h"
#include"text.h"

typedef struct _form {
    string type;
    void *details;
}FORM;

form newForm(string instruction) {
    if(instruction == NULL) return NULL;

    FORM *f = (FORM *) malloc(sizeof(FORM));
    if(f == NULL) {
        printf("ERROR: Could not allocate memory for form\n");
        exit(EXIT_FAILURE);
    }

    if(instruction[0] == 'c') {
        f->type = copyString("círculo");
        f->details = newCircle(instruction);
    }
    else if(instruction[0] == 'r') {
        f->type = copyString("retângulo");
        f->details = newRectangle(instruction);
    }
    else if(instruction[0] == 'l') {
        f->type = copyString("reta");
        f->details = newLine(instruction);
    }
    else if(instruction[0] == 't') {
        f->type = copyString("texto");
        f->details = newText(instruction);
    }
    else {
        printf("WARNING: Invalid form\n");
        return NULL;
    }

    return f;
}

llist formsList(llist instructions) {
    if(instructions == NULL) return NULL;

    llist lst = NewList();

    for(item i = GetFirstItem(instructions); i != NULL; i = GetNextItem(i))
        InsertEnd(lst, newForm(GetItemElement(i)));
    
    return lst;
}

string getFormType(form format) {
    if(format == NULL) return NULL;

    FORM *f = (FORM *) format;

    return f->type;
}

void *getFormInfo(form format) {
    if(format == NULL) return NULL;

    FORM *f = (FORM *) format;

    return f->details;
}

void destroyForm(form format) {
    if(format == NULL) return;

    FORM *f = (FORM *) format;

    if(strcmp(f->type, "círculo") == 0) destroyCircle(f->details);
    if(strcmp(f->type, "retângulo") == 0) destroyRectangle(f->details);
    if(strcmp(f->type, "reta") == 0) destroyLine(f->details);
    if(strcmp(f->type, "text") == 0) destroyText(f->details);

    free(f->type);
    free(f);
    f = NULL;
    format = NULL;
}