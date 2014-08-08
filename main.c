#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "database.h"

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

  char *select_terms[] = {"first_name", "last_name", "address"};
  int num_columns = 3;
  char *result[num_columns];
  select_from(select_terms, num_columns, "customers", 0, result);
  printf("%s %s %s\n", result[0], result[1], result[2]);

  return 0;
}
