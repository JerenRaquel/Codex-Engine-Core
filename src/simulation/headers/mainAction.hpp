#ifndef MAINACTION_HPP_
#define MAINACTION_HPP_

// Engine
#include "action.hpp"

class MainAction : public Action {
 private:
  // Base Class
  void InternalStart(Engine* const engine) const noexcept override;
  void InternalUpdate(Engine* const engine) const noexcept override;
  void InternalFinish(Engine* const engine) const noexcept override;

 public:
  MainAction();
  ~MainAction();
};
#endif  // MAINACTION_HPP_