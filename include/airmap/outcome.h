#ifndef AIRMAP_OUTCOME_H_
#define AIRMAP_OUTCOME_H_

#include <type_traits>

namespace airmap {

/// Outcome<T,U> models a return value from a function XOR an error object
/// describing the error condition if no value can be returned.
template <typename Value, typename Error>
class Outcome{
 public:
  static_assert(not std::is_same<Value, Error>::value, "Value and Error must not be the same type");
  static_assert(std::is_copy_constructible<Value>::value &&
                    std::is_move_constructible<Value>::value,
                "Value must be copy- and move-constructible");
  static_assert(std::is_copy_constructible<Error>::value &&
                    std::is_move_constructible<Error>::value,
                "Error must be copy- and move-constructible");

  explicit Outcome(const Value& value) : type{Type::value} {
    new (&data.value) Value{value};
  }

  explicit Outcome(const Error& error) : type{Type::error} {
    new (&data.error) Error{error};
  }

  Outcome(const Outcome& other) : type{other.type} {
    switch (type) {
      case Type::error:
        new (&data.error) Error{other.data.error};
        break;
      case Type::value:
        new (&data.value) Value{other.data.value};
        break;
    }
  }

  Outcome(Outcome&& other) : type{other.type} {
    switch (type) {
      case Type::error:
        new (&data.error) Error{other.data.error};
        break;
      case Type::value:
        new (&data.value) Value{other.data.value};
        break;
    }
  }

  Outcome& operator=(const Outcome& other) {
    switch (type) {
      case Type::error: {
        (&data.error)->~Error();
        break;
      }
      case Type::value: {
        (&data.value)->~Value();
        break;
      }
    }

    type = other.type;

    switch (type) {
      case Type::error: {
        new (&data.error) Error{other.data.error};
        break;
      }
      case Type::value: {
        new (&data.value) Value{other.data.value};
        break;
      }
    }

    return *this;
  }

  Outcome& operator=(Outcome&& other) {
    switch (type) {
      case Type::error: {
        (&data.error)->~Error();
        break;
      }
      case Type::value: {
        (&data.value)->~Value();
        break;
      }
    }

    type = other.type;

    switch (type) {
      case Type::error: {
        new (&data.error) Error{other.data.error};
        break;
      }
      case Type::value: {
        new (&data.value) Value{other.data.value};
        break;
      }
    }

    return *this;
  }

  ~Outcome() {
    switch (type) {
      case Type::error:
        data.error.~Error();
        break;
      case Type::value:
        data.value.~Value();
        break;
    }
  }

  explicit operator bool() const {
    return !has_error();
  }
  inline bool has_error() const {
    return type == Type::error;
  }

  inline bool has_value() const {
    return type == Type::value;
  }

  inline const Error& error() const {
    return data.error;
  }

  inline const Value& value() const {
    return data.value;
  }

 private:
  enum class Type { value, error };

  Type type;
  union Data {
    Data() : value{} {
    }

    ~Data() {
    }

    Value value;
    Error error;
  } data;
};

}  // namespace airmap

#endif  // AIRMAP_OUTCOME_H_