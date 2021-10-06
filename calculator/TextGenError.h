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
  ~TextGenError() throw() override = default;
  TextGenError(std::string theError);
  const char* what() const throw() override;

 private:
  std::string itsError;

};  // class TextGenError
}  // namespace TextGen

// ======================================================================
