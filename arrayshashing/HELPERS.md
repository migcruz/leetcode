# Helper functions for arrays and strings

## Tokenize a string
```C
int main() {
    char sentence[] = "This is an example sentence";
    char *token = strtok(sentence, " ");
    
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, " ");
    }

    return 0;
}
```

## Check if string is a number
```C
char *endptr;
int num = strtol(str, &endptr, 10); //base 10

if (*endptr == '\0') {
    // Successful conversion
} else {
    // Invalid input detected
}
```