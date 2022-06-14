#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "mastermind.h"

int my_strlen(const char* s) {
    if(s == NULL) return -1;
    int i = 0;
    while(s[i] != '\0')
        i++;
    return i;
}

int my_strcmp(char *s1, char *s2){
    int flag = 0;
    while(*s1 != '\0' || *s2 != '\0'){
        s1++;
        s2++;
    if((*s1 == '\0' && *s2 != '\0') || (*s1 != '\0' && *s2 == '\0')||
        (*s1 != *s2)){
        flag = 1;
        break;
    }
        else flag = 0;
    }
    return flag;
}

char *random_code_gen(void){
    int c = 0;
    static char scg[5];
    //if code isn't given, a random one will be generated here
    char *allowed_chars = "0123467";
    for(int i=0;i<4;i++){
        c = rand() % 7;
        scg[i] = allowed_chars[c];
    }
    scg[4] = '\0';

    //printf("%s\n", scg); //uncomment this for debugging :)

    return scg;
}

void play(char *secret_code, int attempts){
    printf("Will you find the secret code?\n---\n");
    char attempt[5];
    char c = '>';

    for(int i=0;i<attempts;i++){
        printf("Round %d\n", i);
        write(1, &c, 1);
        read(0, &attempt, 5);
        attempt[4] = '\0';
        if(!check_code(attempt)) continue;
        if(verify_code(attempt, secret_code)) break;
    }
    return;
}

void handle_cmdline_args(int argc, char **argv, struct cmdline_args *cmda){
    //struct cmdline_args cmda;
    static char *scg;
    scg = random_code_gen();
    cmda->code = scg;
    cmda->attempts = 10;

    if(argc == 3){
        if(my_strcmp(argv[1], "-c") == 0) cmda->code = argv[2]; 
        else if(my_strcmp(argv[1], "-t") == 0) cmda->attempts = atoi(argv[2]);
        else printf("\n");
        //else printf("invalid option: %s\n", argv[1]);
    }else if(argc > 3){
        for(int i=1;i<argc;i++){
            if(my_strcmp(argv[i], "-c") == 0) cmda->code = argv[i+1];
            else if(my_strcmp(argv[i], "-t") == 0) cmda->attempts = atoi(argv[i+1]);
            else continue;
        }
    }else printf("\n"); //just ignore invalid command line arguments
}

int verify_code(char *given_code, char *secret_code){
    if(!check_code(given_code)) return 0;
    int wpp = 0, mpp = 0; //wpp = well-placed pieces, mpp = misplaced pieces

    if(my_strcmp(given_code, secret_code) == 0){
        printf("Congratz! You did it!");
        return 1; 
    }

    for(int i=0;i<4;i++){
        for(int n=4;n>=0;n--){
            if(n != i && given_code[n] == secret_code[i]) mpp += 1;
            else if (n == i && given_code[n] == secret_code[i]) wpp +=1;
            else continue;
        }
    }
    printf("Well placed pieces: %d\n", wpp);
    printf("Misplaced pieces: %d\n", mpp);
    return 0;
}

int check_code(char *code){
    if(my_strlen(code) > 4 || my_strlen(code) < 4){
        printf("Given code has invalid length(it should be 4)\n");
        return 0;
    }
    for(int i=0;i<4;i++){
        if(code[i] >= '0' && code[i] <= '7') continue;
        else {printf("Wrong input!\n"); return 0;}
    }
    return 1;
}

int main(int argc, char **argv){
    srand(time(0));
    if(argc == 1){
        printf("user options: %s -c <secret code> -t <number of attempts>\n", argv[0]);
        static char *scg;
        scg = random_code_gen();
        //printf("%s\n", scg);
        play(scg, 10);
        return 0;
    }

    if(argc > 1){ 
        struct cmdline_args cmda;
        handle_cmdline_args(argc, argv, &cmda);
        char *code = cmda.code;
        int attempts = cmda.attempts;
        if(!check_code(code)) return 0;
        //printf("%s\n%d\n", code, attempts);
        play(code, attempts);
        //if(attempts == 0) {printf("Wrong number of attempts\n");return 0;}
    }
    return 0;
}
