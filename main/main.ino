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

#define NNOTASM1 17

#define NNOTASM2 10

#define NNOTASM3 19

#define NNOTASM4 16

#define NNOTASM5 15

#define NNOTAS 7

#define BUTTONSSLTSCREEN 3

enum notas{
  DO,
  RE,
  MI,
  FA,
  SOL,
  LA,
  SI,
};

uint8_t difficulty = 0;

uint8_t readButtonsSelectScreen [BUTTONSSLTSCREEN] = {BOTAO1, BOTAO3, BOTAO5};

uint8_t notas[NNOTAS] = {262, 294, 330, 349, 392, 440, 494};

uint8_t musica1[NNOTASM1] = {DO, RE, MI, FA, FA, DO, RE, DO, RE, DO, SOL, FA, MI, DO, RE, MI, FA};

uint8_t musica2[NNOTASM2] = {DO, DO, SOL, SOL, MI, MI, FA, MI, RE, DO};

uint8_t musica3[NNOTASM3] = {DO, DO, RE, RE, MI, MI, FA, MI, RE, DO, DO, RE, RE, MI, MI, FA, MI, RE, DO};

uint8_t musica4[NNOTASM4] = {MI, MI, RE, DO, FA, FA, MI, RE, SOL, SOL, FA, MI, FA, MI, RE, DO};

uint8_t musica5[NNOTASM5] = {DO, RE, MI, RE, MI, FA, MI, FA, SOL, RE, MI, FA, RE, MI, DO};

uint8_t* listaMusicas[NSONGS] = {musica1, musica2, musica3, musica4, musica5};

uint8_t listaNNotasMusicas[NSONGS] = {NNOTASM1, NNOTASM2, NNOTASM3, NNOTASM4, NNOTASM5};

uint8_t songsIndex = 0; // index usado para selecionar musicas

uint8_t screenIndex; // index da selecao de tela

uint8_t songsList[NSONGS]; // ira ficar a lista de musicas

bool first = 0; // para sair da tela inicial

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5}; // instancia dos botoes

uint8_t lastSongSelected; // armazena o parametro da ultima musica selecionada

bool playTime = 0;

uint8_t currentNoteIndex = 0; // Índice da nota atual

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

uint8_t getSizeMusicByDifficult(uint8_t size, uint8_t difficulty) {
  uint8_t sizeOf;
  if (difficulty == 0) {
    sizeOf = size / 2;  
  } else if (difficulty == 1) {
    sizeOf = (size / 2) + (size / 3);
  } else if (difficulty == 3) {
    sizeOf = size;
  }
  return sizeOf;
}

void songScreen() {
  lcd.clear();
  uint8_t size = getSizeMusicByDifficult(listaNNotasMusicas[songsIndex];, difficulty);
  for (uint8_t i = 0; i < size; i++) {
    
  }
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

void readButtonsSongScreen() {
  for (size_t i = 0; i < NBUTTONS; i++) {
    bool readButtons = digitalRead(nButtons[i]); // Lê os botões
    if (readButtons) {
      uint8_t notaEsperada = listaMusicas[songsIndex][currentNoteIndex]; // Obtém a nota correta
      uint8_t notaPressionada = i; // Assumindo que BOTAO1 → DO, BOTAO2 → RE, etc.

      if (notaPressionada == notaEsperada) {
        tone(BUZZER, notas[notaEsperada]); // Som correto
        delay(300);
        noTone(BUZZER);
        currentNoteIndex++; // Avança para a próxima nota

        if (currentNoteIndex >= listaNNotasMusicas[songsIndex]) {
          lcd.clear();
          lcd.setCursor(3, 0);
          lcd.print("Parabéns!");
          lcd.setCursor(0, 1);
          lcd.print("Musica concluida!");
          delay(2000);
          currentNoteIndex = 0; // Reseta a música
          changeScreen(updateSelectSong, SCREENSELECTSONG); // Retorna à seleção
        }
      } else {
        // Nota errada
        tone(BUZZER, 100); // Som de erro
        delay(300);
        noTone(BUZZER);
        delay(1000);
      }
    }
  }
}

void readButtonsSelectionScreen() {
  for (size_t i = 0; i < BUTTONSSLTSCREEN; i++) {
    bool readButtons = digitalRead(readButtonsSelectScreen[i]);
    if (readButtons) {
      if (i == 0) {
        if (songsIndex <= 0) {
          songsIndex = 5; // corrige para respeitar o número de músicas
        } else {
          songsIndex--;
        }
      } else if (i == 1) {
        lcd.clear();
        changeScreen(updateSongScreen, SCREENSONG);
      } else if (i == 2) {
        if (songsIndex >= NSONGS) {
          songsIndex = 0;
        } else {
          songsIndex++;
        }
      }
      delay(185); // delay para nao rodar rapido demais entre as musicas
    } 
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
      if (playTime) {
        readButtonsSongScreen();
      } else {
        updateSongScreen();
      }
      // lógica para a tela de execução de música (ainda não implementada)
    }
  }
}
