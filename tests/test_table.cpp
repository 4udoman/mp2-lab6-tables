#include "gtest/gtest.h"
#include "TableManager.h"

// Common tests for all tables
typedef UnsortListTable<int, int> Tab;

TEST(TTable, can_create_table)
{
  Tab t;
}

TEST(TTable, new_table_is_empty)
{
  ADD_FAILURE();
}

TEST(TTable, can_add_elem_in_table)
{
  ADD_FAILURE();
}

TEST(TTable, throws_when_add_existing_elem_in_table)
{
  ADD_FAILURE();
}

TEST(TTable, can_find_existing_elem_in_table)
{
  ADD_FAILURE();
}

TEST(TTable, cant_find_non_existing_elem_in_table)
{
  ADD_FAILURE();
}

TEST(TTable, can_delete_existing_elem_from_table)
{
  ADD_FAILURE();
}

TEST(TTable, can_delete_non_existing_elem_from_table)
{
  ADD_FAILURE();
}

// Tests for TableManager

TEST(TableManager, can_set_active_table)
{
  ADD_FAILURE();
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  ADD_FAILURE();
}

TEST(TableManager, cant_add_existing_elem_into_all_tables)
{
  ADD_FAILURE();
}

TEST(TableManager, can_delete_existing_elem_from_all_tables)
{
  ADD_FAILURE();
}

TEST(TTable, can_delete_non_existing_elem_from_all_tables)
{
  ADD_FAILURE();
}
