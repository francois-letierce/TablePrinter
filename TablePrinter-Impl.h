/*******************************************************************************
 * Copyright (c) 2020 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: Francois Letierce
 *******************************************************************************/

#ifndef _TABLE_PRINTER_IMPL_H_
#define _TABLE_PRINTER_IMPL_H_

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include <type_traits>
#include <vector>
#include <string>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*!
 * \brief
 * Writing method
 *
 * \param input: data to push in the table
 */
/*---------------------------------------------------------------------------*/
template<typename T>
TablePrinter& TablePrinter::operator<<(T input)
{
  // If 1st input, we create a table entry
  if (m_i == 0 && m_j == 0)
    m_table.push_back(std::vector<std::vector<std::string>>(_nbColumns()));
  
  // We need a stream to format input and a string once it is formated correctly
  std::stringstream ss;
  std::string formated_input;
  
  // For some particular cases (floating point numbers) we need to change format
  if (std::is_floating_point<T>::value) {
    ss << std::setiosflags(std::ios::scientific)
       << std::setprecision(m_precision)
       << input;
    // We look at useless added zeros because of the setprecision and remove them
    formated_input = _removeTrailingZeros(ss.str());
  } else {
    ss << input;
    formated_input = ss.str();
  }
  
  // We store this formated entry in the table
  m_table.at(m_i).at(m_j) = _makeMultiline(formated_input);
  
  // Getting ready for the next entry
  if (m_j == _nbColumns() - 1) {
    // if we are at the last column, the next entry will be the begining of a new line
    m_j = 0;
    ++m_i;
    m_table.push_back(std::vector<std::vector<std::string>>(_nbColumns()));
  } else {
    ++m_j;
  }
  return *this;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif /* _TABLE_PRINTER_IMPL_H_ */
