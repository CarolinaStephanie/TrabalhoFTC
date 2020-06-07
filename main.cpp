#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/***/
typedef struct Alphab
{
    char simbolo[100];          ///Simbolo do alfabeto
    struct Alphab *next;

    void print(){
        printf("\n Alphab: ");
        struct Alphab *t = this;
        while(t != NULL)
        {   printf("%s", t->simbolo);
            if(t->next != NULL)
                printf(", ");
            t = t->next;
        }
    }
} lAlphab;
/***/
typedef struct nameList
{
    char name[100];
    struct nameList *next;

    void print(){
        printf("\n nameList: ");
        struct nameList *t = this;
        while(t != NULL)
        {   printf("%s", t->name);
            if(t->next !=NULL)
                printf(", ");
            t = t->next;
        }
    }
} lName;
/***/
typedef struct States
{
    char name[100];            /// Nome do estado
    int eState;                /// Indicador de estado final se igual a 1;
    int id;                    ///ID;
    struct States *next;

    lName *listname;

    void print(){
        printf("\n States: ");
        struct States *t = this;
        while(t != NULL)
        {   printf("\n name: %s | Final? %d | ID: %d | ", t->name, t->eState, t->id);
            t->listname->print();
            t = t->next;
        }
    }
} lStates;
/***/
typedef struct Edge
{
    char from[100];            /// Origem
    char to[100];              /// Destino
    char input[100];           /// Simbolo nescessario
    struct Edge *next;


    void print(){
        printf("\n Transicoes: \n");
        struct Edge *t = this;
        while(t != NULL)
        {   printf("( %s, %s )->%s\n", t->from, t->input, t->to);
            t = t->next;
        }
    }
} lEdge;
/***/
typedef struct AFi
{
    lStates *States;         /// Conjuto de Estados
    lAlphab *Alpha;          /// Alfabeto
    lEdge *Transations;      /// Lista de edges
    lStates *Start;          /// Estado Inicial


    void print(){
        printf("\n AF: \n");
        printf(" Inicial: %s\n ", Start->name);
        printf(" Estados: ");
        States->print();
        Alpha->print();
        Transations->print();
    }
} AF;
/***/
lName* newLName ()
{

    lName *new1 = (lName*) calloc ( sizeof (lName), 1 );


    if ( new1 == NULL )
    {
        printf ( " ERRO (lName): Impossivel montar." );
    }
    else
    {
        strcpy(new1->name,"nothing");
        new1->next=NULL;
        return new1;
    }
}
/***/
void putName (lName **Lista,lName *new1)
{
    if(*Lista==NULL)
    {
        new1->next=NULL;
        *Lista=new1;
    }
    else
    {
        lName *temp;
        temp=*Lista;

        while(temp!=NULL)
        {
            if(temp->next==NULL)
            {
                new1->next=NULL;
                temp->next=new1;
                return;
            }
            temp=temp->next;
        }
    }
}
/***/
lAlphab* newAlphab ()
{

    lAlphab *new1 = (lAlphab*) calloc ( sizeof (lAlphab), 1 );


    if ( new1 == NULL )
    {
        printf ( " ERRO (lAlphab): Impossivel montar." );
    }
    else
    {
        strcpy(new1->simbolo," ");
        new1->next=NULL;
        return new1;
    }
}
/***/
void putAlphab (lAlphab **Lista,lAlphab *new1)
{
    if(*Lista==NULL)
    {
        new1->next=NULL;
        *Lista=new1;
    }

    else
    {
        lAlphab *temp;
        temp=*Lista;

        while(temp!=NULL)
        {
            if(temp->next==NULL)
            {
                new1->next=NULL;
                temp->next=new1;
                return;
            }
            temp=temp->next;
        }

    }


}
/***/
lEdge* newEdge ()
{
    lEdge *new1 = (lEdge*) calloc ( sizeof (lEdge), 1 );


    if ( new1 == NULL )
    {
        printf ( " ERRO (lEdge): Impossivel montar." );
    }
    else
    {
        strcpy(new1->from," ");
        strcpy(new1->to," ");
        strcpy(new1->to," ");
        new1->next=NULL;
        return new1;
    }
}
/***/
void putEdge (lEdge **Lista,lEdge *new2)
{
    if(*Lista==NULL)
    {
        new2->next=NULL;
        *Lista=new2;
        return;
    }

    else
    {
        lEdge *temp;
        temp=*Lista;

        while(temp!=NULL)
        {
            if(temp->next==NULL)
            {

                temp->next=new2;
                temp->next->next=NULL;
                return;
            }
            temp=temp->next;
        }

    }
}
/***/
char* findEdge (lEdge *Lista, char *state,char *input,int op)
{
    lEdge *temp;
    char statetemp[100];

    temp=Lista;
    if (op==0)//Para AFN
    {
        strcpy(statetemp,"");
        while(temp!=NULL)
        {
            if(strcmp(temp->from,state)==0 && strcmp(temp->input,input)==0)
            {
                if(strcmp(statetemp,"")!=0) ///Se caso for mais de um estado
                {
                    strcat(statetemp,",");
                }
                strcat(statetemp,temp->to);

            }
            temp=temp->next;
        }
        return(statetemp);
    }
    else    //Para AFD
    {
        while(temp!=NULL)
        {
            if(strcmp(temp->from,state)==0 && strcmp(temp->input,input)==0)
            {

                return(temp->to);

            }
            temp=temp->next;
        }


    }

}
/***/
lName* findEdgeNFA (lEdge *Lista, char *state,char *input)
{
    lEdge *temp;
    lName *names = NULL;
    lName *tpname;

    temp=Lista;
    while(temp!=NULL)
    {
        if(strcmp(temp->from,state)==0 && strcmp(temp->input,input)==0)
        {
            tpname = newLName();
            strcpy(tpname->name, temp->to);
            putName( &names, tpname );
        }
        temp=temp->next;
    }
    return(names);
}
/***/
lStates* newState ()
{
    lStates *new1 = (lStates*) calloc ( sizeof (lStates), 1 );


    if ( new1 == NULL )
    {
        printf ( " ERRO (lStates): Impossivel montar." );
    }
    else
    {

        new1->eState=0;
        new1->listname = newLName();
        strcpy(new1->name,"");
        new1->next=NULL;
        return new1;
    }
}
/***/
void putState (lStates **Lista,lStates *new1)
{
    if(*Lista==NULL)
    {
        new1->next=NULL;
        *Lista=new1;
        return;
    }

    else
    {
        lStates *temp;
        temp=*Lista;

        while(temp!=NULL)
        {
            if(temp->next==NULL)
            {
                new1->next=NULL;
                temp->next=new1;
                return;
            }
            temp=temp->next;
        }

    }
}
/***/
lStates* findState(lStates *Lista,char*key,int op)
{
    lStates *temp;

    temp=Lista;

    while(temp!=NULL)
    {
        if(strcmp(temp->name,key)==0 && op==0) ///Operação de achar estado para marca como estado final
        {
            temp->eState=1;
            return (temp);
        }
        else if(strcmp(temp->name,key)==0 && op==1) ///Operação de achar estado para retorna o endereço para atribuir como estado inicial
        {
            return (temp);
        }
        temp=temp->next;
    }
    return (temp);

}
/**Função que retorna se e estado final ou nao se sim 1 se nao 0*/
int iseState(char *key,lStates *Lista)
{
    lStates *temp;

    temp=findState(Lista,key,1);
    if(temp==NULL)
    {
        printf("\nERRO!");
        exit(42);
    }
    return(temp->eState);
}
int findid(char *key,lStates *Lista)
{
    lStates *temp;

    temp=findState(Lista,key,1);
    if(temp==NULL)
    {
        printf("\nERRO!");
        exit(42);
    }
    //printf("\n%d",temp->eState);
    return(temp->id);
}
/***/
AF* newAF ()
{
    AF *new1 = (AF*) calloc ( sizeof (AF), 1 );


    if ( new1 == NULL )
    {
        printf ( " ERRO (lStates): Impossivel montar." );
    }
    else
    {

        new1->Alpha=NULL;
        new1->Start=NULL;
        new1->States=NULL;
        new1->Transations=NULL;
        return new1;
    }
}
/** Função que pega uma string entre dois caracteries distintos.

    @param stri     Frase onde a palavra irá ser retirada
    @param in       caractere de inicio de amazenamento da string
    @param out      caractere de fim de amazenamento da string
    @param Sout     String onde a palavra ira ser amazenada
    @param cEnable  Habilida ignora a primeira ocorrencia de out quando =1

    @return void
*/
void separeteforC(char *stri, char in, char out,char *Sout,int cEnable)
{
    int i=0,enable=0,j=0;

    while(enable!=2 && stri[i]!=';' &&(stri[i]!='\0' || stri[i]!='\n' ))
    {
        if(stri[i]==in && enable==0)
        {
            enable=1;
            cEnable=0;
        }
        else if(stri[i]==out && cEnable==0)
        {
            enable=2;
        }
        else if(enable==1 && stri[i]!=in && stri[i]!=out)
        {
            Sout[j]=stri[i];
            j=j+1;
        }

        i=i+1;

    }
    Sout[j]='\0';
}

