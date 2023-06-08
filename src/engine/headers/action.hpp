#ifndef ACTION_HPP_
#define ACTION_HPP_

// Custom
#include "engine.hpp"

class Action {
 protected:
  virtual void InternalStart(Engine* const engine) const noexcept = 0;
  virtual void InternalUpdate(Engine* const engine) const noexcept = 0;

 public:
  Action();
  virtual ~Action();

  void OnStart(Engine* const engine) const noexcept;
  void OnUpdate(Engine* const engine) const noexcept;
};
#endif  // ACTION_HPP_