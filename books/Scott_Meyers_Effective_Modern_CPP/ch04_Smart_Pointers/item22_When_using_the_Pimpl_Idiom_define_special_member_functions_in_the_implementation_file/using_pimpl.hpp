/*****
    Header file should contain only declaration  of the class
    that uses Pimpl idiom
**********/

#ifndef USING_PIMPL_HPP
#define USING_PIMPL_HPP

#include <memory>
#include "data.hpp"

class PimplUsingSharedPtr {
    struct Impl;
    std::shared_ptr<Impl>   m_pimpl;

    public:
    PimplUsingSharedPtr();
    PimplUsingSharedPtr(const St & st);
    // compiler generated compiler will do shallow copy
};


class PimplUsingUniquePtr {
    struct Impl;
    std::unique_ptr<Impl>   m_pimpl;

    public:
    PimplUsingUniquePtr();
    PimplUsingUniquePtr(const St & st);

    // when using unique pointer we need to define our own special member functions 
    ~PimplUsingUniquePtr();

    PimplUsingUniquePtr(PimplUsingUniquePtr && other);
    PimplUsingUniquePtr& operator=(PimplUsingUniquePtr && other);

    PimplUsingUniquePtr(const PimplUsingUniquePtr & other);
    PimplUsingUniquePtr& operator=(const PimplUsingUniquePtr & other);

};

#endif

/*****
    END OF FILE
**********/