/** Função que ler uma arquivo jflap e retira o autonomo descrito

    @param arq Nome do arquivo jflap

    @return AF Um Automato
*/

AF* readNFA (char *arq)//ler o arquivo por palavras
{
    char templ[200],inde[100];
    int cont=0;
    lEdge *EdgeList=NULL;           /// Lista de edges que sera atribuida ao automato
    lEdge *nEdge=newEdge();         /// Elemento para a lista de Edges
    lStates *StateList=NULL;        /// Lista de estados que sera atribuida ao automato
    lStates *nState=newState();     /// Elemento para a Lista de estados
    lAlphab *AlphaList=NULL;        /// Lista do simbolos que sera atribuida ao automato(Alfabeto do Automato)
    lAlphab *nAlpha=newAlphab();    /// Elemento para a Lista de Simbolos
    AF *AFN=newAF();                /// Automato
    //system("cls");

    FILE *fp = fopen(arq, "r");
    //FILE *fp2 = fopen(save, "w");
    //strcpy(templ,save);
    if (!fp)
    {
        printf("\nERRO! Impossivel ler arquivo.\n");
        getchar();
        exit(42);
    }
    while(!feof(fp) && !ferror(fp))

    {
        fgets(templ,200,fp);

        separeteforC(templ,'"','"',inde,0);
        if(strcmp(inde,"transition_set")==0) ///Indetificando transitions
        {
            cont=0;
            // printf("\nIndetifico(Trans) : %s\n",inde);
            fgets(templ,200,fp);
            separeteforC(templ,'<','>',inde,0);
            while(strcmp(inde,"/structure")!=0)
            {
                //printf("\n\nEntrou no while :%s\n\n",inde);
                if(strcmp(inde,"input")==0)
                {
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nCusto: %s",inde);
                    strcpy(nEdge->input,inde);
                    cont++;
                }
                else if(strcmp(inde,"from")==0)
                {
                    fgets(templ,200,fp);
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nOrigem: %s",inde);
                    strcpy(nEdge->from,inde);
                    cont++;

                }
                else if(strcmp(inde,"to")==0)
                {
                    fgets(templ,200,fp);
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nPara: %s\n",inde);
                    strcpy(nEdge->to,inde);
                    cont++;

                }

                fgets(templ,200,fp);
                separeteforC(templ,'<','>',inde,0);

                if (cont==3)
                {
                    putEdge(&EdgeList,nEdge);
                    nEdge=newEdge();
                    cont=0;

                }

            }
            cont=0;
        }
        else if(strcmp(inde,"state_set")==0)      ///Indetificando estados
        {
            // printf("\n\nIndetifico(state): %s\n",inde);
            fgets(templ,200,fp);
            separeteforC(templ,'<','>',inde,0);
            while(strcmp(inde,"/structure")!=0)
            {
                if(strcmp(inde,"name")==0)
                {
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nEstado: %s\n",inde);
                    strcpy(nState->name,inde);
                    if( findState(StateList, nState->name, 1) == NULL)       ///Verificando se o Estado ja se encontra na lista
                    {
                        nState->id=cont;
                        putState(&StateList,nState);
                        cont++;
                    }
                    nState=newState();

                }
                fgets(templ,200,fp);
                separeteforC(templ,'<','>',inde,0);

            }

        }
        else if(strcmp(inde,"final_states")==0)   ///Indetificando estados finais;
        {
            // printf("\n\nIndetifico(Final State):%s\n",inde);
            fgets(templ,200,fp);
            separeteforC(templ,'<','>',inde,0);
            while(strcmp(inde,"/structure")!=0)
            {
                if(strcmp(inde,"name")==0)
                {
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nEstado Final: %s\n",inde);
                    ///Estado já existe?
                    nState = findState(StateList, inde, 1);
                    if( nState == NULL )
                    {   //Nao existe, entao adicione-o...
                        nState = newState();
                        strcpy(nState->name,inde);
                        nState->id=cont;
                        putState(&StateList,nState);
                        cont++;
                    }
                    //Set like final state
                    findState(StateList,inde,0);
                    nState = newState();
                }
                fgets(templ,200,fp);
                separeteforC(templ,'<','>',inde,0);
            }
        }
        else if(strcmp(inde,"start_state")==0)    ///Indetificando estado inicial;
        {
            // printf("\n\nIndetifico(Start State):%s\n",inde);
            fgets(templ,200,fp);
            separeteforC(templ,'<','>',inde,0);
            while(strcmp(inde,"/structure")!=0)
            {
                if(strcmp(inde,"name")==0)
                {
                    separeteforC(templ,'>','<',inde,1);
                    // printf("\nEstado Inicial: %s\n",inde);
                    nState = newState();
                    strcpy(nState->name,inde);
                    nState->id=cont;
                    ///Estado já existe?
                    if( findState(StateList, nState->name, 1) == NULL )
                    {
                        //Nao existe, entao adicione-o...
                        putState(&StateList,nState);
                        cont++;
                    }
                    AFN->Start = findState(StateList, nState->name, 1);
                    nState = newState();
                }

                fgets(templ,200,fp);
                separeteforC(templ,'<','>',inde,0);
            }
        }
        else if(strcmp(inde,"input_alph")==0)     ///Indetificando alfabeto;
        {
            // printf("\n\nIndetifico(Alfabeto):%s\n",inde);
            fgets(templ,200,fp);
            separeteforC(templ,'<','>',inde,0);
            while(strcmp(inde,"/structure")!=0)
            {
                if(strcmp(inde,"symbol")==0)
                {
                    separeteforC(templ,'>','<',inde,1);
                    // printf("simbolo: %s\n",inde);
                    strcpy(nAlpha->simbolo,inde);
                    putAlphab(&AlphaList,nAlpha);
                    nAlpha=newAlphab();
                }
                fgets(templ,200,fp);
                separeteforC(templ,'<','>',inde,0);
            }

        }
    }

    fclose(fp);
    AFN->Alpha=AlphaList;
    AFN->States=StateList;
    AFN->Transations=EdgeList;
    printf("\nArquivo lido com sucesso.\n\n");
    // printf("\nALFABETO: %p",AFN->Alpha);
    // printf("\nSTART: %p",AFN->Start);
    // printf("\nESTADOS: %p",AFN->States);
    // printf("\nEDges: %p",AFN->Transations);
    return(AFN);
    system("pause");

}
/***/

