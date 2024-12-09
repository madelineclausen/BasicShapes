#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

using namespace std;

template <typename T>

class Vector {

 private:
    size_t sz;
    T* buf;  

 public:
    Vector(size_t sz) 
    {
      this->buf = new T[sz];
      this->sz = sz;
    }

    Vector(initializer_list<T> L) 
    {
      this->buf = new T[L.size()];
      this->sz = L.size();
      int i = 0;
      for (auto it = L.begin(); it != L.end(); ++it, ++i) 
      {
        buf[i] = *it;
      }
    }

    ~Vector() 
    {
      delete[] buf;
    }

    Vector(const Vector & v) 
    {
      this->buf = new T[v.size()];
      this->sz = v.size();
      for (int i=0; i<v.size(); i++)
      {
        this->buf[i] = v[i];
      }
    }

    size_t size() const 
    {
      return sz;
    }

  T & operator [] (const int i) 
  {
    // MUST THROW ERROR IF OUT OF BOUNDS
    return this->buf[i];
  }

  T operator [] (const int i) const 
  {
    // MUST THROW ERROR IF OUT OF BOUNDS
    return this->buf[i];
  }

  T operator * (const Vector & v) const 
  {
    T total = 0;
    int vec_size;
    if (this->sz <= v.size())
    {
      vec_size = this->sz;
    }
    else
    {
      vec_size = v.size();
    }
    for (int i=0; i<vec_size; i++)
    {
      total += (this->buf[i] * v[i]);
    }
    return total;
  }

  Vector operator + (const Vector & v) const 
  {
    int vec_size;
    Vector<T> smallest = v;
    Vector<T> largest = v;
    if (this->sz <= v.size())
    {
      vec_size = this->sz;
      smallest = *this;
    }
    else
    {
      vec_size = v.size();
      largest = *this;
    }
    Vector<T> new_vec{largest};
    for (int i=0; i<vec_size; i++)
    {
      new_vec[i] = smallest[i] + largest[i];
    }
    for (int i=vec_size; i<new_vec.size(); i++)
    {
      new_vec[i] = largest[i];
    }
    return new_vec;
  }

  const Vector & operator = (const Vector & v) 
  {
    delete this->buf;
    this->buf = new T[v.size()];
    this->sz = v.size();
    for (int i=0; i<v.size(); i++)
    {
      this->buf[i] = v[i];
    }
    return *this;
  }

  bool operator == (const Vector & v) const 
  {
    if (this->sz != v.size())
    {
      return false;
    }
    else
    {
      for (int i=0; i<this->sz; i++)
      {
        if (this->buf[i] != v[i])
        {
          return false;
        }
      }
      return true;
    }
  }

  bool operator != (const Vector & v) const 
  {
    if (this->sz != v.size())
    {
      return true;
    }
    else
    {
      for (int i=0; i<this->sz; i++)
      {
        if (this->buf[i] != v[i])
        {
          return true;
        }
      }
      return false;
    }
  }

  inline friend Vector operator * (const int scale, const Vector & v) 
  {
    Vector<T> new_vec{v};
    for (int i=0; i<v.size(); i++)
    {
      new_vec[i] = scale * v[i];
    }
    return new_vec;
  }

  inline friend Vector operator + (const int adder, const Vector & v) 
  {
    Vector<T> new_vec{v};
    for (int i=0; i<v.size(); i++)
    {
      new_vec[i] = adder + v[i];
    }
    return new_vec; 
  }

  inline friend ostream& operator << (ostream & o, const Vector & v) 
  {
    string total_string = "(";
    for (int i=0; i<v.size()-1; i++)
    {
      total_string += to_string(v[i]) + ", ";
    }
    total_string += to_string(v[v.size()-1]) + ")";
    o << total_string;
    return o;
  }
};

#endif