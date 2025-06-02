/**********************************************
 * Inclusão de bibliotecas necessárias
 **********************************************/
#include "lwip/apps/mqtt.h"       // Biblioteca MQTT do lwIP
#include "include/mqtt_comm.h"    // Definições locais do MQTT
#include "lwipopts.h"             // Opções de configuração do lwIP
#include <string.h>               // Para funções de manipulação de strings
#include <stdio.h>                // Para funções de entrada/saída padrão

/**********************************************
 * Variáveis globais
 **********************************************/
static mqtt_client_t *client;     // Ponteiro para a estrutura do cliente MQTT
                                  // 'static' limita o escopo a este arquivo

/**********************************************
 * Callback de status da conexão MQTT
 **********************************************/
static void mqtt_connection_cb(mqtt_client_t *client, void *arg, 
                              mqtt_connection_status_t status) {
    // Verifica se a conexão foi aceita pelo broker
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf("Conectado ao broker MQTT com sucesso!\n");
    } else {
        // Imprime mensagem de erro com o código recebido
        printf("Falha ao conectar ao broker, codigo: %d\n", status);
    }
}

/**********************************************
 * Função de configuração inicial do cliente MQTT
 **********************************************/
void mqtt_setup(const char *client_id, const char *broker_ip, 
               const char *user, const char *pass) {
    ip_addr_t broker_addr;  // Estrutura para armazenar o endereço do broker

    // Converte o endereço IP de string para formato binário
    if (!ip4addr_aton(broker_ip, &broker_addr)) {
        printf("Erro no IP\n");  // Mensagem de erro se conversão falhar
        return;                  // Sai da função em caso de erro
    }

    // Cria uma nova instância do cliente MQTT
    client = mqtt_client_new();
    
    // Verifica se a criação do cliente foi bem-sucedida
    if (client == NULL) {
        printf("Falha ao criar o cliente MQTT\n");
        return;  // Sai da função em caso de erro
    }

    // Preenche estrutura com informações do cliente
    struct mqtt_connect_client_info_t ci = {
        .client_id = client_id,  // ID do cliente no broker
        .client_user = user,     // Usuário para autenticação
        .client_pass = pass      // Senha para autenticação
    };

    // Inicia a conexão com o broker MQTT
    mqtt_client_connect(
        client,               // Instância do cliente
        &broker_addr,         // Endereço do broker
        1883,                // Porta padrão do MQTT
        mqtt_connection_cb,  // Callback para status da conexão
        NULL,                // Argumento opcional para o callback
        &ci                  // Informações do cliente
    );
}

/**********************************************
 * Callback de confirmação de publicação
 **********************************************/
static void mqtt_pub_request_cb(void *arg, err_t result) {
    // Verifica se a publicação foi bem-sucedida
    if (result == ERR_OK) {
        printf("Publicação MQTT enviada com sucesso!\n");
    } else {
        // Imprime mensagem de erro com o código recebido
        printf("Erro ao publicar via MQTT: %d\n", result);
    }
}

/**********************************************
 * Função para publicar dados no broker MQTT
 **********************************************/
void mqtt_comm_publish(const char *topic, const uint8_t *data, size_t len) {
    // Realiza a publicação dos dados
    err_t status = mqtt_publish(
        client,               // Instância do cliente
        topic,                // Tópico de publicação
        data,                 // Dados a serem publicados
        len,                  // Tamanho dos dados
        0,                    // QoS (Quality of Service) nível 0
        0,                    // Flag retain (não reter mensagem)
        mqtt_pub_request_cb,  // Callback para confirmação
        NULL                  // Argumento opcional para o callback
    );

    // Verifica se a requisição de publicação foi aceita
    if (status != ERR_OK) {
        printf("mqtt_publish falhou ao ser enviada: %d\n", status);
    }
}
