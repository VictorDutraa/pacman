#include<stdio.h>
#include<string.h>

#define MAX_LINHAS 40
#define MAX_COLUNAS 101
#define PAC_MAN '>'
#define PAREDE '#'
#define SETA_CIMA 'w'
#define SETA_BAIXO 's'
#define SETA_E 'a'
#define SETA_D 'd'
#define COMIDA '*'
#define FANTASMA_H_ESQUERDA 'B'
#define FANTASMA_H_DIREITA 'C'
#define FANTASMA_V_CIMA 'P'
#define FANTASMA_V_BAIXO 'I'
#define RESUMO_PAREDE 'p'
#define RESUMO_COMIDA 'c'
#define RESUMO_FANTASMA 'f'
#define COMIDA_ESPECIAL '%'

typedef struct{
    int posicaoLinhaPacman;
    int posicaoColunaPacman;
}tPacman;

typedef struct{
    int movimento;
}tPegouComida;

typedef struct{
    int qtdLinhas;
    int qtdColunas;
    char mapa[MAX_LINHAS][MAX_COLUNAS];
    int colidiuFantasma;
    int pontuacao;
    int sentidoFantasmaVC;
    int sentidoFantasmaVB;
    int sentidoFantasmaHE;
    int sentidoFantasmaHD;
    int comidaPendenteFVC;
    int comidaPendenteFVB;
    int comidaPendenteFHE;
    int comidaPendenteFHD;
    int comidaEspecialPendenteFVC;
    int comidaEspecialPendenteFVB;
    int comidaEspecialPendenteFHE;
    int comidaEspecialPendenteFHD;
    int esperaPacmanFVC;
    int esperaPacmanFVB;
    int esperaPacmanFHE;
    int esperaPacmanFHD;
    int totalMovimentos;
    int movimentosNaoPontuados;
    int colisoesParede;
    int qtdSetaCima;
    int qtdSetaBaixo;
    int qtdSetaE;
    int qtdSetaD;
}tMapa;

typedef struct{ 
    tMapa dadosMapa;
    tPacman pacman;
    int qtdJogadas;
    char diretorioJogo[1001];
    char movimentoAtual;
    int inicio;
    int totalJogadasFixa;
    int mapeiaRastro[MAX_LINHAS][MAX_COLUNAS];
    int mapeiaMovimentos[MAX_LINHAS][MAX_COLUNAS];
}tJogo;

//FUNCOES DO JOGO EM SI.
void InicializarJogo(tJogo jogo);
tJogo LerMapa(tJogo jogo, FILE * mapaInicial);
tJogo LeJogadas(tJogo);
int HouverQtdJogadas(tJogo jogo);
tJogo RealizarJogo(tJogo jogo);
tJogo DecrementaJogadas(tJogo jogo);
int AcabouOJogo(tJogo jogo);
tJogo AtribuiInicio(tJogo jogo);
tJogo AcrescentaInicio(tJogo jogo);
int VocePerdeu(tJogo jogo);
int VoceGanhou(tJogo jogo);
tJogo ZeraEsperaPacman(tJogo jogo);
void GeraEstatisticas(tJogo jogo);
tJogo ArmazenaDiretorio(tJogo jogo, char diretorio[1001]);
tJogo LimpaTudo(tJogo jogo);
tJogo LimpaTudo(tJogo jogo);
tMapa LimpaDadosMapa(tMapa dadosMapa);
void GerarResumo(char opcao, char diretorio[1001], char movimento, int qtdJogadas, int totalJogadasFixo);
tJogo RastrearTrilha(tJogo jogo, tMapa dadosMapa, int qtdJogadas, int totalJogadasFixa);
void GerarTrilha(tJogo jogo);
int AcessaCelulaRastro(tJogo jogo, int a, int b);
int AcessaCelulaMovimentos(tJogo jogo, int a, int b);

//FUNCOES DO MAPA
int AcabouComida(tMapa dadosMapa);
int AcessoLinhas(tMapa dadosMapa);
int AcessoColunas(tMapa dadosMapa);
void ImprimeMapa(tJogo jogo, char movimento, tMapa dadosMapa);
int AcessaMapa(tJogo jogo);
int AcessaPontuacao(tMapa mapa);
tMapa ArmazenaLinhasColunas(tMapa dadosMapa, int linhas, int colunas);
int TotalSetaCima(tMapa dadosMapa);
int TotalSetaBaixo(tMapa dadosMapa);
int TotalSetaE(tMapa dadosMapa);
int TotalSetaD(tMapa dadosMapa);
tMapa ArmazenaLinhasColunas(tMapa dadosMapa, int linhas, int colunas);
tMapa AtribuiCelulaMapa(tMapa dadosMapa, int a, int b, char celula);
char AcessaCelulaMapa(tMapa dadosMapa, int a, int b);
int AcessaColisoes(tMapa mapa);
int TotalDeMovimentos(tMapa dadosMapa);
int TotalMovNaoPontuados(tMapa dadosMapa);

//FUNCOES DO PACMAN
int PosicaoLinhaPacman(tMapa dadosMapa);
int PosicaoColunaPacman(tMapa dadosMapa);
int PacmanColidiuFantasma(tMapa mapa);
tMapa MovimentaPacman(tJogo jogo, int inicio, tPacman pacman, char movimentoAtual, tMapa dadosMapa);
tPacman PosicaoLinhaStructPacman(tPacman pacman, tMapa dadosMapa);
tPacman PosicaoColunaStructPacman(tPacman pacman, tMapa dadosMapa);
tMapa MoverPacmanCima(tPacman pacman, tMapa dadosMapa);
tMapa MoverPacmanBaixo(tPacman pacman, tMapa dadosMapa);
tMapa MoverPacmanEsquerda(tPacman pacman, tMapa dadosMapa);
tMapa MoverPacmanDireita(tPacman pacman, tMapa dadosMapa);
tMapa ZeraColisoesParede(tMapa dadosMapa);


