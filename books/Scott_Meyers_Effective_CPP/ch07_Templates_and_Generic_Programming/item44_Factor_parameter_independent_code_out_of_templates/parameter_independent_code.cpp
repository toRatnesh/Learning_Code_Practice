/*****

Chapter 7: Templates and Generic Programming

	Generic programming — the ability to write code that is independent of the types of objects being manipulated

	It can be used to compute any computable value. That led to template metaprogramming: the creation of programs 
	that execute inside C++ compilers and that stop running when compilation is complete.


Item 44: Factor parameter-independent code out of templates

	If you’re not careful, using templates can lead to code bloat: 
	binaries with replicated (or almost replicated) code, data, or both.
	
	In template code, replication is implicit: there’s only one copy of the template source code, 
	so you have to train yourself to sense the replication that may take place when a template is instantiated multiple times.
	
	Consider following example
	
	template<typename T,		// template for n*n matrices of objects of type T
	std::size_t n>
	class SquareMatrix {
		public:
		...
		void invert();			// invert the matrix in place
	};
	
	for a type i.e. int, invert() will be instantiated for different n values
	but other than the constant n, the two functions will be the same
	
	This is a classic way for template-induced code bloat to arise.
	
	
	Now conider following code
	
	template<typename T>		// size-independent base class for
	class SquareMatrixBase {	// square matrices
		protected:
		...
		void invert(std::size_t matrixSize);	// invert matrix of the given size (do not inline it)
		
		//	If it’s inlined, each instantiation of SquareMatrix::invert will get a copy of 
		//	SquareMatrix-Base::invert’s code, leading to object code replication.)
		
		...
	};
	
	template<typename T, std::size_t n>
	class SquareMatrix: private SquareMatrixBase<T> {
	
		//	inheritance between SquareMatrix and SquareMatrixBase is private
		//	base class is only to facilitate the derived classes’ implementations, not to express a conceptual is-a relationship
	
		private:
		using SquareMatrixBase<T>::invert;		// make base class version of invert visible in this class;
		public:
		...
		void invert() { invert(n); } // make inline call to base class  version of invert
	};

	SquareMatrixBase is templatized only on the type of objects in the matrix, not on the size of the matrix.
	Hence, all matrices holding a given type of object will share a single SquareMatrixBase class. 
	They will thus share a single copy of that class’s version of invert.


    How does SquareMatrixBase::invert know what data to operate on?
    How does the derived class communicate that to the base class so that the base class can do the inversion?
    SquareMatrixBase store a pointer to the memory for the matrix values. 
    And as long as it’s storing that, it might as well store the matrix size, too.

	type parameters can lead to bloat, too
	For example, 
	on many platforms, int and long have the same binary representation, so the member functions for, 
	say, vector<int> and vector<long> would likely be identical — the very definition of bloat

	on most platforms, all pointer types have the same binary representation, so templates 
	holding pointer types (e.g., list<int*>, list<const int*>, list<SquareMatrix<long, 3>*>, etc.) 
	should often be able to use a single underlying implementation for each member function
	
Summary:

	. any template code not dependent on a template parameter causes bloat.
	. Bloat due to non-type template parameters can often be eliminated by 
	  replacing template parameters with function parameters or class data members.
	. Bloat due to type parameters can be reduced by sharing implementations for 
	  instantiation types with identical binary representations.

**********/

#include <iostream>
#include <string>
#include <memory>
#include <array>

//#define LOGINFO std::cout << "[" << __FILE__ << ' ' << __LINE__ << ' ' << __func__ << "] ";
#define LOG(msg) std::cout << msg;

