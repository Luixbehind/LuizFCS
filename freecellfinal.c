#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include<windows.h>
#include<locale.h>
typedef struct no
{
    int num;
    char naipe;
    struct no *prox;
} tCarta;
int i=0,j=0;
tCarta *prim;
tCarta *primMesa[8];
tCarta *primNaipe[4];
tCarta *temp[4];
tCarta *primMonte = NULL;
void incializa()
{
    int i;
    for(i=0; i<8; i++)
    {
        primMesa[i] = NULL;
    }
    for(i=0; i<4; i++)
    {
        primNaipe[i] = NULL;
        temp[i] = NULL;
    }
}
tCarta * valorCarta (int id);
void  moveMesaTemp();
void moveMesaNape();
void geraBaralho()
{
    int k,i,j;
    for(i=3; i<=6; i++)
    {
        for(j=1; j<=13; j++)
        {
            tCarta *novo = malloc(sizeof(tCarta));
            novo->naipe = i;
            novo->num = j;
            novo->prox = primMonte;
            primMonte = novo;
        }
    }
}
void embaralhaBaralho()
{
    int pos;
    tCarta *aux = primMonte;
    int help;
    tCarta *cartaSorteada;
    srand(time(NULL));
    while(aux != NULL)
    {
        cartaSorteada = valorCarta(rand()%52);
        help = aux->num;
        aux->num = cartaSorteada->num;
        cartaSorteada->num = help;
        help = aux->naipe;
        aux->naipe = cartaSorteada->naipe;
        cartaSorteada->naipe = help;
        aux = aux->prox;
    }
}
tCarta * valorCarta (int id)
{
    tCarta *aux = primMonte;
    while(id!=0)
    {
        aux = aux->prox;
        id--;
    }
    return aux;
}
void  distribuirMesa()
{
    int i;
    for(i=0; i<4; i++)
    {
        for(int j=0; j<7; j++)
        {
            tCarta *remove = primMonte;
            primMonte = primMonte->prox;
            remove->prox = primMesa[i];
            primMesa[i] = remove;
        }
    }
    for(i=4; i<8; i++)
    {
        for(int j=0; j<6; j++)
        {
            tCarta *remove = primMonte;
            primMonte = primMonte->prox;
            remove->prox = primMesa[i];
            primMesa[i] = remove;
        }
    }
}
void moveMesaTemp()
{
    int op=0,aux;
    tCarta *ant;
    tCarta *atual;
    tCarta *help;
    i=0;
    while(i<4)
    {
        if(temp[i]==NULL)
        {
            printf("\nDIGITE de qual MESA  sairá a carta para o TEMP:\n");
            scanf("%d",&op);
            while(op>7)
            {
                printf("\nNão é possível realizar o movimento!\nDigite outra opção de MESA\n");
                scanf("%d",&op);
            }
            if(op>=0 && op<=7)
            {
                if(primMesa[op]==NULL)
                {
                    printf("Mesa vazia!\n");
                    break;
                }
                else
                {
                    atual = primMesa[op];
                    while(atual->prox !=NULL)
                    {
                        ant = atual;
                        atual = atual->prox;
                    }
                    if(atual == primMesa[op])
                    {
                        temp[i] = atual;
                        primMesa[op] = NULL;
                    }
                    else
                    {
                        temp[i] = atual;
                        ant->prox = NULL;
                    }
                    i++;
                    if(primMesa[op]==NULL)
                    {
                        printf("Mesa vazia, impossível enviar alguma coisa ao temporário!\n");
                    }
                }
            }
            if(i>3)
            {
                printf("TEMP LOTADO!\n");
            }
            break;
        }
        else i++;
    }
}
void moveTempMesa()
{
    int op1,op2;
    tCarta *aux;
    tCarta *atual;
    tCarta *ant;
    printf("Digite de qual posição do temporário você deseja remover a carta:\n");
    scanf("%d",&op1);
    while(op1>4)
    {
        printf("Essa posição não existe na temporário, digite novamente a posição desejada:\n");
        scanf("%d",&op1);
    }
    printf("Digite para qual mesa você quer levar a carta retirada do temporário:\n");
    scanf("%d",&op2);
    while(op2>7)
    {

        printf("Essa posição não existe na MESA, digite novamente a posição desejada:\n");
        scanf("%d",&op2);
    }

    if(temp[op1]!=NULL)
    {
        atual = primMesa[op2];
        if(atual==NULL)
        {
            aux = temp[op1];
            aux->prox = primMesa[op2];
            primMesa[op2] = aux;
            temp[op1]=NULL;
        }
        else
        {
            while(atual->prox != NULL)
            {
                ant = atual;
                atual = atual->prox;
            }
            if((temp[op1]->num == (atual->num)-1) &&((temp[op1]->naipe == 3 || temp[op1]->naipe == 4) && (atual->naipe == 5 || atual->naipe == 6)))
            {
                atual->prox = temp[op1];
                temp[op1]->prox = NULL;
                temp[op1] = NULL;
            }
            else if((temp[op1]->num == (atual->num)-1) &&((temp[op1]->naipe == 5 || temp[op1]->naipe == 6) && (atual->naipe == 3 || atual->naipe == 4)))
            {
                atual->prox = temp[op1];
                temp[op1]->prox = NULL;
                temp[op1] = NULL;
            }
            else
            {
                printf ("\nNão é possível realizar a operação.\n");
            }
        }
    }
    else if(temp[op1]==NULL) printf("Temporário vazio nesta posição, não é possível realizar a operação.\n");
}

