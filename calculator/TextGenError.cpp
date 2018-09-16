// ======================================================================
/*!
 * \file
 * \brief Implementation of class TextGen::TextGenError
 */
// ======================================================================
/*!
 * \class TextGen::TextGenError
 *
 * \brief The generic exception thrown by TextGen library
 *
 */
// ======================================================================

#include "TextGenError.h"

namespace TextGen
{
// ----------------------------------------------------------------------
/*!
 * \brief Constructor
 *
 * \param theError The error message
 */
// ----------------------------------------------------------------------

TextGenError::TextGenError(std::string theError) : itsError(std::move(theError)) {}
// ----------------------------------------------------------------------
/*!
 * \brief Returns the error message
 *
 * \return The error message
 */
// ----------------------------------------------------------------------

const char* TextGenError::what() const throw() { return itsError.c_str(); }
}  // namespace TextGen

// ======================================================================
