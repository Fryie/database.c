#define MAX_COLUMNS 6
#define MAX_ROWS 10
#define MAX_TABLES 10

/* type definitions */
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

/* function headers */
int find_table(char *table_name);
int find_column(Table *table, char *column_name);
void create_table(char *name);
void drop_table(char *name);
void add_column(char *table_name, char *column_name);
void insert_into(char *table_name, char *values[], int num_values);
void select_from(char *column_names[], int num_columns, char *table_name, int row_index, char *result[]);
void list_columns(Table *table);
void list_tables();