///Concatena duas listas de nomes recusando as repeticoes de nomes
void concatLname(lName **original, lName *apendice){
    lName *tpo = *original;
    lName *tpa = apendice;
    lName *nname;
    int fgrepeat = 0;

    while(tpa != NULL)
    {   tpo = *original;
        while(tpo != NULL)
        {   if( strcmp(tpo->name, tpa->name)==0 )
                fgrepeat = 1;
            tpo = tpo->next;
        }

        if(fgrepeat == 0){//Se nao repetiu, add à lista
            nname = newLName();
            strcpy(nname->name , tpa->name);
            putName(original, nname);
        }
        fgrepeat = 0;
        tpa = tpa->next;
    }
}

int cmplName( lName *esq, lName *dir)
{   int qtdeq[2]  = {0,0};
    int qtddif[2] = {0,0};
    int fgachou = 0;

    lName *tesq = esq;
    lName *tdir = dir;

    while(tesq != NULL)
    {   fgachou = 0;
        tdir = dir;
        while(tdir != NULL)
        {   if( strcmp(tesq->name, tdir->name)==0 )
            {   fgachou = 1;
                qtdeq[0]++;
            }
            tdir = tdir->next;
        }

        if(fgachou == 0)
            qtddif[0]++;

        tesq = tesq->next;
    }

    tdir = dir;
    while(tdir != NULL)
    {   fgachou = 0;
        tesq = esq;
        while(tesq != NULL)
        {   if( strcmp(tesq->name, tdir->name)==0 )
            {   fgachou = 1;
                qtdeq[1]++;
            }
            tesq = tesq->next;
        }

        if(fgachou == 0)
            qtddif[1]++;

        tdir = tdir->next;
    }

    if( qtdeq[0]==qtdeq[1] && qtddif[0]==0 && qtddif[1]==0)
        return 0;///Sao iguais
    /// OU Sao diferentes OU está contido
    //Caso contrario retorna quantidade de estados em comum e maior que ZERO
    if( qtdeq[0]==qtdeq[1] && qtdeq[0]>0 && qtdeq[1]>0)
        return qtdeq[0];
    //Erro
    return -1;
}

