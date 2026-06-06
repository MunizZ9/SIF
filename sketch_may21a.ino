#define BLYNK_TEMPLATE_ID "TMPL2yL-ugS7t"
#define BLYNK_TEMPLATE_NAME "SIF Bom Leite"
#define BLYNK_AUTH_TOKEN "6-8wDBfQOztV4T0xKbJGYQ1h4Aw4WNHK"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Sala";
char pass[] = "emxm1978";

const int sensorA = 14; // Entrada
const int sensorB = 13; // Saída

int totalPessoas = 0;

// 0 = Livre, 1 = Entrando, 2 = Saindo, 3 = Bloqueio
int estado = 0; 
unsigned long tempoFiltro = 0;

BlynkTimer timer;

void enviarDadosBlynk() {
  Blynk.virtualWrite(V1, totalPessoas);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(sensorA, INPUT_PULLUP);
  pinMode(sensorB, INPUT_PULLUP);
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, enviarDadosBlynk);
  
  Serial.println("Sistema Pronto e Conectado!");
}

void loop() {
  Blynk.run();
  timer.run();
  
  int leituraA = digitalRead(sensorA); 
  int leituraB = digitalRead(sensorB);

  if (estado == 0) {
    if (leituraA == HIGH && leituraB == LOW) {
      estado = 1; //acionou a Entrada primeiro
      tempoFiltro = millis();
    } 
    else if (leituraB == HIGH && leituraA == LOW) {
      estado = 2; //acionou a Saída primeiro
      tempoFiltro = millis();
    }
  }

  // ENTRANDO
  else if (estado == 1) {
    if (leituraB == HIGH) { // Atingiu o segundo sensor
      totalPessoas++;
      Serial.print("[ENTRADA] Total na Fabrica: ");
      Serial.println(totalPessoas);
      estado = 3; // Manda para a trava de segurança
      tempoFiltro = millis();
    }
    //se colocar a mão só no A, reseta em 3s
    else if (millis() - tempoFiltro > 3000) {
      estado = 0;
    }
  }

  // SAINDO 
  else if (estado == 2) {
    if (leituraA == HIGH) { // Atingiu o primeiro sensor
      if (totalPessoas > 0) totalPessoas--;
      Serial.print("[SAÍDA] Total na Fabrica: ");
      Serial.println(totalPessoas);
      estado = 3; 
      tempoFiltro = millis();
    }
    //se colocar a mão só no B, reseta em 3s
    else if (millis() - tempoFiltro > 3000) {
      estado = 0;
    }
  }

  else if (estado == 3) {
    // O sistema volta a aceitar contagem quando a pessoa sair totalmente da frente dos DOIS sensores
    if (leituraA == LOW && leituraB == LOW) {
      delay(150); 
      estado = 0; 
    }
    // se ficar parado na porta por 5s, reseta o sistema
    else if (millis() - tempoFiltro > 5000) {
      estado = 0;
    }
  }
}