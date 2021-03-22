#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct aluno
{
    char semestre[30];
    char nome[60];
    char codigo[60];
    char CPF[15];
    char disc[30];
    char aux[30];
};

struct disciplina
{
    char semestre[30];
    char nome[60];
    char codigo[20];
    char prof[20];
    char creditos[5];
    char aluno[30];
    char aux[30];
} ;

struct auxiliar
{
    char linha[100];
    char aux[30];
    char aux1[30];
    char aux2[30];
    char aux3[30];
    char aux4[30];
};

struct alunodisciplina
{
    char cod_aluno[20];
    char cod_disc[20];
    char codigo[20];
} ;


void aluno_novo()
{
    struct aluno *al;
    al=(struct aluno*)malloc(sizeof(struct aluno));
    FILE *pont1;
    printf("Periodo em que o aluno esta matriculado: ");
    gets(al->semestre);
    for(int i=0; i<=strlen(al->semestre); i++)
        al->aux[i]=al->semestre[i];
    pont1=fopen(strcat(al->semestre,"_alunos.txt"),"a");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo.\n");
    printf("Codigo do aluno: ");
    gets(al->codigo);
    fprintf(pont1, "%s\n", al->codigo);
    pont1=fopen(strcat(al->codigo,".txt"),"a");
    printf("Nome do aluno: ");
    gets(al->nome);
    fprintf(pont1, "%s\n", al->nome);
    printf("CPF do aluno: ");
    gets(al->CPF);
    fprintf(pont1, "%s\n", al->CPF);
    for(int i=0; i<=strlen(al->aux); i++)
        al->semestre[i]=al->aux[i];
    fprintf(pont1, "%s\n", al->semestre);
    fclose(pont1);
    free(al);
};

void disciplina_nova()
{
    struct disciplina *disc;
    disc=(struct disciplina*)malloc(sizeof(struct disciplina));
    FILE *pont1;
    printf("Periodo em que a disciplina eh ministrada: ");
    gets(disc->semestre);
    for(int i=0; i<=strlen(disc->semestre); i++)
        disc->aux[i]=disc->semestre[i];
    pont1=fopen(strcat(disc->semestre,"_disciplinas.txt"),"a");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo do semestre_disciplinas.\n");
    printf("Codigo da disciplina: ");
    gets(disc->codigo);
    fprintf(pont1, "%s\n", disc->codigo);
    pont1=fopen(strcat(disc->codigo,".txt"),"a");
    printf("Nome da disciplina: ");
    gets(disc->nome);
    fprintf(pont1, "%s\n", disc->nome);
    printf("Professor da disciplina: ");
    gets(disc->prof);
    fprintf(pont1, "%s\n", disc->prof);
    printf("Quantidade de creditos da disciplina: ");
    gets(disc->creditos);
    fprintf(pont1, "%s\n", disc->creditos);
    for(int i=0; i<=strlen(disc->aux); i++)
        disc->semestre[i]=disc->aux[i];
    fprintf(pont1, "%s\n", disc->semestre);
    fclose(pont1);
    free(disc);
};

void aluno_disciplina()
{
    struct alunodisciplina *ad;
    ad=(struct alunodisciplina*)malloc(sizeof(struct alunodisciplina));
    FILE *pont1;
    char *pont;
    printf("Codigo do aluno: ");
    gets(ad->cod_aluno);
    printf("Codigo da disciplina: ");
    gets(ad->cod_disc);
    for(int i=0; i<=strlen(ad->cod_aluno);i++)
        ad->codigo[i]=ad->cod_aluno[i];
    pont1=fopen(strcat(ad->cod_aluno,".txt"),"a");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo.\n");
    for(int i=0; i<=strlen(ad->codigo);i++)
        ad->cod_aluno[i]=ad->codigo[i];
    fprintf(pont1, "%s\n", ad->cod_disc);
    fclose(pont1);
    pont1=fopen(strcat(ad->cod_disc, ".txt"), "a");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo.\n");
    fprintf(pont1, "%s\n", ad->cod_aluno);
    fclose(pont1);
    free(ad);
};

