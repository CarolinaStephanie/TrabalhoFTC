#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 500

int init[20], fin[20], a = 0, b = 0;

/***/
typedef struct Alphab
{
    char simbolo[100]; ///Simbolo do alfabeto
    struct Alphab *next;

    void print()
    {
        printf("\n Alphab: ");
        struct Alphab *t = this;
        while (t != NULL)
        {
            printf("%s", t->simbolo);
            if (t->next != NULL)
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

    void print()
    {
        printf("\n nameList: ");
        struct nameList *t = this;
        while (t != NULL)
        {
            printf("%s", t->name);
            if (t->next != NULL)
                printf(", ");
            t = t->next;
        }
    }
} lName;
/***/
typedef struct States
{
    char name[100]; /// Nome do estado
    int eState;     /// Indicador de estado final se igual a 1;
    int id;         ///ID;
    struct States *next;

    lName *listname;

    void print()
    {
        printf("\n States: ");
        struct States *t = this;
        while (t != NULL)
        {
            printf("\n name: %s | Final? %d | ID: %d | ", t->name, t->eState, t->id);
            t->listname->print();
            t = t->next;
        }
    }
} lStates;
/***/
typedef struct Edge
{
    char from[100];  /// Origem
    char to[100];    /// Destino
    char input[100]; /// Simbolo nescessario
    struct Edge *next;

    void print()
    {
        printf("\n Transicoes: \n");
        struct Edge *t = this;
        while (t != NULL)
        {
            printf("( %s, %s )->%s\n", t->from, t->input, t->to);
            t = t->next;
        }
    }
} lEdge;
/***/
typedef struct AFi
{
    lStates *States;    /// Conjuto de Estados
    lAlphab *Alpha;     /// Alfabeto
    lEdge *Transations; /// Lista de edges
    lStates *Start;     /// Estado Inicial

    void print()
    {
        printf("\n AF: \n");
        printf(" Inicial: %s\n ", Start->name);
        printf(" Estados: ");
        States->print();
        Alpha->print();
        Transations->print();
    }
} AF;
/***/
lName *newLName()
{

    lName *new1 = (lName *)calloc(sizeof(lName), 1);

    if (new1 == NULL)
    {
        printf(" ERRO (lName): Impossivel montar.");
    }
    else
    {
        strcpy(new1->name, "nothing");
        new1->next = NULL;
        return new1;
    }
}
/***/
void putName(lName **Lista, lName *new1)
{
    if (*Lista == NULL)
    {
        new1->next = NULL;
        *Lista = new1;
    }
    else
    {
        lName *temp;
        temp = *Lista;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                new1->next = NULL;
                temp->next = new1;
                return;
            }
            temp = temp->next;
        }
    }
}
/***/
lAlphab *newAlphab()
{

    lAlphab *new1 = (lAlphab *)calloc(sizeof(lAlphab), 1);

    if (new1 == NULL)
    {
        printf(" ERRO (lAlphab): Impossivel montar.");
    }
    else
    {
        strcpy(new1->simbolo, " ");
        new1->next = NULL;
        return new1;
    }
}
/***/
void putAlphab(lAlphab **Lista, lAlphab *new1)
{
    if (*Lista == NULL)
    {
        new1->next = NULL;
        *Lista = new1;
    }

    else
    {
        lAlphab *temp;
        temp = *Lista;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                new1->next = NULL;
                temp->next = new1;
                return;
            }
            temp = temp->next;
        }
    }
}
/***/
lEdge *newEdge()
{
    lEdge *new1 = (lEdge *)calloc(sizeof(lEdge), 1);

    if (new1 == NULL)
    {
        printf(" ERRO (lEdge): Impossivel montar.");
    }
    else
    {
        strcpy(new1->from, " ");
        strcpy(new1->to, " ");
        strcpy(new1->to, " ");
        new1->next = NULL;
        return new1;
    }
}
/***/
void putEdge(lEdge **Lista, lEdge *new2)
{
    if (*Lista == NULL)
    {
        new2->next = NULL;
        *Lista = new2;
        return;
    }

    else
    {
        lEdge *temp;
        temp = *Lista;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {

                temp->next = new2;
                temp->next->next = NULL;
                return;
            }
            temp = temp->next;
        }
    }
}
/***/
char *findEdge(lEdge *Lista, char *state, char *input, int op)
{
    lEdge *temp;
    char statetemp[100];

    temp = Lista;
    if (op == 0) //Para AFN
    {
        strcpy(statetemp, "");
        while (temp != NULL)
        {
            if (strcmp(temp->from, state) == 0 && strcmp(temp->input, input) == 0)
            {
                if (strcmp(statetemp, "") != 0) ///Se caso for mais de um estado
                {
                    strcat(statetemp, ",");
                }
                strcat(statetemp, temp->to);
            }
            temp = temp->next;
        }
        return (statetemp);
    }
    else //Para AFD
    {
        while (temp != NULL)
        {
            if (strcmp(temp->from, state) == 0 && strcmp(temp->input, input) == 0)
            {

                return (temp->to);
            }
            temp = temp->next;
        }
    }
}
/***/
lName *findEdgeNFA(lEdge *Lista, char *state, char *input)
{
    lEdge *temp;
    lName *names = NULL;
    lName *tpname;

    temp = Lista;
    while (temp != NULL)
    {
        if (strcmp(temp->from, state) == 0 && strcmp(temp->input, input) == 0)
        {
            tpname = newLName();
            strcpy(tpname->name, temp->to);
            putName(&names, tpname);
        }
        temp = temp->next;
    }
    return (names);
}
/***/
lStates *newState()
{
    lStates *new1 = (lStates *)calloc(sizeof(lStates), 1);

    if (new1 == NULL)
    {
        printf(" ERRO (lStates): Impossivel montar.");
    }
    else
    {

        new1->eState = 0;
        new1->listname = newLName();
        strcpy(new1->name, "");
        new1->next = NULL;
        return new1;
    }
}
/***/
void putState(lStates **Lista, lStates *new1)
{
    if (*Lista == NULL)
    {
        new1->next = NULL;
        *Lista = new1;
        return;
    }

    else
    {
        lStates *temp;
        temp = *Lista;

        while (temp != NULL)
        {
            if (temp->next == NULL)
            {
                new1->next = NULL;
                temp->next = new1;
                return;
            }
            temp = temp->next;
        }
    }
}
/***/
lStates *findState(lStates *Lista, char *key, int op)
{
    lStates *temp;

    temp = Lista;

    while (temp != NULL)
    {
        if (strcmp(temp->name, key) == 0 && op == 0) ///Opera��o de achar estado para marca como estado final
        {
            temp->eState = 1;
            return (temp);
        }
        else if (strcmp(temp->name, key) == 0 && op == 1) ///Opera��o de achar estado para retorna o endere�o para atribuir como estado inicial
        {
            return (temp);
        }
        temp = temp->next;
    }
    return (temp);
}
/**Fun��o que retorna se e estado final ou nao se sim 1 se nao 0*/
int iseState(char *key, lStates *Lista)
{
    lStates *temp;

    temp = findState(Lista, key, 1);
    if (temp == NULL)
    {
        printf("\nERRO!");
        exit(42);
    }
    return (temp->eState);
}
int findid(char *key, lStates *Lista)
{
    lStates *temp;

    temp = findState(Lista, key, 1);
    if (temp == NULL)
    {
        printf("\nERRO!");
        exit(42);
    }
    //printf("\n%d",temp->eState);
    return (temp->id);
}
/***/
AF *newAF()
{
    AF *new1 = (AF *)calloc(sizeof(AF), 1);

    if (new1 == NULL)
    {
        printf(" ERRO (lStates): Impossivel montar.");
    }
    else
    {

        new1->Alpha = NULL;
        new1->Start = NULL;
        new1->States = NULL;
        new1->Transations = NULL;
        return new1;
    }
}
/** Fun��o que pega uma string entre dois caracteries distintos.

    @param stri     Frase onde a palavra ir� ser retirada
    @param in       caractere de inicio de amazenamento da string
    @param out      caractere de fim de amazenamento da string
    @param Sout     String onde a palavra ira ser amazenada
    @param cEnable  Habilida ignora a primeira ocorrencia de out quando =1

    @return void
*/
void separeteforC(char *stri, char in, char out, char *Sout, int cEnable)
{
    int i = 0, enable = 0, j = 0;

    while (enable != 2 && stri[i] != ';' && (stri[i] != '\0' || stri[i] != '\n'))
    {
        if (stri[i] == in && enable == 0)
        {
            enable = 1;
            cEnable = 0;
        }
        else if (stri[i] == out && cEnable == 0)
        {
            enable = 2;
        }
        else if (enable == 1 && stri[i] != in && stri[i] != out)
        {
            Sout[j] = stri[i];
            j = j + 1;
        }

        i = i + 1;
    }
    Sout[j] = '\0';
}

