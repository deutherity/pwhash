#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char clipcopy(const char* text)
{
    FILE* proc = popen("xclip -i -sel clipboard", "w");
    if (proc == NULL)
    return 1;
    fwrite(text, strlen(text), 1, proc);
    fclose(proc);
    return 0;
}