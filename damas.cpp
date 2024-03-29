#include <iostream>
#include <ctime>
#include <locale.h>
using namespace std;
void criatab(); // MOSTRA O TABULEIRO EM TELA
char tabuleiro[8][8]; // MATRIZ DO TABULEIRO
void setB(); // SETA AS PEÇAS NO TABULEIRO JOGADOR BRANCO
void setP(); // SETA AS PEÇAS NO TABULEIRO JOGADOR PRETO
void jogar(); // CONTROLA AS JOGADAS
int JG1 = 1;
int J1 = 1;
int dx, dy, x, y;
int pecasP, pecasB; // CONTAGEM DE PECAS CAPTURADAS NO TABULEIRO

void clrscr() {
  cout << "\033[2J\033[1;1H";
}

void wait(int wait_time)
{
  long* start_time = new long;
  *start_time = time(0);

  while ((*start_time + wait_time) > time(0)) {
  };

  delete start_time;
};

void criatab() {
  cout << "| 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |" << endl;
  cout << "|-------------------------------|" << endl;

  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      if (j != 8) {
        cout << "| " << tabuleiro[i][j] << " ";
      }
      if (j == 8) {
        cout << "| " << tabuleiro[i][j] << " | " << i << endl;
        cout << "|-------------------------------|" << endl;
      }

    }
  }

}


void fimtab() { // PEÇA CHEGA NO FINAL DO TABULEIRO
  if (tabuleiro[1][y] == 'P'){
    tabuleiro[1][y] = ' ';
  } else if (tabuleiro[8][y] == 'B'){
    tabuleiro[8][y] = ' ';
  }
}

void setB() {   // FUNÇÃO PARA JOGADAS DO JOGADOR BRANCO
  criatab();
  cout << "[JOGADOR BRANCO]" << endl;
  cout << "Digite a linha de origem: " << endl;
  cin >> dx;
  cout << "Digite a coluna de origem: " << endl;
  cin >> dy;
  if (tabuleiro[dx][dy] == 'B') {
    cout << "Digite a linha de destino: " << endl;
    cin >> x;
    cout << "Digite a coluna de destino: " << endl;
    cin >> y;
  }
  else {
    cout << "Não há peças Brancas na origem!" << endl;
    setB();
  }
  
 
  if (dx < x && x - dx == 1 && (x + y) % 2 != 0) {  // MOVIMENTO DE PEÇAS
    tabuleiro[x][y] = 'B';
    tabuleiro[dx][dy] = ' ';
    setP();
  } else if (dx < x && (tabuleiro[x-1][y+1] == 'P' || tabuleiro[x-1][y-1] == 'P') && (x + y) % 2 != 0 && x-dx == 2) { // JOGADAS EM 2 CASAS [BRANCO]
    tabuleiro[x-1][y+1] = ' ';
    tabuleiro[x-1][y-1] = ' ';
    tabuleiro[x][y] = 'B';                                                           //   L - C
    tabuleiro[dx][dy] = ' ';                                                          // [-][+] Diagonal esquerda
    pecasP += 1;                                                                       // [-][-] Diagonal direita
    cout << "Você capturou uma peça PRETA, você tem um nova jogada!" << endl;
    setB();
  } else {
    cout << "Você só pode ir pra frente / em Diagonal / Locais sem peças" << endl; // ERROS DE JOGADAS
    setB();
  }
  fimtab();
  wait(0.5);
  clrscr();
  criatab();
}

void setP() {  // FUNÇÃO PARA JOGADAS DO JOGADOR PRETO
  criatab();
  cout << "[JOGADOR PRETO]" << endl;
  cout << "Digite a linha de origem: " << endl;
  cin >> dx;
  cout << "Digite a coluna de origem: " << endl;
  cin >> dy;
  if (tabuleiro[dx][dy] == 'P') {
    cout << "Digite a linha de destino: " << endl;
    cin >> x;
    cout << "Digite a coluna de destino: " << endl;
    cin >> y;
  }
  else {
    cout << "Não há peças Pretas na origem!" << endl;
    setP();
  }
  
  if (dx > x && dx - x == 1 && (x + y) % 2 != 0) {
    tabuleiro[x][y] = 'P';
    tabuleiro[dx][dy] = ' ';
    setB();
  } else if (dx > x && (tabuleiro[x+1][y+1] == 'B' || tabuleiro[x+1][y-1] == 'B') && (x + y) % 2 != 0 && dx-x == 2) { // JOGADAS EM 2 CASAS [PRETO]
    tabuleiro[x+1][y+1] = ' ';
    tabuleiro[x+1][y-1] = ' ';
    tabuleiro[x][y] = 'P';                                                  // L - C
    tabuleiro[dx][dy] = ' ';                                                // [+][-] Diagonal pra direita = 'B'
    pecasB += 1;                                                                       // [+][+] Diagonal pra esquerda = 'B'
    cout << "Você capturou uma peça BRANCA, você tem um nova jogada!" << endl;
    setP();
  } else {
    cout << "Você só pode ir pra frente / em Diagonal / Locais sem peças" << endl;
    setP();
  }
  fimtab();
  wait(0.5);
  clrscr();
}


