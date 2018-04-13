/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: coldisk
 *
 * Created on 10 mars 2018, 23:52
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

int lire(char *chaine, int longueur);
typedef struct dirent dirent;
void parcours(char *dir_name);
int isDir(const char* name);
char* pathTo_jdn_cfg = "/home/coldisk/Documents/langC/jfo_projet/NewFolder/jordonn/jdn.jcg";

int main(int argc, char* argv[])
{
    char dossierDonne[255]; // ISN'T THE DIRECTORY!!!!!!!
    printf("Veuillez donner un dossier à lister: \n");
    lire(dossierDonne, 255);
    printf("Le dossier donné est %s \n", dossierDonne);
    parcours(dossierDonne);
    addDirec("test");

    return 0;
}

int lire(char *chaine, int longueur)
{
    char *positionEntree = NULL;
 
    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

void parcours(char *dir_name)
{
    printf("in parcours \n");
    printf("%d\n", strlen(dir_name));
    DIR *useDir = opendir(dir_name); //IT'S THE DIRECTORY!!!!!!
    dirent *currentCouple = NULL;
    int pathLen = 0;
    char* path = NULL;

    while ((currentCouple = readdir(useDir)) != NULL)
    {
        pathLen = strlen(dir_name) + strlen(currentCouple->d_name) + 1;
        path=malloc(pathLen * sizeof(char)); //path construction
        
        if (path !=NULL)
        {
            sprintf(path,"%s%s",dir_name,currentCouple->d_name);
            printf("%d \n", pathLen);
            printf("%s \n", path);
            printf("l'élément lu est : %s %s\n", currentCouple->d_name, ((isDir(path) == 0) ? "-->F" : "-->D"));  
            free(path);
        }
    }

    closedir(useDir);
}

int isDir(const char* name)
{
    struct stat path_stat;
    stat(name, &path_stat);
    
    return S_ISDIR(path_stat.st_mode);
}

void addDirec(char* nameNewDir)
{
    FILE* jdn_cfg= NULL; 
    jdn_cfg = fopen(pathTo_jdn_cfg, "a");
    fprintf(jdn_cfg,"[%s]\n[/%s]\n", nameNewDir, nameNewDir);
    fclose(jdn_cfg);
    
}


/*
int main()
{
    float *ptr1 = NULL, *ptr2 = NULL;
    int i, n = 5, termination = 1;
    
    ptr1 = calloc(n, sizeof(float)); /* On alloue de la mémoire avec calloc() pour ptr1. 
    if (ptr1 == NULL) 
        printf("Echec de calloc().\n");
    else {
        ptr2 = malloc(n * sizeof(float));/* On alloue de la mémoire avec malloc() pour ptr2. 
        if (ptr2 == NULL)
            printf("Echec de malloc().\n");
        else {
            printf("Allocation de memoire avec\n");
            printf("calloc() pour ptr1\n");
            printf("malloc() pour ptr2.\n\n");
            for (i=0; i<n; i++)
                printf("ptr1[%d]=%f, ptr2[%d]=%f\n", i, ptr1[i], i, ptr2[i]);
            /* On affiche la valeur de chacune des cases des pointeurs. 
            printf("\n");
            free(ptr2);
            termination = 0;
        }
        free(ptr1);
    }
    
    return termination;
}*/