//FUNCOES DO FANTASMA
int PosicaoLinhaFantasma(tMapa dadosMapa);
int PosicaoColunaFantasma(tMapa dadosMapa);
tMapa MovimentaFantasma(tMapa dadosMapa);
int EhFantasma(char fantasma);
tMapa SentidoInicialFantasmas(tMapa dadosMapa);
tMapa ComidaPendenteFantasmas(tMapa dadosMapa);
tMapa ParaDeEsperarPacman(tMapa dadosMapa);
int EsperouPacman(tMapa dadosMapa);
tMapa MovimentaFHE(tMapa dadosMapa);
tMapa MovimentaFHD(tMapa dadosMapa);
tMapa MovimentaFVC(tMapa dadosMapa);
tMapa MovimentaFVB(tMapa dadosMapa);
tMapa ParaDeEsperarPacmanFVC(tMapa dadosMapa);
tMapa ParaDeEsperarPacmanFVB(tMapa dadosMapa);
tMapa ParaDeEsperarPacmanFHD(tMapa dadosMapa);
tMapa ParaDeEsperarPacmanFHE(tMapa dadosMapa);
tMapa MovimentaFHE(tMapa dadosMapa);
tMapa MovimentaFHD(tMapa dadosMapa);
tMapa MovimentaFVC(tMapa dadosMapa);
tMapa MovimentaFVB(tMapa dadosMapa);
int EsperouPacmanFHE(tMapa dadosMapa);
int EsperouPacmanFHD(tMapa dadosMapa);
int EsperouPacmanFVC(tMapa dadosMapa);
int EsperouPacmanFVB(tMapa dadosMapa);

//MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN-MAIN

int main(int argc, char **argv){
    tJogo jogo;
    int acabouOJogo=0;
    FILE * mapaInicial;
   char diretorio[1001];
   int pontuacao, perdeu=0, ganhou=0;
    jogo = LimpaTudo(jogo);
    if(argc < 2){
        printf("ERRO: O diretorio de arquivos de configuracao nao foi informado");
        return 1;
    }

    strcpy(diretorio, argv[1]);
    jogo = ArmazenaDiretorio(jogo, diretorio);
    strcat(diretorio, "/mapa.txt");
    mapaInicial = fopen(diretorio, "r");
    if(mapaInicial == NULL){
        printf("ERRO: Nao foi possivel ler o arquivo 'mapa.txt' no diretorio %s.", argv[1]);
        return 1;
    } 

    //Arquivo do mapa eh lido pela funcao LerMapa e armazenado na mega-struct jogo.
    jogo = LerMapa(jogo, mapaInicial);
    InicializarJogo(jogo);
    fclose(mapaInicial);

    //aproveito nesse atribui inicio e igualo qtd jogadas com total fixo de jogadas pra usar no resumo
    jogo = AtribuiInicio(jogo);
    jogo = ZeraEsperaPacman(jogo);

    //EXTRAS: 
    /*
    --nao afeta em nada nas saidas.
    tirei jogo.dadosMapa.movimentosNaoPontuados = 0, pois, devido a falta de atencao, nao removi
    esses dois pontos pra acessar struct, eu estava testando e esqueci de retirar. Inicializo agora na funcao LimpaDadosMapa.*/

    while( !acabouOJogo ){
        
        jogo = LeJogadas(jogo);
        jogo = RealizarJogo(jogo);
        //jogo = DecrementaJogadas(jogo);
        acabouOJogo = AcabouOJogo(jogo);
        jogo = AcrescentaInicio(jogo);

        //se perdeu:
        perdeu = VocePerdeu(jogo);
        if(perdeu){
            pontuacao = AcessaMapa(jogo);
            printf("Game over!\nPontuacao final: %d\n", pontuacao);
        }

        //se ganhou:
        ganhou = VoceGanhou(jogo);
        if(ganhou){
            pontuacao = AcessaMapa(jogo);
            printf("Voce venceu!\nPontuacao final: %d\n", pontuacao);
        }
    }
    GeraEstatisticas(jogo);
    GerarTrilha(jogo);
    return 0;
}