/** Fun��o que ler uma arquivo jflap e retira o autonomo descrito

    @param arq Nome do arquivo jflap

    @return AF Um Automato
*/

AF *readNFA(int nfa_table[][MAXCHAR], int states, int qtdSymbols, char *symbols) //ler o NFA da table
{
    char templ[200], inde[100];
    int cont = 0;
    lEdge *EdgeList = NULL;        /// Lista de edges que sera atribuida ao automato
    lEdge *nEdge = newEdge();      /// Elemento para a lista de Edges
    lStates *StateList = NULL;     /// Lista de estados que sera atribuida ao automato
    lStates *nState = newState();  /// Elemento para a Lista de estados
    lAlphab *AlphaList = NULL;     /// Lista do simbolos que sera atribuida ao automato(Alfabeto do Automato)
    lAlphab *nAlpha = newAlphab(); /// Elemento para a Lista de Simbolos
    AF *AFN = newAF();             /// Automato
    char str[2] = "\0";            /* gives {\0, \0} */
    char aux[10];                  /* gives {\0, \0} */
    //system("cls");

    // TRANSIÇOES
    for (int l = 1; l <= states; l++)
    {
        for (int c = 1; c <= states; c++)
        {
            if (nfa_table[l][c] != -1 && nfa_table[l][c] != 0) // tem um estado e não é lixo
            {
                if (c <= qtdSymbols)
                {
                    str[0] = symbols[c - 1]; // transformar em string
                    strcpy(nEdge->input, str);
                }
                else
                {
                    strcpy(nEdge->input, " "); // colocando lambida
                }
                sprintf(aux, "%d", l);
                strcpy(nEdge->from, aux);
                sprintf(aux, "%d", nfa_table[l][c]);
                strcpy(nEdge->to, aux);
                putEdge(&EdgeList, nEdge);
                nEdge = newEdge();
            }
        }
    }

    // ESTADOS

    for (int i = 1; i < states; i++)
    {
        sprintf(aux, "q%d", i);
        strcpy(nState->name, aux);
        nState->id = i;
        putState(&StateList, nState);
        nState = newState();
    }

    // ESTADO INICIAL
    sprintf(aux, "q%d", init[a - 1]);
    AFN->Start = findState(StateList, aux, 1);

    // ESTADO FINAL

    for (int i = 0; i < b; i++)
    {
        sprintf(aux, "q%d", fin[i]);
        findState(StateList, aux, 0);
    }

    // ALFABETOS

    for (int i = 0; i < qtdSymbols; i++)
    {
        str[0] = symbols[i]; // transformar em string
        strcpy(nAlpha->simbolo, str);
        putAlphab(&AlphaList, nAlpha);
        nAlpha = newAlphab();
    }

    AFN->Alpha = AlphaList;
    AFN->States = StateList;
    AFN->Transations = EdgeList;

    // printf("\nALFABETO: %p", AFN->Alpha);
    // printf("\nSTART: %s", AFN->Start->name);
    // printf("\nESTADOS: %s", AFN->States);
    // printf("\nEDges: %p", AFN->Transations);
    return (AFN);
    system("pause");
}
/***/

