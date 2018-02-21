# include <stdio.h>
# include <stdlib.h>
# include <iostream>
# include <iomanip>
# include <windows.h>
# include <string.h>
# include <time.h>
# include <ctype.h>
# include <cstring>
# include <conio.h>
using namespace std;

class Campo {
    private:
        int lin,col,linGol_1,linGol_2,colGol1,colGol2;
    public:
        void Layout();
};
class Jogador {
    private:
       int ljog1,cjog1,ljog2,cjog2,flag,flag2;
    public:
       Jogador();
       void mover(char ch1,char ch2,int c11,int c12, int c13, int c21, int c22, int c23);
       int linjog1();
       int linjog2();
       int coljog1();
       int coljog2();
};
class bola {
    private:
        int col,lin,flag,flag2,del;
        static int cont1,cont2;
    public:
         bola();
         void mover(int cjog1,int ljog1, int cjog2, int ljog2);
         int ReturnGol1();
         int ReturnGol2();
         void delay(unsigned int mseconds);

};

class jogo{
   private:
	 int c11,c12,c13,c21,c22,c23,opcao, opcao2;
	 class bola bola1;
	 class Jogador p1,p2;
	 class Campo ca1;
	  public:
	 jogo();
	 void comecaJogo();
};

class Introducao{
   private:
	 int opcao;
   public:
	 Introducao();
	 void gotoxy(int x, int y);
     void delay(unsigned int mseconds);
};
void gotoxy(int x, int y){
     COORD coord;
     coord.X=x;
     coord.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void Introducao::delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void Introducao::gotoxy(int x, int y){
     COORD coord;
     coord.X=x;
     coord.Y=y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
Introducao::Introducao(){
    int x=0,p=2,y;
    char c=0;
    while(x==0){
       gotoxy(33,3);cout<<"INSTRUCOES";
       gotoxy(12,7);cout<<"Jogador 1 - w(sobe) s(desce)";
       gotoxy(12,8);cout<<"Jogador 2 - p(sobe) l(desce)";
       gotoxy(10,10);cout<<"Velocidade da Bola:";
       gotoxy(12,11);cout<<"+ (Aumenta)";
       gotoxy(12,12);cout<<"- (Diminui)";
       gotoxy(10,15);cout<<"ESC para sair do Jogo";
       gotoxy(10,17);cout<<"PAUSE para Pausar e Qualquer Tecla para Despausar";
       gotoxy(10,19);printf("ENTER para Iniciar o Jogo");delay(200);
       if(kbhit()){
          x=1;
          c=getch();
          if(c==27)
            exit(0);
        }
    }
}
void Campo::Layout(){
int x;
for(x=1;x<75;x++){
    gotoxy(x,1);printf("\xCD");//linha horizontal superior
}
gotoxy(75,1);printf("\xBB");//canto superior direito
for(x=2;x<31;x++){
    gotoxy(75,x);printf("\xBA");//linha vertical direita
}
gotoxy(75,26);printf("\xB9");//canto inferior direito
for(x=1;x<75;x++){
    gotoxy(x,26);printf("\xCD");//linha horizontal inferior
}
gotoxy(1,1);printf("\xC9");//desenha o canto esquerdo superior
for(x=2;x<31;x++){
    gotoxy(1,x);printf("\xBA");//linha vertical esquerda
}
gotoxy(1,26);printf("\xCC");//canto inferior esquerdo
gotoxy(1,30);printf("\xC8");//ultimo canto inferior esquerdo
for(x=2;x<75;x++){
    gotoxy(x,30);printf("\xCD");//ultima linha inferior
}
gotoxy(75,30);printf("\xBC");//ultimo canto inferior direito
gotoxy(1,20);printf("\xCC");printf("\xCD");//trave goleira esquerda inferior
gotoxy(1,10);printf("\xCC");printf("\xCD");//trave goleira esquerda superior
gotoxy(74,20);printf("\xCD");printf("\xB9");//trave goleira direita inferior
gotoxy(74,10);printf("\xCD");printf("\xB9");//trave goleira direita superior
}
//construtor Jogador
Jogador::Jogador(){
    ljog1=15;//posiciona goleiro da esquerda no meio do gol
    cjog1=3;//posiciona goleiro da esquerda na coluna 3
    ljog2=15;//posiciona goleiro da direito no meio do gol
    cjog2=73;//posiciona goleiro da direita na coluna 73
    flag=1;
    flag2=1;
}
//retornar colunas e linhas dos Jogadores
int Jogador::coljog1(){
    return(cjog1);
}
int Jogador::coljog2(){
    return(cjog2);
}
int Jogador::linjog1(){
    return(ljog1);
}
int Jogador::linjog2(){
     return(ljog2);
}
//mover Jogadores
void Jogador::mover(char ch1,char ch2,int c11,int c12, int c13, int c21, int c22, int c23){
    gotoxy(cjog1,ljog1-1); //printa os Jogadores na posicao inicial
    printf("\xDB");
    gotoxy(cjog1,ljog1);
    printf("\xDB");
    gotoxy(cjog1,ljog1+1);
    printf("\xDB");
    gotoxy(cjog2,ljog2-1);
    printf("\xDB");
    gotoxy(cjog2,ljog2);
    printf("\xDB");
    gotoxy(cjog2,ljog2+1);
    printf("\xDB");
    if(ch1!=0){ //se o caractere ch1 que veio como parametro for != 0 entao ‚ caractere normal
	   gotoxy(cjog1,ljog1-1);    //apaga Jogador
	   cout<<" ";
	   gotoxy(cjog1,ljog1);
	   cout<<" ";
	   gotoxy(cjog1,ljog1+1);
	   cout<<" ";
	   gotoxy(cjog2,ljog2-1);   //apaga Jogador
	   cout<<" ";
	   gotoxy(cjog2,ljog2);
	   cout<<" ";
	   gotoxy(cjog2,ljog2+1);
	   cout<<" ";
	    switch(ch1){    //escolhe qual tecla
            case 's':
               flag=1;
               ljog1+=flag; //movimento
               if(ljog1+1==26)   //26 é o limite inferior
                ljog1-=1;
               if(ljog1+1==ljog2-1 && cjog1==cjog2)//colidir com o outro
                ljog1-=1;                        //Jogador
            break;
    	    case 'w':
    	       flag=-1;
    	       ljog1+=flag;
    	       if(ljog1-1==1)//limite superior
                ljog1+=1;
    	       if(ljog1-1==ljog2+1 && cjog1==cjog2)
                ljog1+=1;
            break;
            case 'l':  //para baixo
    	       flag2=1;
    	       ljog2+=flag2; //mesmos testes do Jogador 1
    	       if(ljog2+1==26)//26 é o limite inferior
                ljog2-=1;
    	       if(ljog2+1==ljog1-1 && cjog1==cjog2)
                ljog2-=1;
            break;
    	    case 'p':   //para cima
    	       flag2=-1;
    	       ljog2+=flag2;
    	       if(ljog2-1==1)//1 é o limite superior
                ljog2+=1;
    	       if(ljog2-1==ljog1+1  && cjog1==cjog2)
                ljog2+=1;
            break;
	    }
	   gotoxy(cjog1,ljog1-1); //printa o Jogador na nova posicao
	   printf("\xDB");
	   gotoxy(cjog1,ljog1);
	   printf("\xDB");
	   gotoxy(cjog1,ljog1+1);
	   printf("\xDB");
	   gotoxy(cjog2,ljog2-1); //reescreve Jogador
	   printf("\xDB");
	   gotoxy(cjog2,ljog2);
	   printf("\xDB");
	   gotoxy(cjog2,ljog2+1);
	   printf("\xDB");
    }

}
//construtor da clase bola
bola::bola(){
    lin=12;
    col=40;
    flag=1;
    flag2=0;
    del=70;
 }
//mover bola
void bola::mover(int cjog1,int ljog1,int cjog2,int ljog2){//recebe as posicoes dos Jogadores

    char ch1;
    gotoxy(38,1);
    while (kbhit()){//mudar velocidade
        ch1=getch();
        if(ch1==43) //+ aumenta velocidade, logo diminui delay
           del=del-1000;
        else
           if(ch1==45)//- diminui a velocidade, logo aumenta o delay
              del=del+1000;

    }
    gotoxy(col,lin);
    cout<<" ";
    col+=flag;
    lin+=flag2;
    if (col<4)//se bater na linha de fundo esquerda
        if(lin<=18 && lin>=10){//testar se ‚ gol
            cont2++;//incrementa os gols
            gotoxy(66,27);//posiciona os gols do jogador da direita
            printf("Gols: %d",cont2);//imprimi os gols do jogador da direita
            if(lin<11) //para printar entrando dentro da goleira
                flag2=1;
              else
                 if(lin>13)
                flag2=-1;
              if(col<8)//quando chegar no fim goleira - rede
                 col=40;   //recoloca a bola em jogo
        }
        else //se nao for gol, rebate
            flag=1;
            if(col>72){ //teste se bater na linha de fundo da direita
                if(lin<=18 && lin>=10){//se for gol
                    cont1++;//incrementa os gols
                    gotoxy(4,27);//Posiciona os gols feitos pelo jogador da esquerda
                    printf("Gols: %d",cont1);//imprimi os gols realizado pelo jogador da esquerda
                    if(lin<11)  //printar bola entrando no gol
                        flag2=1;
                    else
                        if(lin>13)
                            flag2=-1;
                        if(col>72) //quando bater na rede
                            col=40; //‚ recolocada em jogo no meio do Campo
                }
                else //se nao for gol, rebate
                    flag=-1;
            }
            if(lin==ljog1 || lin==ljog1+1 || lin==ljog1-1){           //se bola bater no Jogador 1
                if(col==cjog1+1)//ve de qual lado vem a bola
                   flag=1;
                else
                    if(col==cjog1-1)
                     flag=-1;
            }

            if(lin==ljog2 || lin==ljog2+1 || lin==ljog2-1){//se a bola bater no jog 2
               if(col==cjog2+1) //analiza de qual lado veio a bola
                flag=1;
               else
                if(col==cjog2-1)
                  flag=-1;
            }
            if(lin==ljog1-2){ //se bola bater nos cantos do Jogador, parte de cima
                if(flag2!=0){//somente fara colidir se a bola nao estiver andando retilinamente
                	if(col==cjog1){//se bater na cabe‡a
                	   if(flag==1)   //novamente analiza a direcao da bola
                	       flag2=-1;
                	   else
                	      if(flag==-1)
                		    flag2=-1;
                	}
                	else
            	    if(col==cjog1-1){//colisao com canto esquerdo
                	    if(flag2==1){
                	       if(flag==1){
                		      flag2=-1;
                		      flag=-1;
                	       }
                	    }
            	    }
            	    else
        	        if(col==cjog1+1){ //colisao com canto direito
        	           if(flag2==1){
        		            if(flag==-1){
    		                  flag2=-1;
        		              flag=1;
    		                }
        		        }
        	        }
                }
            }
            if(lin==ljog1+2){//cantos do Jogador 1 , parte de baixo
                if(flag2!=0){//somente fara colidir se a bola nao estiver andando retilinamente
                	if(col==cjog1){ //colidir com o p‚
                	  if(flag==1) //ve a direcao da bola
                	     flag2=1;
                	  else
                	     if(flag==-1)
                	       flag2=1;
                	}
                	if(col==cjog1-1){//colidir com canto esquerdo
            	        if(flag2==-1){
            	           if(flag==1){
            		          flag2=1;
            		          flag=-1;
            	            }
            	        }
                	}
                	else
            	    if(col==cjog1+1){//colidir com canto direito
            	       if(flag2==-1){
            		        if(flag==-1){
            		          flag2=1;
            		          flag=1;
            		        }
            		    }
            	    }
                }
            }
            
            if(lin==ljog2-2){//Jogador 2, cantos superiores
                if(flag2!=0){ //somente fara colidir se a bola nao estiver andando retilinamente
	                if(col==cjog2){  //cabeca
                	   if(flag==1)
                	     flag2=-1;
                	   else
                	      if(flag==-1)
                		 flag2=1;
	                }
                	else
            	    if(col==cjog2-1){ //canto esquerdo
            	       if(flag2==1){
            	           if(flag==1){
            		          flag=-1;
            		          flag2=-1;
            	            }
            	        }
            	    }
            	    else
        	        if(col==cjog2+1){//canto direito
        	           if(flag2==1){
        		            if(flag==-1){
        		              flag=1;
        		              flag2=-1;
        		            }
        	            }
        	        }
                }
            }

            if(lin==ljog2+2){ //jog 2, parte inferior
                if(flag2!=0){//somente fara colidir se a bola nao estiver andando retilinamente
            	   if(col==cjog2){//pes
            	       if(flag==1)
            	           flag2=1;
            	        else
            	         if(flag==-1)
        	               flag2=1;
            	    }

            	    if(col==cjog2-1){//canto esquerdo
            	       if(flag2==-1){
            	           if(flag==1){
            		          flag=-1;
            		          flag2=1;
            	            }
            	        }
            	    }
            	    else
        	        if(col==cjog2+1){  //canto direito
        	           if(flag2==-1){
        		            if(flag==-1){
        		              flag=1;
        		              flag2=1;
                            }
        	            }
        	        }
                }
            }

            if(flag2==0){ //se a bola esta andando retilianamente, para fazer ela andar na diagonal
            	if(lin==ljog2+1){ //preciso faze ela colidir com a parte superior ou inferior do Jogadores
            	    if(col==cjog2+1)
            	      flag2=-1;    //parte inferior Jogador 2
            	    else            //testa de qual lado vem a bola, para
            	     if(col==cjog2-1) //rebate-la certo.
            	       flag2=1;
            	}
            	else
        	    if(lin==ljog2-1){     //parte superior jog 2
        	        if(col==cjog2+1)
        		      flag2=1;
        	        else
        		      if(col==cjog2-1)
        		        flag2=-1;
    	        }
            	if(lin==ljog1+1){  //parte inferior jog 1
            	    if(col==cjog1+1)
            	      flag2=+1;
            	    else
            	     if(col==cjog1-1)
            	       flag2=-1;
            	}
            	else
        	    if(lin==ljog1-1){ //parte superior jog 1
        	      if(col==cjog1+1)
        		    flag2=-1;
        	      else
        		    if(col==cjog1-1)
        		      flag2=+1;
        	    }
            }

            if(lin>23)//limite inferior do campo, rebate a bola
	           flag2=-1;
                if(lin<3)//limite superior do campo, rebate a bola
                	flag2=1;
                    gotoxy(col,lin);
                    printf("\xDC");
                    delay(del); //com delay
}
int bola::ReturnGol1(){//retorna gols do jogador 1
    return(cont1);
}

int bola::ReturnGol2(){//retorna gols do jogador 2
    return(cont2);
}

//incializar contadores de gol
int bola::cont1=0;
int bola::cont2=0;
void bola::delay(unsigned int mseconds){
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

jogo::jogo(){//contrutor da classe jogo
    bola bola1;
    Jogador p1;
    Campo ca1;
   // Placar pl1;
}
void jogo::comecaJogo(){//metodo para iniciar o jogo
    system("cls");
   char ch1,ch2;
   int x,y,lj1,cj1,lj2,cj2,gol1,gol2,aux;

   //placar do jogo
   ca1.Layout();
   gotoxy(9,0);cout<<"ESC para sair";
   gotoxy(55,0);cout<<"PAUSE para pausar";
   
   while(ch1!=27){ //enquanto nao teclar ESC continua executando o jogo
        ch1=0;
        ch2=0;
        if(kbhit()){ //capta as teclas
           ch1=getch();
           if(ch1==0)
           ch2=getch();
        }
        bola1.mover(cj1,lj1,cj2,lj2); //bola
        p1.mover(ch1,ch2,c11,c12,c13,c21,c22,c23); //Jogadores
        cj1=p1.coljog1(); //colunas e linhas dos Jogadores
        cj2=p1.coljog2();
        lj1=p1.linjog1();
        lj2=p1.linjog2();
    }
    gol1=bola1.ReturnGol1();
    gol2=bola1.ReturnGol2();
    gotoxy(35,10);cout<<"FIM DE JOGO";
    if(gol1>gol2){//resultado final
       gotoxy(21,13);
       cout<<"Jogador 1 Venceu com o Placar: P1 "<<gol1<<" X "<<gol2<<" P2";
    }
    else
      if(gol1<gol2){
        gotoxy(21,13);
        cout<<"Jogador 2 Venceu com o Placar: P1 "<<gol1<<" X "<<gol2<<" P2";
      }
      else{
           gotoxy(27,13);
           cout<<"EMPATE - Placar: P1 "<<gol1<<" X "<<gol2<<" P2";
      }
      gotoxy(24,18);cout<<"Pressione qualquer tecla para sair";
      getch();
}


int main (){
  system("cls");
  Introducao I1;
  jogo j1;
  j1.comecaJogo();
  system("cls");
  getch();
}
