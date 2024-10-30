

int length_of_last_word(char *s)
{
    int len  = 0;
    int i    = 0;
    int flag = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == ' ') {
            flag = 0;
        } else {
            if (flag == 0) {
                len  = 1;
                flag = 1;
            } else {
                len++;
            }
        }
    }
    return len;
}