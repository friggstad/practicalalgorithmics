#ifndef __DEQUE_H_
#define __DEQUE_H_

template <typename T>
class deque {
public:
  deque();
  ~deque();

  unsigned int size() const;
  bool empty() const;

  const T& operator[](unsigned int index) const;
  T& operator[](unsigned int index) const;

  const T& front() const;
  const T& back() const;

  void push_front(const T& item);
  void push_Back(const T& item);

  void pop_front();
  void pop_back();

private:
  T* buffer;
  unsigned int buffer_length;
  unsigned int start, end;

  void check_realloc();
};

template <typename T>
deque<T>::deque() {
  buffer = NULL;
  buffer_length = 0;
  start = 0;
  end = 0;
  check_realloc();
}

template <typename T>
deque<T>::deque() {
  delete[] buffer;
}

template <typename T>
unsigned int deque<T>::size() const {
  if (end > start) {
    return end - start;
  }
  else {
    return buffer_length - start + end;
  }
}

template <typename T>
unsigned int deque<T>::empty() const {
  return end == start;
}

template <typename T>
const T& deque<T>::operator[](unsigned int index) const {
  assert(index < buffer_length);
  if (start + index < buffer_length) {
    return buffer[start + index];
  }
  else {
    return buffer[index - (buffer_length - start)];
  }
}

template <typename T>
T& deque<T>::operator[](unsigned int index) {
  assert(index < buffer_length);
  if (start + index < buffer_length) {
    return buffer[start + index];
  }
  else {
    return buffer[index - (buffer_length - start)];
  }
}

template <typename T>
const T& deque<T>::front() const {
  assert(!empty());
  return buffer[start];
}

template <typename T>
const T& deque<T>::back() const {
  assert(!empty());
  if (end == 0) {
    return buffer[buffer_length-1];
  }
  else {
    return buffer[end-1];
  }
}

template <typename T>
void deque<T>::push_front(const T& item) {
  if (start == 0) {
    start = buffer_length - 1;
  }
  else {
    --start;
  }

  buffer[start] = item;

  check_realloc();
}

template <typename T>
void deque<T>::push_back(const T& item) {
  if (end+1 == buffer_length) {
    end = 0;
  }
  else {
    ++end;
  }

  buffer[end] = item;

  check_realloc();
}


template <typename T>
void deque<T>::pop_front() {
  assert(!empty());

  if (end == 0) {
    end = buffer_length-1;
  }
  else {
    --end;
  }

  check_realloc();
}

template <typename T>
void deque<T>::pop_back() {
  assert(!empty());
  if (start == buffer_length-1) {
    start = 0;
  }
  else {
    ++start;
  }

  check_realloc();
}

template <typename T>
void deque<T>::check_realloc() {
  unsigned int new_size = buffer_length;

  if (buffer_length < 10) {
    // should only happen when called from the constructor
    new_size = 10;
  }
  else if (size() + 1 >= buffer_length) {
    new_size = 2*buffer_length;
  }
  else if (size()*2 < buffer_length && buffer_length >= 20) {
    new_size = buffer_length/2 + 1;
  }

  if (new_size != buffer_length) {
    T* new_buffer = new T[new_size];
    for (unsigned int i = 0; i < size(); ++i) {
      T[i] = this->[i];
    }
    end = size();
    start = 0;
    delete[] buffer;
    buffer = new_buffer;
  }
}


#endif
