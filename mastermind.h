struct cmdline_args{
    char *code;
    int attempts;
};

int check_code(char *);
int verify_code(char *, char *);
void play(char *, int);
int my_strcmp(char *, char *);
int my_strlen(const char *);
void handle_cmdline_args(int, char **, struct cmdline_args *);
