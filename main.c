//
//  main.c
//  crime_statistics
//
//  Created by Hien Tran on 11/28/22.
//  Palomar College

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define NUM_OF_STATE    100
FILE *fp, *fpIn;
typedef struct {
    char state [15];    //14
    int population;     //8
    int destruction;    //4
    int larceny;        //3
    int kidnapping;     //3
    int drug;           //4
    int weapon;         //4
} Crime;

void strsub(char buf[], char sub[], int start, int end);
int readCriminalData(FILE *fpIn, Crime criminal[NUM_OF_STATE]);
void printHeader(void);
void outputCriminalData(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal);
void insertionSort(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal);
void searchCrimeRate(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal);

int main(void) {
    Crime criminal[NUM_OF_STATE];
    int maxCriminal = 0;
    
    fp = fopen("csis.txt", "w");
    if(fp == NULL){
        printf("csis.txt could not be open.\n");
        exit(1);
    }
    
    fpIn = fopen("crimedata.txt", "r");
    if(fpIn == NULL){
        printf("crimedata.txt could not be open.\n");
        exit(1);
    }
    
    maxCriminal = readCriminalData(fpIn, criminal);
    printHeader();
    outputCriminalData(fp, criminal, maxCriminal);
    insertionSort(fp, criminal, maxCriminal);
    searchCrimeRate(fp, criminal, maxCriminal);
    
    fclose(fp);
    fclose(fpIn);
    return 0;
}

void strsub (char buf[], char sub[], int start, int end){
    int i, j;
    
    for (j = 0, i = start; i <= end; i++, j++) {
        sub[j] = buf[i];
    }
    sub[j] = '\0';
}

int readCriminalData(FILE *fpIn, Crime criminal[]){
    char buf[NUM_OF_STATE];
    char cPopulation[9];
    char cDestruction[5];
    char cLarceny[4];
    char cKidnapping[4];
    char cDrug[5];
    char cWeapon[5];
    
    int i = 0;
    while (!feof(fpIn)) {
        fgets(buf, NUM_OF_STATE, fpIn);
        strsub(buf, criminal[i].state, 0, 13);
        strsub(buf, cPopulation, 15, 22);
        criminal[i].population = atoi(cPopulation);
        strsub(buf, cDestruction, 24, 27);
        criminal[i].destruction = atoi(cDestruction);
        strsub(buf, cLarceny, 29, 31);
        criminal[i].larceny = atoi(cLarceny);
        strsub(buf, cKidnapping, 33, 35);
        criminal[i].kidnapping = atoi(cKidnapping);
        strsub(buf, cDrug, 37, 40);
        criminal[i].drug = atoi(cDrug);
        strsub(buf, cWeapon, 42, 45);
        criminal[i].weapon = atoi(cWeapon);
        i++;
    }
    fclose(fpIn);
    return i;
}