void consulta_aluno()
{
    struct aluno *al;
    al=(struct aluno*)malloc(sizeof(struct aluno));
    FILE* pont1;
    char *pont;
    printf("Digite o codigo do aluno que deseja consultar: ");
    gets(al->codigo);
    pont1 = fopen(strcat(al->codigo,".txt"),"r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo.\n");
    else
    {
        fgets(al->nome,sizeof(al->nome),pont1);
        printf("Nome: %s", al->nome);
        fgets(al->CPF,sizeof(al->CPF),pont1);
        printf("CPF: %s", al->CPF);
        fgets(al->semestre,sizeof(al->semestre),pont1);
        printf("Semestre: %s", al->semestre);
        printf("Disciplinas cursadas:\n");
        strcpy(al->aux, " ");
        strcpy(al->disc, " ");
        while(!feof(pont1))
        {
            fgets(al->disc, sizeof(al->disc), pont1);
            if(strcmp(al->aux, al->disc)==0)
                break;
            printf("%s", al->disc);
            strcpy(al->aux, al->disc);
        }
    }
    fclose(pont1);
    free(al);
};

void consulta_disciplina()
{
    struct disciplina *disc;
    disc=(struct disciplina*)malloc(sizeof(struct disciplina));
    FILE* pont1;
    char *pont;
    printf("Digite o codigo da disciplina que deseja consultar: ");
    gets(disc->codigo);
    pont1 = fopen(strcat(disc->codigo,".txt"),"r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo.\n");
    else
    {
        fgets(disc->nome,sizeof(disc->nome),pont1);
        printf("Nome: %s", disc->nome);
        fgets(disc->prof,sizeof(disc->prof),pont1);
        printf("Professor: %s", disc->prof);
        fgets(disc->creditos, sizeof(disc->creditos), pont1);
        printf("Quantidade de creditos: %s", disc->creditos);
        fgets(disc->semestre, sizeof(disc->semestre), pont1);
        printf("Semestre: %s", disc->semestre);
        printf("Alunos matriculados:\n");
        strcpy(disc->aux, " ");
        strcpy(disc->aluno, " ");
        while(!feof(pont1))
        {
            fgets(disc->aluno, sizeof(disc->aluno), pont1);
            if(strcmp(disc->aux, disc->aluno)==0)
                break;
            printf("%s", disc->aluno);
            strcpy(disc->aux, disc->aluno);
        }
    }
    fclose(pont1);
    free(disc);
};

void remove_aluno()
{
    struct aluno *al;
    struct auxiliar *help;
    al=(struct aluno*)malloc(sizeof(struct aluno));
    help=(struct auxiliar*)malloc(sizeof(struct auxiliar));
    FILE *pont1, *pont2, *pont3;
    char *result;
    printf("Codigo do aluno: ");
    gets(al->codigo);
    strcpy(help->aux1, al->codigo);
    strcat(help->aux1,"\n");
    pont1=fopen(strcat(al->codigo, ".txt"), "r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo do aluno.\n");

    fgets(al->nome,sizeof(al->nome),pont1);
    fgets(al->CPF,sizeof(al->CPF),pont1);
    fgets(al->semestre,sizeof(al->semestre),pont1);

    strcpy(help->aux2, " ");
    strcpy(al->disc, " ");
    while(!feof(pont1))
    {
        fgets(al->disc, sizeof(al->disc), pont1);
        if(strcmp(al->disc, help->aux2)==0 || strcmp(al->disc, " ")==0)
            break;
        al->disc[strlen(al->disc)-1]='\0';
        pont2=fopen(strcat(al->disc, ".txt"), "r");
        strcpy(help->aux2, al->disc);
        if(pont2==NULL)
            printf("Erro na abertura do arquivo da disciplina.\n");
        else
        {
            pont3=fopen("copiadisc.txt", "a");
            if(pont3==NULL)
                printf("Erro na abertura do arquivo copia.\n");

            strcpy(help->aux3, " ");
            strcpy(help->linha, " ");
            while(!feof(pont2))
            {
                fgets(help->linha, 100, pont2);
                if(strcmp(help->linha,help->aux1)!=0 && strcmp(help->aux3, help->linha)!=0)
                {
                    fprintf(pont3, "%s", help->linha);
                    strcpy(help->aux3, help->linha);
                }
            }
            fclose(pont2);
            fclose(pont3);
            remove(al->disc);
            rename("copiadisc.txt", al->disc);
        }
    }
    fclose(pont1);

    for(int i=0; i<(strlen(al->semestre)-1); i++)
        help->aux[i]=al->semestre[i];
    help->aux[strlen(al->semestre)-1]='\0';
    pont1=fopen(strcat(help->aux,"_alunos.txt"),"r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo do semestre_alunos.\n");

    pont2=fopen("copia.txt", "a");
    if(pont2==NULL)
        printf("Erro na criacao do arquivo copia.\n");

    strcpy(help->aux4, " ");
    strcpy(help->linha, " ");
    while(!feof(pont1))
    {
        result=fgets(help->linha, 100, pont1);
        if(result)
        {
            if(strcmp(help->linha, help->aux1)!=0 && strcmp(help->aux4, help->linha)!=0)
            {
                fprintf(pont2, "%s", help->linha);
                strcpy(help->aux4, help->linha);
            }
        }
    }
    fclose(pont1);
    fclose(pont2);
    remove(help->aux);
    rename("copia.txt", help->aux);
    remove(al->codigo);
    free(al);
    free(help);
};

