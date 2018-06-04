/*
*@file:    区间描述类
*@brief:
*@author   zhangh-t
*@date:    2017年7月7日
*@remarks
*@version 1.0
*/
#ifndef __VTINTERVAL_H
#define __VTINTERVAL_H
template <typename T>
class VTInterval {
    typedef VTInterval<T> VTIntervalImp;
public:
    VTInterval();
    VTInterval(T min, T max);
    VTInterval(const VTIntervalImp& other);
    VTInterval<T>& operator = (const VTIntervalImp& other);
    T operator [] (int index);
public:
    bool valid();
    bool intersected(const VTIntervalImp& other, T epsilon = 0);
    bool contains(const VTIntervalImp& other, T epsilon = 0);
    bool contains(T point, T epsilon = 0);
    VTInterval<T> intersection(const VTIntervalImp& other);
public:
    T m_Min;
    T m_Max;
};

template <typename T>
VTInterval<T>::VTInterval()
    :m_Min(0), m_Max(0)
{

}

template <typename T>
T VTInterval<T>::operator[](int index)
{
    if (index <= 0)
    {
        return m_Min;
    }
    else {
        return m_Max;
    }
}

template <typename T>
VTInterval<T> VTInterval<T>::intersection(const VTIntervalImp& other)
{
    if (intersected(other, 0))
    {
        return VTIntervalImp(m_Min > other.m_Min ? m_Min : other.m_Min,
            m_Max < other.m_Max ? m_Max : other.m_Max);
    }
    else {
        return VTIntervalImp(*this);
    }
}

template <typename T>
bool VTInterval<T>::contains(T point, T epsilon /*= 0*/)
{
    return point >= m_Min - epsilon && point <= m_Max + epsilon;
}

template <typename T>
bool VTInterval<T>::intersected(const VTIntervalImp& other, T epsilon)
{
    return contains(other.m_Min, epsilon) || contains(other.m_Max, epsilon);
}

template <typename T>
bool VTInterval<T>::valid()
{
    return this->m_Max > this->m_Min;
}

template <typename T>
VTInterval<T>& VTInterval<T>::operator=(const VTIntervalImp& other)
{
    this->m_Min = other.m_Min;
    this->m_Max = other.m_Max;
    return *this;
}

template <typename T>
VTInterval<T>::VTInterval(const VTIntervalImp& other)
{
    this->m_Min = other.m_Min;
    this->m_Max = other.m_Max;
}

template <typename T>
VTInterval<T>::VTInterval(T min, T max)
    :m_Min(min), m_Max(max)
{

}

typedef VTInterval<int> VTIntervali;
typedef VTInterval<double> VTIntervald;
#endif