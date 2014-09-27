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
  hash_each_val(tables, {
    drop_table((Table *) val);
  })
  hash_free(tables);
}

Table *find_table(char *table_name) {
  return hash_get(tables, table_name);
}

int create_table(char *name) {
  Table *table = malloc(sizeof(Table));
  table->name = name;
  table->columns = hash_new();
  table->rows = malloc(sizeof(*table->rows));
  vec_init(table->rows);
  hash_set(tables, name, table);

  return 0;
}

int drop_table(Table *table) {
  if (!table) {
    return -1;
  }

  /* free columns */
  hash_each_val(table->columns, {
    drop_column(table, (Column *) val);
  })
  hash_free(table->columns);

  /* free rows */
  /* I have to store the rows in a temp array,
   * because otherwise I'd be modifying the structure I'm looping over */
  int row_num = table->rows->length;
  Row *rows[row_num];

  int i;
  Row *row;
  vec_foreach(table->rows, row, i) {
    rows[i] = row;
  }
  for (i = 0; i < row_num; i++) {
    drop_row(table, rows[i]);
  }

  vec_deinit(table->rows);
  free(table->rows);

  /* free table */
  free(table);
  hash_del(tables, table->name);

  return 0;
}

int add_column(Table *table, char *column_name) {
  if (table == NULL) {
    return -1;
  }

  Column *column = malloc(sizeof(Column)); 
  column->name = column_name;
  hash_set(table->columns, column_name, column);

  return 0;
}

int drop_column(Table *table, Column *column) {
  hash_del(table->columns, column->name);

  /* drop for each row */
  Row *row;
  int i;
  vec_foreach(table->rows, row, i) {
    hash_del(row->cells, column->name);
  }

  free(column);

  return 0;
}

int drop_row(Table *table, Row *row) {
  hash_free(row->cells);
  vec_remove(table->rows, row);
  free(row);
}

Column *find_column(Table *table, char *column_name) {
  return hash_get(table->columns, column_name);
}

int insert_into(Table *table, char *column_names[], char *values[], int num_values) {
  if (!table) {
    return -1;
  }

  Row *row = malloc(sizeof(Row));
  row->cells = hash_new();
  for (int i = 0; i < num_values; i++) {
    /* this is not schemaless! only allow access to defined columns */
    Column *column = find_column(table, column_names[i]);
    if (!column) {
      return -1;
    }

    hash_set(row->cells, column_names[i], values[i]);  
  }
  vec_push(table->rows, row);

  return 0;
}

hash_t *select_from(Table *table, char *column_names[], int num_columns, int row_index) {
  if (row_index == -1) {
    return NULL;
  }

  if (!table) {
    return NULL;
  }

  if (row_index >= table->rows->length) {
    return NULL;
  }
  Row *row = table->rows->data[row_index];
  if (!row) {
    return NULL;
  }

  hash_t *result = hash_new();
  for (int i = 0; i < num_columns; i++) {
    /* this is not schemaless! only allow access to defined columns */
    Column *column = find_column(table, column_names[i]);
    if (!column) {
      hash_free(result);
      return NULL;
    }

    hash_set(result, column_names[i], hash_get(row->cells, column_names[i]));
  }

  return result;
}

int list_columns(Table *table) {
  hash_each_key(table->columns, {
    printf("%s\n", key);
  })

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
  if (!table) {
    return -1;
  }

  Column *column = find_column(table, column_name);
  if (!column) {
    return -1;
  }

  int row_index = -1;
  Row *row;
  int i;
  vec_foreach(table->rows, row, i) {
    if (strcmp(hash_get(row->cells, column_name), value) == 0) {
      row_index = i;
      break;
    }
  }

  return row_index;
}