void printHeader(void){
    printf("%43s\n\n", "crime_statistics");
    fprintf(fp, "%43s\n", "crime_statistics");
    printf("%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "State", "Population", "Destruction", "Larceny", "Kidnapping", "Drug", "Weapon");
    fprintf(fp, "%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "State", "Population", "Destruction", "Larceny", "Kidnapping", "Drug", "Weapon");
    printf("%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "-----", "----------", "-----------", "-------", "----------", "----", "------");
    fprintf(fp, "%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "-----", "----------", "-----------", "-------", "----------", "----", "------");
    
    
}

void outputCriminalData(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal){
    int i;
    
    for (i = 1; i < maxCriminal; i++) {
        printf("%-14s %-10d %-11d %-7d %-10d %-4d %-6d\n", criminal[i].state, criminal[i].population, criminal[i].destruction, criminal[i].larceny, criminal[i].kidnapping, criminal[i].drug, criminal[i].weapon);
        fprintf(fp, "%-14s %-10d %-11d %-7d %-10d %-4d %-6d\n", criminal[i].state, criminal[i].population, criminal[i].destruction, criminal[i].larceny, criminal[i].kidnapping, criminal[i].drug, criminal[i].weapon);
    }
}

void insertionSort(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal){
    int i, j;
    int tPopulation = 0, tDestruction = 0, tLarceny = 0, tKidnapping = 0, tDrug = 0, tWeapon = 0;
    char tState [15];
    
    for (i = 1; i < maxCriminal; i++) {
        strcpy(tState, criminal[i].state);
        tPopulation = criminal[i].population;
        tDestruction = criminal[i].destruction;
        tLarceny = criminal[i].larceny;
        tKidnapping = criminal[i].kidnapping;
        tDrug = criminal[i].drug;
        tWeapon = criminal[i].weapon;
        j = i - 1;
        while (j >= 0 && tPopulation < criminal[j].population) {
            strcpy(criminal[j+1].state, criminal[j].state);
            criminal[j+1].population = criminal[j].population;
            criminal[j+1].destruction = criminal[j].destruction;
            criminal[j+1].larceny = criminal[j].larceny;
            criminal[j+1].kidnapping = criminal[j].kidnapping;
            criminal[j+1].drug = criminal[j].drug;
            criminal[j+1].weapon = criminal[j].weapon;
            j--;
        }
        strcpy(criminal[j+1].state, tState);
        criminal[j+1].population = tPopulation;
        criminal[j+1].destruction = tDestruction;
        criminal[j+1].larceny = tLarceny;
        criminal[j+1].kidnapping = tKidnapping;
        criminal[j+1].drug = tDrug;
        criminal[j+1].weapon = tWeapon;
    }
    
    printf("\n-----------------------------------------------\n");
    fprintf(fp, "\n-----------------------------------------------\n");
    printf("|Order By Population From Smallest To Largest:|\n");
    fprintf(fp, "|Order By Population From Smallest To Largest:|\n");
    printf("-----------------------------------------------\n");
    fprintf(fp, "-----------------------------------------------\n");
    printf("%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "State", "Population", "Destruction", "Larceny", "Kidnapping", "Drug", "Weapon");
    fprintf(fp, "%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "State", "Population", "Destruction", "Larceny", "Kidnapping", "Drug", "Weapon");
    printf("%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "-----", "----------", "-----------", "-------", "----------", "----", "------");
    fprintf(fp, "%-14s %-10s %-11s %-7s %-10s %-4s %-6s\n", "-----", "----------", "-----------", "-------", "----------", "----", "------");
    
    for (i = 1; i < maxCriminal; i++) {
        printf("%-14s %-10d %-11d %-7d %-10d %-4d %-6d\n", criminal[i].state, criminal[i].population, criminal[i].destruction, criminal[i].larceny, criminal[i].kidnapping, criminal[i].drug, criminal[i].weapon);
        fprintf(fp, "%-14s %-10d %-11d %-7d %-10d %-4d %-6d\n", criminal[i].state, criminal[i].population, criminal[i].destruction, criminal[i].larceny, criminal[i].kidnapping, criminal[i].drug, criminal[i].weapon);
    }
}

void searchCrimeRate(FILE *fp, Crime criminal[NUM_OF_STATE], int maxCriminal){
    int i, j, temp;
    char tempState [15];
    int crimeRate[NUM_OF_STATE];
    
    for (i = 0; i < maxCriminal; i++) {
        crimeRate[i] = criminal[i].destruction + criminal[i].larceny + criminal[i].kidnapping + criminal[i].drug + criminal[i].weapon;
    }
    
    for (i = 1; i < maxCriminal; i++) {
        strcpy(tempState, criminal[i].state);
        temp = crimeRate[i];
        j = i - 1;
        while (j >= 0 && temp < crimeRate[j]) {
            strcpy(criminal[j+1].state, criminal[j].state);
            crimeRate[j+1] = crimeRate[j];
            j--;
        }
        strcpy(criminal[j+1].state, tempState);
        crimeRate[j+1] = temp;
    }
    printf("\nState with least number of crime rate is %s with %d\n", criminal[1].state, crimeRate[1]);
    fprintf(fp, "\nState with least number of crime rate is %s with %d\n", criminal[1].state, crimeRate[1]);
    printf("State with greatest number of crime rate is %s with %d\n", criminal[maxCriminal-1].state, crimeRate[maxCriminal-1]);
    fprintf(fp, "State with greatest number of crime rate is %s with %d\n", criminal[maxCriminal-1].state, crimeRate[maxCriminal-1]);
}
