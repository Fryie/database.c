#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define BOOL short

#define MAX_TABLES 10
#define MAX_COLUMNS 6
#define MAX_ROWS 10

typedef char *Column;

struct Row {
  char *cells[MAX_COLUMNS];
  int num_cells;
};

typedef struct Row Row;

struct Table {
  char *name;
  Column columns[MAX_COLUMNS];
  int num_columns;
  Row *rows[MAX_ROWS];
  int num_rows;
};

typedef struct Table Table;

Table *tables[MAX_TABLES];
int num_tables = 0;

int find_table(char *table_name) {
  int index = -1;
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL && strcmp(tables[i]->name, table_name) == 0) {
      index = i;
    }
  }
  return index;
}

void create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  table->num_columns = 0;
  table->num_rows = 0;
  tables[num_tables++] = table;
}

void drop_table(char *name) {
  int table_index = find_table(name);

  if (table_index == -1) {
    printf("Table not found: %s\n", name);
    return;
  }

  free(tables[table_index]);
  tables[table_index] = NULL;
}

void add_column(char *table_name, char *column_name) {
  int table_index = find_table(table_name);

  if (table_index == -1) {
    printf("Table not found: %s\n", table_name);
    return;
  }

  Table *table = tables[table_index];
  table->columns[table->num_columns++] = column_name;
}

void insert_into(char *table_name, char *values[], int num_values) {
  int table_index = find_table(table_name);

  if (table_index == -1) {
    printf("Table not found: %s\n", table_name);
    return;
  }

  Table *table = tables[table_index];

  if (table->num_columns != num_values) {
    printf("Number of values does not match number of columns!");
    return;
  }

  Row *row = malloc(sizeof(Row));
  for (int i = 0; i < num_values; i++) {
    row->cells[row->num_cells++] = values[i];
  }
  table->rows[table->num_rows++] = row;
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
  char *values[] = {"John", "Doe", "3 Kensington Lane"};
  insert_into("customers", values, 3);
  create_table("articles");
  add_column("articles", "name");
  add_column("articles", "price");
  char *values2[] = {"MacBook Pro", "$1200"};
  insert_into("articles", values2, 2);
  create_table("stores");
  add_column("stores", "city");
  add_column("stores", "size (in km^2)");
  char *values3[] = {"San Francisco", "80"};
  insert_into("stores", values3, 2);
  list_tables();
  drop_table("articles");
  list_tables();
  /*
  first_name = select_from("first_name", "customers");
  last_name = select_from("last_name", "customers");
  printf("%s %s", first_name, last_name);*/

  return 0;
}
