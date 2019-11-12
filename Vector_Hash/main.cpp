#include <iostream>
#include <fstream>
#include "sparse_matrix.h"

int main() {

	sparse_matrix<int> a;
  sparse_matrix<int> b;

	a.insert(1, 1, 3).insert(2, 0, 2).insert(3, 1, 2).insert(4, 3, 1).insert(5,5,3).insert(9, 0, 1).insert(7, 3, 0);
	std::cout << "Matrix A" << std::endl;
	std::cout << a << std::endl;

  show::print(std::cout, a.get(3,2));
	std::cout << std::endl << std::endl;
	std::cout << "Matrix A = After Delete" << std::endl;
	a.delete_node(1, 2);
	a.delete_node(1, 3);
	a.delete_node(0, 2);
	a.delete_node(3, 1);
	a.delete_node(0, 1);
	a.delete_node(3, 0);
	a.delete_node(1, 2);
	std::cout << a.delete_node(5, 3) << std::endl;

	std::cout << "Matrix B = Transpose of Matrix A" << std::endl;
  b = transpose(a);
	std::cout << b << std::endl;
	std::cout << "Addition of A and B" << std::endl;
  std::cout << add(a, a) << std::endl;
	std::cout << "Multiplication of A and B" << std::endl;
	std::cout << mult(a, b) << std::endl;

	sparse_matrix<float> c;
	std::cout << "Matrix C" << std::endl;
	c.insert(5,0,0).insert(7,0,1).insert(8,0,2).insert(15,0,3);
	c.insert(3,1,0).insert(25,1,1).insert(58,1,2).insert(100,1,3);
	c.insert(89,2,0).insert(2,2,1).insert(45,2,2).insert(1,2,3);
	c.insert(3,3,0).insert(75,3,1).insert(65,3,2).insert(17,3,3);
	std::cout << c << std::endl;
	std::cout << "Inverse of Matrix C" << std::endl;
	std::cout << inv(c) << std::endl;

	sparse_matrix<int> id = sparse_matrix<int>::identity(100, 100);
	std::ofstream _out("res.txt");
	_out << id << std::endl;
	_out.close();

	sparse_matrix<int> imagen("binary_triangle.txt");
	std::cout << imagen << std::endl;
}
