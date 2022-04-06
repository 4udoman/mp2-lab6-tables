#include "gtest/gtest.h"
#include "TableManager.h"

// Common tests for all tables
typedef UnsortListTable   Tab;
//typedef UnsortArrayTable  Tab;
//typedef SortArrayTable    Tab;
//typedef OpenHashTable     Tab;
//typedef ChainHashTable    Tab;
//typedef AVLTreeTable      Tab;

TEST(TTable, can_create_table)
{
  ASSERT_NO_THROW(Tab t);
}
 
TEST(TTable, can_get_size_of_table)
{
  Tab t;
  ASSERT_NO_THROW(t.getCurSize());
}

TEST(TTable, new_table_is_empty)
{
  Tab t;
  EXPECT_EQ(t.getCurSize(), 0);
}

TEST(TTable, can_add_elem_in_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Insert(PolinomObj::Create("name", "xyz")));
}

TEST(TTable, cant_change_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Insert(PolinomObj::Create("name", "x2"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TTable, can_find_existing_elem_in_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  EXPECT_EQ(t.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TTable, cant_find_non_existing_elem_in_table)
{
  Tab t;
  EXPECT_EQ(t.Find("x"), nullptr);
}

TEST(TTable, can_delete_existing_elem_from_table)
{
  Tab t;
  t.Insert(PolinomObj::Create("name", "xyz"));
  t.Delete("name");
  EXPECT_EQ(t.Find("name"), nullptr);
}

TEST(TTable, can_delete_non_existing_elem_from_table)
{
  Tab t;
  ASSERT_NO_THROW(t.Delete("x"));
}

// Tests for TableManager

TEST(TableManager, can_create_table_manager_with_tables)
{
  ASSERT_NO_THROW(TableManager m(2););
}

TEST(TableManager, can_set_active_table)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.setActiveTable(1));
}

TEST(TableManager, can_add_elem_into_all_tables)
{
  TableManager m(2);
  ASSERT_NO_THROW(m.Insert("name", "xyz"));
}

TEST(TableManager, can_find_elem)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, cant_change_existing_elem)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  m.Insert("name", "x2");
  EXPECT_EQ(m.Find("name")->get()->getStrPol(), "xyz");
}

TEST(TableManager, can_delete_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("name"));
}

TEST(TTable, no_throw_deleting_non_existing_elem_from_all_tables)
{
  TableManager m(2);
  m.Insert("name", "xyz");
  ASSERT_NO_THROW(m.Delete("x"));
}

