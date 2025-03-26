#include <LiquidCrystal.h>

#define BUZZER 13
#define BOTAO1 10
#define BOTAO2 9
#define BOTAO3 8
#define BOTAO4 7
#define BOTAO5 6
// defs dos botoes

#define SCREENHOME 0
#define SCREENSELECTSONG 1
#define SCREENSONG 2

#define NBUTTONS 5 // numero de botoes
#define NSONGS 5 // numero de musicas

uint8_t songsIndex = 0; // index usado para selecionar musicas

uint8_t screenIndex; // index da selecao de tela

uint8_t songsList[NSONGS]; // ira ficar a lista de musicas

bool first = 0; // para sair da tela inicial

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5}; // instancia dos botoes

uint8_t lastSongSelected; // armazena o parametro da ultima musica selecionada

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // instancia lcd

void displayHome() {
  lcd.setCursor(1, 0);
  lcd.print("Pressione para");
  lcd.setCursor(5, 1);
  lcd.print("Comecar");
} // tela inicial

uint8_t updateSelectSong() {
  lastSongSelected = songsIndex;
  selectSong();
  return true;
} // funçao de atualizar display e parametros assim ele nao é chamado o tempo todo

void selectSong() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Selecione Musica");
  lcd.setCursor(0, 1);
  lcd.print("<");
  lcd.setCursor(15, 1);
  lcd.print(">");
  lcd.setCursor(4, 1);
  lcd.print("Musica");
  lcd.setCursor(11, 1);
  lcd.print(songsIndex);
} // tela de selecao de musicas

uint8_t updateSongScreen() {
  songScreen();
  return true;
}

void songScreen() {
  lcd.clear();
}

void changeScreen(uint8_t (*callback)(), uint8_t screenID) {
  screenIndex = screenID;//salva a tela selecionada
  callback();//funçao de chamar a tela
}

void setup() {
  lcd.begin(16, 2); // inicia o lcd
  for (size_t i = 0; i < NBUTTONS; i++) {
    pinMode(nButtons[i], INPUT); // inicia todos os botoes
  }
  displayHome(); // seleciona a tela inicial
}

void readButtonsSelectionScreen() {
  bool botao1 = digitalRead(BOTAO1);
  bool botao5 = digitalRead(BOTAO5);
  bool botao3 = digitalRead(BOTAO3);
  if (botao1) { // botao de selecionar a musica anterior
    if (songsIndex <= 0) {
      songsIndex = 5; // corrige para respeitar o número de músicas
      delay(200);
    } else {
      songsIndex--;
      delay(200);
    }
  } else if (botao5) { // botao de selecionar a musica seguinte
    if (songsIndex >= NSONGS) {
      songsIndex = 0;
      delay(200);
    } else {
      songsIndex++;
      delay(200); // delay para nao rodar rapido demais entre as musicas
    }
  } else if (botao3) {
    lcd.clear();
    changeScreen(updateSongScreen, SCREENSONG);
  }
} // leitura dos botoes da tela de seleção de musica para poder alterar as musicas selecionadas

void loop() {
  if (!first) {
    for (size_t i = 0; i < NBUTTONS; i++) {
      bool pressed = digitalRead(nButtons[i]); // leitura de todos os botoes para selecionar a tela de musicas
      if (pressed) {
        first = true;
        lcd.clear(); // clear para selecionar outro display
        changeScreen(updateSelectSong, SCREENSELECTSONG);
        delay(200);
      }
    }
  } else {
    if (screenIndex == SCREENSELECTSONG) {
      readButtonsSelectionScreen(); // chama a funçao de ler os botoes 
      if (lastSongSelected != songsIndex) {
        updateSelectSong(); // funçao de update de display na tela de selecao de musicas
      }
    } else if (screenIndex == SCREENSONG) {
      // lógica para a tela de execução de música (ainda não implementada)
    }
  }
}
