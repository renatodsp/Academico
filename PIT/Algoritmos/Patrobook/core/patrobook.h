#ifndef PATROBOOK_H
#define PATROBOOK_H

#include <stdbool.h>

typedef struct Usuario {
    int id;
    char nome[100];
    int idade;
    
    // O Vetor de ponteiros para os amigos
    struct Usuario** amigos; 
    
    // Controles do vetor de amigos
    int num_amigos;          
    int capacidade_amigos;   
} Usuario;


typedef struct {
    Usuario** usuarios;      
    int num_usuarios;        
    int capacidade_usuarios; 
} RedeSocial;


// Inicializa a rede e os vetores globais
void inicializar_rede();

// Libera toda a memória antes do servidor desligar (Requisito obrigatório)
void liberar_memoria();

// Usuários (Retornam true se deu certo, false se deu erro, ex: ID duplicado)
bool adicionar_usuario(int id, const char* nome, int idade);
bool remover_usuario(int id);

// Amizades
bool criar_amizade(int id1, int id2);
bool remover_amizade(int id1, int id2);



// 3. FUNÇÕES GETTERS (A "Ponte" para o Python)

int get_total_usuarios();
int get_usuario_id_por_indice(int indice);
const char* get_usuario_nome(int id);
int get_usuario_idade(int id);
int get_numero_amigos(int id);
int get_amigo_id_por_indice(int id_usuario, int indice_amigo);

#endif // PATROBOOK_H