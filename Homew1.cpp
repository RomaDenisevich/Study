#include <iostream>
#include <stdexcept>
int func(int a,int b){
	int** c = new int* [b];
	for (int v=0;v<b;v++){
		c[v]= new int[a];
	}
	for (int j=0;j<a;j++){
		for (int k=0;k<b;k++){
			std::cin >> c[k][j];
			if (std::cin.fail()){
				throw 1;
			}
		}
	}
	for (int sh=0;sh<b;sh++){
		for (int kh=0;kh<a;kh++){
			std::cout << c[sh][kh];
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
	int m=0, n=0;
	std::cin >> m >> n;
	if (std::cin.fail()){
		std::cerr << "Error 1" << "\n";
		return 1;
	}
	try{
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
