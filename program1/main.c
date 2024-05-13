
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "leak_detector_c.h"

typedef struct monster {
    char *name;
    char *element;
    int population;
} monster;

typedef struct region {
    char *name;
    int nmonsters;
    int total_population;
    monster **monsters;
} region;

typedef struct itinerary {
    int nregions;
    region **regions;
    int captures;
} itinerary;

typedef struct trainer {
    char *name;
    itinerary *visits;
} trainer;

monster* makeMonster(char *name, char *element, int population);
monster** readMonsters(int *monsterCount);
region** readRegions(int *countRegions, monster** monsterList, int monsterCount);
trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions);
void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);

int main() {
    //atexit(report_mem_leak); //memory leak check

    int monsterCount;
    int countRegions;
    int trainerCount;

    monster ** monsterList = readMonsters(&monsterCount);

    region ** regionList = readRegions(&countRegions, monsterList, monsterCount);

    trainer * trainerList = loadTrainers(&trainerCount, regionList, countRegions);

    processInputs(monsterList, monsterCount, regionList, countRegions, trainerList, trainerCount);

    releaseMemory(monsterList, monsterCount, regionList, countRegions, trainerList, trainerCount);

    return 0;
}

monster * makeMonster(char *name, char *element, int population)
{
    monster * makeMonster_arr = malloc(sizeof(monster));

    makeMonster_arr->name = malloc(sizeof(char) * 51);
    makeMonster_arr->element = malloc(sizeof(char) * 51);

    strcpy(makeMonster_arr->name, name);
    strcpy(makeMonster_arr->element, element);

    if(population < 1000000)
        makeMonster_arr->population = population;
    else
        printf("Out of bounds!");

    return makeMonster_arr;
}

monster** readMonsters(int *monsterCount)
{
    char name[51], element[51], garbage[51];
    int population = 0;

    scanf("%d %s", monsterCount, garbage);

    monster ** monsterList = malloc(*monsterCount * sizeof(monster*));

    for(int i = 0; i < *monsterCount; i++)
    {
        scanf("%s", name);
        scanf("%s", element);
        scanf("%d", &population);

        monsterList[i] = makeMonster(name, element, population);
    }

    return monsterList;
}

region** readRegions(int *countRegions, monster** monsterList, int monsterCount)
{
    char regionName[51], monsterName[51], garbage[51];

    scanf("%d %s", countRegions, garbage);

    region ** regionList = malloc(*countRegions * sizeof(region*));

    for(int i = 0; i < *countRegions; i++)
    {
        regionList[i] = malloc(sizeof(region));

        scanf("%s", regionName);

        int nmonsters = 0;
        scanf("%d %s", &nmonsters, garbage);

        int length = (int) strlen(regionName) + 1;

        regionList[i]->name = malloc(sizeof(char) * (length));

        strcpy(regionList[i]->name, regionName);

        regionList[i]->nmonsters = nmonsters;

        int total_population = 0;

        regionList[i]->monsters = malloc(sizeof(monster*) * nmonsters);

        for(int i = 0; i < nmonsters; i++)
        {
            scanf("%s", monsterName);

            for(int j = 0; j < monsterCount; j++)
            {
                if(strcmp(monsterList[i]->name, regionName) == 0)
                {
                    regionList[i]->monsters[j] = monsterList[i];
                    total_population += monsterList[i]->population;
                    break;
                }
            }
        }
        regionList[i]->total_population = total_population;

    }

    return regionList;
}

trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions)
{

    char trainerName[51];
    char regionName[51];
    char garbage[51];

    scanf("%d %s", trainerCount, garbage);

    trainer * trainerList = malloc(*trainerCount * sizeof(trainer));

    for(int i = 0; i < *trainerCount; i++)
    {
        scanf("%s", trainerName);

        int length = (int) strlen(trainerName) + 1;

        trainerList[i].name = malloc(sizeof(char) * length);

        strcpy(trainerList[i].name, trainerName);

        itinerary* Visits = malloc(sizeof(itinerary));

        scanf("%d %s", &Visits->captures, garbage);
        scanf("%d %s", &Visits->nregions, garbage);

        int nregions = Visits->nregions;

        region** trainerRegions = malloc(sizeof(region*) * nregions);

        for(int i = 0; i < nregions; i++)
        {
            scanf("%s", regionName);

            for(int j = 0; j < countRegions; j++)
            {
                if(strcmp(regionList[i]->name, regionName) == 0)
                {
                    trainerRegions[i] = regionList[i];
                    break;
                }
            }
        }
        Visits->regions = trainerRegions;
        trainerList[i].visits = Visits;
    }

    return trainerList;
}

void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount)
{
    float monsterMR;
    float monsterCapture;
    int capture;

    for(int i = 0; i < trainerCount; i++)
    {
        printf("Trainer Names: %s\n", trainerList[i].name);

        for(int j = 0; j < regionCount; j++)
        {
            printf("%s\n", regionList[j]->name);

            monsterMR = regionList[j]->nmonsters / regionList[j]->total_population;

            for(int k = 0; k < trainerCount; k++)
            {
                capture = trainerList[k].visits->captures;
                monsterCapture = round(monsterMR * capture);

                for(int l = 0; l < monsterCount; l++)
                {
                    printf("%f#%s\n", monsterCapture, monsterList[l]->name);
                }
            }
        }
    }
}
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount)
{
    for(int i = 0; i < monsterCount; i++)
    {
        free(monsterList[i]->name);
        free(monsterList[i]->element);
        free(monsterList[i]);
    }
    for(int i = 0; i < regionCount; i++)
    {
        free(regionList[i]->name);

        for(int j = 0; j < monsterCount; j++)
        {
            free(regionList[i]->monsters[j]);
        }

        free(regionList[i]);
    }
    for(int i = 0; i < trainerCount; i++)
    {
        free(trainerList[i].name);

        for(int j = 0; j < trainerCount; j++)
        {
            free(trainerList[i].visits);
        }

        //????
        //free(trainerList[i]);
    }
    free(monsterList);
    free(regionList);
    free(trainerList);

}