///Concatena duas listas de nomes recusando as repeticoes de nomes
void concatLname(lName **original, lName *apendice)
{
    lName *tpo = *original;
    lName *tpa = apendice;
    lName *nname;
    int fgrepeat = 0;

    while (tpa != NULL)
    {
        tpo = *original;
        while (tpo != NULL)
        {
            if (strcmp(tpo->name, tpa->name) == 0)
                fgrepeat = 1;
            tpo = tpo->next;
        }

        if (fgrepeat == 0)
        { //Se nao repetiu, add � lista
            nname = newLName();
            strcpy(nname->name, tpa->name);
            putName(original, nname);
        }
        fgrepeat = 0;
        tpa = tpa->next;
    }
}

int cmplName(lName *esq, lName *dir)
{
    int qtdeq[2] = {0, 0};
    int qtddif[2] = {0, 0};
    int fgachou = 0;

    lName *tesq = esq;
    lName *tdir = dir;

    while (tesq != NULL)
    {
        fgachou = 0;
        tdir = dir;
        while (tdir != NULL)
        {
            if (strcmp(tesq->name, tdir->name) == 0)
            {
                fgachou = 1;
                qtdeq[0]++;
            }
            tdir = tdir->next;
        }

        if (fgachou == 0)
            qtddif[0]++;

        tesq = tesq->next;
    }

    tdir = dir;
    while (tdir != NULL)
    {
        fgachou = 0;
        tesq = esq;
        while (tesq != NULL)
        {
            if (strcmp(tesq->name, tdir->name) == 0)
            {
                fgachou = 1;
                qtdeq[1]++;
            }
            tesq = tesq->next;
        }

        if (fgachou == 0)
            qtddif[1]++;

        tdir = tdir->next;
    }

    if (qtdeq[0] == qtdeq[1] && qtddif[0] == 0 && qtddif[1] == 0)
        return 0; ///Sao iguais
    /// OU Sao diferentes OU est� contido
    //Caso contrario retorna quantidade de estados em comum e maior que ZERO
    if (qtdeq[0] == qtdeq[1] && qtdeq[0] > 0 && qtdeq[1] > 0)
        return qtdeq[0];
    //Erro
    return -1;
}

lStates *findStateNFA(lStates *Lista, lName *key)
{
    lStates *temp;

    temp = Lista;

    while (temp != NULL)
    {

        if (cmplName(temp->listname, key) == 0)
        {
            return (temp);
        }
        temp = temp->next;
    }
    return (temp);
}

int SetFinalStatesContained(lStates *Final, lStates *Container)
{
    lName *finalState = newLName();
    strcpy(finalState->name, Final->name);
    finalState->next = NULL;
    int cont = 0;

    lStates *temp;
    temp = Container;

    while (temp != NULL)
    {
        int cmp = cmplName(finalState, temp->listname);
        if (cmp == 1 || cmp == 0)
        {
            temp->eState = 1;
            cont++;
        }
        temp = temp->next;
    }
    return cont;
}