//=============================DESKTOP====================================================
//funcoes do jogo em si.
void InicializarJogo(tJogo jogo){
    int linhaAtual=PosicaoLinhaPacman(jogo.dadosMapa), colunaAtual=PosicaoColunaPacman(jogo.dadosMapa), a, b,
    linhas=AcessoLinhas(jogo.dadosMapa), colunas=AcessoColunas(jogo.dadosMapa);
    FILE * inicializar;
    char diretorioInicializacao[1026], celulaDoMapa;
    //1000 caracteres para o diretorio, 25 para /saidas em diante e +1 para o \0. nao esquecer!!!

    strcpy(diretorioInicializacao, jogo.diretorioJogo);
    strcat(diretorioInicializacao, "/saida/inicializacao.txt");
    inicializar = fopen(diretorioInicializacao, "w");
    //o FOR das colunas tem que ir ate colunas+1 para incluir o \n
    for(a=0; a<linhas; a++){
        for(b=0; b<=colunas;b++){
            celulaDoMapa = AcessaCelulaMapa(jogo.dadosMapa, a, b);
            fprintf(inicializar, "%c", celulaDoMapa);
        }
    }
    fprintf(inicializar, "Pac-Man comecara o jogo na linha %d e coluna %d", linhaAtual+1, colunaAtual+1);
    fclose(inicializar);
}
tJogo LerMapa(tJogo jogo, FILE * mapaInicial){
    tJogo jogo2=jogo;
    int a, b, qtdLinhas, qtdColunas;
    char celulaDoMapa;
        fscanf(mapaInicial, "%d %d %d", &qtdLinhas, &qtdColunas, &jogo2.qtdJogadas);
        fscanf(mapaInicial, "%*c");
        jogo2.dadosMapa = ArmazenaLinhasColunas(jogo2.dadosMapa, qtdLinhas, qtdColunas);
        
        for(a=0; a<qtdLinhas; a++){
            // o FOR das colunas tem que ir até colunas+1 para incluir o \n
            for(b=0; b<=qtdColunas; b++){
                fscanf(mapaInicial, "%c", &celulaDoMapa);
                jogo2.dadosMapa = AtribuiCelulaMapa(jogo2.dadosMapa, a, b, celulaDoMapa);
            }
        }   
    return jogo2;
}
tJogo LeJogadas(tJogo jogo){
    tJogo jogo2;
    jogo2 = jogo;
    char movimento;
    scanf("%c", &movimento);
    //limpar \n da entrada padrao.
    scanf("%*c");
    jogo2.movimentoAtual = movimento;
    return jogo2;
}
int AcabouOJogo(tJogo jogo){
    int bateuFantasma, acabouComida, temJogadas;
    bateuFantasma = PacmanColidiuFantasma(jogo.dadosMapa);
    acabouComida = AcabouComida(jogo.dadosMapa);
    temJogadas = HouverQtdJogadas(jogo);

    if( bateuFantasma || acabouComida || !temJogadas ){
        return 1;
    }
    return 0;
}
int HouverQtdJogadas(tJogo jogo){
    return jogo.qtdJogadas;
}
tJogo DecrementaJogadas(tJogo jogo){
    tJogo jogo2;
    jogo2=jogo;
    jogo2.qtdJogadas-=1;
    return jogo2;
}
tJogo AtribuiInicio(tJogo jogo){
    tJogo jogo2=jogo;
    jogo2.inicio = 0;
    jogo2.totalJogadasFixa = jogo2.qtdJogadas;
    return jogo2;
}
tJogo AcrescentaInicio(tJogo jogo){
    tJogo jogo2=jogo;
    jogo2.inicio = jogo2.inicio + 1;
    return jogo2;
}
int VocePerdeu(tJogo jogo){
    int temJogadas = HouverQtdJogadas(jogo);
    int bateuFantasma = PacmanColidiuFantasma(jogo.dadosMapa);
    if(temJogadas == 0 || bateuFantasma == 1){
        return 1;
    }
    return 0;
}
int VoceGanhou(tJogo jogo){
    if(AcabouComida(jogo.dadosMapa) && !VocePerdeu(jogo)){
        return 1;
    }
    return 0;
}
void GeraEstatisticas(tJogo jogo){
    char diretorio[1026];
    int qtdMovimentosFinal = TotalDeMovimentos(jogo.dadosMapa);
    int movimentosNaoPontuados = TotalMovNaoPontuados(jogo.dadosMapa);
    int colisoesParede = AcessaColisoes(jogo.dadosMapa), totalSetaCima = TotalSetaCima(jogo.dadosMapa);
    int totalSetaBaixo = TotalSetaBaixo(jogo.dadosMapa), totalSetaE = TotalSetaE(jogo.dadosMapa);
    int totalSetaD = TotalSetaD(jogo.dadosMapa);
    strcpy(diretorio, jogo.diretorioJogo);
    strcat(diretorio, "/saida/estatisticas.txt");
    FILE * estatisticas=fopen(diretorio, "w");
    fprintf(estatisticas, "Numero de movimentos: %d\n", qtdMovimentosFinal);
    fprintf(estatisticas, "Numero de movimentos sem pontuar: %d\n", movimentosNaoPontuados);
    fprintf(estatisticas, "Numero de colisoes com parede: %d\n", colisoesParede);
    fprintf(estatisticas, "Numero de movimentos para baixo: %d\n", totalSetaBaixo);
    fprintf(estatisticas, "Numero de movimentos para cima: %d\n", totalSetaCima);
    fprintf(estatisticas, "Numero de movimentos para esquerda: %d\n", totalSetaE);
    fprintf(estatisticas, "Numero de movimentos para direita: %d\n", totalSetaD);
    fclose(estatisticas);
}
tJogo ArmazenaDiretorio(tJogo jogo, char diretorio[1001]){
    tJogo jogo2=jogo;
    strcpy(jogo2.diretorioJogo, diretorio);
    return jogo2;
}
void GerarResumo(char opcao, char diretorio[1001], char movimento, int qtdJogadas, int totalJogadasFixo){
    int numMovimentoAtual = totalJogadasFixo+1 - qtdJogadas;
    char diretorioJogo[1026];
    strcpy(diretorioJogo, diretorio);
    strcat(diretorioJogo, "/saida/resumo.txt");
    FILE * resumo=fopen(diretorioJogo, "a");
    if(opcao == RESUMO_FANTASMA){
        fprintf(resumo, "Movimento %d (%c) fim de jogo por encostar em um fantasma\n", numMovimentoAtual, movimento);
    }
    if(opcao == RESUMO_PAREDE){
        fprintf(resumo, "Movimento %d (%c) colidiu na parede\n", numMovimentoAtual, movimento);
    }
    if(opcao == RESUMO_COMIDA){
        fprintf(resumo, "Movimento %d (%c) pegou comida\n", numMovimentoAtual, movimento);
    }
    fclose(resumo);
}
tJogo RastrearTrilha(tJogo jogo, tMapa dadosMapa, int qtdJogadas, int totalJogadasFixa){
    int a,b;
    tJogo jogo2=jogo;
    if(jogo.inicio==0){
        for(a=0; a<dadosMapa.qtdLinhas; a++){
            for(b=0;b<dadosMapa.qtdColunas; b++){    

                //faco um mapa com numeros. 5 eh o valor da parede
                if(dadosMapa.mapa[a][b] != PAC_MAN){

                    //mapeiaRastro apenas ve por onde ele passou
                    jogo2.mapeiaRastro[a][b] = 5;
                    //mapeiaMovimentos eh a matriz que atribui os movimentos em si
                    jogo2.mapeiaMovimentos[a][b] = 5;
                }
                else if(dadosMapa.mapa[a][b] == PAC_MAN) {

                    //1 eh o valor do pacman.
                    jogo2.mapeiaRastro[a][b] = 1;

                    //recebe movimento atual
                    //essa subtracao sempre resultara no movimento atual
                    jogo2.mapeiaMovimentos[a][b] = totalJogadasFixa - qtdJogadas;
                }
           }
        }       
    }
    else{
        for(a=0; a<dadosMapa.qtdLinhas; a++){
            for(b=0;b<dadosMapa.qtdColunas; b++){    
                 if(dadosMapa.mapa[a][b] == PAC_MAN) {
                    //1 eh o valor do pacman.
                    jogo2.mapeiaRastro[a][b] = 1;
                    jogo2.mapeiaMovimentos[a][b] = totalJogadasFixa - qtdJogadas;
                 }
            }
        }
    }
    return jogo2;
}
void GerarTrilha(tJogo jogo){
    int a,b;
    int linhas=AcessoLinhas(jogo.dadosMapa), colunas=AcessoColunas(jogo.dadosMapa);
    int celulaMovimentos;
    int celulaTrilha;
    char trilhaFinal[MAX_LINHAS][MAX_COLUNAS];
    char diretorioJogo[1026];

    strcpy(diretorioJogo, jogo.diretorioJogo);
    strcat(diretorioJogo, "/saida/trilha.txt");
    FILE * trilha=fopen(diretorioJogo, "w");

        for(a=0; a<linhas; a++){
            for(b=0;b<colunas; b++){

                //varro a matriz que mapeiou por onde ele percorreu
                celulaTrilha = AcessaCelulaRastro(jogo, a, b);
                //se foi 5, recebe 1.
                if(celulaTrilha == 5){
                    trilhaFinal[a][b] = PAREDE;
                    fprintf(trilha, "%c ", trilhaFinal[a][b]);
                }
                else if(celulaTrilha==1){
                    celulaMovimentos = AcessaCelulaMovimentos(jogo, a, b);
                    fprintf(trilha, "%d ", celulaMovimentos);
                }
                
            }
            fprintf(trilha, "\n");
        }
    fclose(trilha);
}
tJogo RealizarJogo(tJogo jogo){
     tJogo jogo2=jogo;
     int esperouPacmanFHE=0, esperouPacmanFHD=0, esperouPacmanFVC=0, esperouPacmanFVB=0;
    if(jogo2.inicio == 0){
        jogo2.dadosMapa = SentidoInicialFantasmas(jogo2.dadosMapa);
        jogo2.dadosMapa = ComidaPendenteFantasmas(jogo2.dadosMapa);
    }
    //se a prox posicao for o pacman, espera o pacman movimentar primeiro.

    jogo2 = RastrearTrilha(jogo2, jogo2.dadosMapa, jogo2.qtdJogadas, jogo2.totalJogadasFixa);

    jogo2.dadosMapa = MovimentaFantasma(jogo2.dadosMapa);
    esperouPacmanFHE=EsperouPacmanFHE(jogo2.dadosMapa);
    esperouPacmanFHD=EsperouPacmanFHD(jogo2.dadosMapa);
    esperouPacmanFVC=EsperouPacmanFVC(jogo2.dadosMapa);
    esperouPacmanFVB=EsperouPacmanFVB(jogo2.dadosMapa);
    

    jogo2.pacman = PosicaoLinhaStructPacman(jogo2.pacman, jogo2.dadosMapa);
    jogo2.pacman = PosicaoColunaStructPacman(jogo2.pacman, jogo2.dadosMapa);
    jogo2.dadosMapa = MovimentaPacman(jogo2, jogo2.inicio, jogo2.pacman, jogo2.movimentoAtual, jogo2.dadosMapa);


    //se ele esperou e a posicao futura do fantasma for igual ao do pac, colidiu, se nao, posicao futura recebe fantasma
    if(esperouPacmanFHE){
        jogo2.dadosMapa = MovimentaFHE(jogo2.dadosMapa);
        jogo2.dadosMapa = ParaDeEsperarPacmanFHE(jogo2.dadosMapa);
    }
    if(esperouPacmanFHD){
        jogo2.dadosMapa = MovimentaFHD(jogo2.dadosMapa);
        jogo2.dadosMapa = ParaDeEsperarPacmanFHD(jogo2.dadosMapa);
    }
    if(esperouPacmanFVC){
        jogo2.dadosMapa = MovimentaFVC(jogo2.dadosMapa);
        jogo2.dadosMapa = ParaDeEsperarPacmanFVC(jogo2.dadosMapa);
    }
    if(esperouPacmanFVB){
        jogo2.dadosMapa = MovimentaFVB(jogo2.dadosMapa);
        jogo2.dadosMapa = ParaDeEsperarPacmanFVB(jogo2.dadosMapa);
    }
    //decremento aqui se nao o if nao sabe se tem que rastrear de novo
    jogo2 = DecrementaJogadas(jogo2);

    int acabouOJogo = AcabouOJogo(jogo2);
    int acabouComida = AcabouComida(jogo2.dadosMapa);
    int pacmanBateuFantasma=PacmanColidiuFantasma(jogo2.dadosMapa);
    int temJogadas = HouverQtdJogadas(jogo);
    
   if((acabouOJogo==1)){
        //jogo2.qtdJogadas-=1;
        jogo2 = RastrearTrilha(jogo2, jogo2.dadosMapa, jogo2.qtdJogadas, jogo2.totalJogadasFixa);
    }

    ImprimeMapa(jogo2, jogo2.movimentoAtual, jogo2.dadosMapa);
    return jogo2;
}


