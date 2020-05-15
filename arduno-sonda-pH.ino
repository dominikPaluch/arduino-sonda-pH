// Arduino Sonda Ph numer

// ustawienie pinu połączenia
const int pinPo = A0;

void setup() {
  // komunikacja szeregowa dla portu 9600
  Serial.begin(9600);
}

void loop() {
  // zmienne pomocnicze
  int attempt[10];
  int temp;
  unsigned long int avgValue = 0;
  
  for (int i = 0; i < 10; i++) {
    attempt[i] = analogRead(pinPo);
    delay(10);
  }
  // sortowanie elementów tablicy zmierzonych wyników według wielkości
  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (attempt[i] > attempt[j]) {
        temp = attempt[i];
        attempt[i] = attempt[j];
        attempt[j] = temp;
      }
    }
  }
  // przechowywanie wyników od 2 do 8 w zmiennej, z której należy obliczyć średnią 
  // (pominięcie dwóch elementów pola na początku i na końcu dla większej dokładności)
  for (int i = 2; i < 8; i++) {
    avgValue += attempt[i];
  }
  // obliczanie pH na podstawie średniej
  // pomiar i konwersja do zakresu pH 0-14
  float avgPh = (float)avgValue * 5.0 / 1024 / 6;
  float calcPh = -5.70 * avgPh + 21.34;
  // wypisanie wyników
  Serial.print("Pomiar pH: ");
  Serial.println(calcPh);
  // opóźnienie 900ms
  delay(900);
}
