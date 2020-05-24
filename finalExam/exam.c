#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#define MAXLINKS 10
FILE * file;
struct page {
  char * url;
  int visited;
  struct page * links[MAXLINKS];
  struct page * next;
};
struct page * add_page(struct page ** web, char * url) {
  struct page * curr = * web;
  struct page * prev = NULL;
  while (curr != NULL) {
    if (!strcmp(url, curr - > url)) {
      return NULL;
    }
    curr = curr - > next;
  }
  struct page * new = (struct page * ) malloc(sizeof(struct page));
  new - > url = (char * ) malloc(sizeof(char) * (strlen(url) + 1));
  strcpy(new - > url, url);
  new - > visited = -1;
  if ( * web == NULL) {
    new - > next = * web;
    * web = new;
    return *web
  }

  curr = * web;
  while (curr != NULL && strcmp(curr - > url, url) < 0) {
    prev = curr;
    curr = curr - > next;
  }
  if (prev == NULL) {
    new - > next = * web;
    * web = new;
  } else {
    new - > next = prev - > next;
    prev - > next = new;
  }

  return *web;
}
void print_web(struct page * web) {
  struct page * curr = web;
  while (curr != NULL) {
    printf("{URL=\"%s\",visited=%d} -> ", curr - > url, curr - > visited);
    for (int i = 0; i < MAXLINKS; i++) {
      if (curr - > links[i] != NULL) {
        printf("\"%s\" ", curr - > links[i] - > url);
      }
    }
    printf("\n");
    curr = curr - > next;
  
}
struct page * find_page(struct page * web, char * url) {
  struct page * curr = web;
  while (curr != NULL) {
    if (!strcmp(url, curr - > url)) {
      return curr;
    }
    curr = curr - > next;
  }
  return NULL;
}
void reset_visited(struct page * web) {
  struct page * curr = web;
  while (curr != NULL) {
    curr - > visited = 0;
    curr = curr - > next;
  }
}
void add_link(struct page ** web, char * source_url, char * dest_url) {
  struct page * source = find_page(( * web), source_url);
  struct page * dest = find_page(( * web), dest_url);

  if (source == NULL) {
    printf("Source URL \"%s\" is not on the web\n", source_url);
    return;
  }
  if (dest == NULL) {
    printf("Destination URL \"%s\" is not on the web\n", dest_url);
    return
  }
  if (dest == source) {
    printf("Source and destination URL cannot be the same\n");
    return;
  }

  for (int i = 0; i < MAXLINKS; i++) {
    if (source - > links[i] == dest) {
      printf("\"%s\" is already a destination for \"%s\"\n", dest_url, source_url);
      return;
    }
  }
  for (int i = 0; i < MAXLINKS; i++) {
    if (source - > links[i] == NULL) {
      source - > links[i] = dest;
      return;
    }
  }
}
void remove_page(struct page ** web, char * url) {
  struct page * curr = * web;
  struct page * prev = NULL;
  struct page * deleter = find_page( * web, url);
  if (deleter == NULL) {
    printf("URL \"%s\" is not on the web\n", url);
    return;
  }
  while (curr != NULL) {
    for (int i = 0; i < MAXLINKS; i++) {
      if (curr - > links[i] == deleter) {
        curr - > links[i] = NULL;
      }
    }
    curr = curr - > next;
  }
  curr = * web;
  while (curr != NULL && curr != deleter) {
    prev = curr;
    curr = curr - > next;
  }
  if (prev == NULL) {
    * web = ( * web) - > next;

  } else {
    prev - > next = deleter - > next;
  }
  free(deleter - > url);
  free(deleter);
}
void reachable(struct page * page) {
  if (page - > visited != 1) {
    printf("%s\n", page - > url);
    page - > visited = 1;
  }
  for (int i = 0; i < MAXLINKS; i++) {
    if (page - > links[i] != NULL) {
      reachable(page - > links[i]);
    }
  }
int search_page(struct page * page, char * keyword) {
  char string[100] = "";
  char prev[100] = "";
  if ((file = fopen(page - > url, "r")) == NULL) {
    return 0;
  }
  do {
    strcpy(string, prev);
    fscanf(file, "%s", & string);
    if (!strcmp(string, keyword)) {
      return 1;
    }
  } while (strcmp(string, prev));
  fclose(file);
  return 0;
}
void search_web(struct page * web, char * keyword) {
  struct page * curr = web;
  while (curr != NULL) {
    if (search_page(curr, keyword) == 1) {
      printf("%s\n", curr - > url);
      return;
    }
    curr = curr - > next;
  }
}
int main(void) {
  char cmd = ' ';
  struct page * web = NULL;
  char url[100] = " ";
  char destUrl[100] = " ";
  char word[100] = " ";
  struct page * temp;

  do {

    printf("Command? ");
    scanf(" %c", & cmd);
    switch (cmd) {
    case 'p':
      printf("Page URL? ");
      scanf(" %s", & url);
      if (add_page( & web, url) == NULL) {
        printf("URL \"%s\" is already on the web\n", url);
      }
      break;
    case 'w':
      print_web(web);
      break;
    case 'f':
      printf("Page URL? ");
      scanf(" %s", & url);
      if (find_page(web, url) != NULL) {
        printf("URL \"%s\" is on the web\n", url);
      } else {
        printf("URL \"%s\" is not on the web\n", url);
      }
      break;
    case 'v':
      reset_visited(web);
      break;
    case 'l':
      printf("Source & destination URL? ");
      scanf(" %s %s", & url, & destUrl);
      add_link( & web, url, destUrl);
      break;
    case 'P':
      printf("Page URL? ");
      scanf(" %s", & url);
      remove_page( & web, url);
      break;
    case 'r':
      printf("Page URL? ");
      scanf(" %s", & url);
      temp = find_page(web, url);
      if (temp != NULL) {
        reset_visited(web);
        reachable(temp);
      } else {
        printf("No such page \"%s\"", url);
      }
      break;
    case 's':
      printf("Search word in page? ");
      scanf(" %s %s", & word, & url);
      temp = find_page(web, url);
      if (temp == NULL) {
        printf("No page \"%s\"\n", url);
      } else {
        if (search_page(temp, word)) {
          printf("Page \"%s\" contains the word \"%s\"\n", url, word);
        } else {
          printf("Page \"%s\" does not contain the word \"%s\"\n", url, word);
        }
      }
      break;
    case 'S':
      printf("Search web for word? ");
      scanf(" %s", & word);
      if (web != NULL) {
        search_web(web, word);
      }
      break;
    case 'q':
      break;
    default:
      printf("Invalid Command '%c'\n", cmd);
      break;
    }

  } while (cmd != 'q');
  printf("Bye!");
}