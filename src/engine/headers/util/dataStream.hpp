#ifndef DATASTREAM_HPP_
#define DATASTREAM_HPP_

// Std
#include <iostream>
#include <vector>
#include <algorithm>
// Custom
#include "util/vector3.hpp"

template <typename T>
class DataStream {
 private:
  std::vector<T*>* data;

 public:
  DataStream(std::vector<T*>* data);
  ~DataStream();

  std::vector<T*>* const GetData() const noexcept;

  const DataStream* const DebugCount() const noexcept;
  const DataStream* const Map(
      T* (*applicator)(const T* const value)) const noexcept;
  const DataStream* const ForEach(
      void (*applicator)(const T* const value)) const noexcept;
  const DataStream* const ForEachRelative(
      void* const relative,
      void (*applicator)(void* const relative,
                         const T* const value)) const noexcept;
  const DataStream* const FilterAgainst(
      const T* const value,
      bool (*compareFunction)(const T* const value,
                              const T* const other)) noexcept;
  T Sum(const T& defaultValue) const noexcept;
  T Average(const T& defaultValue) const noexcept;
  unsigned int Count() const noexcept;
};
#endif  // DATASTREAM_HPP_