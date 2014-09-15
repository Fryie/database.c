#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

#include "util.h"
#include "database.h"

hash_t *tables;

void init_db() {
  tables = hash_new();
}

void free_db() {
  hash_each_key(tables, {
    drop_table((char *) key);
  })
  hash_free(tables);
}

Table *find_table(char *table_name) {
  return hash_get(tables, table_name);
}

int create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  table->num_columns = 0;
  table->num_rows = 0;
  hash_set(tables, name, table);

  return 0;
}

int drop_table(char *name) {
  Table *table = find_table(name);

  if (table == NULL) {
    return -1;
  }

  free(table);
  hash_del(tables, name);

  return 0;
}

int add_column(Table *table, char *column_name) {
  if (table == NULL) {
    return -1;
  }

  table->columns[table->num_columns++] = column_name;

  return 0;
}

int find_column(Table *table, char *column_name) {
  for (int i = 0; i < table->num_columns; i++) {
    if (strcmp(table->columns[i], column_name) == 0) {
      return i;
    }
  }

  return -1;
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
  hash_each(tables, {
    printf("Table %s\n", key);
    puts("COLUMNS:");
    list_columns((Table *) val);
    puts("");
  })

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
