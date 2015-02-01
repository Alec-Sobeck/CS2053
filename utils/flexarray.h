#ifndef FLEX_ARRAY_H
#define FLEX_ARRAY_H

#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdexcept>

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
        memory = new T[arraySize];
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

    T& operator[](const int &position)
    {
        if(position >= arraySize || position < 0)
        {
            std::stringstream ss;
            ss << "Index of " << position << " is out of range for FlexArray of size " << arraySize;
            throw std::out_of_range(ss.str());
        }
        return memory[position];
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
        delete[] memory;
    }
};

template<class T>
FlexArray<FlexArray<T>> make2DFlex(int dim1, int dim2)
{
    FlexArray<FlexArray<T>> flex(dim1);
    for(int i = 0; i < dim1; i++)
    {
        flex[i] = FlexArray<T>(dim2);
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

