#include <stdio.h>
#include <stdlib.h>

struct Table {
  char *name;
};

typedef struct Table Table;

Table *tables[10];
int i = 0;

void create_table(char *name) {
  struct Table *table = malloc(sizeof(Table));
  table->name = name;
  tables[i++] = table;
}

int main() {
  create_table("customers");
  create_table("articles");
  create_table("buyers");
  for (int j = 0; j < i; j++) {
    printf("Table %d: %s\n", j, tables[j]->name);
  }
  /*
  first_name = select_from("first_name", "customers");
  last_name = select_from("last_name", "customers");
  printf("%s %s", first_name, last_name);*/

  return 0;
}
