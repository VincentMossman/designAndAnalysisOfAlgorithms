/*
  Author:  Vincent T. Mossman
  Date:    October 4, 2016
  Descrip: Gets number of possible items, weights and values for those 
   items, and maximum knapsack weight capacity. Shows optimum selection.
  Compile: gcc -o knapsack knapsack.c -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//function prototypes
void printWeightedPowerSet(int,double*,double*,double*,double*);
void printValidSets(double,double*,int,int**,int*);
void printOptimumSelection(double*,double*,int*,int);

int main(int argc, char * argv[]) {

  int numItems, validSetsSize, *validSets, i, j;
  double *itemWeights, *itemValues, *setWeights, *setValues, knapsackCapacity;

  //get # of items (easiest for memory allocation)
  printf("\nHow many items? ");
  scanf("%d", &numItems);

  //allocate memory for weights, values and power sets
  itemWeights = (double *) malloc(sizeof(double) * numItems);
  itemValues  = (double *) malloc(sizeof(double) * numItems);
  setWeights  = (double *) malloc(sizeof(double) * pow(2, numItems));
  setValues   = (double *) malloc(sizeof(double) * pow(2, numItems));

  //populate weights and values
  printf("\nNOTE: to enter all values on same line, separate with space\n");
  for (i = 0; i < numItems; i++) {
    printf("Please enter Item %d Weight: ", i+1);
    scanf("%lf", &itemWeights[i]);
  }
  printf("\nNOTE: to enter all values on same line, separate with space\n");
  for (i = 0; i < numItems; i++) {
    printf("Please enter Item %d Value: ", i+1);
    scanf("%lf", &itemValues[i]);
  }

  //print weighted and valued power set and get setWeights/Values
  printf("\nPossible knapsack selections (ignoring max capacity):\n");
  printWeightedPowerSet(numItems, itemWeights, itemValues, setWeights, setValues);

  //get max capacity
  printf("\nWhat is knapsack maximum weight capacity? ");
  scanf("%lf", &knapsackCapacity);

  //print valid weights and optimum knapsack selection
  printf("\nKnapsack selections possible givin maximum weight capacity:\n");
  printValidSets(knapsackCapacity, setWeights, pow(2, numItems), &validSets, &validSetsSize);
  printf("\nOptimum knapsack selection (ties not accounted for):\n");
  printOptimumSelection(setWeights, setValues, validSets, validSetsSize);
  
  printf("\n\n");
  
  //return memory
  free(itemWeights);
  free(itemValues);
  free(setWeights);
  free(setValues);

}

/***********************************************************************
  Gets set size as well as item weights and values and prints power    *
   set along with weight and value information.  Also passes back      *
   arrays of weights and values associated with power set. To be       *
   honest, I modified code from "geeksforgeeks.org"                    *
***********************************************************************/
void printWeightedPowerSet(int setSize, double *weights, double *values, double *setWeights, double *setValues) {

  int counter = 0, j;
  double weightSub = 0.0, valueSub = 0.0;
  unsigned int powSetSize = pow(2, setSize); 

  printf("%d.) { Empty", counter + 1);
  for (counter = 0; counter < powSetSize; counter++) {
    for (j = 0; j < setSize; j++) {
      if (counter & (1<<j)) {
		weightSub += weights[j];
		valueSub += values[j];
		printf(" %d", j+1);
      }
    } 
    if (counter != powSetSize - 1) {
      printf(" }  W:%0.2lf V:%0.2lf\n%d.) {", weightSub, valueSub, counter+2);
    }
    else {
      printf(" }  W:%0.2lf V:%0.2lf\n", weightSub, valueSub);
    }
    setWeights[counter] = weightSub;
    setValues[counter] = valueSub;
    weightSub = 0.0;
    valueSub = 0.0;
  }

}

/***********************************************************************
  Gets max knapsack capacity and set of weights and passes back array  *
   of valid sets. Also prints list of valid knapsack items.            *
***********************************************************************/
void printValidSets(double maxWeight, double *setWeights, int setSize, int **validSets, int *validSetsSize) {
  
  int i, j = 0;
  *validSetsSize = 0;

  for (i = 0; i < setSize; i++) {
    if (setWeights[i] <= maxWeight) {
      printf("Selection #%d fits into knapsack\n", i+1);
      (*validSetsSize)++;
    }
  }
  
  *validSets = (int *) malloc(sizeof(int) * (*validSetsSize));

  for (i=0; i < setSize; i++) {
    if (setWeights[i] <= maxWeight) {
      (*validSets)[j] = i;
      j++;
    }
  }
  
}

/***********************************************************************
  Gets weights, values, and valid sets. Prints optimum selection.      *
***********************************************************************/
void printOptimumSelection(double *setWeights, double *setValues, int *validSets, int validSetsSize) {
  
  int i, maxIndex = 0;
  
  for (i = 0; i < validSetsSize; i++) {
    if (setValues[((int) validSets[i])] > setValues[maxIndex]) {
      maxIndex = validSets[i];
    }
  }

  printf("Selection #%d with Weight %0.2lf and Value %0.2lf is optimum knapsack selection\n", maxIndex+1, setWeights[maxIndex], setValues[maxIndex]);

}