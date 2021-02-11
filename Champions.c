#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dos.h>

/*UEFA CHAMPIONS LEAGUE
Queremos realizar el sorteo de la UEFA CHAMPIONS LEAGUE , para ello queremos incluir a 32 equipos de diferentes ligas europeas, pero con condiciones:
- No se enfrentaran entre equipos del mismo país
- De España:        4 equipos
- De Inglaterra:    4 equipos
- De Italia:        4 equipos
- De Alemania:      3 equipos
- De Francia:       3 equipos
- De Portugal:      2 equipos
- De Turquía:       2 equipos
- De Rusia:         2 equipos 
- 9 del resto de Europa (Escocia,Grecia,Rumania,Paises Bajos,Hungría,Eslovaquia ...) (1 de cada país)

- El campeón de la pasada EUROPA LEAGUE (una competicion aparte pero que te asegura participar en este torneo) con su pais correspondiente (Este equipo podrá ser el mismo de los añadidos anteriormente, por lo que habrá que ver si ocupa o no una plaza de más ) de no ocupar plaza , la restante viene de Resto de Europa

- Hay que separar los equipos en 4 bombos con sus respectivas caracteristicas (Cada equipo de un bombo irá a un grupo diferente)
- En el 1º bombo los campeones de sus respectivas ligas (Las 7 ligas principales) y el ganador de la Europa League ,(si es repetido se pasa a la siguiente liga)
- En el 2º bombo 2 de España , 2 de Inglaterra , 2 de Alemania y 1 de Francia e Italia
- En el 3º bombo 2 de Italia, 1 de Alemania,España,Inglaterra,Francia,Portugal,Rusia
- En el cuarto bombo 
*/

typedef struct eq
{
    char    nombre [50];
    char    *pais;
    int     N_pais;
    int     posicionLiga;
    int     EL;
    int     asignado;
}Champions;

typedef struct
{
    struct  eq equipo[8];
    int     contador;
}bombos;

typedef struct
{
    struct  eq equipo[4]; 
    int     contador;
}cocos;    //Del 65 al 72 que son de la A a la H poniendo %c

Champions equipo[32];
bombos bombo[4];
cocos grupo[8];

void recuento(int clubes,Champions equipo[32]);
void verificacion(int clubes);
void cambiar(int clubes, int CL);
void asignacion(int clubes,Champions equipo[32], bombos bombo[4]);
void sorteo(int clubes,Champions equipo[32],bombos bombo[8],cocos grupo[8]);

int main()
{
    int clubes = 32;

    printf("------BIENVENIDOS AL SORTEO DE LA CHAMPIONS-------\n\n");
    
    recuento(clubes,equipo);
    verificacion(clubes);
    asignacion(clubes,equipo,bombo);
    sorteo(clubes,equipo,bombo,grupo);

    printf("\n\nGracias y hasta la proxima\n\n");

    return 0;
}


void recuento(int clubes,Champions equipo[32])
{ 

    int i,j,choice,otr;
    char *paises []= {"Spain","England","Italy","Germany","France","Portugal","Russia","Turkey","Otro "};
    char *otros[] = {"Austria","Belgica","Bosnia","Chipre","Croacia","Dinamarca","Escocia","Grecia","Holanda","Hungria","Israel","Noruega","Polonia","Rumania","Serbia","Suecia","Suiza","Ucrania"};
    int contador[]= {4,4,4,3,3,2,2,2,7};  //numero de equipos de cada pais
    int N_otros[18];
    char aux[50];

    for(i=0; i<18; i++)
    {
        N_otros[i]=0;
    }

    for (i = 0; i < clubes; i++)
    {
        equipo[i].EL = 0;

        if(i==0)
        {
            printf("Primero pondremos al campeon de la pasada Europa League\n");
            equipo[i].EL = 1;
        }

        printf("Nombre del equipo %d de %d: ",i+1,clubes);
        scanf("%s",equipo[i].nombre);

        for (j = 0; j < 9; j++)
        {
            if (contador[j]>0)
            {
                printf("\n%d. %s\t(%d)",j+1,paises[j],contador[j]);
            }
        }
        printf("\nNumero de pais: ");
        scanf("%d",&choice);
        equipo[i].N_pais = choice;

        if(choice < 9)
        {
            equipo[i].pais = paises[choice-1];

            printf("Posicion en su liga: ");
            scanf("%i",&equipo[i].posicionLiga);
        }
        else if (choice == 9)
        {
            for (j = 0; j < 18; j++)
            {
                if (N_otros[j] ==0)
                {
                    printf("%d. %s\t\t",j+1,otros[j]);
                    if(j%6 ==5)
                    {
                        printf("\n");
                    }
                } 
            }
            printf("\nPais concreto: ");
            scanf("%d",&otr);
            equipo[i].pais = otros[otr-1];
            N_otros[otr-1]=1;
            equipo[i].posicionLiga = 1;
        }
        if(i>0)
        {
            contador[choice-1]--;   //Da igual el pais del primer equipo 
        }
        printf("\n");
    }
}

