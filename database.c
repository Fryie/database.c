#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "database.h"

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

int find_column(Table *table, char *column_name) {
  int index = -1;
  for (int i = 0; i < table->num_columns; i++) {
    if (strcmp(table->columns[i], column_name) == 0) {
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

void select_from(char *column_names[], int num_columns, char *table_name, int row_index, char *result[]) {
  int table_index = find_table(table_name);
  if (table_index == -1) {
    printf("Could not find table: %s\n", table_name);
    for (int i = 0; i < num_columns; i++) {
      result[i] = "";
    }
  }

  Table *table = tables[table_index];

  Row *row = table->rows[row_index];
  if (row == NULL) {
    printf("No such row found: %d\n", row_index);
    for (int i = 0; i < num_columns; i++) {
      result[i] = "";
    }
  }

  for (int i = 0; i < num_columns; i++) {
    int column_index = find_column(table, column_names[i]);
    result[i] = row->cells[column_index];
  }
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

