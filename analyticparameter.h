/***
 *
 *
 * the class is desigen to parse query_string from url query
 * author zhouxiang
 * date 2014/12/09
 * Tag V0.0.1
 *
 *
 *
 *
  ***/
#ifndef ANALYTICPARAMETER_H
#define ANALYTICPARAMETER_H

#include <exception>
#include <functional>
#include <algorithm>

#include "typedefs.h"


#define NOCOPYANDASSIGNMENT(CLASS) \
    private: \
    CLASS(const CLASS&); \
    CLASS& operator=(const CLASS&) \




///
/// \brief The BadParameter class
///
class BadParameter : public std::exception
{
public:
    BadParameter(const std::string& val_):
        m_content(val_)
    {

    }
    ~BadParameter() throw()
    {

    }

    const char* what() const throw()
    {

        return m_content.c_str();
    }
private:
    std::string m_content;
};

template <typename T>
class ParameterAnalytic;


template <typename T>
///
/// \brief The ParametersValues class
/// a template class to describe parameter-values
///
class ParametersValues
{
    friend class ParameterAnalytic<ParametersValues<T> >;
    template <typename N>
    friend ParametersValues<N>& operator <<(ParametersValues<N>& pv_, const std::string& para_);
public:
    typedef std::string type_parameter;
    typedef T type_value;
    typedef T& type_ref_value;
    typedef const T& type_const_ref_value;
    typedef std::pair<std::string, T> type_paraPair;
    typedef std::vector<type_paraPair> type_Container;
    ParametersValues();
    ParametersValues(const StringList& parameters_);
    const T& operator[](const std::string& para_) const;
    void clear() {m_VectorParaValue.clear();}
    void insert(const type_paraPair& p_)
    {
        m_VectorParaValue.push_back(p_);
    }

    NOCOPYANDASSIGNMENT(ParametersValues);
private:
    type_Container m_VectorParaValue;
};

template <typename T>
ParametersValues<T>& operator<<(ParametersValues<T>& pv_, const std::string& para_)
{
    typename ParametersValues<T>::type_paraPair _t = {para_, T()};
    pv_.m_VectorParaValue.push_back(_t);
    return pv_;
}

template <typename T>
ParametersValues<T>::ParametersValues()
{

}


template <typename T>
ParametersValues<T>::ParametersValues(const StringList& parameters_)
{
    for (StringList::const_iterator _ite = parameters_.begin(); _ite != parameters_.end(); ++_ite)
    {
        (*this) << (*_ite);
    }
}

template <typename T>
const T& ParametersValues<T>::operator [](const std::string& para_) const
{
    for (typename type_Container::const_iterator _ite = m_VectorParaValue.begin(); _ite != m_VectorParaValue.end(); ++_ite)
    {
        if ((*_ite).first == para_)
        {
            return (*_ite).second;
        }
    }
    throw BadParameter(para_ + " is a bad parameter!!!");
}


template <typename T>
///
/// \brief The ParameterAnalytic class
/// a class pares string to T, T is a real ParametersValues
///
class ParameterAnalytic
{
public:
    typedef T type_value;
    typedef std::function<typename type_value::type_const_ref_value(const std::string&,
                                                                    const std::string&)> do_parse;
    typedef std::function<void(const std::string&, type_value&)> do_fast_parse;
    template <typename N>
    friend ParameterAnalytic<N>& operator <<(ParameterAnalytic<N>& pa_, const std::string& para_)
    {
        pa_.m_ParaVals << para_;
        return pa_;
    }

    ParameterAnalytic() {}
    ParameterAnalytic(const StringList& paras_):m_ParaVals(paras_)
    {

    }

    const T& get_result() const
    {
        return m_ParaVals;
    }
    const T& get_result()
    {
        return m_ParaVals;
    }
    ///
    /// \brief analytic
    ///根据指定的参数解析其值
    void analytic();
    ///
    /// \brief fast_analytic
    ///不指定parameter,直接解析全部的参数和值
    void fast_analytic();
    void resetParameterStr(const std::string& str_)
    {
        m_paravalsBuffer = str_;
    }
    void registerParse(const do_parse& functional_)
    {
        m_doParseFunctional = functional_;
    }
    void registerFastParse(const do_fast_parse& functional_)
    {
        m_doParseFastFunctional = functional_;
    }

    void clear()
    {
        m_ParaVals.clear();
    }

    NOCOPYANDASSIGNMENT(ParameterAnalytic);
private:
    std::string m_paravalsBuffer;
    T m_ParaVals;
    do_parse m_doParseFunctional;
    do_fast_parse m_doParseFastFunctional;
};

template <typename T>
void ParameterAnalytic<T>::analytic()
{
    for_each(m_ParaVals.m_VectorParaValue.begin(), m_ParaVals.m_VectorParaValue.end(),
             [](typename T::type_paraPair& t){t.second.clear();});
    for (typename T::type_Container::iterator _ite = m_ParaVals.m_VectorParaValue.begin();
         _ite != m_ParaVals.m_VectorParaValue.end(); ++_ite)
    {
        (*_ite).second = m_doParseFunctional(m_paravalsBuffer, (*_ite).first);
    }
}

template <typename T>
void ParameterAnalytic<T>::fast_analytic()
{
    for_each(m_ParaVals.m_VectorParaValue.begin(), m_ParaVals.m_VectorParaValue.end(),
             [](typename T::type_paraPair& t){t.second.clear();});
    try
    {
        m_doParseFastFunctional(m_paravalsBuffer, m_ParaVals);
    }catch(const std::exception &ex)
    {
        throw ex;
    }
}



#endif // ANALYTICPARAMETER_H