void verificacion(int clubes)
{
    int i,choice,malo;
    printf("\nEquipos introducidos:\n");
    for(i=0; i< clubes; i++)
    {
        printf("\n- %d: %s , %d de %s",i+1,equipo[i].nombre,equipo[i].posicionLiga,equipo[i].pais);
    }

    printf("\n\nEs correcto?\n1. Si\n2.No\n");
    scanf("%d",&choice);

    if(choice !=1)
    {
        printf("Numero del que desea modificar: ");
        scanf("%d",&malo);
        cambiar(clubes,malo-1); //Una funcion para cambiar parametros
    }
}

void cambiar(int clubes, int CL)
{
    int j,choice;
    char *paises []= {"Spain","England","Italy","Germany","France","Portugal","Turkey","Russia","Otro "};
    char aux[50];

    printf("\n1.Nombre\n2.Posicion\n3.Pais\n Que desea modificar de %s?: ",equipo[CL].nombre);
    scanf("%d",&choice);
    if(choice ==1)
    {
        printf("Nuevo nombre: ");
        scanf("%s",equipo[CL].nombre);
    }
    else if(choice == 2)
    {
        printf("Nueva posicion: ");
        scanf("%d",&equipo[CL].posicionLiga);
    }
    else if(choice ==3)
    {
        for (j = 0; j < 9; j++)
        {
            printf("\n%d. %s",j+1,paises[j]);
        }
        printf("\nNumero de pais: ");
        scanf("%d",&choice);
        equipo[CL].N_pais = choice;

        if(choice < 9)
        {
            equipo[CL].pais = paises[choice-1];
        }
        else if (choice == 9)
        {
            printf("Pais concreto: ");
            scanf("%s",aux);
            equipo[CL].pais = aux;
        }
    }
    else
    {
        printf("Error");
        cambiar(clubes,CL);
    }
    printf("\n- %s , %d de %s",equipo[CL].nombre,equipo[CL].posicionLiga,equipo[CL].pais);
    printf("\n Es correcto?\n1. Si\n2. No\n");
    scanf("%d",&choice);
    if(choice !=1)
    {
        cambiar(clubes,CL);
    }
    else if(choice ==1)
    {
        verificacion(clubes);
    }
}