//funcoes do pacman.
int PosicaoLinhaPacman(tMapa dadosMapa){
    int a,b,c;
    for(a=0; a<dadosMapa.qtdLinhas; a++){
        for(b=0; b<dadosMapa.qtdColunas; b++){
            if(dadosMapa.mapa[a][b]==PAC_MAN){
                return a;
            }
        }
    }
}
int PosicaoColunaPacman(tMapa dadosMapa){

    int a,b,c;
    for(a=0; a<dadosMapa.qtdLinhas; a++){
        for(b=0; b<dadosMapa.qtdColunas; b++){
            if(dadosMapa.mapa[a][b]==PAC_MAN){
                return b;
            }
        }
    }
}
int PacmanColidiuFantasma(tMapa dadosMapa){
    return dadosMapa.colidiuFantasma;
}
tPacman PosicaoLinhaStructPacman(tPacman pacman, tMapa dadosMapa){
    //''backup'' do pacman.
    tPacman pacman2=pacman;
    pacman2.posicaoLinhaPacman = PosicaoLinhaPacman(dadosMapa);
    return pacman2;
}
tPacman PosicaoColunaStructPacman(tPacman pacman, tMapa dadosMapa){
    tPacman pacman2=pacman;
    pacman2.posicaoColunaPacman = PosicaoColunaPacman(dadosMapa);
    return pacman2;
}
tMapa MovimentaPacman(tJogo jogo, int inicio, tPacman pacman, char movimentoAtual, tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    char parede = RESUMO_PAREDE, pontos = RESUMO_COMIDA, morreu = RESUMO_FANTASMA;
    if(inicio == 0){
        dadosMapa2.pontuacao=0;
        dadosMapa2.totalMovimentos=0;
        dadosMapa2.movimentosNaoPontuados=0;
        dadosMapa2.qtdSetaCima=0;
        dadosMapa2.qtdSetaBaixo=0;
        dadosMapa2.qtdSetaE=0;
        dadosMapa2.qtdSetaD=0;
        dadosMapa2.colisoesParede=0;
    }
    //flag de comida
    int flagPontos1=dadosMapa2.pontuacao;
    int flagColisoesParede1=dadosMapa2.colisoesParede;
    if(movimentoAtual == SETA_CIMA){
        dadosMapa2 = MoverPacmanCima(pacman, dadosMapa);
        dadosMapa2.qtdSetaCima+=1;
    }
    else if(movimentoAtual == SETA_BAIXO){
        dadosMapa2 = MoverPacmanBaixo(pacman, dadosMapa);
        dadosMapa2.qtdSetaBaixo+=1;
    }
    else if(movimentoAtual == SETA_E){
        dadosMapa2 = MoverPacmanEsquerda(pacman, dadosMapa);
        dadosMapa2.qtdSetaE+=1;
    }
    else if(movimentoAtual == SETA_D){
        dadosMapa2 = MoverPacmanDireita(pacman, dadosMapa);
        dadosMapa2.qtdSetaD+=1;
    }
    //segunda flag de comida
    int flagPontos2=dadosMapa2.pontuacao;
     if(flagPontos1==flagPontos2){
        dadosMapa2.movimentosNaoPontuados+=1;
    }
    dadosMapa2.totalMovimentos+=1;
    //a medida que o pacman vai fazendo movimentos significativos, eh imediatamente impresso no resumo.
    //verifica colisao com fantasma
    if(dadosMapa2.colidiuFantasma){
        GerarResumo(morreu, jogo.diretorioJogo, movimentoAtual, jogo.qtdJogadas, jogo.totalJogadasFixa);
    }
    //flag de parede
    int flagColisoesParede2=dadosMapa2.colisoesParede;
    if(flagColisoesParede1<flagColisoesParede2){
        GerarResumo(parede, jogo.diretorioJogo, movimentoAtual, jogo.qtdJogadas, jogo.totalJogadasFixa);
    }
    //flag de comida para resumo
    if(flagPontos1 < flagPontos2){
        GerarResumo(pontos, jogo.diretorioJogo, movimentoAtual, jogo.qtdJogadas, jogo.totalJogadasFixa);
    }
    

    return dadosMapa2;
}
tMapa MoverPacmanCima(tPacman pacman, tMapa dadosMapa){
    int a,b;
    tMapa dadosMapa2=dadosMapa;
    int ehFantasma=EhFantasma(dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman]);
    int acabouTudo=0;

    for(a=0; a<dadosMapa2.qtdLinhas; a++){
        for(b=0; b<dadosMapa2.qtdColunas; b++){
            if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
               dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman] != PAREDE){
                if(ehFantasma==1){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.colidiuFantasma=1;
                    acabouTudo++;
                    break;
                }
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman] == COMIDA){
                    dadosMapa2.pontuacao++;
                }
                
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman] == COMIDA_ESPECIAL){
                    dadosMapa2.pontuacao += 5;
                }

                if(!(dadosMapa2.colidiuFantasma)){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman] = PAC_MAN;
                }
                break;
            }
            else if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman-1][pacman.posicaoColunaPacman] == PAREDE){
                    dadosMapa2.colisoesParede+=1;
                }
            if(acabouTudo){
                break;
            }
        }
        if(acabouTudo){
            break;
        }
    } 
    return dadosMapa2;
}
tMapa MoverPacmanBaixo(tPacman pacman, tMapa dadosMapa){
    int a,b;
    tMapa dadosMapa2=dadosMapa;
    int ehFantasma=EhFantasma(dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman]);
    int acabouTudo=0;

    /* NAO FAZ NADA SE BATER NA PAREDE. O MESMO VALE PROS OUTROS MOVIMENTOS.*/
    for(a=0; a<dadosMapa2.qtdLinhas; a++){
        for(b=0; b<dadosMapa2.qtdColunas; b++){
            if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
               dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman] != PAREDE){
                if(ehFantasma==1){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.colidiuFantasma=1;
                    acabouTudo++;
                    break;
                }
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman] == COMIDA){
                    dadosMapa2.pontuacao++;
                }
                
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman] == COMIDA_ESPECIAL){
                    dadosMapa2.pontuacao+=5;
                }

                if(!(dadosMapa2.colidiuFantasma)){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman] = PAC_MAN;
                }
                break;
            }
            else if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman+1][pacman.posicaoColunaPacman] == PAREDE){
                        dadosMapa2.colisoesParede+=1;
                    }
            
            if(acabouTudo){
                break;
            }
        }
        if(acabouTudo){
            break;
        }
    } 
    return dadosMapa2; 
}
tMapa MoverPacmanEsquerda(tPacman pacman, tMapa dadosMapa){
    int a,b;
    tMapa dadosMapa2=dadosMapa;
    int ehFantasma=EhFantasma(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1]);
    int acabouTudo=0;

    /* NAO FAZ NADA SE BATER NA PAREDE. O MESMO VALE PROS OUTROS MOVIMENTOS.*/
    for(a=0; a<dadosMapa2.qtdLinhas; a++){
        for(b=0; b<dadosMapa2.qtdColunas; b++){
            if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
               dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1] != PAREDE){

                if(ehFantasma==1){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.colidiuFantasma=1;
                    acabouTudo++;
                    break;
                }
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1] == COMIDA){
                    dadosMapa2.pontuacao++;
                }
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1] == COMIDA_ESPECIAL){
                    dadosMapa2.pontuacao+=5;
                }

               if(!(dadosMapa2.colidiuFantasma)){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1] = PAC_MAN;
                }
                break;
            }
            else if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
                dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman-1] == PAREDE){
                    dadosMapa2.colisoesParede+=1;
            }
            if(acabouTudo){
                break;
            }
        }
        if(acabouTudo){
            break;
        }
    } 
    return dadosMapa2; 
}
tMapa MoverPacmanDireita(tPacman pacman, tMapa dadosMapa){
    int a,b;
    tMapa dadosMapa2=dadosMapa;
    int ehFantasma = EhFantasma(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1]);
    int acabouTudo=0;

    /* NAO FAZ NADA SE BATER NA PAREDE. O MESMO VALE PROS OUTROS MOVIMENTOS.*/
    for(a=0; a<dadosMapa2.qtdLinhas; a++){
        for(b=0; b<dadosMapa2.qtdColunas; b++){
            if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
               dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1] != PAREDE){

                
                if(ehFantasma){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.colidiuFantasma=1;
                    acabouTudo++;
                    break;
                }
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1] == COMIDA){
                    dadosMapa2.pontuacao++;
                }
                
                if(dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1] == COMIDA_ESPECIAL){
                    dadosMapa2.pontuacao+=5;
                }

                if(!(dadosMapa2.colidiuFantasma)){
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] = ' ';
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1] = PAC_MAN;
                }
                break;
            }
            else if(dadosMapa2.mapa[a][b] == dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman] && 
                    dadosMapa2.mapa[pacman.posicaoLinhaPacman][pacman.posicaoColunaPacman+1] == PAREDE){
                        dadosMapa2.colisoesParede+=1;
            }
            if(acabouTudo){
                break;
            }
        }
        if(acabouTudo){
            break;
        }
    } 
    return dadosMapa2; 
}