int check(){
  if (pecasB == 12){
    cout << "O jogador PRETO venceu a partida!" << endl;
    return 0;
  }
  if (pecasP == 12){
    cout << "O jogador BRANCO venceu a partida!" << endl;
    return 0;
  }
}

void jogar() {
  if (JG1 == 0 && J1 == 1) {
    J1 = 0;
    setB();
  }
  else if (JG1 == 1 && J1 == 1) {
    J1 = 0;
    setP();
  }


}


int main() {
  setlocale(LC_ALL, "portuguese");
  int us_b, us_p, us_b2, us_p2;
  bool control = true; // VARIÁVEL DE CONTROLE BOLEANO
  int random; // VARIÁVEL DA RAND
  srand(time(NULL)); // SEMENTE DA RAND

  while (control) {
    cout << "Jogador Branco digite um número de 0 a 9: " << endl;  // JOGADOR BRANCO DIGITA UM NÚMERO
    cin >> us_b;
    if (us_b > 9 || us_b < 0) {
      cout << "Número inválido!" << endl;  // VERIFICA SE ESTÁ ENTRE 0 E 9
      return 0;
    }

    cout << "Jogador Preto digite um número de 0 a 9: " << endl;  // JOGADOR PRETO DIGITA UM NÚMERO
    cin >> us_p;
    if (us_p > 9 || us_p < 0) {
      cout << "Número inválido!" << endl; // VERIFICA SE ESTÁ ENTRE 0 E 9
      return 0;
    }
    control = false;  // TERMINA O LAÇO
  }

  control = true;
  while (control) {                           //LAÇO DE VERIFICAÇÃO DO VALOR MAIS PRÓXIMO DO PONTO RANDOMICO
    random = (rand() + time(0)) % 9 + 1;
    cout << "Número aleatório gerado: " << random << endl;
    us_b2 = us_b;
    us_p2 = us_p;
    us_b2 -= random;
    us_p2 -= random;

    if (us_b2 < 0) {
      us_b2 = us_b2 * -1;
    }
    else if (us_p2 < 0) {
      us_p2 = us_p2 * -1;
    }

    if (us_p == us_b) {  // TESTA OS VALORES DIGITADOS E RANDOMIZADOS
      cout << "Os valores são iguais. Impossível determinar o valor mais próximo." << endl;
      return 0;
    }
    else if (us_p2 == us_b2) {
      cout << "Os valores são igualmente próximos. Reiniciando o ponto randomico." << endl;
    }
    if (us_b2 > us_p2) {
      cout << "PRETO VENCEU!" << endl;
      control = false;
      JG1 = 1;
      wait(2);
      clrscr();
    }
    else if (us_p2 > us_b2) {
      cout << "BRANCO VENCEU!" << endl;
      control = false;
      JG1 = 0;
      wait(2);
      clrscr();
    }
    else if (us_p2 == us_b2) {
      cout << "O valores são igualmente próximas do ponto. Reiniciando ponto aleatório." << endl;
    }
  }

  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {

      if ((i + j) % 2 != 0 && i <= 3) {         // SET DE PEÇAS BRANCAS NO TABULEIRO
        tabuleiro[i][j] = 'B';
      }
      else if ((i + j) % 2 != 0 && i >= 6) {    // SET DE PEÇAS PRETAS NO TABULEIRO
        tabuleiro[i][j] = 'P';
      }


      if (tabuleiro[i][j] != 'B' && tabuleiro[i][j] != 'P' && (i + j) % 2 == 0) {
        tabuleiro[i][j] = ' ';
      } // INSERE LOCAIS VAZIOS BRANCOS = 0

      else if (tabuleiro[i][j] != 'B' && tabuleiro[i][j] != 'P' && (i + j) % 2 != 0) {
        tabuleiro[i][j] = ' ';  // INSERE LOCAIS VAZIOS PRETOS = 1
      }
    }
  }

  jogar();

  return 0;
}



    
