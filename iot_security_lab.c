// Bibliotecas necessárias
#include <string.h>       // Funções para manipulação de strings
#include <stdio.h>        // Funções de entrada/saída padrão
#include <time.h>         // Funções de manipulação de tempo
#include "pico/stdlib.h"  // Biblioteca padrão do Raspberry Pi Pico
#include "pico/cyw43_arch.h" // Controle do chip Wi-Fi CYW43439
#include "include/wifi_conn.h" // Conexão Wi-Fi personalizada
#include "include/mqtt_comm.h" // Comunicação MQTT personalizada
#include "include/xor_cipher.h" // Cifra XOR para ofuscação

/**
 * @brief Função principal do programa
 * 
 * @return int Código de saída (nunca retorna neste caso - loop infinito)
 * 
 * Fluxo do programa:
 * 1. Inicializa comunicação serial
 * 2. Conecta ao Wi-Fi
 * 3. Configura cliente MQTT
 * 4. Loop principal:
 *    a) Coleta timestamp
 *    b) Formata mensagem JSON
 *    c) Aplica cifra XOR
 *    d) Publica via MQTT
 *    e) Aguarda 10 segundos
 */
int main() {
    // Inicializa todas as interfaces stdio (USB/UART)
    stdio_init_all();
    
    // Conecta à rede Wi-Fi com credenciais hardcoded (NÃO RECOMENDADO para produção)
    connect_to_wifi("HAWUEI WIFI", "MaRcAl09021995");

    // Configura conexão MQTT com broker local
    // Parâmetros: client_id, broker_ip, usuario, senha
    mqtt_setup("bitdog1", "192.168.3.101", "aluno", "senha123");

    // Loop principal infinito
    while (1) {
        // Obtém timestamp atual (segundos desde 1/1/1970 - Unix time)
        time_t agora = time(NULL);

        // Formata mensagem JSON com timestamp e valor fixo de temperatura
        char mensagem_json[128];
        snprintf(mensagem_json, sizeof(mensagem_json), 
                "{\"timestamp\":%ld,\"valor\":\"26.5\"}", agora);

        // Buffer para mensagem criptografada
        uint8_t criptografada[128];
        
        // Aplica cifra XOR com chave 42 (ofuscação básica)
        xor_encrypt((uint8_t *)mensagem_json, criptografada, 
                   strlen(mensagem_json), 42);

        // Publica mensagem no tópico MQTT (não criptografado - apenas ofuscado)
        // Tópico: escola/sala1/temperatura
        // Observação: O broker/recebedor precisa saber a chave XOR para decifrar
        mqtt_comm_publish("escola/sala1/temperatura", criptografada, 
                         strlen(mensagem_json));

        // Intervalo de 10 segundos entre publicações
        sleep_ms(10000);
    }
}
