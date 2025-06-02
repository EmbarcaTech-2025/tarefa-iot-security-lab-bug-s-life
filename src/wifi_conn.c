// Inclusão de bibliotecas necessárias
#include "include/wifi_conn.h"      // Arquivo de cabeçalho com definições locais
#include "pico/cyw43_arch.h"       // Biblioteca específica para hardware Wi-Fi do Raspberry Pi Pico
#include <stdio.h>                 // Biblioteca padrão para entrada/saída


void connect_to_wifi(const char *ssid, const char *password) {
    // Inicializa o hardware Wi-Fi
    if (cyw43_arch_init()) {
        printf("Erro ao iniciar Wi-Fi\n");
        return;  // Sai da função se a inicialização falhar
    }

    // Configura o modo estação (cliente Wi-Fi)
    cyw43_arch_enable_sta_mode();

    // Tenta conectar à rede Wi-Fi com timeout de 30 segundos
    if (cyw43_arch_wifi_connect_timeout_ms(ssid, password, CYW43_AUTH_WPA2_AES_PSK, 30000)) {
        printf("Erro ao conectar\n");  // Mensagem de falha na conexão
    } else {        
        printf("Conectado ao Wi-Fi\n");  // Mensagem de sucesso
    }
}