void asignacion(int clubes,Champions equipo[32], bombos bombo[4])
{
    int i,j,aux=8;
    
    if((equipo[0].N_pais < 8) && (equipo[0].posicionLiga == 1))
    {
        aux++;
    }
    for (i = 0; i < 4; i++)
    {
        bombo[i].contador =0;
    }
    
    for(i=0; i<clubes; i++)
    {

        if(((equipo[i].posicionLiga == 1 && equipo[i].N_pais < aux) || (equipo[i].EL ==1)) && (bombo[0].contador < 8))
        {
            j=0;
            bombo[j].equipo[bombo[j].contador] = equipo[i];
            bombo[j].contador ++;
        }
        else if (((equipo[i].N_pais < 6 && equipo[i].posicionLiga == 2) || (equipo[i].N_pais < 4 && equipo[i].posicionLiga == 3)) && (bombo[1].contador < 8))
        {
            j=1;
            bombo[j].equipo[bombo[j].contador] = equipo[i];
            bombo[j].contador ++;
        }
        else if ((equipo[i].N_pais > 8 && bombo[3].contador < 8) || (equipo[i].N_pais == 8 && equipo[i].posicionLiga >1))
        {
            j=3;
            bombo[j].equipo[bombo[j].contador] = equipo[i];
            bombo[j].contador ++;
        }
        else if (((equipo[i].N_pais < 4 && equipo[i].posicionLiga > 3) || (equipo[i].N_pais < 6 && equipo[i].posicionLiga > 2) || (equipo[i].N_pais < 8 && equipo[i].posicionLiga > 1) ||  equipo[i].N_pais == 8) && (bombo[2].contador < 8))
        {
            j=2;
            bombo[j].equipo[bombo[j].contador] = equipo[i];
            bombo[j].contador ++;
        }
    }

    for(j=0; j<4; j++)
    {
        printf("\nBombo %d:\n",j+1);
        for(i=0; i<bombo[j].contador; i++)
        {
            sleep(1);
            printf("- %s\t(%s)\n",bombo[j].equipo[i].nombre,bombo[j].equipo[i].pais);
        }
        printf("\n");
        sleep(1);
    }
}

void sorteo(int clubes,Champions equipo[32],bombos bombo[8],cocos grupo[8])
{
    int i,j,k,l,asignado;

    sleep(1);
    printf("\n\n--Hora de asignar los grupos--\n\n");

    for (k = 0; k < 8; k++)
    {
        for (l = 0; l < 4; l++)
        {
            grupo[k].equipo[l].N_pais = 0;  //Poner todos los grupos a 0
        }               
    }

    for(i=0; i<4; i++)  //Cada bombo
    {
        int aux[] = {0,0,0,0,0,0,0,0};
        int orden[8],num;
        sleep(2);
        printf("\n\n\t---Bombo %d---\n",i+1);

        for(j=0; j<8; j++)  //Cada equipo
        {
            sleep(2);
            printf("\nTurno de: %s ",bombo[i].equipo[j].nombre);
            for (k = 0; k < 3; k++)
            {
                sleep(1);
                printf(".");
            }
            
            bombo[i].equipo[j].asignado = 0;

            for (k = 0; k < 8; k++)//Para establecer un orden de grupos aletorio sin repetición 
            {
                num = rand() % 8;
                if (k>0)
                {
                    for (l = 0; l < k; l++)
                    {
                        if (num == orden[l])
                        {
                            num = rand() % 8 ;
                            l = -1;
                        }
                    }
                }
                orden[k] = num;    
            }

            for(k=0; k<8; k++)  //Cada grupo
            {
                for(l=0;l<4;l++)    //Los cuatro espacios del grupo
                {
                    if(bombo[i].equipo[j].pais == grupo[orden[k]].equipo[l].pais)
                    {
                        aux[orden[k]]=2;   //Ese equipo no puede ir a ese grupo.
                    }
                }
                if((aux[orden[k]]==0 && grupo[orden[k]].equipo[i].N_pais == 0) && bombo[i].equipo[j].asignado == 0)    //'i' en lugar de 'l' porque cada uno de un bombo ocupa ese lugar en su grupo 
                {
                    grupo[orden[k]].equipo[i] = bombo[i].equipo[j];

                    bombo[i].equipo[j].asignado = 1;
                    aux[orden[k]]=1;
                    sleep(1);
                    printf("\t grupo %c",orden[k]+65);
                }
            }
            for(l=0;l<8;l++)
            {
                if(aux[l]==2)
                {
                    aux[l]=0;
                }
            }
        }
    }

    sleep(2);
    printf("\n\nPor lo tanto, los grupos son:\n");

    for(i=0; i< 8 ; i++)
    {
        sleep(2);
        printf("\nGrupo %c:\n",i+65);
        for(j=0; j<4; j++)
        {
            sleep(1);
            printf("- %s\t(%s)\n",grupo[i].equipo[j].nombre,grupo[i].equipo[j].pais);
        }
    }
}