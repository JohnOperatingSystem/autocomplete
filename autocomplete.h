#if !defined(AUTOCOMPLETE_H)
#define AUTOCOMPLETE_H

typedef struct term{
    char term[200]; // assume terms are not longer than 200
    double weight;
} term;


void read_in_terms(struct term **terms, int *pnterms, char *filename);

#endif