#include <iostream>
#include <stdexcept>
#include <new>
int func(int a ,int b ){
	int** c = new int* [b];
	int allocated=0;
	try{
		for (;allocated<b;allocated++){
			c[allocated]= new int[a];
	}
	}
	catch(const std::bad_alloc&){
		for (int l=0;l<allocated;l++){
			delete[] c[l];
		}
		delete[] c;
		throw;
	}
	for (int j=0;j<a;j++){
		for (int k=0;k<b;k++){
			std::cin >> c[k][j];
			if (std::cin.fail()){
				for (int perem=0;perem<b;perem++){
					delete[] c[perem];
}
				delete[] c;
				throw 1;
}
		}
	}
	std::cout << "\n";
	for (int sh=0;sh<b;sh++){
		for (int kh=0;kh<a;kh++){
			std::cout << c[sh][kh] << " ";
		}
		std::cout << "\n";
	}
	for (int n=0;n<b;n++){
		delete[] c[n];
	}
	delete[] c;
	return 0;
}
int main(){
	try{
	int m=0, n=0;
	std::cin >> m >> n;
	if (n<0 || m<0){
		throw 1;
	}
	if (std::cin.fail()){
		std::cerr << "Error 1" << "\n";
		return 1;
	}

		int yo=func(m,n);
	}
	catch (int err){
		std::cerr << "Error 1" << "\n";
		return 1;
		}
	catch (const std::bad_alloc){
		std::cerr << "Error 2" << "\n";
		return 2;	
	}
	return 0;
}