//funcoes do fantasma.
int EhFantasma(char fantasma){
    if(fantasma == FANTASMA_H_DIREITA||fantasma == FANTASMA_H_ESQUERDA||fantasma == FANTASMA_V_BAIXO|| fantasma == FANTASMA_V_CIMA){
        return 1;
    }
    return 0;
}
tMapa SentidoInicialFantasmas(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    //subir = diminuir uma linha da matriz
    dadosMapa2.sentidoFantasmaVC = -1;
    //descer = acrescentar uma linha da matriz
    dadosMapa2.sentidoFantasmaVB = 1;
    //esquerda = diminuir uma coluna da matriz
    dadosMapa2.sentidoFantasmaHE = -1;
    //direita = somar uma coluna da matriz;
    dadosMapa2.sentidoFantasmaHD = 1;
    return dadosMapa2;
}
tMapa ComidaPendenteFantasmas(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.comidaPendenteFVC = 0;
    dadosMapa2.comidaPendenteFVB = 0;
    dadosMapa2.comidaPendenteFHE=0;
    dadosMapa2.comidaPendenteFHD = 0;
    return dadosMapa2;
}
int EsperouPacmanFHE(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.esperaPacmanFHE;
}
int EsperouPacmanFHD(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.esperaPacmanFHD;
}
int EsperouPacmanFVC(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.esperaPacmanFVC;
}
int EsperouPacmanFVB(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.esperaPacmanFVB;
}
tMapa ParaDeEsperarPacmanFHE(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.esperaPacmanFHE = 0;
    return dadosMapa2;
}
tMapa ParaDeEsperarPacmanFHD(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.esperaPacmanFHD = 0;
    return dadosMapa2;
}
tMapa ParaDeEsperarPacmanFVC(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.esperaPacmanFVC = 0;
    return dadosMapa2;
}
tMapa ParaDeEsperarPacmanFVB(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.esperaPacmanFVB = 0;
    return dadosMapa2;
}
tMapa MovimentaFantasma(tMapa dadosMapa){
    int a,b, saiDoLoop=0;
    tMapa dadosMapa1=dadosMapa;
    //vertical cima = soma -1 linha|||vertical baixo = soma linha
    //horizontal esquerda = soma -1 coluna|||horizontal direita = soma coluna
        dadosMapa1 = MovimentaFHE(dadosMapa1);
        dadosMapa1 = MovimentaFHD(dadosMapa1);
        dadosMapa1 = MovimentaFVC(dadosMapa1);
        dadosMapa1 = MovimentaFVB(dadosMapa1);
        /*o FANTASMA P TÁ COMENDO A COMIDA QUANDO O PACMAN É A POSICAO FUTURA DELE EU ACHO*/
    return dadosMapa1;
}
tMapa MovimentaFHE(tMapa dadosMapa){
    int a,b, saiDoLoop=0;
    tMapa dadosMapa2=dadosMapa;
    for(a=0; a<dadosMapa2.qtdLinhas;a++){
            for(b=0; b<=dadosMapa2.qtdColunas;b++){
                if(dadosMapa2.mapa[a][b]==FANTASMA_H_ESQUERDA){
                    if(!(dadosMapa2.comidaPendenteFHE)){
                        dadosMapa2.mapa[a][b] = ' ';
                    }
                    if(dadosMapa2.comidaPendenteFHE){
                        dadosMapa2.mapa[a][b] = COMIDA;
                        dadosMapa2.comidaPendenteFHE = 0;
                    }
                    if(dadosMapa2.comidaEspecialPendenteFHE){
                        dadosMapa2.mapa[a][b] = COMIDA_ESPECIAL;
                        dadosMapa2.comidaEspecialPendenteFHE=0;
                    }                    
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == PAREDE){
                        dadosMapa2.sentidoFantasmaHE = dadosMapa2.sentidoFantasmaHE * (-1);
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == ' '){
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] = FANTASMA_H_ESQUERDA;
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == COMIDA){
                        dadosMapa2.comidaPendenteFHE = 1;
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] = FANTASMA_H_ESQUERDA;
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == COMIDA_ESPECIAL){
                        dadosMapa2.comidaEspecialPendenteFHE = 1;
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] = FANTASMA_H_ESQUERDA;
                    }

                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == PAC_MAN){
                        /*se ele esperou o pacman, e a posicao futura do fantasma é igual a do pacman, colidiuFantasma.
                          se nao eh igual a do pacman, a posicao futura do fantasma recebe fantasma*/

                          //esperaPacman inicialmente eh zero.
                        if(dadosMapa2.esperaPacmanFHE){
                            if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] == PAC_MAN){
                                dadosMapa2.colidiuFantasma=1;
                            }
                            else{
                                dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] = FANTASMA_H_ESQUERDA;
                            }
                        }
                        else{
                            //fantasma permanece parado esperando pacman.
                            if(dadosMapa2.mapa[a][b] == COMIDA){
                                dadosMapa2.comidaPendenteFHE = 1;
                            }
                            if(dadosMapa2.mapa[a][b] == COMIDA_ESPECIAL){
                                dadosMapa2.comidaEspecialPendenteFHE = 1;
                            }
                            dadosMapa2.mapa[a][b]= FANTASMA_H_ESQUERDA;
                            dadosMapa2.esperaPacmanFHE=1;
                        }
                    }
                    //&&dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaXXXX] == ' '
                    if(dadosMapa2.esperaPacmanFHE && dadosMapa2.colidiuFantasma==1){
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHE] = FANTASMA_H_ESQUERDA;
                    }
                    saiDoLoop++; 
                }
                if(saiDoLoop){
                    break;
                }                    
            }
            if(saiDoLoop){
                break;
            }
        } 
        return dadosMapa2;
}
tMapa MovimentaFHD(tMapa dadosMapa){
    int a,b, saiDoLoop=0;
    tMapa dadosMapa2=dadosMapa;
    for(a=0; a<dadosMapa2.qtdLinhas;a++){
            for(b=0; b<=dadosMapa2.qtdColunas;b++){
                if(dadosMapa2.mapa[a][b]==FANTASMA_H_DIREITA){
                    if(!(dadosMapa2.comidaPendenteFHD)){
                        dadosMapa2.mapa[a][b] = ' ';
                    }
                    if(dadosMapa2.comidaPendenteFHD){
                        dadosMapa2.mapa[a][b] = COMIDA;
                        dadosMapa2.comidaPendenteFHD = 0;
                    }
                    if(dadosMapa2.comidaEspecialPendenteFHD){
                        dadosMapa2.mapa[a][b] = COMIDA_ESPECIAL;
                        dadosMapa2.comidaEspecialPendenteFHD = 0;
                    }

                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == PAREDE){
                        dadosMapa2.sentidoFantasmaHD = dadosMapa2.sentidoFantasmaHD * (-1);
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == ' '){
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] = FANTASMA_H_DIREITA;
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == COMIDA){
                        dadosMapa2.comidaPendenteFHD = 1;
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] = FANTASMA_H_DIREITA;
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == COMIDA_ESPECIAL){
                        dadosMapa2.comidaEspecialPendenteFHD = 1;
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] = FANTASMA_H_DIREITA;
                    }
                    if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == PAC_MAN){
                        /*se ele esperou o pacman, e a posicao futura do fantasma é igual a do pacman, colidiuFantasma.
                          se nao eh igual a do pacman, a posicao futura do fantasma recebe fantasma*/

                          //esperaPacman inicialmente eh zero.
                        if(dadosMapa2.esperaPacmanFHD){
                            if(dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] == PAC_MAN){
                                dadosMapa2.colidiuFantasma=1;
                            }
                            else{
                                dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] = FANTASMA_H_DIREITA;
                            }
                        }
                        else{
                            //fantasma permanece parado esperando pacman.
                            if(dadosMapa2.mapa[a][b] == COMIDA){
                                dadosMapa2.comidaPendenteFHD = 1;
                            }
                            if(dadosMapa2.mapa[a][b] == COMIDA_ESPECIAL){
                                dadosMapa2.comidaEspecialPendenteFHD = 1;
                            }
                            dadosMapa2.mapa[a][b]= FANTASMA_H_DIREITA;
                            dadosMapa2.esperaPacmanFHD=1;
                        }
                    }
                    //&dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaXXXX] == ' '
                    if(dadosMapa2.esperaPacmanFHD && dadosMapa2.colidiuFantasma==1){
                        dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaHD] = FANTASMA_H_DIREITA;
                    }
                    saiDoLoop++; 
                }
                if(saiDoLoop){
                    break;
                }                    
            }
            if(saiDoLoop){
                break;
            }
        } 
        return dadosMapa2;
}
tMapa MovimentaFVC(tMapa dadosMapa){
    int a,b, saiDoLoop=0;
    tMapa dadosMapa2=dadosMapa;
    for(a=0; a<dadosMapa2.qtdLinhas;a++){
            for(b=0; b<=dadosMapa2.qtdColunas;b++){
                if(dadosMapa2.mapa[a][b]==FANTASMA_V_CIMA){
                    if(!(dadosMapa2.comidaPendenteFVC)){
                        dadosMapa2.mapa[a][b] = ' ';
                    }
                    if(dadosMapa2.comidaPendenteFVC){
                        dadosMapa2.mapa[a][b] = COMIDA;
                        dadosMapa2.comidaPendenteFVC = 0;
                    }  
                     if(dadosMapa2.comidaEspecialPendenteFVC){
                        dadosMapa2.mapa[a][b] = COMIDA_ESPECIAL;
                        dadosMapa2.comidaEspecialPendenteFVC = 0;
                    }                   
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == PAREDE){
                        dadosMapa2.sentidoFantasmaVC = dadosMapa2.sentidoFantasmaVC * (-1);
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == ' '){
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] = FANTASMA_V_CIMA;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == COMIDA){
                        dadosMapa2.comidaPendenteFVC = 1;
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] = FANTASMA_V_CIMA;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == COMIDA_ESPECIAL){
                        dadosMapa2.comidaEspecialPendenteFVC = 1;
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] = FANTASMA_V_CIMA;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == PAC_MAN){
                        /*se ele esperou o pacman, e a posicao futura do fantasma é igual a do pacman, colidiuFantasma.
                          se nao eh igual a do pacman, a posicao futura do fantasma recebe fantasma*/

                          //esperaPacman inicialmente eh zero.
                        if(dadosMapa2.esperaPacmanFVC){
                            if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] == PAC_MAN){
                                dadosMapa2.colidiuFantasma=1;
                            }
                            else{
                                dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] = FANTASMA_V_CIMA;
                            }
                        }
                        else{
                            //fantasma permanece parado esperando pacman.
                            if(dadosMapa2.mapa[a][b] == COMIDA){
                                dadosMapa2.comidaPendenteFVC = 1;
                            }
                            if(dadosMapa2.mapa[a][b] == COMIDA_ESPECIAL){
                                dadosMapa2.comidaEspecialPendenteFVC = 1;
                            }
                            dadosMapa2.mapa[a][b]= FANTASMA_V_CIMA;
                            dadosMapa2.esperaPacmanFVC=1;
                        }
                    }
                    //&&dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaXXXX] == ' '
                    if(dadosMapa2.esperaPacmanFVC && dadosMapa2.colidiuFantasma==1){
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVC][b] = FANTASMA_V_CIMA;
                    }
                    saiDoLoop++; 
                }
                if(saiDoLoop){
                    break;
                }                    
            }
            if(saiDoLoop){
                break;
            }
        } 
        return dadosMapa2;
}
tMapa MovimentaFVB(tMapa dadosMapa){
    int a,b, saiDoLoop=0;
    tMapa dadosMapa2=dadosMapa;
    for(a=0; a<dadosMapa2.qtdLinhas;a++){
            for(b=0; b<=dadosMapa2.qtdColunas;b++){
                if(dadosMapa2.mapa[a][b]==FANTASMA_V_BAIXO){
                    if(!(dadosMapa2.comidaPendenteFVB)){
                        dadosMapa2.mapa[a][b] = ' ';
                    }
                    if(dadosMapa2.comidaPendenteFVB){
                        dadosMapa2.mapa[a][b] = COMIDA;
                        dadosMapa2.comidaPendenteFVB = 0;                
                    }   
                    if(dadosMapa2.comidaEspecialPendenteFVB){
                        dadosMapa2.mapa[a][b] = COMIDA_ESPECIAL;
                        dadosMapa2.comidaEspecialPendenteFVB = 0;                
                    }                
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == PAREDE){
                        dadosMapa2.sentidoFantasmaVB = dadosMapa2.sentidoFantasmaVB * (-1);
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == ' '){
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] = FANTASMA_V_BAIXO;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == COMIDA){
                        dadosMapa2.comidaPendenteFVB = 1;
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] = FANTASMA_V_BAIXO;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == COMIDA_ESPECIAL){
                        dadosMapa2.comidaEspecialPendenteFVB = 1;
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] = FANTASMA_V_BAIXO;
                    }
                    if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == PAC_MAN){
                        /*se ele esperou o pacman, e a posicao futura do fantasma é igual a do pacman, colidiuFantasma.
                          se nao eh igual a do pacman, a posicao futura do fantasma recebe fantasma*/

                          //esperaPacman inicialmente eh zero.
                        if(dadosMapa2.esperaPacmanFVB){
                            if(dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] == PAC_MAN){
                         
                                dadosMapa2.colidiuFantasma=1;
                            }
                            else{
                                dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] = FANTASMA_V_BAIXO;
                            }
                        }
                        else{
                            //fantasma permanece parado esperando pacman.
                            if(dadosMapa2.mapa[a][b] == COMIDA){
                                dadosMapa2.comidaPendenteFVB = 1;
                            }
                            if(dadosMapa2.mapa[a][b] == COMIDA_ESPECIAL){
                                dadosMapa2.comidaEspecialPendenteFVB = 1;
                            }
                            dadosMapa2.mapa[a][b]= FANTASMA_V_BAIXO;
                            dadosMapa2.esperaPacmanFVB=1;
                        }
                    }
                     //&&dadosMapa2.mapa[a][b+dadosMapa2.sentidoFantasmaXXXX] == ' '
                    if(dadosMapa2.esperaPacmanFVB && dadosMapa2.colidiuFantasma==1){
                        dadosMapa2.mapa[a+dadosMapa2.sentidoFantasmaVB][b] = FANTASMA_V_BAIXO;
                    }
                    saiDoLoop++; 
                }
                if(saiDoLoop){
                    break;
                }                    
            }
            if(saiDoLoop){
                break;
            }
        } 
        return dadosMapa2;
}
tJogo ZeraEsperaPacman(tJogo jogo){
    tJogo jogo2=jogo;
    jogo2.dadosMapa = ParaDeEsperarPacmanFHE(jogo2.dadosMapa);
    jogo2.dadosMapa = ParaDeEsperarPacmanFHD(jogo2.dadosMapa);
    jogo2.dadosMapa = ParaDeEsperarPacmanFVC(jogo2.dadosMapa);
    jogo2.dadosMapa = ParaDeEsperarPacmanFVB(jogo2.dadosMapa);
    return jogo2;
}

