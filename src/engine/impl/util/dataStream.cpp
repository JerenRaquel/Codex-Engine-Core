#include "util/dataStream.hpp"

template <typename T>
DataStream<T>::DataStream(std::vector<T*>* data) {
  this->data = new std::vector<T*>(data->size());
  std::copy(data->begin(), data->end(), this->data->begin());
}

template <typename T>
DataStream<T>::~DataStream() {
  delete this->data;
}

template <typename T>
std::vector<T*>* const DataStream<T>::GetData() const noexcept {
  return this->data;
}

template <typename T>
const DataStream<T>* const DataStream<T>::DebugCount() const noexcept {
  std::cout << this->Count() << "\n";

  return this;
}

template <typename T>
const DataStream<T>* const DataStream<T>::Map(
    T* (*applicator)(const T* const value)) const noexcept {
  if (this->data == nullptr || this->data->size() == 0) return this;

  for (T* const data : *this->data) {
    *data = *applicator(data);
  }
  return this;
}

template <typename T>
const DataStream<T>* const DataStream<T>::ForEach(
    void (*applicator)(const T* const value)) const noexcept {
  if (this->data == nullptr || this->data->size() == 0) return this;

  for (T* const data : *this->data) {
    applicator(data);
  }
  return this;
}

template <typename T>
const DataStream<T>* const DataStream<T>::ForEachRelative(
    void* const relative,
    void (*applicator)(void* const relative,
                       const T* const value)) const noexcept {
  if (this->data == nullptr || this->data->size() == 0) return this;

  for (T* const data : *this->data) {
    applicator(relative, data);
  }
  return this;
}

template <typename T>
const DataStream<T>* const DataStream<T>::FilterAgainst(
    const T* const value,
    bool (*compareFunction)(const T* const value,
                            const T* const other)) noexcept {
  if (this->data == nullptr || this->data->size() == 0) return this;

  std::vector<T*>* filteredData = new std::vector<T*>();
  for (T* const data : *this->data) {
    if (compareFunction(value, data)) {
      filteredData->push_back(data);
    }
  }
  delete this->data;

  if (filteredData->size() > 0) {
    this->data = new std::vector<T*>(filteredData->size());
    std::copy(filteredData->begin(), filteredData->end(), this->data->begin());
  }
  delete filteredData;

  return this;
}

template <typename T>
T DataStream<T>::Sum(const T& defaultValue) const noexcept {
  if (this->data == nullptr || this->data->size() == 0) return defaultValue;

  T sum = T();
  for (T* const data : *this->data) {
    sum += *data;
  }
  return sum;
}

template <typename T>
T DataStream<T>::Average(const T& defaultValue) const noexcept {
  if (this->data == nullptr || this->data->size() == 0) return defaultValue;

  return this->Sum(defaultValue) / this->data->size();
}

template <typename T>
unsigned int DataStream<T>::Count() const noexcept {
  if (this->data == nullptr) return 0;

  return this->data->size();
}

//
// Instantiate the template
//
template class DataStream<Vector<float>>;
