#pragma once

#include <iostream>
#include <sstream>
#include <functional>
#include <vector>

namespace hl7parsercpp::util {
  namespace hof {
    // ref: https://gist.github.com/dant3/fe28dd98539c4b671990
    template <typename T, typename U>
    U foldLeft(const std::vector<T>& data,
              const U& initialValue,
              const std::function<U(U,T)>& foldFn) {
        typedef typename std::vector<T>::const_iterator Iterator;
        U accumulator = initialValue;
        Iterator end = data.cend();
        for (Iterator it = data.cbegin(); it != end; ++it) {
            accumulator = foldFn(accumulator, *it);
        }
        return accumulator;
    }

    template <typename T>
    T reduce(const std::vector<T>& data,
            const std::function<T(T,T)>& reduceFn) {
        typedef typename std::vector<T>::const_iterator Iterator;
        Iterator it = data.cbegin();
        Iterator end = data.cend();
        if (it == end) {
            throw 0;
        } else {
            T accumulator = *it;
            ++it;
            for (; it != end; ++it) {
                accumulator = reduceFn(accumulator, *it);
            }
            return accumulator;
        }
    }

    template <typename T, typename U>
    std::vector<U> map(const std::vector<T>& data, const std::function<U(T)> mapper) {
        std::vector<U> result;
        foldLeft<T, std::vector<U>&>(data, result, [mapper] (std::vector<U>& res, T value)  -> std::vector<U>& {
            res.push_back(mapper(value));
            return res;
        });
        return result;
    }


    template <typename T>
    std::string mkString(const std::vector<T>& data, const std::string& separator = ",", const std::string& begin = "", const std::string& end = "") {
        std::stringstream buffer;
        bool first_item = true;
        buffer << begin;
        foldLeft<T, std::stringstream*>(data, &buffer, [separator, &first_item] (std::stringstream* res, T item) -> std::stringstream* {
            if (first_item) {
                *res << item;
                first_item = false;
            } else {
                *res << separator << item;
            }
            return res;
        });
        buffer << end;
        return buffer.str();
    }

    template <typename T>
    std::vector<T> filter(const std::vector<T>& data, std::function<bool(T)> filterFn) {
        std::vector<T> result;
        foldLeft<T, std::vector<T>&>(data, result, [filterFn] (std::vector<T>& res, T value)  -> std::vector<T>& {
            if (filterFn(value)) {
                res.push_back(value);
            }
            return res;
        });
        return result;
    }
  }

  namespace strings {
    // The standard way.  Use ranges in C++20.
    std::vector<std::string> split(const std::string& s, char delimiter) {
      std::vector<std::string> tokens;
      std::string token;
      std::istringstream tokenStream(s);
      while (std::getline(tokenStream, token, delimiter)) {
          tokens.push_back(token);
      }
      return tokens;
    }

    // std::string s=join(array.begin(), array.end(), std::string(","));
    template <class T, class A>
    T join(const A &begin, const A &end, const T &t) {
      T result;
      for (A it = begin;
        it != end;
        it++) {
        if (!result.empty())
          result.append(t);
        result.append(*it);
      }
      return result;
    }

    struct concat1 {
      template <typename LHS, typename RHS>
      std::string operator()(LHS const& lhs, RHS const& rhs) const {
        std::stringstream ss;
        ss << lhs << rhs;
        return ss.str();
      }
    };

    template <typename... T>
    std::string concat(T... vals) {
      std::stringstream ss;
      for (auto&& x : { vals... }) {
        ss << x;
      }        
      return ss.str();
    }

  }

}
