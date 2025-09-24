#include "autocomplete.h"




int main(void)
{
    struct term *terms;
    int nterms;
    read_in_terms(&terms, &nterms, "cities.txt");
    
    //free allocated blocks here -- not required for the project, but good practice
    return 0;
}
