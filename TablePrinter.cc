/*******************************************************************************
 * Copyright (c) 2020 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: Francois Letierce
 *******************************************************************************/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "TablePrinter.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <regex>
#include <locale>

/*---------------------------------------------------------------------------*/
/*!
 * \brief
 * Ctor
 * 
 * \param precision: number of digits to dispay for floating point numbers. Default is 8
 * \param output: Stream to use as output. Default is std::cout
 * \param separator: Pattern to use to separate columns. Default is " | ".
 * 
 */
/*---------------------------------------------------------------------------*/
TablePrinter::TablePrinter(const std::string& table_title, const size_t& precision,
                           std::ostream& output, const std::string& separator)
  : m_title_width(0), m_table_width(0), m_i(0), m_j(0), m_precision(precision),
    m_ostream(output), m_separator(separator), m_CORNER("+"), m_HORIZONTAL_BORDER("-"),
    m_LEFT_VERTICAL_BORDER("| "), m_RIGHT_VERTICAL_BORDER(" |")
{
  setTitle(table_title);
}

/*---------------------------------------------------------------------------*/
/*!
 * \brief
 * Dtor
 * 
 */
/*---------------------------------------------------------------------------*/
TablePrinter::~TablePrinter()
{
  // Nothing
}

