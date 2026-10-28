#include <iostream>
#include <stdexcept>
#include <new>
#include <cstddef>
#include <algorithm>
int** concat_rows(const int* const * lhs,size_t n1,size_t m1,const int* const * rhs,size_t n2,size_t m2) {
	if (rhs == nullptr || lhs == nullptr) {
		throw std::invalid_argument("rhs or lhs is a nullptr");
	}
	for (size_t i=0;i<n1;i++) {
		if (lhs[i] == nullptr) {
			throw std::invalid_argument("hey");
		}
	}
	for (size_t j=0;j<n2;j++) {
		if (rhs[j] == nullptr) {
			throw std::invalid_argument("yo");
		}
	}
	size_t column = 0;
	size_t low = 0;
	size_t str = 0;
	if (n1>=n2) {
		str = n1;
		low = n2;
		column = m1;
	}
	else  {
		str = n2;
		low = n1;
		column = m2;
	}
	int** result = nullptr;
	result = new int* [str];
	size_t much1 = 0;
	try {
		for (size_t k=0;k<low;k++,much1++) {
			result[k] = new int [m1+m2];
		}
	}
	catch (std::bad_alloc&) {
		free_matrix(result,much1);
		throw;
	}
	size_t much2=0;
	try {
		for (size_t p=low;p<str;p++,much2++) {
			result[p] = new int [column];
		}
	}
	catch(std::bad_alloc&) {
		size_t N = low+much2;
		free_matrix(result,N);
		throw;
	}
	for (size_t i=0;i<n1;i++) {
		for (size_t j=0;j<m1;j++) {
			result[i][j] = lhs[i][j];
		}
	}
	for (size_t i=0;(i<low && i<n2);i++) {
		for (size_t j = 0,p = m1;(j<m2 && p<(m1+m2));j++,p++) {
			result[i][p]=rhs[i][j];	
		}
	}
	if (str==n2) {
		for (size_t i=low;i<str;i++) {
			for (size_t j=0;j<m2;j++) {
				result[i][j]=rhs[i][j];
			}
		}
	}
	return result;
}
void free_matrix (int** h,size_t l) {
	if (h==nullptr) {
		return;
	}	
	for (size_t i=0;i<l;i++) {
		delete[] h[i];
	}	
	delete[] h;
}
int main () {
	size_t enumenator = 0;
	int Invalid_input = 1, Memory_cant = 2;
	size_t N1=0,M1=0,N2=0,M2=0;
		if (!(std::cin >> N1 >> M1 >> N2 >> M2)) {
			throw std::invalid_argument("Incorrect input");
		}
	}
	catch (std::invalid_argument&) {
		return Invalid_input;
	}
	int** first = new int* [N1];
	int** second = new int* [N2];
	try {
	for (size_t i=0;i<N1;i++) {
		first[i]=new int [M1];
		enumenator++;
		for (size_t j=0;j<M1;j++) {
			if (!(std::cin >> first[i][j])) {
				throw std::future_error("1");
			}
		}
	}
	enumenator = 0;
	for (int i=0;i<N2;i++) {
		second[i] = new int [M2];
		enumenator++;
		for (int j=0;j<M2;j++) {
			if(!(second[i][j])) {
				throw std::future_error("2");
			}
		}
	}
	} catch (std::future_error& e) {
		if (e.what()[0]== "1") {
			free_matrix(first,enumenator);
			std::cerr << "Wrong data";
			return 1;
		}
		free_matrix(second,enumenator);
	}
	int** massive = nullptr;
	try {
		massive = concat_rows(first,N1,M1,second,N2,M2);
		free_matrix(first,N1);		
		free_matrix(second,N2);
		return 0;
	}
	catch (std::invalid_argument&) {
		std::cerr << "wrong data";
		free_matrix(first,N1);
		free_matrix(second,N2);
		return 2;
	}	
	catch (std::bad_alloc&) {
		std::cerr << "too big numbers";
		return 1;
	}
	return 0;
}