//funcoes do mapa.
int AcabouComida(tMapa dadosMapa){
    int a,b;
    int comidaPendente;
    //verifica se algum dos fantasmas esta por cima da comida escondendo do pacman.
    comidaPendente = dadosMapa.comidaPendenteFVC;
    if(comidaPendente){
        return 0;
    }
    comidaPendente = dadosMapa.comidaPendenteFVB;
    if(comidaPendente){
        return 0;
    }
    comidaPendente = dadosMapa.comidaPendenteFHE;
    if(comidaPendente){
        return 0;
    }
    comidaPendente = dadosMapa.comidaPendenteFHD;
    if(comidaPendente){
        return 0;
    }

    for(a=0; a<dadosMapa.qtdLinhas; a++){
        for(b=0; b<dadosMapa.qtdColunas;b++){
            if(dadosMapa.mapa[a][b]==COMIDA){
                return 0;
            }
        }
    }
    return 1;
}
int AcessoLinhas(tMapa dadosMapa){
    return dadosMapa.qtdLinhas;
}
int AcessoColunas(tMapa dadosMapa){
    return dadosMapa.qtdColunas;
}
void ImprimeMapa(tJogo jogo, char movimento, tMapa dadosMapa){
    int a,b;
    int perdeu;
    tJogo jogo2=jogo;
    perdeu = VocePerdeu(jogo2);
    if(perdeu==0){
        printf("Estado do jogo apos o movimento '%c':\n", movimento);
        for(a=0; a<dadosMapa.qtdLinhas; a++){
            for(b=0; b<=dadosMapa.qtdColunas; b++){
                printf("%c", dadosMapa.mapa[a][b]);
            }
        }
        printf("Pontuacao: %d\n\n", dadosMapa.pontuacao);
    }
    else{
        printf("Estado do jogo apos o movimento '%c':\n", movimento);
        for(a=0; a<dadosMapa.qtdLinhas; a++){
            for(b=0; b<=dadosMapa.qtdColunas; b++){
                printf("%c", dadosMapa.mapa[a][b]);
            }
        }
        printf("Pontuacao: %d\n\n", dadosMapa.pontuacao);
    }
}
int AcessaMapa(tJogo jogo){
    tJogo jogo2=jogo;
    int pontuacao=AcessaPontuacao(jogo.dadosMapa);
    return pontuacao;
}
int AcessaPontuacao(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.pontuacao;
}
int TotalSetaCima(tMapa dadosMapa){
    return dadosMapa.qtdSetaCima;
}
int TotalSetaBaixo(tMapa dadosMapa){
    return dadosMapa.qtdSetaBaixo;
}
int TotalSetaE(tMapa dadosMapa){
    return dadosMapa.qtdSetaE;
}
int TotalSetaD(tMapa dadosMapa){
    return dadosMapa.qtdSetaD;
}
tMapa ArmazenaLinhasColunas(tMapa dadosMapa, int linhas, int colunas){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.qtdLinhas=linhas;
    dadosMapa2.qtdColunas=colunas;
    return dadosMapa2;
}
tMapa AtribuiCelulaMapa(tMapa dadosMapa, int a, int b, char celula){
    tMapa dadosMapa2=dadosMapa;
    dadosMapa2.mapa[a][b] = celula;
    return dadosMapa2;
}
char AcessaCelulaMapa(tMapa dadosMapa, int a, int b){
    return dadosMapa.mapa[a][b];
}
int AcessaColisoes(tMapa mapa){
    return mapa.colisoesParede;
}
int TotalDeMovimentos(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.totalMovimentos;
}
int TotalMovNaoPontuados(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    return dadosMapa2.movimentosNaoPontuados;
}
tJogo LimpaTudo(tJogo jogo){
    tJogo jogo2=jogo;
    jogo2.inicio=0;
    jogo2.qtdJogadas=0;
    jogo2.dadosMapa=LimpaDadosMapa(jogo2.dadosMapa);
    jogo2.totalJogadasFixa=0;
    return jogo2;
}
tMapa LimpaDadosMapa(tMapa dadosMapa){
    tMapa dadosMapa2=dadosMapa;
    //limpa quase todos...
    dadosMapa2.qtdLinhas=0;
    dadosMapa2.qtdColunas=0;
    dadosMapa2.colidiuFantasma=0;
    dadosMapa2.pontuacao=0;
    dadosMapa2.sentidoFantasmaVC=0;
    dadosMapa2.sentidoFantasmaVB=0;
    dadosMapa2.sentidoFantasmaHE=0;
    dadosMapa2.sentidoFantasmaHD=0;
    dadosMapa2.comidaPendenteFVC=0;
    dadosMapa2.comidaPendenteFVB=0;
    dadosMapa2.comidaPendenteFHE=0;
    dadosMapa2.comidaPendenteFHD=0;
    dadosMapa2.esperaPacmanFVC=0;
    dadosMapa2.esperaPacmanFVB=0;
    dadosMapa2.esperaPacmanFHE=0;
    dadosMapa2.esperaPacmanFHD=0;
    dadosMapa2.totalMovimentos=0;
    dadosMapa2.movimentosNaoPontuados=0; 
    dadosMapa2.colisoesParede=0;
    dadosMapa2.qtdSetaCima=0;
    dadosMapa2.qtdSetaBaixo=0;
    dadosMapa2.qtdSetaE=0;
    dadosMapa2.qtdSetaD=0;
    dadosMapa2.movimentosNaoPontuados=0;
    dadosMapa2.comidaEspecialPendenteFHE = 0;
    dadosMapa2.comidaEspecialPendenteFHD = 0;
    dadosMapa2.comidaEspecialPendenteFVC = 0;
    dadosMapa2.comidaEspecialPendenteFVB = 0;

    return dadosMapa2;
}
int AcessaCelulaRastro(tJogo jogo, int a, int b){
    return jogo.mapeiaRastro[a][b];
}
int AcessaCelulaMovimentos(tJogo jogo, int a, int b){
    return jogo.mapeiaMovimentos[a][b];
}
