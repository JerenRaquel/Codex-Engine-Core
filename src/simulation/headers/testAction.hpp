#ifndef TESTACTION_HPP_
#define TESTACTION_HPP_

// Engine
#include "action.hpp"

class TestAction : public Action {
 private:
  // Base Class
  void InternalStart(const Engine* const engine) const noexcept override;
  void InternalUpdate(const Engine* const engine) const noexcept override;

 public:
  TestAction();
  ~TestAction();
};
#endif  // TESTACTION_HPP_