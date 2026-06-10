# Space Capsule Monitor IoT

Projeto desenvolvido para a Global Solution 2026 - 1º semestre, na disciplina de Computer Science.

## Integrantes
Caio Eguia Ceschini RM: 570798
Gustavo Pola Simões RM: 570114 
Pedro Henrique Lemgruber RM: 572094

## Tema

O projeto está conectado ao tema Space Connect, relacionando espaço, tecnologia e dados por meio de um sistema IoT de monitoramento para uma cápsula espacial simulada.

## Descrição do projeto

O Space Capsule Monitor IoT é um sistema embarcado desenvolvido no Tinkercad com Arduino Uno. O objetivo é monitorar variáveis físicas importantes para a segurança de uma cápsula espacial experimental.

O sistema realiza a leitura de:

- Temperatura;
- Luminosidade;
- Vibração.

As informações são exibidas em tempo real em um display LCD I2C. Caso algum valor ultrapasse os limites definidos como seguros, o sistema ativa um alerta visual e sonoro por meio de um LED vermelho e um buzzer.

## Componentes utilizados

- Arduino Uno;
- Display LCD I2C 16x2;
- Sensor TMP36 para temperatura;
- LDR para luminosidade;
- Potenciômetro para simular vibração;
- LED vermelho;
- Buzzer;
- Resistores;
- Protoboard;
- Jumpers.

## Regras de alerta

O sistema entra em alerta quando pelo menos uma das condições abaixo é verdadeira:

- Temperatura menor que 18°C ou maior que 30°C;
- Luminosidade menor que 20% ou maior que 85%;
- Vibração maior que 70%.

Quando todos os valores estão dentro dos limites, o sistema exibe o status de operação normal.

## Lógica principal

```cpp
bool tempCritica = temperatura < TEMP_MIN || temperatura > TEMP_MAX;
bool luzCritica = luminosidade < LUZ_MIN || luminosidade > LUZ_MAX;
bool vibracaoCritica = vibracao > VIB_MAX;

bool alertaGeral = tempCritica || luzCritica || vibracaoCritica;