lStates* findStateNFA(lStates *Lista, lName *key){
    lStates *temp;

    temp=Lista;

    while(temp!=NULL)
    {

        if(cmplName( temp->listname, key)==0)
        {
            return (temp);
        }
        temp=temp->next;
    }
    return (temp);
}

int SetFinalStatesContained(lStates *Final, lStates *Container){
    lName *finalState = newLName();
    strcpy( finalState->name, Final->name);
    finalState->next = NULL;
    int cont=0;

    lStates *temp;
    temp=Container;

    while(temp!=NULL)
    {   int cmp = cmplName( finalState, temp->listname);
        if( cmp==1 || cmp==0)
        {
            temp->eState=1;
            cont++;
        }
        temp=temp->next;
    }
    return cont;
}

AF* NFAtoDFA(AF *AFN)
{
    lEdge *EdgeList=NULL;           /// Lista de edges que sera atribuida ao automato
    lEdge *nEdge = NULL;            /// Elemento para a lista de Edges
    lStates *StateList=NULL;        /// Lista de estados que sera atribuida ao automato
    lStates *nState=newState();     /// Elemento para a Lista de estados
    lAlphab *AlphaList=NULL;        /// Lista do simbolos que sera atribuida ao automato(Alfabeto do Automato)
    lAlphab *nAlpha=newAlphab();    /// Elemento para a Lista de Simbolos
    AF *AFD=newAF();                /// Automato
    lName   *nNameList = newLName();
    lName   *nlName = NULL;

    int contID=1;

    nlName = newLName();
    strcpy( nlName->name, AFN->Start->name);
    strcpy( nState->name, AFN->Start->name );///Add start state
    nState->listname = nlName;
    nState->id=0;
    putState(&StateList,nState);
    AFD->Start=nState;              ///Definindo Estado de Inicio
//    printf("\n\n\nEstado incial: %s",AFD->Start->name);

    AlphaList=AFN->Alpha;           ///Same Alphabet
    AFD->Alpha=AlphaList;

    lStates *tempLstates = StateList;

    while( tempLstates != NULL )
    {
//        printf("\nEstado X: %s\n", tempLstates->name);
        lAlphab *templAlphab = AlphaList;
        while(templAlphab != NULL )
        {
//            printf("Symbol a: %s\n", templAlphab->simbolo);
            lName *tpStateName = tempLstates->listname;
            nlName = NULL;

            ///Pesquisar estados destino das transicoes com estados origem e simbolo especifico
            while(tpStateName != NULL)
            {   lName *namesTo = findEdgeNFA(AFN->Transations, tpStateName->name, templAlphab->simbolo);
                if(nlName == NULL)
                    nlName = namesTo;
                else concatLname(&nlName, namesTo);

                tpStateName = tpStateName->next;
            }

            ///Se houver transicao:
            if( nlName!= NULL)
            {
                ///Se estado gerado nao estiver na lista, add:
                nState = findStateNFA( StateList, nlName);
                if(nState == NULL )
                {   lName *namesTo = nlName;
                    char chnamesTo[100] = "";
                    while(namesTo != NULL)
                    {   strcat(chnamesTo, namesTo->name);
                        if(namesTo->next != NULL) strcat(chnamesTo, ",");
                        namesTo = namesTo->next;
                    }
                    nState = newState();
                    nState->id = contID; contID++;
                    nState->listname = nlName;
                    strcpy( nState->name, chnamesTo);

                    putState(&StateList, nState);
                }
//                printf(" X com a vai para: %s\n", nState->name);


                ///Add nova transicao
                nEdge = newEdge();
                strcpy( nEdge->input, templAlphab->simbolo);
                strcpy( nEdge->from , tempLstates->name);
                strcpy( nEdge->to   , nState->name);
                putEdge( &EdgeList, nEdge);
            }

            templAlphab = templAlphab->next;
//            printf(" prox symbol: %s\n", templAlphab->simbolo);
        }
        tempLstates = tempLstates->next;
    }

    ///Reencontrar estados Finais:
    tempLstates = AFN->States;
//    printf("\nProcurando Estados Finais: \n");
    while( tempLstates != NULL )
    {
        if(tempLstates->eState == 1)///Se é estado Final...
        {   int x = SetFinalStatesContained( tempLstates, StateList );
//            printf("\nEstado %s encontrado em outros %d estados do AFD resultante \n",
//                        tempLstates->name, x);
        }
        tempLstates = tempLstates->next;
    }

    AFD->States=StateList;
    AFD->Transations=EdgeList;
    printf("\n\n AFN Convertido\n");
    return(AFD);
}

