#ifndef MATRIX_H_
#define MATRIX_H_

#include "matrix_utils.h"
#include "version.h"
#include <functional>
#include <map>
#include <utility>

namespace mtrx
{

template <
    class T,
    std::enable_if_t<(std::is_arithmetic_v<T>), int> default_value = 0>
class Matrix
{
private:
    std::map<std::pair<size_t, size_t>, T> values;
    int default_val;

public:
    Matrix() : values{}, default_val{default_value} {}
    Matrix(const Matrix& x) = delete;
    Matrix(Matrix &&x) = delete;
    ~Matrix() {}

    T value(const size_t index_i, const size_t index_j) const
    {
        if (values.find(std::make_pair(index_i, index_j)) != values.end())
            return values.at(std::make_pair(index_i, index_j));
        else
            return default_val;
    }

    bool set_value(const size_t index_i, const size_t index_j, T new_value)
    {
        auto temp_val = value(index_i, index_j);
        if (new_value == temp_val) return false;
        if (new_value == default_val) values.erase(std::make_pair(index_i,index_j));
        else values[std::make_pair(index_i,index_j)] = new_value;
        return true;
    }

    class MValue
    {
    
    template<class T1>
    friend std::ostream &operator<<(std::ostream &out, const T1 &val);

    private:
        size_t m_i;
        size_t m_j;
        Matrix &m_matrix;

    public:
        MValue(const size_t i, const size_t j, Matrix &m) : m_i{i}, m_j{j}, m_matrix{m} {}
        MValue(const MValue &x) : m_i{x.m_i}, m_j{x.m_j}, m_matrix{x.m_matrix} {}

        template <class Type>
        bool operator==(const Type x) const { return m_matrix.value(m_i, m_j) == x; }

        MValue &operator=(T new_val)
        {
            m_matrix.set_value(m_i, m_j, new_val);
            return *this;
        }
    };

    class MLine
    {
    private:
        size_t line;
        Matrix &m_matrix;

    public:
        MLine(size_t line_number, Matrix &m) : line{line_number}, m_matrix{m} {}

        MValue operator[](size_t index_j) { return MValue(line, index_j, m_matrix); }
    };

    MLine operator[](size_t index_i) { return MLine(index_i, *this); }

    size_t size() { return values.size(); }

    auto begin() {return values.begin();}
    auto end() {return values.end();}
};


template<class T1>
std::ostream &operator<<(std::ostream &out, const T1 &val)
{
    
    out << val.m_matrix.value(val.m_i, val.m_j);
    return out;
}

} // namespace mtrx

#endif /* MATRIX_H_ */
