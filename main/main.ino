#include <LiquidCrystal.h>

//Defs dos botões e buzzer:
#define BUZZER 13
#define BOTAO1 10
#define BOTAO2 9
#define BOTAO3 8
#define BOTAO4 7
#define BOTAO5 6


#define NBUTTONS 5 //Número dos botões
#define NSONGS 5 //Números de músicas

uint8_t songsIndex = 0;//Index usado para selecionar músicas

uint8_t songsList[NSONGS];//Onde irá ficar armazenado a lista de músicas

bool first = 0;//Para sair da tela inicial

bool songsSelect;//Bool para seleção na tela de músicas

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5}; //Instância dos botões

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); //Instância LCD
//Definindo função tempoInicial para a mensagem inicial:
long tempoInicial = 0;
bool mostrarBemvindo = true;

//Tela inicial:
void displayHome() {
  lcd.clear(); //clear para que o loop seja rodado e apareça outra mensagem:
  lcd.setCursor(3,0);
  if (mostrarBemvindo) {
    lcd.print("Bem Vindo!");
  } else {
  lcd.setCursor(1,0);
  lcd.print("Pressione para");
  lcd.setCursor(4,1);
  lcd.print("Iniciar");
  }
  
  //mostrarBemvindo:
  mostrarBemvindo = !mostrarBemvindo;
      
}

void selectSong() {
  //Tela para seleção das músicas:
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
}

void setup() {
  lcd.begin(16, 2); //Inicia o display LCD
  for (size_t i = 0; i < NBUTTONS; i++) {
    pinMode(nButtons[i], INPUT); //Inicia todos os botões
  }
  displayHome(); //Seleciona a tela inicial
}

void loop() {
  if(!first) {
  //Tempo de loop da mensagem inicial:
    if (millis() - tempoInicial >= 2000) {
      tempoInicial = millis();
      displayHome();
    }
    for (size_t i = 0; i < NBUTTONS; i++) {
      bool pressed = digitalRead(nButtons[i]); //Leitura de todos os botões para selecionar a tela de música
      if (pressed) {
        first = true;
        lcd.clear(); //Clear para selicionar próximo display
      }
    }
  } else {
    if (songsSelect) {
      selectSong(); //Seleção das músicas
    }
  }
}
