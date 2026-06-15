# SIF - Sistema Inteligente de Gestão de Fluxo

**Projeto de Extensão Industrial - Bom Leite**
**Autores:** Gustavo Muniz, Pedro e Everton

---

##  Sobre o Projeto
Este projeto nasceu de uma necessidade real na fábrica da **Bom Leite**. A ideia foi criar um sistema automático e de baixo custo para monitorizar quantas pessoas estão na área de produção em simultâneo, sem precisar de alocar um funcionário para contagem manual na porta.

O "cérebro" do projeto é um ESP32 que faz a leitura da ativação de dois sensores infravermelhos industriais. Para evitar contagens duplicadas e bugs, implementámos uma lógica de **Máquina de Estados** no código.

## O que o sistema faz
- **Contagem Bidirecional:** Lê a ordem exata em que os sensores são cortados para determinar se a pessoa está a entrar ou a sair do setor.
- **Dashboard no Telemóvel:** O ESP32 envia os dados via Wi-Fi em tempo real diretamente para o painel do aplicativo **Blynk**.
- **Totalmente Autónomo:** Não necessita de estar ligado a um computador. O circuito fica ligado diretamente na tomada com uma fonte comum de 5V.

## Hardware Utilizado
- 1x Placa ESP32 (DevKit V1)
- 2x Sensores Infravermelhos E18-D80NK (Ajustados para 15cm)
- Protoboard e cabos jumpers
- Fonte de alimentação 5V (Carregador comum)

## Mapeamento de Pinos (Pinout)
- **GPIO 18:** Sensor A (Interno)
- **GPIO 19:** Sensor B (Externo)
- **VIN (5V):** Entrada positiva da fonte de alimentação
- **GND:** Barramento comum (Terra)

## Como rodar o projeto
1. Abra o ficheiro `.ino` na Arduino IDE.
2. Nas configurações de Placa, selecione **DOIT ESP32 DEVKIT V1**.
3. Instale a biblioteca **Blynk** (autor: *Volodymyr Shymanskyy*) através do Gerenciador de Bibliotecas.
4. Altere as variáveis `ssid` e `password` no código para as credenciais da sua rede Wi-Fi.
5. Insira o seu `BLYNK_AUTH_TOKEN` (gerado no painel web do Blynk) no local indicado.
6. Compile e faça o upload para a placa.
7. Para testes locais, abra o Monitor Serial na velocidade **115200 baud**.