AF *NFAtoDFA(AF *AFN)
{
    lEdge *EdgeList = NULL;        /// Lista de edges que sera atribuida ao automato
    lEdge *nEdge = NULL;           /// Elemento para a lista de Edges
    lStates *StateList = NULL;     /// Lista de estados que sera atribuida ao automato
    lStates *nState = newState();  /// Elemento para a Lista de estados
    lAlphab *AlphaList = NULL;     /// Lista do simbolos que sera atribuida ao automato(Alfabeto do Automato)
    lAlphab *nAlpha = newAlphab(); /// Elemento para a Lista de Simbolos
    AF *AFD = newAF();             /// Automato
    lName *nNameList = newLName();
    lName *nlName = NULL;

    int contID = 1;

    nlName = newLName();
    strcpy(nlName->name, AFN->Start->name);
    strcpy(nState->name, AFN->Start->name); ///Add start state
    nState->listname = nlName;
    nState->id = 0;
    putState(&StateList, nState);
    AFD->Start = nState; ///Definindo Estado de Inicio
                         //    printf("\n\n\nEstado incial: %s",AFD->Start->name);

    AlphaList = AFN->Alpha; ///Same Alphabet
    AFD->Alpha = AlphaList;

    lStates *tempLstates = StateList;

    while (tempLstates != NULL)
    {
        // printf("\nEstado X: %s\n", tempLstates->name);
        lAlphab *templAlphab = AlphaList;
        while (templAlphab != NULL)
        {
            // printf("Symbol a: %s\n", templAlphab->simbolo);
            lName *tpStateName = tempLstates->listname;
            nlName = NULL;

            ///Pesquisar estados destino das transicoes com estados origem e simbolo especifico
            while (tpStateName != NULL)
            {
                lName *namesTo = findEdgeNFA(AFN->Transations, tpStateName->name, templAlphab->simbolo);
                if (nlName == NULL)
                    nlName = namesTo;
                else
                    concatLname(&nlName, namesTo);

                tpStateName = tpStateName->next;
            }

            ///Se houver transicao:
            if (nlName != NULL)
            {
                ///Se estado gerado nao estiver na lista, add:
                nState = findStateNFA(StateList, nlName);
                // printf("\nState name: %s\n", nState->name);
                if (nState == NULL)
                {
                    lName *namesTo = nlName;
                    char chnamesTo[100] = "";
                    while (namesTo != NULL)
                    {
                        strcat(chnamesTo, namesTo->name);
                        if (namesTo->next != NULL)
                            strcat(chnamesTo, ",");
                        namesTo = namesTo->next;
                    }
                    nState = newState();
                    nState->id = contID;
                    contID++;
                    nState->listname = nlName;
                    strcpy(nState->name, chnamesTo);

                    putState(&StateList, nState);
                }
                //  printf(" X com a vai para: %s\n", nState->name);

                ///Add nova transicao
                nEdge = newEdge();
                strcpy(nEdge->input, templAlphab->simbolo);
                strcpy(nEdge->from, tempLstates->name);
                strcpy(nEdge->to, nState->name);
                putEdge(&EdgeList, nEdge);
            }

            templAlphab = templAlphab->next;
            //  printf(" prox symbol: %s\n", templAlphab->simbolo);
        }
        tempLstates = tempLstates->next;
    }

    ///Reencontrar estados Finais:
    tempLstates = AFN->States;
    //    printf("\nProcurando Estados Finais: \n");
    while (tempLstates != NULL)
    {
        if (tempLstates->eState == 1) ///Se � estado Final...
        {
            int x = SetFinalStatesContained(tempLstates, StateList);
            //  printf("\nEstado %s encontrado em outros %d estados do AFD resultante \n",
            //       tempLstates->name, x);
        }
        tempLstates = tempLstates->next;
    }

    AFD->States = StateList;
    AFD->Transations = EdgeList;
    return (AFD);
}

void saveJflap(AF *AF, char *arq)
{
    lEdge *tempEdge;
    lStates *tempState;
    lAlphab *tempAlpha;
    FILE *fp = fopen(arq, "w");

    if (!fp)
    {
        printf("\nERRO! Impossivel ler arquivo.\n");
        getchar();
        exit(42);
    }
    fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><!--Created with JFLAP 6.4.--><structure>\n");
    fprintf(fp, "	<type>fa</type>\n");
    fprintf(fp, "	<automaton>\n");
    fprintf(fp, "		<!--The list of states.-->\n");

    tempState = AF->States;
    while (tempState != NULL)
    {
        fprintf(fp, "		<state id=\"%d\" name=\"%s\">\n", tempState->id, tempState->name);
        fprintf(fp, "			<x>%d</x>\n", rand() % 100);
        fprintf(fp, "			<y>%d</y>\n", rand() % 100);
        if (strcmp(tempState->name, AF->Start->name) == 0) // é estado inicial
            fprintf(fp, "			<initial/>\n");
        if (tempState->eState == 1) // é estado final
            fprintf(fp, "			<final/>\n");
        fprintf(fp, "		</state>\n");
        tempState = tempState->next;
    }

    fprintf(fp, "		<!--The list of transitions.-->\n");
    tempEdge = AF->Transations;
    while (tempEdge != NULL)
    {

        fprintf(fp, "		<transition>\n");
        fprintf(fp, "			<from>%d</from>\n", findid(tempEdge->from, AF->States));
        fprintf(fp, "			<to>%d</to>\n", findid(tempEdge->to, AF->States));
        fprintf(fp, "			<read>%s</read>\n", tempEdge->input);
        fprintf(fp, "		</transition>\n");
        tempEdge = tempEdge->next;
    }
    fprintf(fp, "	</automaton>\n");
    fprintf(fp, "</structure>\n");
    fclose(fp);
}

void readSentece(AF *AF, char *sentence)
{
    int i = 0;
    lStates *temp;
    char nextState[100], tempSimbolo[2];

    temp = AF->Start;
    tempSimbolo[1] = '\0';
    while (sentence[i] != '\0')
    {
        tempSimbolo[0] = sentence[i];
        if (findEdge(AF->Transations, temp->name, tempSimbolo, 1) == NULL)
        {
            printf("Rejeita");
            return;
        }
        //printf("\n%c | %s->%s", sentence[i], temp->name, findEdge(AF->Transations, temp->name, tempSimbolo, 1));
        strcpy(nextState, findEdge(AF->Transations, temp->name, tempSimbolo, 1));
        if (strcmp(nextState, "") == 0) ///nao tem edge para este simbolo neste estado
        {
            if (iseState(temp->name, AF->States) == 1 && sentence[i + 1] == '\0')
            {
                printf("Aceita");
                return;
            }
            else
            {
                printf("Rejeita");
                return;
            }
        }
        else
        {
            temp = findState(AF->States, nextState, 1);
            if (temp == NULL)
            {
                printf("Rejeita");
                return;
            }
        }
        i++;
    }
    if (iseState(temp->name, AF->States) == 1 && sentence[i] == '\0')
    {
        printf("Aceita");
        return;
    }
    else
    {
        printf("Rejeita");
        return;
    }
}

