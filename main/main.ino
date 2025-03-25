#include <LiquidCrystal.h>

#define BUZZER 13
#define BOTAO1 10
#define BOTAO2 9
#define BOTAO3 8
#define BOTAO4 7
#define BOTAO5 6
//defs dos botoes


#define NBUTTONS 5 // numero de botoes
#define NSONGS 5 // numero de musicas

uint8_t songsIndex = 0;//index usado para selecionar musicas

uint8_t songsList[NSONGS];// ira ficar a lista de musicas

bool first = 0;//para sair da tela inicial

bool songsSelect;//bool para selecao de tela de musicas

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5};//instancia dos botoes

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//instancia lcd

void displayHome() {
  lcd.setCursor(3, 0);
  lcd.print("Press To");
  lcd.setCursor(5, 1);
  lcd.print("Start");
}//tela inicial

void selectSong() {
  lcd.setCursor(2, 0);
  lcd.print("Select Song");
  lcd.setCursor(0, 1);
  lcd.print("<");
  lcd.setCursor(15, 1);
  lcd.print(">");
  lcd.setCursor(4, 1);
  lcd.print("Musica");
  lcd.setCursor(11, 1);
  lcd.print(songsIndex);
}//tela de selecao de musicas

void setup() {
  lcd.begin(16, 2); //inicia o lcd
  for (size_t i = 0; i < NBUTTONS; i++) {
    pinMode(nButtons[i], INPUT); //inicia todos os botoes
  }
  displayHome(); // seleciona a tela inicial
}

void loop() {
  if(!first) {
    for (size_t i = 0; i < NBUTTONS; i++) {
      bool pressed = digitalRead(nButtons[i]); //leitura de todos os botoes para selecionar a tela de musicas
      if (pressed) {
        first = true;
        lcd.clear(); //clear para selecionar outro display
      }
    }
  } else {
    if (songsSelect) {
      selectSong();// selecao de display das musicas
    }
  }
}
