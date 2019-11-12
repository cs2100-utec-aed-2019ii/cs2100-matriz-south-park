#include <iostream>

namespace show{
  
  template<typename type>
  void print(std::ostream& out, const type& _value){
    out<<_value;
  }
  
  template<template<typename...>class container, typename type, typename... args>
  void print(std::ostream& out, const container<type, args...>& collection){
    for(const auto& c : collection){
      print(out, c);
      print(out, "\t");
    }
  }
  
  template<template<typename...>class container, typename... args, template<typename...>class subcont, typename... subargs>
  void print(std::ostream& out, const container<subcont<subargs...>, args...>& collection){
    print(out, '\n');
    print(out, ">>>");
    print(out, '\n');
    for(const auto& c: collection){
      print(out, c);
      print(out, '\n');
    }
    print(out, '\n');
    print(out, "<<<");
    print(out, '\n');
}

template<typename type>
  void printe(std::ostream& out, const type& _value){
    print(out, _value);
    print(out, '\n');
  }
	
}