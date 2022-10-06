#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void
print_result(FILE *fp)
{
        char buf[100];
 
        if(!fp) {
                return;
        }
        printf("\n>>>\n");
        while(memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf) - 1, fp) != 0 ) {
                printf("%s", buf);
        }
        printf("\n<<<\n");
}

int
main(void)
{
        FILE *fp = NULL;
        fp = NULL;
        fp = popen("cd pythonmicroserver-update_weights && python test.py", "r");
        if(!fp) {
                perror("popen");
                exit(EXIT_FAILURE);
        }
        print_result(fp);
        pclose(fp);
}