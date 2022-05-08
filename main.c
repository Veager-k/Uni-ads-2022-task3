#include <stdio.h>
#include <stdlib.h>
#include <time.h>   
#include <math.h>
#include "stack.h"
#include "queue.h"

double randomize(double middle, double variance);
double findWeightedValue(Stack *stack);
int findStackValueSum(Stack *stack, double *totalValue, double *totalMass);

int main(){
    double grainPurchaseCount; // tons
    double grainPurchaseCountVariation; //in percentages (eg. 15 == 15%)
    double grainPurchaseCost; // eur/ton
    double grainPurchaseCostVariation; // percentages
    double markup; // percentages


    FILE *input;
    input = fopen("input.txt", "r");

    fscanf(input, "%lf%lf", &grainPurchaseCount, &grainPurchaseCountVariation);
    fscanf(input, "%lf%lf", &grainPurchaseCost, &grainPurchaseCostVariation);
    fscanf(input, "%lf", &markup);

    fclose(input);


    Queue *grainSiloFIFO = createQueue();
    Stack grainSiloLIFO;
    init(&grainSiloLIFO);


    srand(time(NULL));
    const int dayCount = 365;
    double currGrainCount = 0.0;
    double profitFIFO = 0.0;
    double profitLIFO = 0.0;

    for(int i = 0; i < dayCount; ++i){
        
        // buying grain
        int grainPurchased = randomize(grainPurchaseCount, grainPurchaseCountVariation);
        int purchaseCostPerTon = randomize(grainPurchaseCost, grainPurchaseCostVariation);
        int cost = grainPurchased*purchaseCostPerTon;
        int *error;

        enQueue(grainSiloFIFO, grainPurchased, purchaseCostPerTon, error);
        push(&grainSiloLIFO, grainPurchased, purchaseCostPerTon);
        currGrainCount += grainPurchased;
        profitFIFO -= cost;
        profitLIFO -= cost;

        // selling grain

        double grainToSellFIFO = fmod(rand(),(currGrainCount+1));
        double grainToSellLIFO = grainToSellFIFO;
        currGrainCount -= grainToSellFIFO;
        
        while(grainToSellFIFO > 0){
            QNode* oldestGrain = peek(grainSiloFIFO);
            if(oldestGrain->count > grainToSellFIFO){
                oldestGrain->count -= grainToSellFIFO;
                profitFIFO += grainToSellFIFO * oldestGrain->value * ((100+markup)/100);
                grainToSellFIFO = 0;

            } else{
                grainToSellFIFO -= oldestGrain->count;
                profitFIFO += oldestGrain->count * oldestGrain->value * ((100+markup)/100);
                deQueue(grainSiloFIFO);
            }
        }
        
        // selling grain LIFO

        while(grainToSellLIFO > 0){
            Node* newestGrain = peekStack(grainSiloLIFO);

            if(newestGrain->count > grainToSellLIFO){
                double count = newestGrain->count - grainToSellLIFO;
                profitLIFO += grainToSellLIFO * findWeightedValue(&grainSiloLIFO) * ((100+markup)/100);
                grainToSellLIFO = 0;
            } else{
                grainToSellLIFO -= newestGrain->count;
                profitLIFO += newestGrain->count * findWeightedValue(&grainSiloLIFO) * ((100+markup)/100);
                pop(&grainSiloLIFO);
            }
        }
    }
    printf("fifo profit = %.2lf\n", profitFIFO);
    printf("lifo profit = %.2lf\n", profitLIFO);

    return 0;
}

double randomize(double middle, double variance){
    double min = (middle * (100 - variance))/100;
    double max = (middle * (100 + variance))/100;

    return min + fmod(rand(), (max-min + 1));
}

double findWeightedValue(Stack *stack){
    double totalValue = 0;
    double totalMass = 0;
    findStackValueSum(stack, &totalValue, &totalMass);
    totalValue /= totalMass;

    return totalValue;
}

int findStackValueSum(Stack *stack, double *totalValue, double *totalMass){
    if(isStackEmpty(*stack)){
        return 1;
    } else{
        Node* temp = peekStack(*stack);
        double tempCount = temp->count;
        double tempValue = temp->value;
        pop(stack);

        *totalMass += temp->count;
        *totalValue += temp->value * temp->count;

        findStackValueSum(stack, totalValue, totalMass);
        push(stack, tempCount, tempValue);
        return 1;
    }
}