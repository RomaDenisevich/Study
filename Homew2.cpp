#include <iostream>
#include <stdexcept>
#include <new>
#include <cstddef>
#include <algorithm>
int** concat_rows(const int* const * lhs,size_t n1,size_t m1,const int* const * rhs,size_t n2,size_t m2) {
	if (rhs==nullptr || lhs==nullptr) {
		throw std::invalid_argument("rhs or lhs is a nullptr");
	}
	for (size_t i=0;i<n1;i++) {
		if (lhs[i]==nullptr) {
			throw std::invalid_argument("hey");
		}
	}
	for (size_t j=0;j<n2;j++) {
		if (rhs[j]==nullptr) {
			throw std::invalid_argument("yo");
		}
	}
	size_t column = 0;
	size_t low =0;
	size_t str=0;
	if (n1>=n2) {
		str=n1;
		low=n2;
		column=m1;
	}
	else  {
		str=n2;
		low=n1;
		column=m2;
	}
	int** result=nullptr;
	result = new int* [str];
	size_t much1=0;
	try {
		for (size_t k=0;k<low;k++,much1++) {
			result[k]=new int [m1+m2];
		}
	}
	catch (std::bad_alloc&) {
		for (size_t i=0;i<much1;i++) {
			delete[] result[i];
		}
		delete[] result;
		throw;
	}
	size_t much2=0;
	try {
		for (size_t p=low;p<str;p++,much2++) {
			result[p]=new int [column];
		}
	}
	catch(std::bad_alloc&) {
		for (size_t j=0;j<(low+much2);j++) {
			delete[] result[j];
		}
		delete[] result;
		throw;
	}
	for (size_t i=0;i<n1;i++) {
		for (size_t j=0;j<m1;j++) {
			result[i][j]=lhs[i][j];
		}
	}
	for (size_t i=0,o=0;(i<low && o<n2);i++,o++) {
		for (size_t j=0,p=m1;(j<m2 && p<(m1+m2));j++,p++) {
			result[i][p]=rhs[o][j];	
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
	size_t N1=3,M1=3,N2=4,M2=2;
	int** first = new int* [3];
	for (size_t i=0;i<3;i++) {
		first[i]=new int [3];
		for (size_t j=0;j<3;j++) {
			first[i][j]=1; 
		}
	}
	int** second = new int* [4];
	for (int i=0;i<4;i++) {
		second[i] = new int [2];
		for (int j=0;j<2;j++) {
			second[i][j]=3;
		}
	}
	int** massive = nullptr;
	try {
		massive = concat_rows(first,N1,M1,second,N2,M2);
		for (int i=0;i<3;i++) {
			std::cout << "\n";
			for (int j=0;j<5;j++) {
				std::cout << massive[i][j] << " ";
			}	
		}	
		std::cout << "\n";
		for (int j=0;j<2;j++) {
			std::cout << massive[3][j] << " ";
		}
		std::cout << "\n";
		free_matrix(massive,std::max(N1,N2));
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
	}
	free_matrix(massive,std::max(N1,N2));
	free_matrix(first,N1);
	free_matrix(second,N2);
	return 2;
}

