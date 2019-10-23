# CS2100-Esparza
#CS2100/groups


## Work
Realizar la implementación de una matriz esparza.  Usando vector y listas circulares.  

## Example Code
```
template <class T>
class Node {
      public:
             T data;
             int posX;
             int posY;
             Node<T>* next;
             Node<T>* down;
};

template <class T>
class SparseMatrix {
      private:
              Node<T>* x;
              Node<T>* y;
              int columns;
              int rows;
};

```



## Mandatory: (20pts)  and Extra: (4pts c/u)
	
```
int main( int, char * []) 
{
    Matrix<double> m1;
    m1 << (2,0,0) << (8,0,1) << (6,1,0) << (100,2,20);  // Insert
    cout << m1 << endl; // print in console
    m1 >> (100,2,20); // delete
    
    Matrix<double> m2 = Matrix<double>::identity(100,100); 
    ofstream _out("res.txt");
    _out << m2 << endl; // print in file
    _out.close();

    cout << mult(m1 * m2) << endl; //  mutiplication
    cout << add(m1 + m2) << endl; // addition
    cout << transpose(m1) << endl; // transpose

    cout << inv(m1 * m2) << endl; // Inversa - Extra!     

	  // Cargar desde imagen -  Extra (Usar CImg.h)
    Matrix<double> m_image = load_from_image("myimage.jpg");
    m_image = transpose(m_image;
    ofstream _out_i("res.txt");
    _out_i << m_image;
    _out_i.close()

    return 1;
}

```



## Tooling
	* Lenguaje C++
	* Git + GitFlow + Karma Comments
	* Branch per Developer
	* Si el código no compila se calificara sobre 11.
	* Evitar warnings 
	* Código limpio -> _Keep it short and simple_. 

## Help!
	* Usemos el canal de Slack!   (https://bit.ly/2LYbIbh)

