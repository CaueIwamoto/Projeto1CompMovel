#include <LiquidCrystal.h>

#define BUZZER 13
#define BOTAO1 6
#define BOTAO2 5
#define BOTAO3 4
#define BOTAO4 3
#define BOTAO5 2
// defs dos botoes

#define LED1 A4  
#define LED2 A5  
// defs dos leds

#define SCREENHOME 0
#define SCREENSELECTSONG 1
#define SCREENSONG 2
#define SCREENLOOSE 3
#define SCREENPLAYTIME 4

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

uint8_t nvidas = 3;

uint8_t difficulty = 0;

uint8_t readButtonsSelectScreen [BUTTONSSLTSCREEN] = {BOTAO1, BOTAO3, BOTAO5};

uint16_t notas[NNOTAS] = {1048, 1176, 1320, 1396, 1568, 1760, 1976}; // freq das notas

uint8_t musica1[NNOTASM1] = {DO, RE, MI, FA, FA, DO, RE, DO, RE, DO, SOL, FA, MI, DO, RE, MI, FA};

uint8_t musica2[NNOTASM2] = {DO, DO, SOL, SOL, MI, MI, FA, MI, RE, DO};

uint8_t musica3[NNOTASM3] = {DO, DO, RE, RE, MI, MI, FA, MI, RE, DO, DO, RE, RE, MI, MI, FA, MI, RE, DO};

uint8_t musica4[NNOTASM4] = {MI, MI, RE, DO, FA, FA, MI, RE, SOL, SOL, FA, MI, FA, MI, RE, DO};

uint8_t musica5[NNOTASM5] = {DO, RE, MI, RE, MI, FA, MI, FA, SOL, RE, MI, FA, RE, MI, DO};

uint8_t* listaMusicas[NSONGS] = {musica1, musica2, musica3, musica4, musica5}; // ponteiro das listas das musicas acima

uint8_t listaNNotasMusicas[NSONGS] = {NNOTASM1, NNOTASM2, NNOTASM3, NNOTASM4, NNOTASM5}; // lista de numero de notas de kd musica

uint8_t songsIndex = 0; // index usado para selecionar musicas

uint8_t screenIndex; // index da selecao de tela

uint8_t songsList[NSONGS]; // ira ficar a lista de musicas

bool first = 0; // para sair da tela inicial

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5}; // instancia dos botoes

uint8_t lastSongSelected; // armazena o parametro da ultima musica selecionada

bool playTime = 0;

uint8_t lastNvidas;

uint8_t currentNoteIndex = 0; // Índice da nota atual

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); // instancia lcd

void changeScreen(uint8_t (*callback)(), uint8_t screenID) {
  screenIndex = screenID;//salva a tela selecionada
  callback();//funçao de chamar a tela
}

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
} // update de tela de musica

uint8_t updateLoose() {
  loose();
  return true;
} // chama a tela da derrota

void loose(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("VOCE PERDEU!");
  delay(2000);
  changeScreen(updateSelectSong, SCREENSELECTSONG);
} // tela da derrota

uint8_t updatePlayTimeScreen() {
  lastNvidas = nvidas;
  playTimeScreen();
  return true;
} // update da tela enquanto a pessoa esta tocando para diminuir as vidas caso erre

void playTimeScreen() {
  lcd.clear();
  lcd.setCursor(15, 0);
  lcd.print("V");
  lcd.setCursor(15, 1);
  lcd.print(nvidas);
  lcd.setCursor(0, 0);
  lcd.print("B1");
  lcd.setCursor(3, 0);
  lcd.print("B2");
  lcd.setCursor(6, 0);
  lcd.print("B3");
  lcd.setCursor(9, 0);
  lcd.print("B4");
  lcd.setCursor(12, 0);
  lcd.print("B5");
} // tela que aparece no display enquanto a pessoa toca

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
} // função para pegar tamanho da musica de acordo com a dificuldade

void songScreen() {
  lcd.clear();
  uint8_t size = getSizeMusicByDifficult(listaNNotasMusicas[songsIndex], difficulty);
  for (uint8_t i = 0; i < size; i++) {
    lcd.setCursor(15, 0);
    lcd.print("V");
    lcd.setCursor(15, 1);
    lcd.print(nvidas);
    lcd.setCursor(0, 0);
    lcd.print("B1");
    lcd.setCursor(3, 0);
    lcd.print("B2");
    lcd.setCursor(6, 0);
    lcd.print("B3");
    lcd.setCursor(9, 0);
    lcd.print("B4");
    lcd.setCursor(12, 0);
    lcd.print("B5");
    uint8_t nota = listaMusicas[songsIndex][i];
    uint8_t step = max(3, 15 / NNOTAS); // Define um espaçamento mínimo de 3
    uint8_t position = nota * step; 
    lcd.setCursor(position, 1);
    lcd.print("-");
    tone(BUZZER, notas[nota]);
    delay(400);
    lcd.clear();
    noTone(BUZZER);
    delay(200);
  }
  playTime = true;
} // tela que aparece enquanto buzzer toca as notas de kd musica

void setup() {
  lcd.begin(16, 2); // inicia o lcd
  for (size_t i = 0; i < NBUTTONS; i++) {
    pinMode(nButtons[i], INPUT); // inicia todos os botoes
  }
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  displayHome(); // seleciona a tela inicial
}

void readButtonsSongScreen() {
  for (size_t i = 0; i < NBUTTONS; i++) {
    bool readButtons = digitalRead(nButtons[i]); // Lê os botões
    if (readButtons) {
      uint8_t notaEsperada = listaMusicas[songsIndex][currentNoteIndex]; // Obtém a nota correta
      uint8_t notaPressionada = i; // nota pressionada igual ao indexador

      if (notaPressionada == notaEsperada) {
        tone(BUZZER, notas[notaEsperada]); // Som correto
        digitalWrite(LED2, HIGH);
        delay(300);
        noTone(BUZZER);
        digitalWrite(LED2, LOW);
        currentNoteIndex++; // Avança para a próxima nota
        uint8_t size = getSizeMusicByDifficult(listaNNotasMusicas[songsIndex], difficulty); // tananho de acordo com a dificuldade
        if (currentNoteIndex >= size) { // caso concluido nNotas
          playTime = false;
          currentNoteIndex = 0;
          difficulty++;
          delay(300);
          if (difficulty > 3) { // caso concluido musica
            difficulty = 0;
            songsIndex = 0;
            changeScreen(updateSelectSong, SCREENSELECTSONG);
          }
        }
      } else {
        // Nota errada
        tone(BUZZER, 100); // Som de erro
        digitalWrite(LED1, HIGH);
        delay(300);
        noTone(BUZZER);
        digitalWrite(LED1, LOW);
        delay(1000);
        nvidas--;
        if(nvidas == 0) { // reset dos indexadores e tela de derrota
          nvidas = 3;
          playTime = false;
          currentNoteIndex = 0;
          difficulty = 0;
          songsIndex = 0;
          changeScreen(updateLoose, SCREENLOOSE);
        }
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
        if (lastNvidas != nvidas) {
          updatePlayTimeScreen(); // funçao de tela de update enquanto esta sendo tocado a musica
        }
        readButtonsSongScreen(); // le os botoes durante a musica
      } else {
        updateSongScreen(); // tela que faz tocar antes a musica selecionada
      }
    }
  }
}