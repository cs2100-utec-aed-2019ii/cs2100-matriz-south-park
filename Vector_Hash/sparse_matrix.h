#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <string>
#include <fstream>
#include "print.h"








//--------------------------------------------------
// Node
//--------------------------------------------------
template <typename type>
class node{
  public:
  using index = unsigned int;
  using ptr_n = std::shared_ptr<node<type>>;

  public:
  type value;
  index x = 0;
  index y = 0;
  
  public:
  ptr_n right;
  ptr_n down;

  public:
  node(const type& value, const index& x, const index& y): value{value}, x{x}, y{y}{}
  };











//--------------------------------------------------
// Sparse matrix
//--------------------------------------------------
template<typename type>
class sparse_matrix{
  private:
	friend sparse_matrix<type> transpose(const sparse_matrix<type>& _s_m);
  using index = unsigned int;

  public:
  using ptr_n = std::shared_ptr<node<type>>;

  private:
  template<typename vec_type>
  using vector = std::vector<vec_type>;
  using axis = vector<ptr_n>;

  private:
  axis x;
  axis y;

	public:
	sparse_matrix() = default;
	sparse_matrix(const std::string& imgName) {
		std::ifstream Image(imgName);
		std::string line;
		int i = 0;
		int j = 0;
		while (Image.good()) {
			std::getline(Image, line, '\n');
			for(auto val : line) {
				if (val == '1') {
					insert(1, i, j);
				}
        j++;
			}
      j = 0;
			i++;
		}
		Image.close();
	}

  public:
  void set_x_size(const index& _n){
    x.resize(_n);
  }

  void set_y_size(const index& _n){
    y.resize(_n);
  }

  index get_x_size(){
    return x.size();
  }

  index get_y_size(){
    return y.size();
  }

	static sparse_matrix<type> identity(const int& x, const int& y) {
		sparse_matrix<type> result;
		result.set_x_size(x);
		result.set_y_size(y);

		for(int i = 0; i<x; i++){
			result.insert(1, i, i);
		}
		return result;
	}

	sparse_matrix<type>& delete_node(const index& _x, const index& _y) {
		
    if(_x > (get_x_size() - 1) || _y > (get_y_size() - 1)){
      return *this;
    }
    
    ptr_n* x_node = &(x[_x]);
		ptr_n* y_node = &(y[_y]);

    if(!(*x_node && *y_node)){
      return *this;
    }
		
		if((*x_node)->y == _y) {	
			(*x_node) = (*x_node)->right;
		}
		else {
      while((*x_node)->right){
				if((*x_node)->right->y == _y){
					(*x_node)->right = (*x_node)->right->right;
          
					break;
				}
				else {
					x_node = &((*x_node)->right);
				}
			}
    }
		
    if((*y_node)->x == _x){
      (*y_node) = (*y_node)->down;
    }
		else {
      while((*y_node)->down) {
				if((*y_node)->down->x == _x){
					(*y_node)->down = (*y_node)->down->down;
					break;
				}
				else {
					y_node = &((*y_node)->down);
				}
			}
    }
		
		return *this;
		
	}

  sparse_matrix<type>& insert(const type& _value, const index& _x, const index& _y){

    if(_x >= (get_x_size()))set_x_size(_x + 1);
    if(_y >= (get_y_size()))set_y_size(_y + 1);

    ptr_n* x_node = &(x[_x]);
    ptr_n* y_node = &(y[_y]);
    ptr_n new_node = std::make_shared<node<type>>(_value, _x, _y);
    
    if(!(*x_node)) *x_node = new_node;
    else while(*x_node){
      if((*x_node)->y < _y){
        x_node = &((*x_node)->right);
        if(!(*x_node)) {
          *x_node = new_node;
          break;
        }
      } else {if ((*x_node)->y > _y){
        ptr_n temp = *x_node;
        *x_node = new_node;
        (*x_node)->right = temp;
        } else 
          (*x_node)->value = _value;
        break;
      }
    }

    if(!(*y_node)) *y_node = new_node;
    else while(*y_node){
      if((*y_node)->x < _x){
        y_node = &((*y_node)->down);
        if(!(*y_node)) {
          *y_node = new_node;
          break;
          }
        }
      else {if ((*y_node)->x > _x){
        ptr_n temp = *y_node;
        *y_node = new_node;
        (*y_node)->down = temp;
        } else 
          (*y_node)->value = _value;
        break;
      }
    }
		return *this;
  }

  type get(const index& _x, const index& _y, bool& found){
    found = false;
    ptr_n node;
    type temp;
    bool notFinded = true;
    if(_x > _y){
      node = x[_x];
      for(index i = 0; i<=_y; i++){
        
        if(!node) return 0;
        if(node->y == _y){
          temp = node->value;
          notFinded = false;
          break;
        }
        node = node->right;
      }
    }else{
      node = y[_y];
      for(index i = 0; i<=_x; i++){
        if(!node) return 0;
        if(node->x == _x){
          temp = node->value;
          notFinded = false;
          break;
        }
        node = node->down;
      }
    }
    if(notFinded) return 0;
    found = true;
    return temp;
  }

  type get(const index& _x, const index& _y){
    bool temp;
    return get(_x, _y, temp);
  }

