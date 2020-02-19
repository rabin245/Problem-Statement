#include <stdio.h>
#include <stdlib.h>

void calculatepizza(char *infilename, char *outfilename, char *logfilename) {
    long int i;

    //loads the input file
    FILE *fptr_read = fopen(infilename, "r");
    if(!fptr_read) {
        printf("Failed to open the input file!\n");
        exit(EXIT_FAILURE);
    }
    //loads the output file
    FILE *fptr_write = fopen(outfilename, "w");
    if(!fptr_write) {
        printf("Could not create output file.\n");
        exit(EXIT_FAILURE);
    }

    //read the values of M (max no of slices) and N (number of types of pizzas available)
    long int max_slices, no_pizzas;
    fscanf(fptr_read, "%ld %ld", &max_slices, &no_pizzas);
    long int *slices=(long int *)malloc(sizeof(long int)*no_pizzas);

    for(i=0; i<no_pizzas; i++) {
        fscanf(fptr_read, "%ld", &slices[i]);
    }

    //loads the log file to keep track of all the possible selections of pizzas
    FILE *fptr_log = fopen(logfilename, "w");
    if(!fptr_log) {
        printf("Could not create log file.\n");
        exit(EXIT_FAILURE);
    }

    long int current_no_slices=0, current_no_selected_pizza=0, last=no_pizzas-1, max_no_slices=0, max_no_selected_pizza=0;
    long int *current_selections=NULL, *max_selections=NULL;
    while(last>1) {
        //adds the silces from the last element in the input file and decreases the position of the last element by 1 in every iteratino
        for(i=last; i>=0; i--) {
            if(slices[i] + current_no_slices <= max_slices) {
                current_no_slices+=slices[i];
                current_no_selected_pizza++;
                current_selections=(long int *)realloc(current_selections, sizeof(long int)*current_no_selected_pizza);
                current_selections[current_no_selected_pizza-1]=i;
            }
        }

        //save the selection in the log file
        fprintf(fptr_log, "last=%ld\tcurrent_no_slices=%ld\tmax_no_slices=%ld\n", last, current_no_slices, max_no_slices);

        //compare the current no of slices with max no of selected slices
        if(current_no_slices>max_no_slices) {
            max_no_slices=current_no_slices;
            max_no_selected_pizza=current_no_selected_pizza;
            max_selections=(long int *)realloc(max_selections, sizeof(long int)*current_no_selected_pizza);

            for(i=0; i<current_no_selected_pizza; i++) {
                max_selections[i]=current_selections[i];
            }
        }

        //if the calculated answer is the max no of slices then stop the iteration
        if(max_no_slices == max_slices)
        {
            fprintf(fptr_log, "last=%ld\tcurrent_no_slices=%ld\tmax_no_slices=%ld\n", last, current_no_slices, max_no_slices);
            break;
        }
        //reset all the current variables
        current_no_slices=0;
        current_no_selected_pizza=0;
        current_selections=NULL;
        free(current_selections);

        //assigns the last position to the preceding element of the last element
        last--;
    }

    //output the answer to the output file
    fprintf(fptr_write, "%ld\n", max_no_selected_pizza);
    for(i=0; i<max_no_selected_pizza; i++) {
        fprintf(fptr_write, "%ld ", max_selections[i]);
    }

    fclose(fptr_read);
    fclose(fptr_write);
    fclose(fptr_log);
    free(slices);
    free(current_selections);
    free(max_selections);
}

int main() {
    int choice;
    printf("Choose the input data file (1 to 5) :\n\n\t(1)Example file\n\t(2)Small file\n\t(3)Medium file\n\t(4)Quite big file\n\t(5)Also big file\n\nChoice : ");
    scanf("%d", &choice);

    switch(choice) {
        case 1:
            calculatepizza("a_example.in", "a_example.out", "a_log_example.out");
            printf("Done!\n");
            break;
        case 2:
            calculatepizza("b_small.in", "b_small.out", "b_log_small.out");
            printf("Done!\n");
            break;
        case 3:
            calculatepizza("c_medium.in", "c_medium.out", "c_log_medium.out");
            printf("Done!\n");
            break;
        case 4:
            calculatepizza("d_quite_big.in", "d_quite_big.out", "d_log_quite_big.out");
            printf("Done!\n");
            break;
        case 5:
            calculatepizza("e_also_big.in", "e_also_big.out", "e_log_also_big.out");
            printf("Done!\n");
            break;
        default:
            printf("Wrnog choice!!\n");
            break;
    }

    printf("\nPizzas calculated\n");
    return 0;
}