void moveMesaNaipe()
{
    int op,op1=0,j;
    tCarta *atual;
    tCarta *ant=NULL;
    printf("De qual mesa você quer mover a carta para o NAIPE?\n");
    printf("Digite a MESA requerida:\n");
    scanf("%d",&op);
    if(op>7) printf("Não é possível realizar o movimento. Mesa inválida!\n");
    else
    {
        if(primMesa[op]==NULL) printf("Mesa vazia, impossível realizar o movimento!\n");
        else
        {
            atual = primMesa[op];
            while(atual->prox != NULL)
            {
                ant = atual;
                atual = atual->prox;
            }
            j=0;
            while(j<4)
            {
                if(ant!=NULL)
                {
                    if(primNaipe[j]==NULL)
                    {
                        if(atual->num == 1)
                        {
                            atual->prox = primNaipe[j];
                            primNaipe[j] = atual;
                            ant->prox = NULL;

                            break;
                        }
                        else if(atual->num!= 1)
                        {
                            j++;
                        }
                    }
                    else if(primNaipe[j]!=NULL)
                    {
                        if((atual->num == ((primNaipe[j]->num)+1)) &&(atual->naipe == primNaipe[j]->naipe))
                        {
                            atual->prox = primNaipe[j];
                            primNaipe[j] = atual;
                            ant->prox = NULL;
                            break;
                        }
                        else j++;
                    }
                    if(j==4) printf("Opção inválida!\n");
                }
                else if(ant==NULL)
                {
                    if(primNaipe[j]==NULL)
                    {
                        if(atual->num == 1)
                        {
                            atual->prox = primNaipe[j];
                            primNaipe[j] = atual;
                            primMesa[op] = NULL;
                            break;
                        }
                        else if(atual->num!= 1)
                        {
                            j++;
                        }
                    }
                    else if(primNaipe[j]!=NULL)
                    {
                        if((atual->num == ((primNaipe[j]->num)+1)) &&(atual->naipe == primNaipe[j]->naipe))
                        {
                            atual->prox = primNaipe[j];
                            primNaipe[j] = atual;
                            primMesa[op] = NULL;
                            break;
                        }
                        else j++;
                    }
                    if(j==4) printf("Opção inválida!\n");
                }
            }
        }
    }
}
void moveNaipeTemp()
{
    tCarta *aux;
    tCarta *ant=NULL;
    int op,k=0;
    printf("Digite de qual mesa de NAIPE você quer mover a carta ao temporário:\n");
    printf("ATENÇÃO, MESA DE NAIPE(0-3)!\n");
    scanf("%d",&op);
    if(op>3||op<0)
    {
        printf("Mesa inexistente, digite novamente outra opção de mesa:\n");
        scanf("%d",&op);
    }
    if(primNaipe[op]==NULL) printf("Mesa de NAIPE vazia\n");
    else
    {
        aux = primNaipe[op];
        while(aux->prox!=NULL)
        {
            ant = aux;
            aux = aux->prox;
        }
        if(aux = primNaipe[op])
        {
            while(k<4)
            {
                if(temp[k]== NULL)
                {
                    temp[k] = aux;
                    primNaipe[op] = NULL;
                    aux->prox = NULL;
                    break;
                }
                k++;
                if(k==4) printf("Temporário lotado!");
            }
        }
        else
        {
            while(k<4)
            {
                if(temp[k]== NULL)
                {
                    temp[k] = aux;
                    ant->prox = NULL;
                    break;
                }
                k++;
                if(k==4) printf("Temporário lotado!");
            }
        }
    }
}
void moveTempNape()
{
    int op,op1;
    tCarta *help;
    printf("Digite de qual posição da mesa TEMPORÁRIO você deseja remover a carta:\n");
    scanf("%d",&op);
    if(op<0||op>3)
    {
        printf("Posição no temporário inexistente, digite novamente qual a posição do temporário requerida:\n ATENÇÃO MESA TEMPORÁRIO(0-3)\n");
        scanf("%d",&op);
    }
    else
    {
        if(temp[op]==NULL)
        {
            printf("Temporário vazio nessa posição, impossível realizar o movimento!\n");
        }
        else
        {
            printf("Digite qual mesa de NAIPE você deseja inserir a carta:\n");
            scanf("%d",&op1);
            if(op1<0||op1>3)
            {
                printf("Posição no NAIPE inexistente, digite novamente qual a posição do NAIPE requerida:\n ATENÇÃO MESA NAIPE(0-3)\n");
                scanf("%d",&op1);
            }
            else
            {
                if(primNaipe[op1]==NULL)
                {
                    if(temp[op]->num == 1)
                    {
                        primNaipe[op1] = temp[op];
                        temp[op] = NULL;
                        primNaipe[op]->prox = temp[op];
                    }
                    else printf("Movimento inválido\n");
                }
                else
                {
                    help = primNaipe[op1];
                    if(temp[op]->num == ((help->num)+1) && (temp[op]->naipe == help->naipe ))
                    {
                        temp[op]->prox = primNaipe[op1];
                        primNaipe[op1] = temp[op];
                        temp[op] = NULL;
                    }
                    else printf("Movimento inválido\n");
                }
            }
        }
    }
}
void moveNaipeMesa()
{
    tCarta *aux;
    tCarta *ct;
    int op,op1;
    printf("Digite de qual mesa dos NAIPES você quer retirar a carta:\n");
    scanf("%d",&op);
    if(op<0||op>3)
    {
        printf("Opção de mesa dos NAIPES inválida, digite novamente:\nATENÇÃO MESA DOS NAIPES(0-3)!\n");
        scanf("%d",&op);
    }
    else
    {
        printf("Digite para qual MESA DE CARTAS você quer inserir a carta removida dos NAIPES:\n");
        scanf("%d",&op1);
        if(op1<0||op1>7)
        {
            printf("Opção de MESA DAS CARTAS inválida, digite novamente:\nATENÇÃO MESA DAS CARTAS(0-7)!\n");
            scanf("%d",&op1);
        }
        else
        {
            if(primNaipe[op]==NULL)
            {
                printf("Mesa NAIPE vazia!\n");
            }
            else
            {
                aux = primNaipe[op];
                ct = primMesa[op1];
                if(primMesa[op1]==NULL)
                {
                    if(aux->prox!=NULL)
                    {
                        primMesa[op1] = aux;
                        primNaipe[op] = aux->prox;
                        aux->prox = NULL;
                    }
                    else
                    {
                        primMesa[op1] = aux;
                        primNaipe[op] = NULL;
                        aux->prox = NULL;
                    }
                }
                else
                {
                    while(ct->prox != NULL)
                    {
                        ct = ct->prox;
                    }
                    if(aux->prox != NULL)
                    {
                        if((((ct->num)-1)==aux->num)&& ((ct->naipe==3 || ct->naipe==4)&&(aux->naipe==5 || aux->naipe==6)))
                        {
                            ct->prox = aux;
                            primNaipe[op] = aux->prox;
                            aux->prox = NULL;
                        }
                        else if((((ct->num)-1)==aux->num)&& ((ct->naipe==5 || ct->naipe==6)&&(aux->naipe==3 || aux->naipe==4)))
                        {
                            ct->prox = aux;
                            primNaipe[op] = aux->prox;
                            aux->prox = NULL;
                        }
                        else printf("Movimento inválido\n");
                    }
                    else
                    {
                        if((((ct->num)-1)==aux->num)&& ((ct->naipe==3 || ct->naipe==4)&&(aux->naipe==5 || aux->naipe==6)))
                        {
                            ct->prox = aux;
                            primNaipe[op] = NULL;
                            aux->prox = NULL;
                        }
                        else if((((ct->num)-1)==aux->num)&& ((ct->naipe==5 || ct->naipe==6)&&(aux->naipe==3 || aux->naipe==4)))
                        {
                            ct->prox = aux;
                            primNaipe[op] = NULL;
                            aux->prox = NULL;
                        }
                        else printf("Movimento inválido\n");
                    }
                }
            }
        }
    }
}
void moveMesaMesa()
{
    int op,op1,op2;
    int num=0;
    int qtd=0,cont=0;
    printf("Digite (1) caso você deseja remover uma única carta:\n");
    printf("Digite (2) caso você deseja remover uma pilha de cartas:\n");
    scanf("%d",&op);
    if(op!=1 && op!= 2)
    {
        printf("Você selecionou uma opção inválida");
    }
    else
    {
        switch(op)
        {
        case 1:
            printf("Digite de qual mesa você quer remover a carta:\n");
            scanf("%d",&op1);
            if(op1<0|| op1>7)
            {
                printf("MESA DE CARTAS INEXISTENTE!\nATENÇÃO MESA DE CARTAS (0-7)\n");
                printf("Digite novamente a MESA DE CARTAS requerida:\n");
                scanf("%d",&op1);
            }
            else
            {
                if(primMesa[op1]==NULL) printf("Movimento inválido, MESA DE CARTAS vazia");
                else
                {

                    tCarta *aux = primMesa[op1];
                    tCarta *ant=NULL;
                    while(aux->prox != NULL)
                    {
                        ant = aux;
                        aux = aux->prox;
                    }
                    printf("Digite para qual mesa você deseja inserir a carta:\n");
                    scanf("%d",&op2);
                    if(op2<0 || op2>7)
                    {
                        printf("MESA DE CARTAS INEXISTENTE!\nATENÇÃO MESA DE CARTAS (0-7)\n");
                        printf("Digite novamente a MESA DE CARTAS requerida:\n");
                        scanf("%d",&op2);
                    }
                    else
                    {
                        if(ant==NULL)
                        {
                            if(primMesa[op2]==NULL)
                            {
                                primMesa[op2] = aux;
                                primMesa[op1] = NULL;
                            }
                            else
                            {
                                tCarta *help = primMesa[op2];
                                while(help->prox !=NULL)
                                {
                                    help = help->prox;
                                }
                                if((aux->num == (help->num)-1) &&(aux->naipe == 3 || aux->naipe ==4) && (help->naipe == 5 || help->naipe ==6))
                                {
                                    help->prox = aux;
                                    primMesa[op1] = NULL;
                                }
                                else if((aux->num == (help->num)-1) &&(aux->naipe == 5 || aux->naipe == 6) && (help->naipe == 4 ||help->naipe == 3))
                                {
                                    help->prox = aux;
                                    primMesa[op1] = NULL;
                                }
                                else printf("Movimento inválido!\n");
                            }
                        }
                        else
                        {
                            if(primMesa[op2]==NULL)
                            {
                                primMesa[op2] = aux;
                                ant->prox = NULL;
                            }
                            else
                            {
                                tCarta *help = primMesa[op2];
                                while(help->prox !=NULL)
                                {
                                    help = help->prox;
                                }
                                if((aux->num == (help->num)-1) &&(aux->naipe == 3 || aux->naipe ==4) && (help->naipe == 5 || help->naipe ==6))
                                {
                                    help->prox = aux;
                                    ant->prox = NULL;
                                }
                                else if((aux->num == (help->num)-1) &&(aux->naipe == 5 || aux->naipe == 6) && (help->naipe == 4 ||help->naipe == 3))
                                {
                                    help->prox = aux;
                                    ant->prox = NULL;
                                }
                                else printf("Movimento inválido!\n");
                            }
                        }
                    }
                }
            }
            break;
        case 2:
            printf("Digite de qual MESA DE CARTAS você quer mover a pilha de cartas:\n");
            scanf("%d",&op1);
            if(op1<0 || op1>7)
            {
                printf("MESA DE CARTAS INEXISTENTE!\nATENÇÃO MESA DE CARTAS (0-7)\n");
                printf("Digite novamente a MESA DE CARTAS requerida:\n");
                scanf("%d",&op1);
            }
            else
            {
                if(primMesa[op1]==NULL) printf("Movimento inválido, MESA DE CARTAS vazia");
                else
                {
                    printf("Digite quantas cartas você quer remover:\n");
                    scanf("%d",&qtd);
                    if (qtd==0) printf("Movimento inválido, você digitou 0 cartas\n");
                    else
                    {
                        tCarta *aux = primMesa[op1];
                        tCarta *ant;
                        while(aux->prox != NULL)
                        {
                            cont++;
                            aux = aux->prox;
                        }
                        cont = cont + 1;
                        if(cont==qtd)
                        {
                            tCarta *ajuda = primMesa[op1];
                            tCarta *before;
                            while(ajuda->prox != NULL)
                            {
                                before = ajuda;
                                ajuda = ajuda->prox;
                                if((before->num ==(ajuda->num)+1) && ((before->naipe == 3 || before->naipe ==4) && (ajuda->naipe == 5 || ajuda->naipe ==6)))
                                {
                                    num++;
                                }
                                else if ((before->num ==(ajuda->num)+1) && ((before->naipe == 5 || before->naipe == 6) && (ajuda->naipe == 3 || ajuda->naipe == 4)))
                                {
                                    num++;
                                }
                            }
                            num = num+1;
                            if(qtd == num)
                            {
                                printf("Digite para qual MESA DE CARTAS você deseja inserir a pilha de cartas:\n");
                                scanf("%d",&op2);
                                if(op2<0 || op2>7)
                                {
                                    printf("MESA DE CARTAS INEXISTENTE!\nATENÇÃO MESA DE CARTAS (0-7)\n");
                                    printf("Digite novamente a MESA DE CARTAS requerida:\n");
                                    scanf("%d",&op2);
                                }
                                else
                                {
                                    tCarta *carta = primMesa[op1];
                                    if(primMesa[op2]==NULL)
                                    {
                                        primMesa[op2] = carta;
                                        primMesa[op1] = NULL;
                                    }
                                    else
                                    {
                                        tCarta *ct = primMesa[op2];
                                        while(ct->prox != NULL)
                                        {
                                            ct = ct->prox;
                                        }
                                        if((ct->num == (carta->num+1)) && ((ct->naipe==3 || ct->naipe==4) &&(carta->naipe==5 || carta->naipe==6)))
                                        {
                                            ct->prox = carta;
                                            primMesa[op1] = NULL;
                                        }
                                        else if((ct->num == (carta->num+1)) && ((ct->naipe==5 || ct->naipe==6) &&(carta->naipe==3 || carta->naipe==4)))
                                        {
                                            ct->prox = carta;
                                            primMesa[op1] = NULL;
                                        }
                                        else printf("Movimento inválido!\n");
                                    }
                                }
                            }
                            else printf("Movimento inválido!\n");
                        }
                        else if(cont>qtd)
                        {
                            num = cont - qtd;
                            tCarta *ajuda = primMesa[op1];
                            tCarta *before;
                            while(num>0)
                            {
                                before = ajuda;
                                ajuda = ajuda->prox;
                                num--;
                            }
                            num = 0;
                            tCarta *anterior;
                            tCarta *aju = ajuda;
                            while(aju->prox != NULL)
                            {
                                anterior = aju;
                                aju = aju->prox;
                                if((anterior->num ==(aju->num)+1) && ((anterior->naipe == 3 || anterior->naipe ==4) && (aju->naipe == 5 || aju->naipe ==6)))
                                {
                                    num++;
                                }
                                else if((anterior->num ==(aju->num)+1) && ((anterior->naipe == 5 || anterior->naipe == 6) && (aju->naipe == 3 || aju->naipe == 4))) num++;
                            }
                            num = num+1;
                            if(qtd == num)
                            {
                                printf("Digite para qual MESA DE CARTAS você deseja inserir a pilha de cartas:\n");
                                scanf("%d",&op2);
                                if(op2<0 || op2>7)
                                {
                                    printf("MESA DE CARTAS INEXISTENTE!\nATENÇÃO MESA DE CARTAS (0-7)\n");
                                    printf("Digite novamente a MESA DE CARTAS requerida:\n");
                                    scanf("%d",&op2);
                                }
                                else
                                {
                                    if(primMesa[op2]==NULL)
                                    {
                                        primMesa[op2] = ajuda;
                                        before->prox = NULL;
                                    }
                                    else
                                    {
                                        tCarta *ct = primMesa[op2];
                                        while(ct->prox != NULL)
                                        {
                                            ct = ct->prox;
                                        }
                                        if((ct->num == (ajuda->num)+1) && ((ct->naipe==3 || ct->naipe==4) &&(ajuda->naipe==5 || ajuda->naipe==6)))
                                        {
                                            ct->prox = ajuda;
                                            before->prox = NULL;
                                        }
                                        else if((ct->num == (ajuda->num+1)) && ((ct->naipe== 5 || ct->naipe== 6) &&(ajuda->naipe==3 || ajuda->naipe==4)))
                                        {
                                            ct->prox = ajuda;
                                            before->prox = NULL;
                                        }
                                        else printf("Movimento inválido!\n");
                                    }
                                }
                            }
                            else printf("Movimento inválido!\n");
                        }
                        else printf("Movimento inválido!\n");
                    }
                }
            }
            break;
        }
    }
}
void imprime()
{
    int i=0;
    tCarta *aux;
    printf("\n");
    printf("[TEMP] = ");
    for(i=0; i<4; i++)
    {
        if(temp[i]!=NULL)
        {

            printf("(%d)[%d/%c] ",i,temp[i]->num,temp[i]->naipe);
        }
    }
    printf("\n\n");
    for(i=0; i<4; i++)
    {
        aux = primNaipe[i];
        printf("[NAIPE (%d)] =",i);
        while(aux != NULL)
        {
            if(aux->num<10)
            {
                printf("[ %d/%c] ",aux->num,aux->naipe);
                aux = aux->prox;
            }
            else
            {
                printf("[%d/%c] ",aux->num,aux->naipe);
                aux = aux->prox;
            }
        }
        printf("\n");
    }
    printf("\n");
    for(i=0; i<8; i++)
    {
        aux = primMesa[i];
        printf("MESA %d =",i);
        while(aux!=NULL)
        {
            if(aux->num<10)
            {
                printf("[ %d/%c] ",aux->num,aux->naipe);
                aux = aux->prox;
            }
            else
            {
                printf("[%d/%c] ",aux->num,aux->naipe);
                aux = aux->prox;
            }
        }
        printf("\n");
    }
    printf("\n");
}
int main()
{
    setlocale(LC_ALL, "Portuguese");
    system("color 27");
    int op=0,i,j;
    geraBaralho();
    embaralhaBaralho();
    distribuirMesa();
    while(op!=8)
    {
        if(op==0) imprime();
        printf("(1)Move MESA-TEMP\n");
        printf("(2)Move TEMP-MESA\n");
        printf("(3)Move MESA-NAIPE\n");
        printf("(4)Move NAIPE-TEMP\n");
        printf("(5)Move TEMP-NAIPE\n");
        printf("(6)Move NAIPE-MESA\n");
        printf("(7)Move MESA-MESA\n");
        printf("(8)Para sair do jogo!\n");
        printf("Opção: ");
        scanf("%d", &op);
        getchar();
        switch(op)
        {
        case 1:
            moveMesaTemp();
            imprime();
            break;
        case 2:
            moveTempMesa();
            imprime();
            break;
        case 3:
            moveMesaNaipe();
            imprime();
            break;
        case 4:
            moveNaipeTemp();
            imprime();
            break;
        case 5:
            moveTempNape();
            imprime();
            break;
        case 6:
            moveNaipeMesa();
            imprime();
            break;
        case 7:
            moveMesaMesa();
            imprime();
            break;
        case 8:
            printf("Você saiu do jogo!\n");
            printf("X   X\n");
            printf("  -   \n");
            printf("ADEUS");
            break;
        default:
            printf("Opção Inválida!!\nEscolha outra opção:\n");
            break;
        }
        if(temp[i]==NULL&&temp[i+1]==NULL&&temp[i+2]==NULL&&temp[i+3]==NULL&& primMesa[i]==NULL && primMesa[i+1]==NULL && primMesa[i+2]==NULL && primMesa[i+3]==NULL && primMesa[i+4]==NULL && primMesa[i+5]==NULL &&primMesa[i+6]==NULL && primMesa[i+7]==NULL)
        {
            system("cls");

            printf("                   ...:.::..                                                            ..:::::::..\n");
            printf("               .:::::!!!::::...:.                                                   .::.::::::::::.:::.\n");
            printf("             .!::!!:!!!!::::::::::.       ............     ...........             .::::!!:::::::::::::!.\n");
            printf("           .:::!!!!::::::::!::!!!:::...:::::::::::::::::::::::::.::::::::::!:.     ::!!:::::!!::::::::!!!:.\n");
            printf("          :.:!!::::.       ::::!!::::...........:........::...:::::::::::.::::.....::!!::!:.      .::::!!!!:\n");
            printf("         ..:!!!::          :!::::::::::::!!!!!!!!!!!!!!!:!!!!!!!!!!!!!!!!!!!:!!!!:.:::::::.          ::::::::\n");
            printf("        ::!!!:!.           :::::::.::!!!:!!:!::::::::::::::::::::::!!:!!::::!:!!!!::::::::.           .:::!!!:\n");
            printf("       :::::::            .::::::::::::::::::::::::::::::::::::::::::::::::::!!!!!!:::::.::.           .:.:!!!.\n");
            printf("      .::!::.            .::!!::!:::...........UNIFEI FREECELL ..........................:::!:           .:.:!::\n");
            printf("      .:::::.           ::::::!::::::.....................................:!::::!::!!!!!!::!!:          .::!!::.\n");
            printf("      ::!!::.          :!!:!!:::::..::::...............::::::::::.....::::::!:!!!!!!!!!!!!!:::          .:::::..\n");
            printf("      ::::::.          !::!:::::::..::!::::::::::::::!:!!!:!!:::!:::!!:!!!!!!!!!!!!!!:!!!!!::!.         .:.:::..\n");
            printf("      .:!!:::          :::!::::......::::!:::::!::::::::!!:::::::::::::!:::::!!:::::::!!!:!:!!.          :::!:..\n");
            printf("      .:!!:::.         .:::::.......::::::!::!:!:..!:!:.:!!::!:::!::!::!::!!!.:!:.:!::::::::!!.          ::!!:..\n");
            printf("      .::::::.         .:::::::......:::!!!::!!:!!:::!:!::!::!::!!!!!::!::::!::!:!!::.::::::!:          .::::::.\n");
            printf("       ::!!!:!         .!::..:::::::::!:::!!!!!!!!!!!!!:!!!!!!!:::!!!!::!!!!!:!!!::!:::::.::!:          :::!:.:\n");
            printf("       .::!!:::        .::::::::.::::::::!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!::::::.:::!:         :::!!::\n");
            printf("        ::::::::       .::!::::::.:::::!::!:::!!!!!!!!!!:::::::..!!!!!!!!!!!!!!!::::::::::::!.        ::::!::.\n");
            printf("         ::!!!:::       :::!:.:::.:::::!::!::::!!!!!!!:!!:::::::.!::!!!!!!!!!!:::.:::.:.::.:!       .::::!::.\n");
            printf("          ::!::.::.     ..:!!:.:::::::!!:!!:::!!!!!:::::::::::::.!!!!!!!!!!!:::::.:::..::::!       .:!:!!:::\n");
            printf("           :::!!:::.     :.:!::::!:.!:::::::::!:::::::::::::::::.!!!!!!!!!!:::..:::.:::::::!     .::::!!:::\n");
            printf("            ::::!..::.    .::!!:!:!::!!::!::!:!!::::::::::::::::.!!!!!!!!!!::..:::.....:!::!   .:::::!!::.\n");
            printf("             .!::!!::::.  ..:!!::!::.:!::::!!:!!::::::::::::::::.!!!!!!!!!::...:::.....:::::::::.::!!!!:\n");
            printf("               :::!!!:.::...:!!!!::!:.:!::::!:!!!!!!!!!:::::::::.!!!!!!!!:::..::.:....:!!:::::::::!:::.\n");
            printf("                 :::!::...:..!!!!:!::.:!::::!!:!!!!!:!!:::::::::.!!!!!!!!::..:::::...:!!:::.:!::::::.\n");
            printf("                   :!::!::::::!!!!!!:!.:!::::!!!!!!!:!!:::::::::.!!!!!!!!:::::::....:!!!!!::!:!:::\n");
            printf("                     .:!::!!!:!!!!!!!!:.:::::!!!!!!!:!!:::::::::.!!!!!!::::.:::.:::.!!!!!!::::::.\n");
            printf("                       .!:::!:!!!!!!!!:::::::!!!!!!:!!!:::::::::.!!!!!!!::::::..:::!!!!!!::!::.\n");
            printf("                         :!::::!!!!!!!!:::::::!!!!!!:!!:::::::::.!!!!!!!:::::....:!!!!:!:::::\n");
            printf("                           :!:::!!!!!!!!::::::::!!!!:!!:::::::::.!!!!!!:!!:::::::!!!!!:!::.\n");
            printf("                             .!!!!!!!!!!!!::!::::!:!:!!:::::::::.!:!!!!!!:..:!::!!!!!:!:.\n");
            printf("                                ..!!!!!!!!!::!:!:::::!!:::::::::.!!!!:!!:..:!!:!!!!!:.\n");
            printf("                                   .!!!!!!!!::!!!::::!!:::::::::.!!!!:!:::::!:!!!!!.\n");
            printf("                                    :!!!!!!!!:!!!!:::!!:::::::::.!!!!!:.::::::!!!!.\n");
            printf("                                     !!!!!!!!!:!!!!::!!:::::::::.!:::::::::::!!!!:\n");
            printf("                                      !!!!!!!!!:!!!!:!!:::::::::.!:!!::::!!:!!!!!\n");
            printf("                                      .!!!!!!!!!:!!!!!!!::::::::.!!!:::::::!!!!!\n");
            printf("                                       .!!!!!!!!!!!!!!!!!!!!!!!!:!!::::::::!!!!\n");
            printf("                                         !!!!!!!!!!!!!!!!!!!!!!!!!!!:::!:!!!!!.\n");
            printf("                                          :!!!!!!!:!:!!!!!!!!!!!!!!!!!:!!!!!! \n");
            printf("                                           :!!!!!!!!!!!!!!!!!!!!!!!:!!!:!!!!.\n");
            printf("                                            .!!!!!!!!!!!!!!!!!!!!!!!!!:!!!!.\n");
            printf("                                             :!!!!!!!!!!!!!!!!!!!!!:::!!!! \n");
            printf("                                              :!!!!!!!!!!!!!!!!!!!!!!!!!:\n");
            printf("                                               :!!!!!!!!!!!!!!!!!!!!!!!!.\n");
            printf("                                                :!!!!!!!!!!!!!!!!!!:!!:\n");
            printf("                                                  :!!!:!!!!!!!!!!!!!!.\n");
            printf("                                                    .:::::!!!!!!::!.\n");
            printf("                                                    .::!!!::::!!!!!.\n");
            printf("                                                   .::!!!!!!!!!!!!:!:\n");
            printf("                                                  :!::::::::::!!::::!:.\n");
            printf("                                                .!!!!:!!:.:...:!!::!!!!!.\n");
            printf("                                             .::::!!!!::!!:::!!!!!!!!!!!!!:.\n");
            printf("                                         .:::::::!::!!!!!::!!!!!!!!!!!!!!!!!!::\n");
            printf("                                        ::::.::::!!!!!!!!!!!!!!!!!!!!!!!!!!:::.:.\n");
            printf("                                        .!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:.\n");
            getchar();
            break;
        }
    }
    return 0;
}