template<typename T, std::size_t N> 
class SquareMatrix {
    std::array<T, N*N>    m_data{0};
    std::size_t         index(std::size_t r, std::size_t c) { return ((r -1) * N)  + (c-1); }
    public:
    void set(std::size_t r, std::size_t c, T val) {
        m_data[index(r, c)] = val;
    }
    void display() {
        for(std::size_t i = 1; i <= N; ++i) {
            for(std::size_t j = 1; j <= N; ++j) {
                std::cout << m_data[index(i, j)] << ' ';
            }
            std::cout << '\n';
        }
    }
};





template<typename T> 
class MatrixBase {
    T * m_data = nullptr;
	std::size_t		m_data_size;
	std::size_t		m_r, m_c;

    protected:
	//MatrixBase(std::size_t r, std::size_t c, T * data, std::size_t data_size) : 
	//	m_data{data}, m_data_size{data_size}, m_r{r}, m_c{c} { };

	MatrixBase(std::size_t r, std::size_t c) : m_r{r}, m_c{c} { };		

	void initData(T * data, std::size_t data_size) {
		m_data		= data;
		m_data_size	= data_size;
	}

	std::size_t         index(std::size_t r, std::size_t c) { return ((r -1) * m_c)  + (c-1); }

    void set(std::size_t r, std::size_t c, T val) {
        m_data[index(r, c)] = val;
    }

    void display() {
        for(std::size_t i = 1; i <= m_r; ++i) {
            for(std::size_t j = 1; j <= m_c; ++j) {
                std::cout << m_data[index(i, j)] << ' ';
            }
            std::cout << '\n';
        }
    }
};

template<typename T, std::size_t N> 
class ImprovedSquareMatrix : private MatrixBase<T> {
    std::array<T, N*N>    m_data{0};
    public:
	ImprovedSquareMatrix() : MatrixBase<T>(N, N) {
		this->initData(m_data.data(), m_data.size());
	}

    void set(std::size_t r, std::size_t c, T val) {
        //m_data[MatrixBase<T>::index(r, c)] = val;
		MatrixBase<T>::set(r, c, val);
    }

	void display() {
		MatrixBase<T>::display();
	};
};



int main() {
	
	{	std::cout << "=== Using square matrix ===\n";
		{

			SquareMatrix<int, 3>    mat;
			mat.set(1, 1, 1);
			mat.set(1, 2, 2);
			mat.set(1, 3, 3);

			mat.set(2, 1, 4);
			mat.set(2, 2, 5);
			mat.set(2, 3, 6);

			mat.set(3, 1, 7);
			mat.set(3, 2, 8);
			mat.set(3, 3, 9);

			mat.display();			
		}
		std::cout << '\n';

		{

			SquareMatrix<int, 4>    mat;
			mat.set(1, 1, 1);
			mat.set(1, 2, 2);
			mat.set(1, 3, 3);

			mat.set(2, 1, 4);
			mat.set(2, 2, 5);
			mat.set(2, 3, 6);

			mat.set(3, 1, 7);
			mat.set(3, 2, 8);
			mat.set(3, 3, 9);

			mat.display();			
		}		
	}


	{	std::cout << "=== Using improved square matrix ===\n";
		{
			ImprovedSquareMatrix<int, 3>    mat;
			mat.set(1, 1, 1);
			mat.set(1, 2, 2);
			mat.set(1, 3, 3);

			mat.set(2, 1, 4);
			mat.set(2, 2, 5);
			mat.set(2, 3, 6);

			mat.set(3, 1, 7);
			mat.set(3, 2, 8);
			mat.set(3, 3, 9);

			mat.display();			
		}
		std::cout << '\n';

		{
			ImprovedSquareMatrix<int, 4>    mat;
			mat.set(1, 1, 1);
			mat.set(1, 2, 2);
			mat.set(1, 3, 3);

			mat.set(2, 1, 4);
			mat.set(2, 2, 5);
			mat.set(2, 3, 6);

			mat.set(3, 1, 7);
			mat.set(3, 2, 8);
			mat.set(3, 3, 9);

			mat.display();			
		}		
	}


    return 0;
}

/*****
    END OF FILE
**********/