void remove_disciplina()
{
    struct disciplina *disc;
    struct auxiliar *help;
    disc=(struct disciplina*)malloc(sizeof(struct disciplina));
    help=(struct auxiliar*)malloc(sizeof(struct auxiliar));
    FILE *pont1, *pont2, *pont3;
    char disciplina[60];
    char *result;
    printf("Codigo da disciplina: ");
    gets(disciplina);
    strcpy(help->aux1, disciplina);
    strcat(help->aux1,"\n");
    pont1=fopen(strcat(disciplina, ".txt"), "r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo da disciplina.\n");

    fgets(disc->nome,sizeof(disc->nome),pont1);
    fgets(disc->prof,sizeof(disc->prof),pont1);
    fgets(disc->creditos,sizeof(disc->creditos),pont1);
    fgets(disc->semestre,sizeof(disc->semestre),pont1);

    strcpy(help->aux2, " ");
    strcpy(disc->codigo, " ");
    while(!feof(pont1))
    {
        fgets(disc->codigo, sizeof(disc->codigo), pont1);
        if(strcmp(disc->codigo, help->aux2)==0 || strcmp(disc->codigo, " ")==0)
            break;

        disc->codigo[strlen(disc->codigo)-1]='\0';
        pont2=fopen(strcat(disc->codigo, ".txt"), "r");
        strcpy(help->aux2, disc->codigo);
        if(pont2==NULL)
            printf("Erro na abertura do arquivo do aluno %s.\n", disc->codigo);
        else
        {
            pont3=fopen("copiadisc.txt", "a");
            if(pont3==NULL)
                printf("Erro na abertura do arquivo copia.\n");

            strcpy(help->aux3, " ");
            strcpy(help->linha, " ");
            while(!feof(pont2))
            {
                fgets(help->linha, 100, pont2);
                if(strcmp(help->linha,help->aux1)!=0 && strcmp(help->aux3, help->linha)!=0)
                {
                    fprintf(pont3, "%s", help->linha);
                    strcpy(help->aux3, help->linha);
                }
            }
            fclose(pont2);
            fclose(pont3);
            remove(disc->codigo);
            rename("copiadisc.txt", disc->codigo);
        }
    }
    fclose(pont1);

    for(int i=0; i<(strlen(disc->semestre)-1); i++)
        help->aux[i]=disc->semestre[i];
    help->aux[strlen(disc->semestre)-1]='\0';
    pont1=fopen(strcat(help->aux,"_disciplinas.txt"),"r");
    if(pont1==NULL)
        printf("Erro na abertura do arquivo do semestre_disciplinas.\n");

    pont2=fopen("copia.txt", "a");
    if(pont2==NULL)
        printf("Erro na criacao do arquivo copia.\n");
    while(!feof(pont1))
    {
        result=fgets(help->linha, 100, pont1);
        if(result)
        {
            if(strcmp(help->linha, help->aux1)!=0)
                fprintf(pont2, "%s", help->linha);
        }
    }
    fclose(pont1);
    fclose(pont2);
    remove(help->aux);
    rename("copia.txt", help->aux);
    remove(disciplina);
    free(disc);
    free(help);
};

int main()
{
    int n;
    char c;
    while(n!=8){
        printf("\nDigite:\n(1) para inserir um aluno novo\n(2) para inserir uma disciplina nova\n(3) para inserir um aluno em uma disciplina\n(4) para consultar um aluno\n(5) para consultar uma disciplina\n(6) para remover um aluno\n(7) para remover uma disciplina\n(8) para fechar o programa\n");
        scanf("%d%c", &n, &c);
        switch(n)
        {
            case 1:
                aluno_novo();
                break;
            case 2:
                disciplina_nova();
                break;
            case 3:
                aluno_disciplina();
                break;
            case 4:
                consulta_aluno();
                break;
            case 5:
                consulta_disciplina();
                break;
            case 6:
                remove_aluno();
                break;
            case 7:
                remove_disciplina();
                break;
            case 8:
                break;
            default:
                printf("Numero invalido:\n");
                break;
        }
    }
    return 0;
}
