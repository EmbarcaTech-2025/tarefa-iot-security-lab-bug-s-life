// Inclusão do arquivo de cabeçalho que contém a declaração da função
#include "include/xor_cipher.h"

/**
 * @brief Aplica cifra XOR para criptografia/decifração
 * 
 * @param input  Ponteiro para os dados de entrada (texto claro ou cifrado)
 * @param output Ponteiro para armazenar o resultado (deve ter tamanho >= len)
 * @param len    Tamanho dos dados em bytes
 * @param key    Chave de 1 byte (0-255) para operação XOR
 * 
 * @details Funcionamento da cifra XOR:
 * - Operação bit-a-bit entre cada byte do input e a chave
 * - Propriedade reversível: mesma função para cifrar e decifrar
 * 
 * @warning Limitações de segurança:
 * - Criptografia extremamente fraca (não use para proteção real de dados)
 * - Vulnerável a ataques de análise de frequência
 * - Útil apenas para:
 *   * Fins educacionais
 *   * Ofuscação básica
 *   * Implementação de protocolos simples
 * 
 * @example Exemplo de uso:
 * @code
 * uint8_t texto[5] = {'H','e','l','l','o'};
 * uint8_t cifrado[5];
 * uint8_t decifrado[5];
 * 
 * // Cifrar
 * xor_encrypt(texto, cifrado, 5, 0xAA);
 * 
 * // Decifrar (usa mesma função)
 * xor_encrypt(cifrado, decifrado, 5, 0xAA);
 * @endcode
 */
void xor_encrypt(const uint8_t *input, uint8_t *output, size_t len, uint8_t key) {
    // Loop por todos os bytes dos dados de entrada
    for (size_t i = 0; i < len; ++i) {
        // Aplica operação XOR entre o byte atual e a chave
        // XOR truth table:
        // 0 ^ 0 = 0
        // 0 ^ 1 = 1
        // 1 ^ 0 = 1
        // 1 ^ 1 = 0
        output[i] = input[i] ^ key;
        
        // Nota: Para cada bit do byte:
        // - Se igual ao bit da chave -> resultado 0
        // - Se diferente -> resultado 1
    }
}
