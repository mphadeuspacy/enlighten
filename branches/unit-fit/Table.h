#pragma once
#ifndef INCLUDED_TABLE_H
#define INCLUDED_TABLE_H

#include "FixtureGlossary.h"

class Table
{
public:
   Table(const std::string &_tableName) 
      : tableName(_tableName)
   {}

   std::string TableName() const
   {
      return tableName;
   }

   Rows &GetRows()
   {
      return rows;
   }

   size_t RowsCount() const
   {
      return rows.size();
   }

   RowIterator FirstRow()
   {
      return rows.begin();
   }

   RowIterator LastRow()
   {
      return rows.end();
   }   

   size_t FieldsCount() const
   {
      if (rows.empty()) return 0;
      else return rows.begin()->size();
   }

private:
   std::string tableName;
   Rows rows;
};

#endif // INCLUDED_TABLE_H