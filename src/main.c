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
  char *columns[] = {"first_name", "last_name", "address"};
  char *values[] = {"John", "Doe", "3 Kensington Lane"};
  insert_into(customers, columns, values, 3);
  char *values2[] = {"Bruce", "Wayne", "20 Hyde Park Corner"};
  insert_into(customers, columns, values2, 3);

  char *select_terms[] = {"first_name", "last_name", "address"};
  int num_columns = 3;
  hash_t *result = select_from(customers, select_terms, num_columns, where_equals("customers", "last_name", "Wayne"));
  if (result) {
    hash_each(result, {
      printf("%s: %s\n", key, val);
    })
    hash_free(result);
  }

  free_db();

  return 0;
}