void readExpression(char *arq, char *exp)
{
    char templ[MAXCHAR], inde[MAXCHAR];
    int i = 0;

    FILE *fp = fopen(arq, "r");

    if (!fp)
    {
        printf("\nERRO! Impossivel ler arquivo.\n");
        getchar();
        exit(42);
    }
    // get xml, type, comment and expression line
    for (i = 0; i < 4; i++)
        fgets(templ, MAXCHAR, fp); // xml line
    separeteforC(templ, '>', '<', exp, 1);
    fclose(fp);
}

/*
 isStringValid function verify if the symbol is between a-z, A-Z, 0,9
*/

bool isStringValid(char *s, int i)
{
    return ((s[i] >= 97 && s[i] <= 122) || (s[i] >= 65 && s[i] <= 90) || (s[i] >= 48 && s[i] <= 57));
}

/*
 isLastStringValid function verify if the symbol is between a-z, A-Z, 0,9
*/

bool isLastStringValid(char *s, int i)
{
    return ((s[i + 1] >= 97 && s[i + 1] < 122) || (s[i + 1] >= 65 && s[i + 1] < 90) || (s[i + 1] >= 48 && s[i + 1] < 57));
}

/*
 preprocessor function simplifies the expression, as we have no symbol for concatenation
 operation. preprocessor function provide one.
*/

int preprocessor(char *s, char *newExp)
{
    char x[MAXCHAR];
    int l = strlen(s);
    int j = 0;
    x[j] = '(';
    j += 1;

    for (int i = 0; i < l; i++)
    {
        x[j] = s[i];
        j += 1;
        if (isStringValid(s, i) && isStringValid(s, i + 1))
        {
            x[j] = '.';
            j += 1;
        }
        else if (s[i] == ')' && s[i + 1] == '(')
        {
            x[j] = '.';
            j += 1;
        }
        else if (isStringValid(s, i) && s[i + 1] == '(')
        {
            x[j] = '.';
            j += 1;
        }
        else if (s[i] == ')' && isStringValid(s, i + 1))
        {
            x[j] = '.';
            j += 1;
        }
        else if (s[i] == '*' && (s[i + 1] == '(' || isLastStringValid(s, i)))
        {
            x[j] = '.';
            j += 1;
        }
    }
    x[j] = ')';
    j += 1;
    for (int i = 0; i < j; i++)
    {
        newExp[i] = x[i];
    }

    return j;
}

bool checkIfIsInArray(char s, char *symbols, int qtdSymbols)
{
    int i = 0;
    bool answ = false;
    while (i < qtdSymbols)
    {
        if (symbols[i] == s)
        {
            answ = true;
            break;
        }
        i++;
    }
    return answ;
}

int getPositionInArray(char s, char *symbols, int qtdSymbols)
{
    int i = 0;
    while (i < qtdSymbols)
    {
        if (symbols[i] == s)
        {
            break;
        }
        i++;
    }
    return i;
}

bool isSymbolValid(char s)
{
    return ((s >= 97 && s <= 122) || (s >= 65 && s <= 90) || (s >= 48 && s <= 57));
}

int getPositionInArray(char s, int qtdSymbols, char *symbols)
{
    int i = 0;
    while (i < qtdSymbols)
    {
        if (symbols[i] == s)
        {
            break;
        }
        i++;
    }
    return i;
}

void reduce_fin(int x)
{
    for (int i = x; i < b - 1; i++)
        fin[i] = fin[i + 1];
    b -= 1;
}

int reg_nfa(char *s, int nfa_table[][MAXCHAR], int qtdSymbols, char *symbols, int l)
{
    int states = 1;
    int m, n, j, counter, position;
    for (int i = 0; i < l; i++)
    {
        char x = s[i];
        printf("Symbol: %c\n", x);
        if (isSymbolValid(x))
        {
            position = getPositionInArray(x, qtdSymbols, symbols);
            printf("position: %d\n", position);
            nfa_table[states][0] = states;
            init[a] = states;
            a += 1;
            states += 1;
            nfa_table[states - 1][position + 1] = states;
            fin[b] = states;
            b += 1;
            nfa_table[states][0] = states;
            states += 1;
        }
        else
        {
            switch (x)
            {
            case '.':
                m = fin[b - 2];
                n = init[a - 1];
                nfa_table[m][qtdSymbols + 1] = n;
                reduce_fin(b - 2); //reduces final state
                a -= 1;            //reduces initial states
                break;
            case '+':
                for (j = a - 1, counter = 0; counter < qtdSymbols; counter++)
                {
                    m = init[j - counter];
                    nfa_table[states][qtdSymbols + 1 + counter] = m;
                }
                a = a - 2;
                init[a] = states;
                a += 1;
                nfa_table[states][0] = states;
                states += 1;
                for (j = b - 1, counter = 0; counter < qtdSymbols; counter++)
                {
                    m = fin[j - counter];
                    nfa_table[m][qtdSymbols + 1] = states;
                }
                b = b - 2;
                fin[b] = states;
                b += 1;
                nfa_table[states][0] = states;
                states += 1;
                break;
            case '*':
                m = init[a - 1];
                nfa_table[states][qtdSymbols + 1] = m;
                nfa_table[states][0] = states;
                init[a - 1] = states;

                states += 1;
                n = fin[b - 1];
                nfa_table[n][qtdSymbols + 1] = m;
                nfa_table[n][qtdSymbols + 2] = states;
                nfa_table[states - 1][qtdSymbols + 2] = states;
                fin[b - 1] = states;
                nfa_table[states][0] = states;
                states += 1;
                break;
            }
        }
    }
    return states;
}

