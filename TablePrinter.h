/*******************************************************************************
 * Copyright (c) 2020 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: Francois Letierce
 *******************************************************************************/

#ifndef _TABLE_PRINTER_H_
#define _TABLE_PRINTER_H_

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <sstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <initializer_list>
#include <utility>

/*---------------------------------------------------------------------------*/
/*!
 * \brief
 * Simple table class.
 * You define a table with specified precision for numerical values (default is 8), output (default is std::cout) and
 * separation pattern you want to use between displayed data (default is " | ").
 * Name you columns and input data with << operator.
 * You table is ready to be printed !
 * 
 * \example
 * std::stringstream ss;
 * TablePrinter t1("Table\n insertion", 8, ss, " | ");
 * t1.addColumn({"", ""});
 * t1 << "11111111" << "22222222";
 * t1 << "33333333" << "44444444";
 * t1.print();
 * 
 * TablePrinter t2("My table with a\n Biiiiiiiiiiiiiiiiiiiiig title");
 * t2.addColumn("Isotope");
 * t2.addColumn("Mass");
 * t2.addColumn("Name");
 * t2 << "1" << "1.33657e-2" << "D";
 * t2 << "2" << "666.666" << "E";
 * t2 << "3" << 0.1569638743797386917163 << t2.nextLine();
 * t2 << "Careful here:" << ss.str() << "F";
 * t2.print();
 * 
 * \todo
 * - CORNER and BORDERS are not linked to separator pattern, maybe think of something better...
 * - Rework the whole class to come up with a better abstraction for multirow concept...
 * - Get a better Object Oriented design and go all the way to define what are cell, row, column, ...
 * - At least, merge header and table ...
 * - Use a cell grain approach, but if so, rethink the whole API ...
 */
/*---------------------------------------------------------------------------*/
class TablePrinter
{
  private:
   /*---------------------------------------------------------------------------*/
   // Inner empty class to handle carriage return
   /*---------------------------------------------------------------------------*/
   class endl {};
   
  public:
   /*---------------------------------------------------------------------------*/
   // Alignment enum
   /*---------------------------------------------------------------------------*/
   enum class eAlignment
   {
     kAlignLeft,
     kAlignRight,
     kAlignCenter
   };

  /*---------------------------------------------------------------------------*/
  // Public Methods
  /*---------------------------------------------------------------------------*/
  // Ctor
  explicit TablePrinter(const std::string& table_title = std::string(), const size_t& precision = 8,
                        std::ostream& output = std::cout, const std::string& separator = " | ");
                        
  // Dtor
  ~TablePrinter();
  
  // Separator modifier
  void setSeparator(std::string separator);
  // Title modifier
  void setTitle(const std::string& table_title, const eAlignment& alignment = eAlignment::kAlignCenter);
  
  // Column ctor. Default: auto sized, left aligned
  void addColumn(const std::string& column_header, const eAlignment& alignment = eAlignment::kAlignLeft,
                 size_t fixed_size = 0);
  // Multiple columns ctor helper overload.
  void addColumn(const std::initializer_list<std::pair<std::string, eAlignment>>& column_headers,
                 size_t fixed_size = 0);
                 
  // Input opeartor
  template <typename T>
  TablePrinter& operator<<(T input);
  TablePrinter& operator<<(TablePrinter::endl input);
  
  // Carriage return
  TablePrinter::endl nextLine();
  
  // Pretty printer
  void print();

 private:
  /*---------------------------------------------------------------------------*/
  // Private Methods
  /*---------------------------------------------------------------------------*/
  size_t _nbColumns() const;
  void _printHorizontalLine() const;
  void _printTitle() const;
  void _printColumnsHeaders() const;
  void _formatTable();
  std::vector<std::string> _makeMultiline(std::string);
  std::string _removeTrailingZeros(std::string);
  std::string::size_type _findTrailingZerosPos(std::string);
  std::string _getAlignedInput(const std::string& s, const size_t& column_width, const eAlignment& alignment) const;
  static size_t _charCount(const std::string& s);

  /*---------------------------------------------------------------------------*/
  // Attributes
  /*---------------------------------------------------------------------------*/
  // Title related
  std::vector<std::string> m_title;  // multiline title
  size_t m_title_width;
  eAlignment m_title_alignment;
  
  // Column related
  // 1st vector is for column, 2nd is for multiline header
  std::vector<std::vector<std::string>> m_column_headers;
  std::vector<size_t> m_column_widths;
  std::vector<eAlignment> m_column_alignments;
  
  // Table related
  // 1st vector is for rows, 2nd is for columns, 3rd is for lines inside a cell
  std::vector<std::vector<std::vector<std::string>>> m_table;
  size_t m_table_width;
  size_t m_i;  // current row
  size_t m_j;  // current column
  
  size_t m_precision // number of digits after decimal point
  std::ostream& m_ostream;
  std::string m_separator;
  
  const std::string m_CORNER;
  const std::string m_HORIZONTAL_BORDER;
  const std::string m_LEFT_VERTICAL_BORDER;
  const std::string m_RIGHT_VERTICAL_BORDER;  
};

/*---------------------------------------------------------------------------*/
// Template impl.
/*---------------------------------------------------------------------------*/
#include "TablePrinter-Impl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif /* _TABLE_PRINTER_H_ */
