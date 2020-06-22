#include "../../h_files/header.h"


void delete_spaces(char *to_purge) {  
  int i;
  int j = -1;
  for (i = 0; to_purge[i]; i++)
    if (to_purge[i] != ' ')
        to_purge[++j] = to_purge[i];
  to_purge[++j] = '\0';
}