void print_initial_final()
{
    printf("initial state/s is/are :- ");
    for (int i = 0; i < a; i++)
        printf("%d ", init[i]);
    printf("\n");
    printf("final state/s is/are :- ");
    for (int i = 0; i < b; i++)
        printf("%d ", fin[i]);
    printf("\n");
}

void print_nfa_table(int nfa_table[][MAXCHAR], int states, int qtdSymbols, char *symbols)
{
    printf("\n");
    for (int i = 0; i < 60; i++)
        printf("*");
    printf("\n\n");
    printf("                 TRANSITION TABLE FOR NFA\n\n");
    printf("          States");
    for (int i = 0; i < qtdSymbols; i++)
        printf("          %c", symbols[i]);
    for (int i = 0; i < qtdSymbols; i++)
        printf("           e");
    printf("\n");
    for (int i = 0; i < 35 * qtdSymbols; i++)
        printf("-");
    printf("\n");

    for (int i = 1; i < states; i++)
    {
        for (int j = 0; j < states - 1; j++)
        {
            if (nfa_table[i][j] == -1)
                printf("           --");
            else
                printf("          %d", nfa_table[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    for (int i = 0; i < 60; i++)
        printf("*");
    printf("\n");
    ;
    print_initial_final();
}

void push(char element, char stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        stack[stackSize - 1] = element;
        *top = stackSize - 1;
    }
    else if (*top == 0)
    {
        //printf("The stack is already full. \n");
    }
    else
    {
        stack[(*top) - 1] = element;
        (*top)--;
    }
}
void pop(char stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        // printf("The stack is empty. \n");
    }
    else
    {
        // If the element popped was the last element in the stack
        // then set top to -1 to show that the stack is empty
        if ((*top) == stackSize - 1)
        {
            (*top) = -1;
        }
        else
        {
            (*top)++;
        }
    }
}

void pushInt(int element, int stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        stack[stackSize - 1] = element;
        *top = stackSize - 1;
    }
    else if (*top == 0)
    {
        //printf("The stack is already full. \n");
    }
    else
    {
        stack[(*top) - 1] = element;
        (*top)--;
    }
}
void popInt(int stack[], int *top, int stackSize)
{
    if (*top == -1)
    {
        // printf("The stack is empty. \n");
    }
    else
    {
        // If the element popped was the last element in the stack
        // then set top to -1 to show that the stack is empty
        if ((*top) == stackSize - 1)
        {
            (*top) = -1;
        }
        else
        {
            (*top)++;
        }
    }
}

int postfix(char *s, int sizeExp, int qtdSymbols, char *symbols, char *p)
{
    int l = sizeExp;
    char a[MAXCHAR];
    char ch[50];
    int j = 0;
    int top = -1;

    for (int i = 0; i < l; i++)
    {
        char x = s[i];
        if (isSymbolValid(x))
        {
            a[j] = x;
            j += 1;
            if (!checkIfIsInArray(x, symbols, qtdSymbols))
                qtdSymbols++;
        }
        switch (x)
        {
        case '(':
            push('(', ch, &top, 50);
            break;
        case ')':
            while (top != -1)
            {
                if (ch[top] == '(')
                {
                    pop(ch, &top, 50);
                    break;
                }
                else
                {
                    a[j] = ch[top];
                    pop(ch, &top, 50);
                    j += 1;
                }
            }
            break;
        case '.':
            if (top == -1)
            {
                push('.', ch, &top, 50);
            }
            else
            {
                char temp = ch[top];
                if (temp == '(')
                    push('.', ch, &top, 50);
                else if (temp == '*')
                {
                    a[j] = ch[top];
                    pop(ch, &top, 50);
                    j += 1;
                    if (ch[top] == '.')
                    {
                        a[j] = '.';
                        j += 1;
                    }
                    else
                    {
                        push('.', ch, &top, 50);
                    }
                }
                else if (temp == '.')
                {
                    a[j] = ch[top];
                    pop(ch, &top, 50);
                    j += 1;
                    push('.', ch, &top, 50);
                }
                else if (temp == '+')
                {
                    push('.', ch, &top, 50);
                }
            }
            break;
        case '+':
            if (top == -1)
            {
                push('+', ch, &top, 50);
            }
            else
            {
                char temp = ch[top];
                if (temp == '(')
                    push('+', ch, &top, 50);
                else if (temp == '*')
                {
                    a[j] = ch[top];
                    pop(ch, &top, 50);
                    j += 1;
                    push('+', ch, &top, 50);
                }
                else if (temp == '.')
                {
                    a[j] = ch[top];
                    j += 1;
                    pop(ch, &top, 50);
                    push('+', ch, &top, 50);
                }
            }
            break;
        case '*':
            if (top == -1)
            {
                push('*', ch, &top, 50);
            }
            else
            {
                char temp = ch[top];
                if (temp == '(' || temp == '.' || temp == '+')
                    push('*', ch, &top, 50);
                else
                {
                    a[j] = ch[top];
                    pop(ch, &top, 50);
                    j += 1;
                    push('*', ch, &top, 50);
                }
            }
            break;
        }
    }
    for (int i = 0; i < j; i++)
    {
        p[i] = a[i];
    }
    return j;
}

bool checkState(int matrizFechoLambida[][MAXCHAR], int state, int linha, int qtdStates) // conferindo se o estado ja foi colocado no fecho
{
    int j = 0;
    bool result = false;
    while (j < qtdStates)
    {
        if (matrizFechoLambida[linha][j] == state)
        {
            result = true;
            break;
        }
        j++;
    }
    return result;
}
void tableLamToAFN(int nfa_table[][MAXCHAR], int states, int qtdSymbols, int matrizFechoLambida[][MAXCHAR])
{
    int pilha[states]; // pilha
    int j = 1;
    int top = -1;
    int analise = 0;
    // todo mundo tem ele mesmo no fecho
    for (int p = 1; p < states; p++)
    {
        matrizFechoLambida[p][0] = p;
        matrizFechoLambida[p][1] = p;
    }

    j++;
    // printf("states: %d\n", states);
    for (int l = 1; l < states; l++)
    {
        for (int c = qtdSymbols + 1; c <= states; c++)
        {
            if (nfa_table[l][c] != -1 && nfa_table[l][c] != 0) // tem um estado e não é lixo
            {
                //  printf("colocou na pilha: %d\n", nfa_table[l][c]);
                pushInt(nfa_table[l][c], pilha, &top, states);
            }
        }
        //  printf("Da linha: %d\n", l);
        while (top != -1) // enquanto tem coisa na pilha
        {
            analise = pilha[top];
            popInt(pilha, &top, states);                             //tira da pilha
                                                                     //  printf("analise: %d\n", analise);
            if (!checkState(matrizFechoLambida, analise, l, states)) // nao ta la no fecho, acrescenta
            {
                matrizFechoLambida[l][j] = analise;
                j++;
                // analise percorre a tabela e todos que tem lamb coloca na pilha
                for (int q = qtdSymbols + 1; q <= states; q++)
                {
                    if (nfa_table[analise][q] != -1 && nfa_table[analise][q] != 0) // tem um estado e não é lixo
                    {
                        pushInt(nfa_table[analise][q], pilha, &top, states); // poe na pilha
                    }
                }
            }
        }
        while (j < states)
        {
            matrizFechoLambida[l][j] = -1; // coloca vazio no restante
            j++;
        }
        j = 2; // volta pro inicio
    }
}

void printTableFecho(int matrizFechoLambida[][MAXCHAR], int states)
{
    for (int x = 1; x < states; x++)
    {
        for (int y = 0; y < states; y++)
        {
            printf("%d     ", matrizFechoLambida[x][y]);
        }
        printf("\n");
    }
}

AF *matrizFechoToAFN(int matrizFechoLambida[][MAXCHAR], int nfa_table[][MAXCHAR], int states, int qtdSymbols, char *symbols)
{
    char templ[200], inde[100];
    int cont = 0;
    lEdge *EdgeList = NULL;        /// Lista de edges que sera atribuida ao automato
    lEdge *nEdge = newEdge();      /// Elemento para a lista de Edges
    lStates *StateList = NULL;     /// Lista de estados que sera atribuida ao automato
    lStates *nState = newState();  /// Elemento para a Lista de estados
    lAlphab *AlphaList = NULL;     /// Lista do simbolos que sera atribuida ao automato(Alfabeto do Automato)
    lAlphab *nAlpha = newAlphab(); /// Elemento para a Lista de Simbolos
    AF *AFN = newAF();             /// Automato
    char str[2] = "\0";            /* gives {\0, \0} */
    char aux[10];                  /* gives {\0, \0} */
    //system("cls");
    int colFecho = 1, colFecho2 = 1, newFecho = 0, estadoDoFecho, estadoDoFecho2;
    for (int state = 1; state < states; state++)
    {
        for (int symbol = 1; symbol <= qtdSymbols; symbol++)
        {
            estadoDoFecho = matrizFechoLambida[state][colFecho];
            //printf("\nEstado fecho: %d\n", matrizFechoLambida[state][colFecho]);
            while (matrizFechoLambida[state][colFecho] != -1)
            {
                estadoDoFecho2 = nfa_table[matrizFechoLambida[state][colFecho]][symbol];
                // tem transicao desse estado com esse simbolo?
                if (estadoDoFecho2 != -1)
                {
                    // se sim pega o for no fecho dessa transicao e vai criando edge
                    while (matrizFechoLambida[estadoDoFecho2][colFecho2] != -1)
                    {
                        newFecho = matrizFechoLambida[estadoDoFecho2][colFecho2];
                        str[0] = symbols[symbol - 1]; // transformar em string
                        strcpy(nEdge->input, str);
                        sprintf(aux, "q%d", state);
                        strcpy(nEdge->from, aux);
                        sprintf(aux, "q%d", newFecho);
                        strcpy(nEdge->to, aux);
                        putEdge(&EdgeList, nEdge);
                        nEdge = newEdge();
                        colFecho2++;
                    }
                    colFecho2 = 1;
                }

                colFecho++;
            }
            colFecho = 1;
        }
    }

    // ESTADOS

    for (int i = 1; i < states; i++)
    {
        sprintf(aux, "q%d", i);
        strcpy(nState->name, aux);
        nState->id = i;
        putState(&StateList, nState);
        nState = newState();
    }

    // ESTADO INICIAL
    sprintf(aux, "q%d", init[a - 1]);
    AFN->Start = findState(StateList, aux, 1);

    // ESTADO FINAL
    // intersecao do fecho lambida do estado inicial com os estados finais
    // se diferente vazio o inicial final

    for (int p = 0; p < b; p++)
    {
        sprintf(aux, "q%d", fin[p]);
        findState(StateList, aux, 0);
    }

    for (int i = 1; i < states; i++)
    {
        for (int p = 0; p < b; p++)
        {
            if (matrizFechoLambida[init[a - 1]][i] == fin[p])
            {
                sprintf(aux, "q%d", init[a - 1]);
                findState(StateList, aux, 0);
                i = states;
                p = b;
            }
        }
    }

    // ALFABETOS

    for (int i = 0; i < qtdSymbols; i++)
    {
        str[0] = symbols[i]; // transformar em string
        strcpy(nAlpha->simbolo, str);
        putAlphab(&AlphaList, nAlpha);
        nAlpha = newAlphab();
    }

    AFN->Alpha = AlphaList;
    AFN->States = StateList;
    AFN->Transations = EdgeList;
    //  printf("\nTRANSFORMAÇAO FEITA COM SUCESSO AFN TABLE -> AFN.\n\n");

    // printf("\nALFABETO: %p", AFN->Alpha);
    // printf("\nSTART: %s", AFN->Start->name);
    // printf("\nESTADOS: %s", AFN->States);
    // printf("\nEDges: %p", AFN->Transations);
    return (AFN);
}

void validateSentence(AF *AFD)
{
    char templ[MAXCHAR];
    int num;
    int result;
    int l;
    fflush(stdin);
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("\nERRO! Impossivel ler arquivo.\n");
        getchar();
        exit(42);
    }
    while (!feof(fp))
    {
        //result = fgets(templ, 100, fp);
        result = fscanf(fp, "%s\n", &templ);
        if (strcmp(templ, "-") == 0)
        {
            strcpy(templ, "");
        }
        if (result)
        {
            if (strcmp(templ, "") == 0)
            {
                printf("Sentenca lambida: ");
            }
            else
            {
                printf("Sentenca %s: ", templ);
            }
            readSentece(AFD, templ);
            printf("\n");
        }
    };
    fclose(fp);
}