void saveJflap(AF *AF,char *arq)
{
    lEdge *tempEdge;
    lStates *tempState;
    lAlphab *tempAlpha;
    FILE *fp = fopen(arq,"w");

    if (!fp)
    {
        printf("\nERRO! Impossivel ler arquivo.\n");
        getchar();
        exit(42);
    }
    fprintf(fp,"<?xml version=\"1.0\" encoding=\"UTF-8\"?><structure type=\"editor_panel\">&#13;\n");
    fprintf(fp,"<structure type=\"transition_graph\">&#13;\n");
    fprintf(fp,"	<structure mode=\"Default mode\" type=\"fsa\">&#13;\n");
    fprintf(fp,"		<structure type=\"transition_set\">&#13;\n");
    tempEdge=AF->Transations;
    while(tempEdge!=NULL)
    {
        fprintf(fp,"		<fsa_trans>&#13;\n");
        fprintf(fp,"			<input>%s</input>&#13;\n",tempEdge->input);
        fprintf(fp,"			<from>&#13;;\n");
        fprintf(fp,"				<name>%s</name>&#13;\n",tempEdge->from);
        fprintf(fp,"				<id>%d</id>&#13;\n",findid(tempEdge->from,AF->States));
        fprintf(fp,"			</from>&#13;\n");
        fprintf(fp,"			<to>&#13;\n");
        fprintf(fp,"				<name>%s</name>&#13;\n",tempEdge->to);
        fprintf(fp,"				<id>%d</id>&#13;\n",findid(tempEdge->to,AF->States));
        fprintf(fp,"			</to>&#13;\n");
        fprintf(fp,"		</fsa_trans>&#13;\n");
        tempEdge=tempEdge->next;
    }

    fprintf(fp,"</structure>&#13;\n");
    fprintf(fp,"			<structure type=\"start_state\">&#13;\n");
    fprintf(fp,"				<state>&#13;\n");
    fprintf(fp,"					<name>%s</name>&#13;\n",AF->Start->name);
    fprintf(fp,"					<id>%d</id>&#13;\n",AF->Start->id);
    fprintf(fp,"				</state>&#13;\n");
    fprintf(fp,"			</structure>&#13;\n");
    fprintf(fp,"			<structure type=\"state_set\">&#13;\n");
    tempState=AF->States;
    while(tempState!=NULL)
    {
        fprintf(fp,"		<state>&#13;\n");
        fprintf(fp,"			<name>%s</name>&#13;\n",tempState->name);
        fprintf(fp,"			<id>%d</id>&#13;\n",tempState->id);
        fprintf(fp,"		</state>&#13;\n");
        tempState=tempState->next;
    }
    fprintf(fp,"</structure>&#13;\n");
    fprintf(fp,"			<structure type=\"final_states\">&#13;\n");
    tempState=AF->States;
    while(tempState!=NULL)
    {
        if(tempState->eState==1)
        {
            fprintf(fp,"		<state>&#13;\n");
            fprintf(fp,"			<name>%s</name>&#13;\n",tempState->name);
            fprintf(fp,"			<id>%d</id>&#13;\n",tempState->id);
            fprintf(fp,"		</state>&#13;\n");
        }
        tempState=tempState->next;
    }
    fprintf(fp,"</structure>&#13;\n");
    fprintf(fp,"		<structure type=\"input_alph\">&#13;\n");
    tempAlpha=AF->Alpha;
    while(tempAlpha!=NULL)
    {
        fprintf(fp,"				<symbol>%s</symbol>&#13;\n",tempAlpha->simbolo);
        tempAlpha=tempAlpha->next;
    }
    fprintf(fp,"</structure>&#13;\n");
    fprintf(fp,"</structure>&#13;\n");
    fprintf(fp,"	    <state_point_map>&#13;\n");
    tempState=AF->States;
    while(tempState!=NULL)
    {
        fprintf(fp,"       <state_point>&#13;\n");
        fprintf(fp,"			<state>%d</state>&#13;\n",tempState->id);
        fprintf(fp,"			<point>&#13;\n");
        fprintf(fp,"				<x>%d</x>&#13;\n",rand() % 100);
        fprintf(fp,"				<y>%d</y>&#13;\n",rand() % 100);
        fprintf(fp,"			</point>&#13;\n");
        fprintf(fp,"		</state_point>&#13;\n");
        tempState=tempState->next;
    }
    fprintf(fp," 		</state_point_map>&#13;\n");
    fprintf(fp,"	<control_point_map>&#13;\n");
    tempEdge=AF->Transations;
    while(tempEdge!=NULL)
    {
        fprintf(fp,"			<control_point>&#13;\n");
        fprintf(fp,"			<from>%d</from>&#13;\n",findid(tempEdge->from,AF->States));
        fprintf(fp,"			<to>%d</to>&#13;\n",findid(tempEdge->to,AF->States));
        fprintf(fp,"			<point>&#13;\n");
        fprintf(fp,"				<x>%d</x>&#13;\n",rand() % 100);
        fprintf(fp,"				<y>%d</y>&#13;\n",rand() % 100);
        fprintf(fp,"			</point>&#13;\n");
        fprintf(fp,"		</control_point>&#13;\n");
        tempEdge=tempEdge->next;
    }
    fprintf(fp,"    </control_point_map>&#13;\n");
    fprintf(fp,"   </structure>&#13;\n");
    fprintf(fp,"	<state_label_map/>&#13;\n");
    fprintf(fp,"	<note_map/>&#13;\n");
    fprintf(fp,"</structure>\n");

    fclose(fp);

}

