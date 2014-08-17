#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "database.h"

Table *tables[MAX_TABLES];
int num_tables = 0;

int find_table_index(char *table_name) {
  int index = -1;
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL && strcmp(tables[i]->name, table_name) == 0) {
      index = i;
    }
  }

  return index;
}

Table *find_table(char *table_name) {
  int index = find_table_index(table_name);
  if (index == -1) {
    return NULL;
  }

  return tables[index];
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

int create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  table->num_columns = 0;
  table->num_rows = 0;
  tables[num_tables++] = table;

  return 0;
}

int drop_table(char *name) {
  int table_index = find_table_index(name);

  if (table_index == -1) {
    return -1;
  }

  free(tables[table_index]);
  tables[table_index] = NULL;

  return 0;
}

int add_column(char *table_name, char *column_name) {
  Table *table = find_table(table_name);

  if (table == NULL) {
    return -1;
  }

  table->columns[table->num_columns++] = column_name;

  return 0;
}

int insert_into(char *table_name, char *values[], int num_values) {
  Table *table = find_table(table_name);

  if (table == NULL) {
    return -1;
  }

  if (table->num_columns != num_values) {
    return -1;
  }

  Row *row = malloc(sizeof(Row));
  for (int i = 0; i < num_values; i++) {
    row->cells[row->num_cells++] = values[i];
  }
  table->rows[table->num_rows++] = row;

  return 0;
}

int select_from(char *column_names[], int num_columns, char *table_name, int row_index, char *result[]) {
  if (row_index == -1) {
    return -1;
  }

  Table *table = find_table(table_name);
  if (table == NULL) {
    return -1;
  }

  Row *row = table->rows[row_index];
  if (row == NULL) {
    return -1;
  }

  for (int i = 0; i < num_columns; i++) {
    int column_index = find_column(table, column_names[i]);
    result[i] = row->cells[column_index];
  }

  return 0;
}

int list_columns(Table *table) {
  for (int i = 0; i < table->num_columns; i++) {
    printf("%s\n", table->columns[i]);
  }

  return 0;
}

int list_tables() {
  for (int i = 0; i < num_tables; i++) {
    if (tables[i] != NULL) {
      printf("Table %d: %s\n", i, tables[i]->name);
      puts("COLUMNS:");
      list_columns(tables[i]);
      puts("");
    }
  }

  return 0;
}

int where_equals(char *table_name, char *column_name, char *value) {
  Table *table = find_table(table_name);
  if (table == NULL) {
    return -1;
  }

  int column_index = find_column(table, column_name);
  if (column_index == -1) {
    return -1;
  }

  int row_index = -1;

  for (int i = 0; i < table->num_rows; i++) {
    if (strcmp(table->rows[i]->cells[column_index], value) == 0) {
      row_index = i;
      break;
    }
  }

  return row_index;
}
