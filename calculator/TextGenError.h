// ======================================================================
/*!
 * \file
 * \brief Interface of class TextGen::TextGenError
 */
// ======================================================================

#pragma once

#include <stdexcept>
#include <string>

namespace TextGen
{
class TextGenError : public std::exception
{
 public:
  ~TextGenError() throw() = default;
  TextGenError(std::string theError);
  virtual const char* what() const throw();

 private:
  std::string itsError;

};  // class TextGenError
}  // namespace TextGen

// ======================================================================
