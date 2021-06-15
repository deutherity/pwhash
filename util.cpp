#include <string_view>
#include <termios.h>
#include <stdio.h>

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  current = old; /* make new settings same as old settings */
  current.c_lflag &= ~ICANON; /* disable buffered i/o */
  if (echo) {
      current.c_lflag |= ECHO; /* set echo mode */
  } else {
      current.c_lflag &= ~ECHO; /* set no echo mode */
  }
  tcsetattr(0, TCSANOW, &current); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

/* Read 1 character - echo defines echo mode */
char getch_(int echo) 
/* stolen implementation of getch from conio.h on windows */
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

bool confirm()
{
    printf(" [y/N] ");
    char foo = getch_(1);
    printf("\n");
    return foo == 'Y' || foo == 'y';
}

bool less_or_eq(std::string_view tested, std::string_view wanted)
{
    if (tested.length() > wanted.length())
    return false;
    auto i = tested.begin();
    auto j = wanted.begin();
    for (;i != tested.end();++i)
    {
        if (*i != *j)
        return false;
        ++j;
    }
    return true;
}
