#ifndef ERRORHANDLER_HPP_
#define ERRORHANDLER_HPP_

#include <stdexcept>

class FailedError : public std::exception {
 public:
  const char* message_;
  FailedError(const char* message) : message_(message) {}
  const char* what() const throw() { return this->message_; }
};

class ErrorHandler {
 private:
  /*Member vars*/;

 public:
  ErrorHandler();
  ~ErrorHandler();
};
#endif  // ERRORHANDLER_HPP_