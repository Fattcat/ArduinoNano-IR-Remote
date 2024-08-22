#include <IRremote.h>

// Definovanie pinov
const int RECV_PIN = 2;  // Pin, kde je pripojený IR prijímač
const int SEND_PIN = 3;  // Pin, kde je pripojený IR vysielač (LED)
const int BUTTON_PIN = 4; // Pin pre tlačidlo na emuláciu signálu

IRrecv irrecv(RECV_PIN);
IRsend irsend(SEND_PIN);
decode_results results;

void setup() {
  Serial.begin(9600);  // Nastavenie komunikácie pre serial monitor
  irrecv.enableIRIn();  // Začiatok prijímania IR signálov
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Nastavenie tlačidla na vstup s pullup odporom
}

unsigned long capturedCode = 0;

void loop() {
  if (irrecv.decode(&results)) {  // Ak prijmeme IR signál
    capturedCode = results.value; // Uloženie hodnoty zachyteného IR signálu
    Serial.print("Captured IR Code: ");
    Serial.println(capturedCode, HEX);  // Vypísanie zachyteného kódu v hexadecimálnom formáte
    irrecv.resume();  // Pripravenie na ďalší signál
  }

  // Ak stlačíme tlačidlo na emuláciu signálu
  if (digitalRead(BUTTON_PIN) == LOW && capturedCode != 0) {
    Serial.print("Sending IR Code: ");
    Serial.println(capturedCode, HEX);  // Vypísanie odosielaného kódu
    irsend.sendNEC(capturedCode, 32);  // Odoslanie signálu pomocou NEC protokolu (zmeniť podľa typu signálu)
    delay(500);  // Krátke čakanie, aby sme zabránili opakovaniu pri držaní tlačidla
  }
}
