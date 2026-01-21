#include "lista.h"
#include <stdlib.h>

struct lista_{
    void** lista;
    int inicio;
    int fim;
    int tamanho;
}

LISTA* lista_criar(){
    LISTA* aux = (LISTA*)malloc(sizeof(LISTA));

    if(aux){
        aux->lista = (void**)calloc(INICIAL, sizeof(void*));
        
        if(aux->lista){
            aux->inicio = 0;
            aux->fim = aux->inicio;
            aux->tamanho = 0;

            return aux;
        }
        return NULL;
    }

return NULL;
}

int lista_tamanho(LISTA* lista){
    if(lista){
        return lista->tamanho;
    }

return ERRO;
}

bool lista_vazia(LISTA* lista){
    if(lista){
        return aux->fim == aux->inicio;
    }

return true;
}

void* lista_buscar(LISTA* lista, int chave){
    if(lista && chave < lista->fim){
        return lista->lista[chave];
    }

return NULL;
}

bool lista_apagar(LISTA** lista){
    if(*lista){
        free((*lista)->lista);
        free((*lista));

        *lista=NULL;

        return true;
    }

return false;
}

bool lista_inserir(LISTA* lista, void* item, int chave){
    if(lista && item){

    }
}