void readSentece(AF *AF,char *sentence)
{
    int i=0;
    lStates *temp;
    char nextState[100],tempSimbolo[2];

    temp=AF->Start;
    tempSimbolo[1]='\0';
    while(sentence[i]!='\0')
    {
        tempSimbolo[0]=sentence[i];
        if(findEdge(AF->Transations,temp->name,tempSimbolo,1)==NULL)
        {
            printf("\nRejeita\n\n");
            return;
        }
        printf("\n%c | %s->%s",sentence[i],temp->name,findEdge(AF->Transations,temp->name,tempSimbolo,1));
        strcpy(nextState,findEdge(AF->Transations,temp->name,tempSimbolo,1));
        if(strcmp(nextState,"")==0) ///nao tem edge para este simbolo neste estado
        {
            if(iseState(temp->name,AF->States)==1 && sentence[i+1]=='\0')
            {
                printf("\nAceita\n\n");
                return;
            }
            else
            {
                printf("\nRejeita\n\n");
                return;
            }
        }
        else
        {
            temp=findState(AF->States,nextState,1);
            if(nextState==NULL)
            {
                printf("\nRejeita\n\n");
                return;
            }
        }
        i++;

    }
    if(iseState(temp->name,AF->States)==1 && sentence[i]=='\0')
    {
        printf("\nAceita\n\n");
        return;
    }
    else
    {
        printf("\nRejeita\n\n");
        return;
    }
}

