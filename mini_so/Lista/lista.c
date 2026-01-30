#include "lista.h"
#include <stdlib.h>

struct lista_{
    void** lista;
    int espaco;
    int num_itens;
};

LISTA* lista_criar(){
    LISTA* aux = (LISTA*)malloc(sizeof(LISTA));

    if(aux){
        aux->lista = (void**)calloc(INICIAL, sizeof(void*));
        
        if(aux->lista){
            aux->espaco = INICIAL;
            aux->num_itens = 0;

            return aux;
        }
        return NULL;
    }

return NULL;
}

int lista_numItens(LISTA* lista){
    if(lista){
        return lista->num_itens;
    }

return ERRO;
}

bool lista_vazia(LISTA* lista){
    if(lista){
        return lista->num_itens == 0;
    }

return true;
}

void* lista_buscar(LISTA* lista, int chave){
    if(lista && chave < lista->espaco){
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
        if(chave < lista->espaco){
            if(lista->lista[chave] == NULL){
                lista->lista[chave] = item;
                lista->num_itens++;

                return true;
            }
        }else{
            void** temp;
            while(!(temp = (void**)realloc(lista->lista, (lista->espaco+INCREMENTO)*sizeof(void*))));

            lista->lista = temp;

            for(int i = lista->espaco; i < (lista->espaco+INCREMENTO); i++){
                lista->lista[i] = NULL;
            }

            lista->lista[chave] = item;
            lista->espaco+=INCREMENTO;
            lista->num_itens++;

            return true;
        }
    }

return false;
}

void* lista_remover(LISTA* lista, int chave){
    if(lista && (chave < lista->espaco)){
        void* aux = lista->lista[chave];

        if(aux){
            lista->lista[chave] = NULL;
            lista->num_itens--;
        }

        return aux;
    }

return NULL;
}