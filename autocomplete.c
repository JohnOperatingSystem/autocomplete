#include "autocomplete.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Convert a line starting with a number to an integer
int convert_numbers(char *line){
    int i = 0;
    int number = 0;
    // Skip leading spaces
    while (line[i] == ' ') {
        i++;
    }
    // Convert consecutive digits to integer
    while (line[i] >= '0' && line[i] <= '9') { // Ensure valid digit
        number = (number * 10) + (line[i] - '0');
        i++;
    }
    return number;
}

// Compare two terms lexicographically by their term strings
int compare(const void *a, const void *b){
    const term *p_a = (const term *)a;
    const term *p_b = (const term *)b;
    return strncmp(p_a->term, p_b->term, 200); // Compare up to 200 chars
}

// Compare two terms by weight in descending order
int compare_int(const void *a, const void *b){
    term *p_a = (term *)a;
    term *p_b = (term *)b;
    if (p_a->weight < p_b->weight){
        return 1;
    }
    else if (p_a->weight > p_b->weight){
        return -1;
    }
    else{
        return 0;
    }
}

// Calculate the length of a string
int length_str(char *str){
    int i = 0;
    while(*(str+i) != '\0'){
        i++;
    }
    return i;
}

// Read in terms from a file and store them in the terms array
void read_in_terms(term **terms, int *pnterms, char *filename){
    FILE *file = fopen(filename, "r"); // Open file for reading
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    char line[200];
    fgets(line, 200, file);             // Read first line for number of terms
    *pnterms = convert_numbers(line);    // Convert to integer
    *terms = (term*)malloc(sizeof(term) * *pnterms); // Allocate memory for terms

    for (int i = 0; i < *pnterms; i++){
        fgets(line, 200, file);          // Read each term line
        char *tab = strchr(line, '\t');  // Find the tab separator
        *tab = '\0';                     // Terminate the weight string
        (*terms)[i].weight = convert_numbers(line); // Convert weight
        strcpy((*terms)[i].term, tab + 1);         // Copy term string
        (*terms)[i].term[strcspn((*terms)[i].term, "\n")] = '\0'; // Remove newline
    }

    qsort(*terms, *pnterms, sizeof(term), compare); // Sort terms lexicographically
    fclose(file); // Close file
}

// Find the index of the first term that matches the given substring
int lowest_match(struct term *terms, int nterms, char *substr){
    int max_ind = nterms-1;
    int min_ind = 0;
    int length = length_str(substr);
    int ind;
    while(min_ind <= max_ind){
        ind = (max_ind + min_ind) / 2; // Middle index
        if(strncmp(terms[ind].term, substr, length) < 0){
            min_ind = ind + 1;         // Move right
        }
        else if(strncmp(terms[ind].term, substr, length) >= 0){
            max_ind = ind - 1;         // Move left
        }
    }
    return min_ind;
}

// Find the index of the last term that matches the given substring
int highest_match(struct term *terms, int nterms, char *substr){
    int max_ind = nterms-1;
    int min_ind = 0;
    int length = length_str(substr);
    int ind;
    while(min_ind <= max_ind){
        ind = (max_ind + min_ind) / 2; // Middle index
        if(strncmp(terms[ind].term, substr, length) <= 0){
            min_ind = ind + 1;         // Move right
        }
        else if(strncmp(terms[ind].term, substr, length) > 0){
            max_ind = ind - 1;         // Move left
        }
    }
    return max_ind;
}

// Find all terms that match a substring and return them sorted by weight
void autocomplete(struct term **answer, int *n_answer, struct term *terms, int nterms, char *substr){
    int lowest_ans = lowest_match(terms, nterms, substr);  // Find first match
    int highest_ans = highest_match(terms, nterms, substr); // Find last match
    *n_answer = highest_ans - lowest_ans + 1;               // Number of matches
    *answer = (term *)malloc(sizeof(term) * (*n_answer));   // Allocate memory

    // Copy matching terms into answer array
    for(int i = 0; i<*n_answer; i++){
        strcpy((*answer)[i].term, (terms)[lowest_ans+i].term);
        (*answer)[i].weight = (terms)[lowest_ans+i].weight;
    }

    // Sort answer array by descending weight
    qsort(*answer, *n_answer, sizeof(term), compare_int);
}
