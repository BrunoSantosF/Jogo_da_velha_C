#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char player[100];
    char click;
}tJogador;

void PrintJogo(char matriz[3][3]);
void InicializandoJogo(char matriz[3][3]);
tJogador Informacoes_players(int x);
int Linha_Coluna();
int Erro(int l,int c,char matriz[3][3],tJogador player);
void Marcando_tabuleiro(char matriz[3][3],int l,int c,tJogador player);
int Vitoria(char matriz[3][3],tJogador player);
void Jogadas(tJogador player,char matriz[3][3]);

int main(){
    char matriz[3][3]; // tabuleiro do jogo da velha.
    tJogador player1,player2;
    
    InicializandoJogo(matriz);
    
    player1 = Informacoes_players(1);
    player2 = Informacoes_players(2);

    if(player1.click == player2.click){
        printf("\033[01;31mErro , os clikers são iguais !!!\033[m\n");
        exit(1);
    }


    while (1){
        Jogadas(player1, matriz);
        if(Vitoria( matriz, player1)==1){break;}
        Jogadas(player2, matriz);
        if(Vitoria( matriz, player2)==1){break;}  
    }
        
    return 0;
}

void Jogadas(tJogador player,char matriz[3][3]){
    int l,c;

    printf("Vez da jogador %s :\n",player.player);
    printf("Linha:");
    l = Linha_Coluna();
    printf("Coluna:");
    c = Linha_Coluna();

    while(!Erro(l,c,matriz,player)){
        printf("\033[01;31mJogada Invalida\033[m\nInsira uma jogada valida!!\n");
        printf("Linha:");
        l = Linha_Coluna();
        printf("Coluna:");
        c = Linha_Coluna();
    }

    Marcando_tabuleiro(matriz,l,c,player);
}

int Vitoria(char matriz[3][3],tJogador player){
    int resultado = -1;
    if(matriz[0][0] == player.click && matriz[1][1] == player.click && matriz[2][2] == player.click){ resultado = 1;} //diagonal
    else if(matriz[0][0] == player.click && matriz[0][1] == player.click && matriz[0][2] == player.click){resultado = 1;} //horizontal 1
    else if(matriz[1][0] == player.click && matriz[1][1] == player.click && matriz[1][2] == player.click){resultado = 1;} //horizontal 2
    else if(matriz[2][0] == player.click && matriz[2][1] == player.click && matriz[2][2] == player.click){resultado = 1;} //horizontal 3
    else if(matriz[0][0] == player.click && matriz[1][0] == player.click && matriz[2][0] == player.click){resultado = 1;} //vertical 1
    else if(matriz[0][1] == player.click && matriz[1][1] == player.click && matriz[2][1] == player.click){resultado = 1;} //vertical 2
    else if(matriz[0][2] == player.click && matriz[1][2] == player.click && matriz[2][2] == player.click){resultado = 1;} //vertical 3
    else if(matriz[0][2] == player.click && matriz[1][1] == player.click && matriz[2][0] == player.click){resultado = 1;} //diagonal
    else {resultado = 0;}

    if (resultado == 1){
        printf("\nVITORIA\n");
        printf("Jogador %s é o VENCEDOR\n",player.player);
        return 1;
    }
    else {
        int cont= 0;
        for (int i =0;i < 3;i++){
            for (int j=0;j < 3;j++){
                if (matriz[i][j] == ' '){
                    cont++;
                }
            }
        } 
        if(cont == 0){
            printf("\nEMPATE\n");
            printf("DEU VELHA\n");
            return 1;
        }
        return 0;
    }

}

void Marcando_tabuleiro(char matriz[3][3],int l,int c,tJogador player){
    for (int i =0;i < 3;i++){
        for (int j=0;j < 3;j++){
            if (i == l && j == c){matriz[l][c] = player.click;}
        }
    }
    PrintJogo(matriz);
}

int Erro(int l,int c,char matriz[3][3],tJogador player){
    //verifica se a jogada é repetida.
    for (int i =0;i < 3;i++){
        for (int j=0;j < 3;j++){
            if (matriz[l][c] == player.click){return 0;}
        }
    }
    //verifica se a jogada está fora do tabuleiro.
    if (l>2 || c>2 || c<0 || l<0){
        return 0;
    }
    return 1;
}

int Linha_Coluna(){
    int x;
    scanf("%d",&x);
    return x;
}

tJogador Informacoes_players(int x){
    tJogador player;
    printf("\033[00;32mInsira o nome do Jogador %d :\033[m\n",x);
    scanf("%[^\n]",player.player);
    printf("\033[00;33mEscolha [X/O](Ou qualquer letra que seja diferente do outro player) :\033[m\n");
    scanf("\n%c",&player.click);
    scanf("%*c");

    return player;
}


void InicializandoJogo(char matriz[3][3]){
    //incializa o tabuleiro da velha com " " (espaço)
    for (int l = 0;l < 3;l++){
        for (int c = 0;c < 3;c++){
            matriz[l][c] = ' ';
        }
    }
}
void PrintJogo(char matriz[3][3]){
    //imprime o tabuleiro da velha atual.
    printf("\n");
    for (int l = 0;l < 3;l++){
        for (int c = 0;c < 3;c++){
            if (c != 2){printf("%c|",matriz[l][c]);}
            else {printf("%c",matriz[l][c]);}
        } 
        printf("\n"); 
    }
    printf("\n");
}
