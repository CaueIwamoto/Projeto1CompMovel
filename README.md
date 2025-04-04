Projeto1CompMovel

Início do projeto: 24/03/2025

#Introdução:

  Neste projeto serão aplicados os conceitos aprendidos nas aulas de Computação móvel. Onde um circuito será montado apresentando um jogo que testará, através de um display 16x2, a memória musical do jogador com uma música que tocará em um buzzer.

#Metodologia:

**- Materiais utilizados** 

2 protoboards: notamos que o uso de apenas 1 protoboard dificultaria a montagem do circuito, já com dois teremos uma ergonomia melhor;
1 Arduino;
5 botões;
1 potenciômetro;
2 Leds: 1 vermelho para exibir a nota que o usuário errou e 1 verde para exibir a nota que o usuário acertou;
1 buzzer;
1 display LCD 16x2;
1 resistor (223 ohm);
7 resistores (504 ohm);

**- Métodos**

  De maneira geral, o projeto foi desenvolvido utilizando o simulador Tinkercad, onde nós temos a oportunidade de montar e testar circuitos eletrônicos, para que então na entrega final, podemos montar o circuito com menores chances de erros, pois já obtemos a estrutura do circuito feita no Tinkercad. Já o código foi estruturado e produzido através do VSCode, porém o Tinkercad dispõe uma parte que podemos "codar" idem.

**Código completo:**
'''' C++
#include <LiquidCrystal.h>

//Definindo buzzer e botôes:
#define BUZZER 13
#define BOTAO1 6
#define BOTAO2 5
#define BOTAO3 4
#define BOTAO4 3
#define BOTAO5 2

//Definindo leds:
#define LED1 A4  
#define LED2 A5  

//Definindo telas:
#define SCREENHOME 0
#define SCREENSELECTSONG 1
#define SCREENSONG 2
#define SCREENLOOSE 3
#define SCREENPLAYTIME 4

#define NBUTTONS 5 //Número de botões
#define NSONGS 5 //Número  de músicas

#define NNOTASM1 17

#define NNOTASM2 10

#define NNOTASM3 19

#define NNOTASM4 16

#define NNOTASM5 15

#define NNOTAS 7

#define BUTTONSSLTSCREEN 3

//Notas:
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

uint16_t notas[NNOTAS] = {1048, 1176, 1320, 1396, 1568, 1760, 1976}; //Frequência das notas

//Definindo das notas de cada música:
uint8_t musica1[NNOTASM1] = {DO, RE, MI, FA, FA, DO, RE, DO, RE, DO, SOL, FA, MI, DO, RE, MI, FA};

uint8_t musica2[NNOTASM2] = {DO, DO, SOL, SOL, MI, MI, FA, MI, RE, DO};

uint8_t musica3[NNOTASM3] = {DO, DO, RE, RE, MI, MI, FA, MI, RE, DO, DO, RE, RE, MI, MI, FA, MI, RE, DO};

uint8_t musica4[NNOTASM4] = {MI, MI, RE, DO, FA, FA, MI, RE, SOL, SOL, FA, MI, FA, MI, RE, DO};

uint8_t musica5[NNOTASM5] = {DO, RE, MI, RE, MI, FA, MI, FA, SOL, RE, MI, FA, RE, MI, DO};

uint8_t* listaMusicas[NSONGS] = {musica1, musica2, musica3, musica4, musica5}; //Ponteiros listas das músicas acima

uint8_t listaNNotasMusicas[NSONGS] = {NNOTASM1, NNOTASM2, NNOTASM3, NNOTASM4, NNOTASM5}; //Lista de número de notas de cada música

uint8_t songsIndex = 0; //Index para selecionar as músicas

uint8_t screenIndex; //Index seleção de tela

uint8_t songsList[NSONGS]; //Lista de música

bool first = 0; //Para sair da tela inicial

uint8_t nButtons[NBUTTONS] = {BOTAO1, BOTAO2, BOTAO3, BOTAO4, BOTAO5}; //Instância dos botões

uint8_t lastSongSelected; //Armazena o parâmetro da última música selecionada

bool playTime = 0;

uint8_t lastNvidas;

uint8_t currentNoteIndex = 0; //Índice da nota atual

LiquidCrystal lcd(12, 11, 10, 9, 8, 7); //Instância LCD

void changeScreen(uint8_t (*callback)(), uint8_t screenID) {
  screenIndex = screenID;//Salva a tela selecionada
  callback();//Função para chamar a tela
}

//Tela inicial:
void displayHome() {
  lcd.setCursor(1, 0);
  lcd.print("Pressione para");
  lcd.setCursor(5, 1);
  lcd.print("Comecar");
} 

//Função que atualiza display e parâmetros, assim ele não é chamado o tempo todo.
uint8_t updateSelectSong() {
  lastSongSelected = songsIndex;
  selectSong();
  return true;
} 

//Tela seleção das músicas:
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
} 

//Update da tela de música:
uint8_t updateSongScreen() {
  songScreen();
  return true;
} 

//Chama tela de derrota ao perder as vidas música:
uint8_t updateLoose() {
  loose();
  return true;
} 

//Tela derrota:
void loose(){
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("VOCE PERDEU!");
  delay(2000);
  changeScreen(updateSelectSong, SCREENSELECTSONG);
}

//Update da tela enquanto a pessoa está tocando para diminuir as vidas ao errar as notas da música:
uint8_t updatePlayTimeScreen() {
  lastNvidas = nvidas;
  playTimeScreen();
  return true;
} 

//Tela que aparece no display enquanto a pessoa está tocando a música:
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
} 

//Função para pegar o tamanho da música de acordo com a dificuldade selecionada:
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

//Tela que aparece enquanto o buzzer toca as notas de cada música:
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
} 

void setup() {
  lcd.begin(16, 2); //Inicia o display LCD
  for (size_t i = 0; i < NBUTTONS; i++) {
    pinMode(nButtons[i], INPUT); //Inicia todos os botões
  }
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  displayHome(); //Seleciona a tela inicial
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
        uint8_t size = getSizeMusicByDifficult(listaNNotasMusicas[songsIndex], difficulty); //Tamanho de acordo com a dificuldade
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


''''


**Imagem da primeira montagem do circuito feita no Tinkercad:**
![ComputaçãoMovel_primeiraMontagem_Tinkercad](https://github.com/user-attachments/assets/a4a3b487-f55c-4e43-9d6f-e27f3aaef583)


**2 imagens apresentando o circuito montado em aula:**
![Circuito montado 1](https://github.com/user-attachments/assets/31cf54e8-fdb8-4f44-82ec-c819b603c574)

![Circuito montado 2](https://github.com/user-attachments/assets/1a38850e-f0d6-470c-8a87-aae12b8717c7)


**Apresentação em vídeo:**

https://github.com/user-attachments/assets/981afdb4-3d0f-490e-82d7-7f76baab2efc


https://github.com/user-attachments/assets/118e75a8-89d9-4976-9d54-cd336b3e97ca



#Conclusões:

  Diante de todo projeto realizado nessas últimas duas semanas, concluímos que o projeto foi desenvolvivdo de maneira rápida e eficaz. Tivemos um único problema onde, ao montarmos o circuito na apresentação final do projeto, o nosso display LCD estava ligando e apresentando blocos brancos, e não as telas de menu. Contudo, fomos trocando e testando por outros displays e tivemos a conclusão que o problema era com um display anterior. Além de que mudamos as ordens dos cabos dos botões e das entradas do display (DB4, DB5, DB6 e DB7) no Arduino, apenas para garantir que o circuito funcionasse corretamente.
