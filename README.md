[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G8V_0Zaq)

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autor: **Nícolas Marçal**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Campinas, Junho de 2025

---

## Objetivo do projeto

Este projeto demonstra como implementar uma comunicação segura entre dispositivos IoT usando Raspberry Pi Pico W com a BitDogLab. A comunicação ocorre via protocolo MQTT com foco em segurança, incluindo autenticação, criptografia e defesa contra ataques de sniffing e replay.

---

## Lógica

- **Conexão Wi-Fi Segura**  
  Conexão do dispositivo à rede Wi-Fi utilizando o SDK do Raspberry Pi Pico W com suporte a WPA2.

- **Publicação MQTT**  
  Estabelecimento de conexão com o broker MQTT (Mosquitto), publicação em tópicos e tratamento de erros de conexão.

- **Autenticação no Broker**  
  Autenticação via usuário e senha configurada no Mosquitto e implementada no cliente MQTT.

- **Criptografia XOR (Ofuscação)**  
  Cifra leve para ofuscar mensagens antes do envio, dificultando leitura direta por sniffers.

- **Proteção contra Replay**  
  Inclusão de timestamp nas mensagens e verificação para garantir que mensagens antigas não sejam processadas.

### Tecnologias Utilizadas

- **Hardware:**
  - Raspberry Pi Pico W
  - Placa BitDogLab

- **Software:**
  - C/C++ (com Pico SDK)
  - lwIP + pico-mqtt-c
  - Mosquitto (broker MQTT local)
  - Wireshark (análise de tráfego)
  - VSCode + CMake

---

## Componentes:

![componentes_IOT_Security_lab](https://github.com/EmbarcaTech-2025/tarefa-iot-security-lab-bug-s-life/blob/acdecce1b7dd28a33d6422311770112644868610/assets/lista_componentes1.jpeg?raw=true)

---

## Execução

### Upload do Firmware

1. Abra o projeto no VS Code, usando o ambiente com suporte ao SDK do Raspberry Pi Pico (CMake + compilador ARM);
2. Compile o projeto normalmente (`Ctrl+Shift+B` no VS Code ou via terminal com `cmake` e `make`);
3. Conecte sua BitDogLab via cabo USB e coloque a Pico no modo de boot (pressione o botão **BOOTSEL** e conecte o cabo);
4. Copie o arquivo `.uf2` gerado para a unidade de armazenamento que aparecerá (RPI-RP2);
5. A Pico reiniciará automaticamente e começará a executar o código.

### Execução do Broker Mosquitto

6. No computador host, abra o terminal e execute o Mosquitto com autenticação configurada:
   ```bash
   mosquitto -c caminho/para/mosquitto.conf -v
7. Em outra janela de terminal, assine o tópico com autenticação:
   ```bash
   mosquitto_sub -h localhost -t escola/sala1/temperatura -u aluno -P senha123
8. Em uma terceira janela, publique uma mensagem de teste:
   ```bash
   mosquitto_pub -h localhost -t escola/sala1/temperatura -m "26.5" -u aluno -P senha123

---
## 📜 Licença
GNU GPL-3.0.
---
### sdkVersion 2.1.1
