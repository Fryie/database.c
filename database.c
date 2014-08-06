#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define BOOL short

#define MAX_TABLES 10
#define MAX_COLUMNS 6

typedef char *Column;

struct Table {
  char *name;
  Column columns[MAX_COLUMNS];
  int num_columns;
};

typedef struct Table Table;

Table *tables[MAX_TABLES];
int num_tables = 0;

void create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  table->num_columns = 0;
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

void add_column(char *table_name, char *column_name) {
  Table *table = NULL;
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL && strcmp(tables[i]->name, table_name) == 0) {
      table = tables[i];
    }
  }

  if (table == NULL) {
    printf("Table not found: %s\n", table_name);
    return;
  }

  table->columns[table->num_columns++] = column_name;
}

void list_columns(Table *table) {
  for (int i = 0; i < table->num_columns; i++) {
    printf("%s\n", table->columns[i]);
  }
}

void list_tables() {
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL) {
      printf("Table %d: %s\n", i, tables[i]->name);
      puts("COLUMNS:");
      list_columns(tables[i]);
      puts("");
    }
  }
}

int main() {
  create_table("customers");
  add_column("customers", "first_name");
  add_column("customers", "last_name");
  add_column("customers", "address");
  create_table("articles");
  add_column("articles", "name");
  add_column("articles", "price");
  create_table("stores");
  add_column("stores", "city");
  add_column("stores", "size (in km^2)");
  list_tables();
  drop_table("articles");
  list_tables();
  /*
  first_name = select_from("first_name", "customers");
  last_name = select_from("last_name", "customers");
  printf("%s %s", first_name, last_name);*/

  return 0;
}
