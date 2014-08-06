#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define BOOL short

#define MAX_TABLES 10

struct Table {
  char *name;
};

typedef struct Table Table;

Table *tables[MAX_TABLES];
int num_tables = 0;

void create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  tables[num_tables++] = table;
}

void drop_table(char *name) {
  BOOL found = FALSE;
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL && strcmp(tables[i]->name, name) == 0) {
      found = TRUE;
      free(tables[i]);
      tables[i] = NULL;
    }
  }

  if (!found) {
    printf("Table not found: %s\n", name);
  }
}

void list_tables() {
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL) {
      printf("Table %d: %s\n", i, tables[i]->name);
    }
  }
}

int main() {
  create_table("customers");
  create_table("articles");
  create_table("buyers");
  list_tables();
  drop_table("articles");
  list_tables();
  /*
  first_name = select_from("first_name", "customers");
  last_name = select_from("last_name", "customers");
  printf("%s %s", first_name, last_name);*/

  return 0;
}