int main()
{
    AF *AFN, *AFD;
    char exp[MAXCHAR], newExp[MAXCHAR], newPost[MAXCHAR];
    char aqr[MAXCHAR], symbols[MAXCHAR];
    int op, qtdSymbols = 0, i, j, sizeExp = 0;
    int init[50], fin[50], tamPost;
    int nfa_table[1000][MAXCHAR];
    int states = 0;

    fflush(stdin);
    readExpression("exp.jff", exp);
    printf("\nEXPRESSAO ORIGINAL: %s\n", exp);
    for (i = 0; i < strlen(exp); i++)
    {
        if (isSymbolValid(exp[i]) && !checkIfIsInArray(exp[i], symbols, qtdSymbols))
        {
            symbols[qtdSymbols] = exp[i];
            qtdSymbols++;
        }
    }
    printf("\n\nSIMBOLOS: ");
    for (j = 0; j < qtdSymbols; j++)
    {
        printf("%c ", symbols[j]);
    }
    printf("\n");
    //initialize table

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < qtdSymbols * 2 + 1; j++)
        {
            nfa_table[i][j] = -1;
        }
    }
    fflush(stdin);
    sizeExp = preprocessor(exp, newExp);
    printf("\nEXPRESSAO: ");

    for (j = 0; j < sizeExp; j++)
    {
        printf("%c", newExp[j]);
    }
    printf("\n");

    tamPost = postfix(newExp, sizeExp, qtdSymbols, symbols, newPost);

    //printf("\nTam Post: %d\n", tamPost);
    //printf("\nExpressão Post: %s\n", newPost);

    states = reg_nfa(newPost, nfa_table, qtdSymbols, symbols, tamPost);
    //print_nfa_table(nfa_table, states, qtdSymbols, symbols);
    printf("\n\nFEZ AFN LAMBIDA!!\n\n");
    int matrizFechoLambida[states + 1][MAXCHAR];
    tableLamToAFN(nfa_table, states, qtdSymbols, matrizFechoLambida);
    //printTableFecho(matrizFechoLambida, states);

    AFN = matrizFechoToAFN(matrizFechoLambida, nfa_table, states, qtdSymbols, symbols);
    printf("\n\nFEZ AFN LAMBIDA -> AFN !!\n\n");
    // AFN->print();
    AFD = NFAtoDFA(AFN);
    //  AFD->print();
    printf("\n\nFEZ AFN -> AFD!!\n\n");
    saveJflap(AFD, "AFD_GERADO.jff");
    printf("\n\nGEROU ARQUIVO AFD!!\n\n");
    validateSentence(AFD);

    free(AFN);
    free(AFD);
    return 0;
}
