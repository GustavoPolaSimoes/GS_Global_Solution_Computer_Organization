#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0);
#define TMP36_PIN A0
#define LDR_PIN A1
#define VIB_PIN A2
#define LED_ALERTA 8
#define BUZZER 9

const float TEMP_MIN = 18.0;
const float TEMP_MAX = 30.0;

const int LUZ_MIN = 20;
const int LUZ_MAX = 85;

const int VIB_MAX = 70;

unsigned long ultimaTrocaTela = 0;
int telaAtual = 0;

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setBacklight(1);

  pinMode(LED_ALERTA, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Space Capsule");
  lcd.setCursor(0, 1);
  lcd.print("Monitor IoT");

  delay(2000);
  lcd.clear();
}

void loop() {
  int leituraTemp = analogRead(TMP36_PIN);

  float tensao = leituraTemp * (5.0 / 1023.0);
  float temperatura = (tensao - 0.5) * 100.0;

  int leituraLdr = analogRead(LDR_PIN);
  int leituraVib = analogRead(VIB_PIN);

  int luminosidade = map(leituraLdr, 0, 1023, 0, 100);
  int vibracao = map(leituraVib, 0, 1023, 0, 100);

  bool tempCritica = temperatura < TEMP_MIN || temperatura > TEMP_MAX;
  bool luzCritica = luminosidade < LUZ_MIN || luminosidade > LUZ_MAX;
  bool vibracaoCritica = vibracao > VIB_MAX;

  bool alertaGeral = tempCritica || luzCritica || vibracaoCritica;

  if (alertaGeral) {
    digitalWrite(LED_ALERTA, HIGH);
    tone(BUZZER, 1000);
  } else {
    digitalWrite(LED_ALERTA, LOW);
    noTone(BUZZER);
  }

  Serial.println("===== TELEMETRIA DA CAPSULA =====");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println(" C");

  Serial.print("Luminosidade: ");
  Serial.print(luminosidade);
  Serial.println("%");

  Serial.print("Vibracao: ");
  Serial.print(vibracao);
  Serial.println("%");

  Serial.print("Status: ");
  if (alertaGeral) {
    Serial.println("ALERTA");
  } else {
    Serial.println("NORMAL");
  }

  Serial.println();

  if (millis() - ultimaTrocaTela > 2000) {
    telaAtual++;

    if (telaAtual > 3) {
      telaAtual = 0;
    }

    ultimaTrocaTela = millis();
    lcd.clear();
  }

  if (telaAtual == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Status Capsula");

    lcd.setCursor(0, 1);
    if (alertaGeral) {
      lcd.print("ALERTA GERAL");
    } else {
      lcd.print("OPERACAO OK");
    }
  }

  else if (telaAtual == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Temperatura:");

    lcd.setCursor(0, 1);
    lcd.print(temperatura);
    lcd.print(" C");
  }

  else if (telaAtual == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Luminosidade:");

    lcd.setCursor(0, 1);
    lcd.print(luminosidade);
    lcd.print("%");
  }

  else if (telaAtual == 3) {
    lcd.setCursor(0, 0);
    lcd.print("Vibracao:");

    lcd.setCursor(0, 1);
    lcd.print(vibracao);
    lcd.print("%");
  }

  delay(300);
}