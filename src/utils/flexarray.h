#ifndef FLEX_ARRAY_H
#define FLEX_ARRAY_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

template<class T>
class FlexArray
{
private:
    int arraySize;
    T* memory;
public:
    FlexArray() : arraySize(0), memory(new T[0])
    {
    }

    FlexArray(int arraySize) : arraySize(arraySize)
    {
        if(arraySize < 0)
        {
            throw std::invalid_argument("Bad input: size must be greater or equal to 0.");
        }
     //   std::cout << arraySize << std::endl;
        memory = new T[arraySize];
      //  std::cout << "allocated:" << sizeof(T) * arraySize << "bytes" << std::endl;
    }

    FlexArray(std::initializer_list<T> parameters) : arraySize(parameters.size()), memory(new T[parameters.size()])
    {
        int index = 0;
        for(auto it = parameters.begin(); it != parameters.end(); it++)
        {
            memory[index] = *it;
            index++;
        }
    }

    FlexArray(const FlexArray<T> &other)
    {
        this->arraySize = other.arraySize;
        this->memory = new T[arraySize];
        for(int i = 0; i < arraySize; i++)
        {
            memory[i] = T(other.memory[i]);
        }
    }

    T* getRawArray()
    {
        return this->memory;
    }

    T& operator[](const int position)
    {
        if(position >= arraySize || position < 0)
        {
            /*
            std::stringstream ss;
            std::cout << arraySize << std::endl;
            std::cout << position << std::endl;
            char vals[] = "Index of ";
            char vals2[] = " is out of range for FlexArray of size ";
            ss << 3;
            ss << vals;
            ss << position;
            ss << vals2;
            ss << arraySize;
            std::string val = ss.str();
            */
            throw std::out_of_range("out of bounds");
        }
        return memory[position];
    }

    T& at(const int &position)
    {
        if(position >= arraySize || position < 0)
        {
            //std::stringstream ss;
            //ss << "Index of " << position << " is out of range for FlexArray of size " << arraySize;
            throw std::out_of_range("out of bounds");
        }
        return memory[position];
    }

    FlexArray& operator=(const FlexArray &otherArray)
    {
        FlexArray other(otherArray);
        std::swap(arraySize, other.arraySize);
        std::swap(memory, other.memory);
        return *this;
    }


    std::string str()
    {
        std::stringstream ss;
        ss << '[';
        for(int i = 0; i < arraySize; i++)
        {
            ss << memory[arraySize];
            if(i != arraySize - 1)
            {
                ss << ", ";
            }
        }
        ss << ']';
        return ss.str();
    }

    int size() const
    {
        return this->arraySize;
    }

    ~FlexArray()
    {
        if(memory)
        {
            delete[] memory;
        }
    }
};

template<class T>
class Flex2D
{
private:
    int dimension1;
    int dimension2;
    T* memory;
public:
    Flex2D() : dimension1(0), dimension2(0), memory(new T[0])
    {
    }

    Flex2D(int dimension1, int dimension2) : dimension1(dimension1), dimension2(dimension2)
    {
        if(dimension1 < 0 || dimension2 < 0)
        {
            throw std::invalid_argument("Illegal dimensions: dim1, dim2 values must be >= 0");
        }
        memory = new T[dimension1 * dimension2];
    }

    Flex2D(const Flex2D<T> &other)
    {
        this->dimension1 = other.dimension1;
        this->dimension2 = other.dimension2;
        this->memory = new T[other.dimension1 * other.dimension2];
        for(int i = 0; i < other.dimension1 * other.dimension2; i++)
        {
            memory[i] = T(other.memory[i]);
        }
    }

    T* getRawArray()
    {
        return this->memory;
    }

    /*
    T& operator[](const int dim1, const int dim2)
    {
        if(dim1 >= this->dimension1 || dim1 < 0 || dim2 < 0 || dim2 >= this->dimension2)
        {
            / *
            std::stringstream ss;
            std::cout << arraySize << std::endl;
            std::cout << position << std::endl;
            char vals[] = "Index of ";
            char vals2[] = " is out of range for FlexArray of size ";
            ss << 3;
            ss << vals;
            ss << position;
            ss << vals2;
            ss << arraySize;
            std::string val = ss.str();
            * /
            throw std::out_of_range("out of bounds");
        }
        return memory[position];
    }
    */

    Flex2D& operator=(const Flex2D &otherArray)
    {
        Flex2D other(otherArray);
        std::swap(dimension1, other.dimension1);
        std::swap(dimension2, other.dimension2);
        std::swap(memory, other.memory);
        return *this;
    }

    T& at(const int &dim1, const int &dim2)
    {
        if(dim1 >= this->dimension1 || dim1 < 0 || dim2 < 0 || dim2 >= this->dimension2)
        {
            //std::stringstream ss;
            //ss << "Index of " << position << " is out of range for FlexArray of size " << arraySize;
            throw std::out_of_range("out of bounds");
        }
        return memory[dim1 * dimension2 + dim2];
    }

    std::string str()
    {
        /*
        std::stringstream ss;
        ss << '[';
        for(int i = 0; i < arraySize; i++)
        {
            ss << memory[arraySize];
            if(i != arraySize - 1)
            {
                ss << ", ";
            }
        }
        ss << ']';
        return ss.str();
        */
        return "Flex2D";
    }

    int size() const
    {
        return this->dimension1;// * this->dimension2;
    }

    int dim1()
    {
        return this->dimension1;
    }

    int dim2()
    {
        return this->dimension2;
    }

    ~Flex2D()
    {
        delete[] memory;
    }
};

template<class T>
FlexArray<T> make1DFlex(std::vector<T> val, int size = -1)
{
    FlexArray<T> flex(((size >= 0) ? size : val.size()));
    for(unsigned int i = 0; i < val.size(); i++)
    {
        flex[i] = val[i];
    }
    return flex;
}

/**
 * Deep copies the FlexArray provided into a std::vector. By deep copy this means that the copy constructor of all elements in
 * the FlexArray will be called.
 */
template<class T>
std::vector<T> toVector(FlexArray<T> &a)
{
    std::vector<T> vec;
    // TODO - optimize this by reducing copies.
    for(int i = 0; i < a.size(); i++)
    {
        vec.push_back(T(a[i]));
    }
    return vec;
}

#endif

