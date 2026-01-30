#ifndef __LISTA__
    #define __LISTA__

    #define ERRO -32000
    #define INICIAL 100
    #define INCREMENTO 50

    #include <stdbool.h>

    typedef struct lista_ LISTA;

    LISTA* lista_criar(); 
    bool lista_inserir(LISTA* lista, void* item, int chave);
    void* lista_remover(LISTA* lista, int chave);
    bool lista_apagar(LISTA** lista);
    void* lista_buscar(LISTA* lista, int chave);
    int lista_tamanho(LISTA* lista);
    bool lista_vazia(LISTA* lista);

#endif