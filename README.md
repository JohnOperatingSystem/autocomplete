# Autocomplete Project

A simple C program that suggests word completions based on a given prefix. Words are loaded from a file with associated weights, and suggestions are sorted by relevance.

## Features
- Reads words and weights from a file (<weight>\t<term>).
- Finds matching words efficiently using binary search.
- Returns suggestions sorted by weight.

## Usage
term *terms;
int nterms;
read_in_terms(&terms, &nterms, "terms.txt");

term *answers;
int n_answer;
autocomplete(&answers, &n_answer, terms, nterms, "pre");

## Example
Prefix: "ap"
Suggestions:
1. apple (100)
2. application (80)
3. apron (60)

This project is lightweight and works well for autocomplete tasks in small to medium datasets.
