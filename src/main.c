#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "database.h"

int main() {
  init_db();
  create_table("customers");
  Table *customers = find_table("customers");
  add_column(customers, "first_name");
  add_column(customers, "last_name");
  add_column(customers, "address");
  char *values[] = {"John", "Doe", "3 Kensington Lane"};
  insert_into("customers", values, 3);
  char *values2[] = {"Bruce", "Wayne", "20 Hyde Park Corner"};
  insert_into("customers", values2, 3);

  char *select_terms[] = {"first_name", "last_name", "address"};
  int num_columns = 3;
  char *result[num_columns];
  int success = select_from(select_terms, num_columns, "customers", where_equals("customers", "last_name", "Wayne"), result);
  if (success == 0) {
    printf("%s %s, %s\n", result[0], result[1], result[2]);
  }
  free_db();

  return 0;
}
