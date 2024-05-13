
/* COP 3502C Assignment 1 
This program is written by: Riya Sawant */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
//#include "leak_detector_c.h"
#define MAXstrLEN 51
#define MAXpop 1000000


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


//1.This function returns a dynamically allocated monster filled with the provided parameters
//2.returns an array of monster pointers where each monster pointer points to the dynamically allocated monsters with fill-up information from the provided inputs.
//3.This function returns an array of region pointers where each region pointer points to a dynamically allocated 
//region, filled up with the information from the inputs, and the region’s monsters member points to an 
//appropriate list of monsters from the monsterList passed to this function. 
//4.returns a dynamically allocated array of trainers, filled up with the information from the inputse, 
//and the trainer’s visits field points to a dynamically allocated itinerary which is filled based on the passed 
//regionList. This function also updates the passed variable reference pointed by trainerCount
//5.this function processes all the data and produce the output.
//6. memory release
monster* makeMonster(char *name, char *element, int population);
monster** readMonsters(int *monsterCount);
region** readRegions(int *countRegions, monster** monsterList, int monsterCount);
trainer* loadTrainers(int *trainerCount, region** regionList, int countRegions);
void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);
void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount);

int main() {
    //atexit(report_mem_leak); //memory leak check

    int monsterCount,countRegions,trainerCount;
  
    monster ** monsterList;
    monsterList = readMonsters(&monsterCount);
    
    region ** regionList;
    regionList = readRegions(&countRegions, monsterList, monsterCount);

    trainer * trainerList;
    trainerList = loadTrainers(&trainerCount, regionList, countRegions);

    processInputs(monsterList, monsterCount, regionList, countRegions, trainerList, trainerCount);

    releaseMemory(monsterList, monsterCount, regionList, countRegions, trainerList, trainerCount);

    return 0;
}

monster * makeMonster(char *name, char *element, int population)
{
    monster * makeMonster_arr;
    makeMonster_arr= malloc(sizeof(monster));
    makeMonster_arr->name = malloc(sizeof(char) * MAXstrLEN);
    makeMonster_arr->element = malloc(sizeof(char) * MAXstrLEN);

    strcpy(makeMonster_arr->name,name);
    strcpy(makeMonster_arr->element,element);

  
    if(population < MAXpop){
        makeMonster_arr->population = population;
    }
    
    else{
    
        printf("program error");}

    return makeMonster_arr;
}


monster** readMonsters(int *monsterCount)
{
    char name[MAXstrLEN],element[MAXstrLEN], name1[MAXstrLEN];
    
    int population = 0;

    scanf("%d %s", monsterCount,name1);

    monster ** monsterList; 
    monsterList= malloc(*monsterCount * sizeof(monster*));

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
    char regionName[MAXstrLEN], monsterName[MAXstrLEN], name1[MAXstrLEN];

    scanf("%d %s", countRegions, name1);

    region ** regionList; 
    regionList = malloc(*countRegions * sizeof(region*));
  
//--------------------------
    for(int i = 0; i < *countRegions; i++)
    {
        //DIFF
        //readRegions[i] = malloc(sizeof(region));
        //scan in name
        regionList[i] = malloc(sizeof(region));
        scanf("%s", regionName);

        int nmonsters = 0;
        scanf("%d %s", &nmonsters, name1);

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

    char trainerName[MAXstrLEN],regionName[MAXstrLEN],name1[MAXstrLEN];
    scanf("%d %s", trainerCount, name1);

    trainer * trainerList;
    trainerList = malloc(*trainerCount * sizeof(trainer));
    

    for(int i = 0; i < *trainerCount; i++)
    {
        scanf("%s", trainerName);

        int length = (int) strlen(trainerName) + 1;
        trainerList[i].name = malloc(sizeof(char) * length);
        strcpy(trainerList[i].name, trainerName);

        itinerary* visits;
        visits = malloc(sizeof(itinerary));

        scanf("%d %s", &visits->captures, name1);
        scanf("%d %s", &visits->nregions, name1);

        int nregions = visits->nregions;

        region** trainerRegions;
        trainerRegions = malloc(sizeof(region*) * nregions);

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
        visits->regions = trainerRegions;
        trainerList[i].visits = visits;
    }

    return trainerList;
}

void processInputs(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount)

{
  float monsterPr = 0;
    float monstercapture = 0;
    int capture = 0;
    //printf("TRAINERCOUNT = %d", trainerCount);

    for(int i = 0; i < trainerCount; i++)
    {
          printf("\n%s\n", trainerList[i].name);

        for(int j = 0; j < regionCount; j++)
        {
            printf("%s\n", regionList[j]->name);

            
            monsterPr = ((regionList[j]->nmonsters * 1.0)/(regionList[j]->total_population));
            
            //printf("regionList[j]->nmonsters = %d\nregionList[j]->total_population = %d\n", regionList[j]->nmonsters, regionList[j]->total_population);

            //for(int k = 0; k < trainerCount; k++)
            //{
                capture = trainerList[i].visits->captures;
                //printf("capture = %d\n", capture);

                //monstercapture = monsterPr * capture;
                monstercapture = (monsterPr * capture);
                //printf("before ceil monstercapture = %f\n", monstercapture);
                monstercapture = ceil(monstercapture);
                //printf("monstercapture = %f\n", monstercapture);

                
                
          
                for(int l = 0; l < trainerList[i].visits->captures; l++)
                {
                  //printf("trainerList[i].visits->captures = %d\n",   trainerList[i].visits->captures);
                  
                    //printf("%0.0f#%s\n", monstercapture, monsterList[l]->name);
                  //printf("%0.1f#%s\n", monstercapture, trainerList[i].visits->regions[j]->nmonsters);
                  printf("%0.0f#%s\n", monstercapture, trainerList[i].visits->regions[j]->monsters[l]->name);
                  //printf("\nmonsterName = %s\n", trainerList[0].visits->regions[0]->monsters[2]->name);
                  

                  


                  
                }
            
        }
      }
  
}








void releaseMemory(monster** monsterList, int monsterCount, region** regionList, int regionCount, trainer* trainerList, int trainerCount)

{
    for(int i = 0; i < monsterCount; i++)
    {
        free(monsterList[i]->name);free(monsterList[i]->element);
        free(monsterList[i]);
        
        free(regionList[i]->name);free(regionList[i]->monsters);
        free(regionList[i]);
        
        free(trainerList[i].name);free(trainerList[i].visits->regions);
        free(trainerList[i].visits);
    }
    free(monsterList);
    free(regionList);
    free(trainerList);


}