# FIS
Sistema Inteligente de Gestão de Fluxo

# SIF - Controle de Ocupação IoT

Esse projeto nasceu de uma necessidade real no chão de fábrica da **Bom Leite**. A ideia foi criar um sistema automático e de baixo custo (gastamos uns R$ 170 no total) para monitorar quantas pessoas estão na área de produção ao mesmo tempo, sem precisar de alguém contando na porta.

O "cérebro" do projeto é um ESP32 que lê a ativação de dois sensores infravermelhos industriais. Para evitar contagens duplicadas e bugs (tipo alguém parar no meio da porta para conversar), implementamos uma lógica de máquina de estados no código.

## O que o sistema faz
- **Contagem bidirecional:** Lê a ordem em que os sensores são cortados para saber se a pessoa está entrando ou saindo do setor.
- **Dashboard no celular:** O ESP32 manda os dados via Wi-Fi em tempo real direto pro painel do aplicativo Blynk.
- **Totalmente autônomo:** Não precisa ficar plugado em um PC. O circuito fica ligado direto na tomada com uma fonte comum de 5V/2A.

## Hardware utilizado
- 1x Placa ESP32 (DevKit V1)
- 2x Sensores Infravermelhos E18-D80NK
- Protoboard e cabos jumpers
- Fonte de alimentação 5V (carregador comum)

## Como rodar o projeto
1. Abra o arquivo `.ino` na Arduino IDE.
2. Instale as bibliotecas padrão do WiFi do ESP32 e a biblioteca do Blynk.
3. Altere as variáveis `ssid` e `password` para a sua rede Wi-Fi.
4. Coloque o seu `BLYNK_AUTH_TOKEN` (gerado lá no painel do Blynk).
5. Compile e faça o upload para a placa.