int main()
{
    AF *AFN,*AFD;
    char aqr[200];
    int op;

    printf("\nDigite o nome do arquivo do jflap a ser lido: ");
    scanf("%s",aqr);

    AFN=readNFA(aqr);
    AFN->print();
    AFD=NFAtoDFA(AFN);
    AFD->print();
    saveJflap(AFD,"TesteAFD.jflap");
    do  //system("CLS");
    {
        printf("\nEscolha uma opcao\n1-Entrada de uma sentenca\n2-Ler outro arquivo Jflap\n3-Sair\n");
        scanf("%d",&op);
        if(op==1)
        {
            do{
                printf("\nDigite a sentenca: (z -> voltar ao MENU)   ");
                scanf("%s",aqr);
                if(strcmp(aqr, "z")==0)
                    op=0;
                else
                    readSentece(AFD,aqr);
            }while(op==1);
        }
        if(op==2)
        {
            printf("\nDigite o nome do arquivo do jflap a ser lido: ");
            scanf("%s",aqr);
            free(AFN);
            free(AFD);

            AFN=readNFA(aqr);
            AFN->print();
            AFD=NFAtoDFA(AFN);
            AFD->print();
            saveJflap(AFD,"TesteAFD.jflap");
        }
    }
    while(op!=3);
    free(AFN);
    free(AFD);
    return 0;
}