  template<template<typename...> class cont_cont, typename cont, typename... args>
  void get_matrix(cont_cont<cont, args...>& container){
    for(index i = 0; i<get_x_size(); i++){
      cont temp;
      for(index j = 0; j<get_y_size(); j++) {
        temp.push_back(get(i, j));
      }
      container.push_back(temp);
    }
  }

};








//--------------------------------------------------
// External functions
//--------------------------------------------------
template<typename type>
sparse_matrix<type> transpose(sparse_matrix<type>& _s_m) {
  sparse_matrix<type> new_s_m;
  int x_size = _s_m.get_x_size();
  int y_size = _s_m.get_y_size();
  for(int i = 0; i<x_size; i++)
    for(int j = 0; j<y_size; j++) {
      bool found;
      type temp = _s_m.get(i, j, found);
      if(found) new_s_m.insert(temp, j, i);
		}
	return new_s_m;
}

template<typename type>
sparse_matrix<type> add(sparse_matrix<type>& a, sparse_matrix<type>& b){
  sparse_matrix<type> result;
  if (a.get_x_size() == b.get_x_size() && a.get_y_size() == b.get_y_size()){
    int x_size = a.get_x_size();
    int y_size = b.get_y_size();

    result.set_x_size(x_size);
    result.set_y_size(y_size);

    for(int i = 0; i<x_size; i++)
    for(int j = 0; j<y_size; j++) {
      bool found_a;
      type temp_a = a.get(i, j, found_a);

      bool found_b;
      type temp_b = b.get(i, j, found_b);

      if(found_a && found_b)
        {result.insert(temp_a + temp_b, i, j);}
      else if(found_a) 
        {result.insert(temp_a, i, j);}
      else if (found_b)
        {result.insert(temp_b, i, j);}
		}
  }
  return result;
}


template<typename type>
sparse_matrix<type> mult(sparse_matrix<type>& a, sparse_matrix<type>& b){
  sparse_matrix<type> result;
  if (a.get_y_size() == b.get_x_size()){
    int x_size = a.get_x_size();
    int y_size = b.get_y_size();
		int y_size_2 = a.get_y_size();

    result.set_x_size(x_size);
    result.set_y_size(y_size);
    
    for (int i = 0; i<x_size; i++) { 
        for (int j = 0; j<y_size; j++) {
					type temp_res = 0;
            for (int k = 0; k<y_size_2; k++) {
							bool found_a;
      				type temp_a = a.get(i, k, found_a);
							bool found_b;
      				type temp_b = b.get(k, j, found_b);

							temp_res += temp_a * temp_b;
						}
						result.insert(temp_res, i, j);
        } 
    } 

  }
  return result;
}

template<typename type>
void getCofactor(sparse_matrix<type>& A, sparse_matrix<type>& temp, int p, int q, int n) {
	int i = 0;
	int j = 0;
	for (int row = 0; row < n; row++) {
		for (int col = 0; col < n; col++) {
			if (row != p && col != q) {
				bool found_a;
  			type temp_a = A.get(row, col, found_a);
				temp.insert(temp_a, i, j++);
				if (j == n - 1) {
					j = 0;
					i++;
				}
			}
		}
	}
}

template<typename type>
int determinant(sparse_matrix<type>& A, int n) {
    int det = 0;
    sparse_matrix<type> temp;
    int sign = 1;

		if (n == 1) {
			bool found_a;
  		type temp_a = A.get(0, 0, found_a);
			return temp_a;
		}

    for(int f = 0; f < n; f++)	{
			getCofactor(A, temp, 0, f, n);
			bool found_a;
  		type temp_a = A.get(0, f, found_a);
			det += sign * temp_a * determinant(temp, n - 1);
			sign = -sign;
    }
    return det;
}

template<typename type>
void adjoint(sparse_matrix<type>& a, sparse_matrix<type>& adj) {
	int sign = 1;
	int x_size = a.get_x_size();
	int y_size = a.get_y_size();
	
	if (x_size == 1) {
		adj.insert(1,0,0);
		return;
	}

	sparse_matrix<type> temp;
	temp.set_x_size(x_size);
	temp.set_y_size(y_size);

	for (int i = 0; i<x_size; i++) {
		for (int j = 0; j<x_size; j++) {
			getCofactor(a, temp, i, j, x_size);
			sign = ((i+j)%2==0)? 1: -1;
			adj.insert( ((sign)*(determinant(temp, x_size-1))) , j, i);
		}
	}
}

template<typename type>
sparse_matrix<type> inv(sparse_matrix<type>& a){
	sparse_matrix<type> result;
	if (a.get_x_size() != a.get_y_size()) {std::cout << "Cant find Inverse"; return result;}
  
	int x_size = a.get_x_size();
	int y_size = a.get_y_size();

	int det = determinant(a, x_size);
  if (det == 0) {std::cout << "Cant find Inverse"; return result;}
  
	sparse_matrix<type> adj;
  adjoint(a, adj);

	for (int i = 0; i<x_size; i++) {
			for (int j = 0; j<x_size; j++) {
				bool found_a;
  			float temp_a = adj.get(i, j, found_a);
				float calc =  temp_a/ static_cast<float>(det);
				result.insert(calc, i, j);
			}
	}
  return result;
}

template <typename type>
std::ostream& operator<< (std::ostream& out, sparse_matrix<type> a) {
	std::vector<std::vector<type>> sm_vectors;
	a.get_matrix(sm_vectors);
	show::print(out, sm_vectors);
	return out;
}
