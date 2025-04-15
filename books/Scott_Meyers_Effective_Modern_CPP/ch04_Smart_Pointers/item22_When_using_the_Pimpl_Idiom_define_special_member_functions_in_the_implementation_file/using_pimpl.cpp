/*****
    Source file should contain the implementation of the class using Pimpl idiom
**********/


#include "using_pimpl.hpp"

struct PimplUsingSharedPtr::Impl {
    St  mst;

    Impl() { }
    Impl(const St & st) : mst(st) { }
};


PimplUsingSharedPtr::PimplUsingSharedPtr() 
    : m_pimpl(std::make_shared<Impl>()) { }

PimplUsingSharedPtr::PimplUsingSharedPtr(const St & st) 
    : m_pimpl(std::make_shared<Impl>(st)) { }



//=========== Using unique pointer ================


struct PimplUsingUniquePtr::Impl {
    St  mst;

    Impl() { }
    Impl(const St & st) : mst(st) { }
};

PimplUsingUniquePtr::PimplUsingUniquePtr() 
    : m_pimpl(std::make_unique<Impl>()) { }

PimplUsingUniquePtr::PimplUsingUniquePtr(const St & st) 
    : m_pimpl(std::make_unique<Impl>(st)) { }


PimplUsingUniquePtr::~PimplUsingUniquePtr()     = default;

PimplUsingUniquePtr::PimplUsingUniquePtr(PimplUsingUniquePtr && other)               = default;
PimplUsingUniquePtr& PimplUsingUniquePtr::operator=(PimplUsingUniquePtr && other)    = default;

PimplUsingUniquePtr::PimplUsingUniquePtr(const PimplUsingUniquePtr & other) 
    : m_pimpl(std::make_unique<Impl>(*(other.m_pimpl))) { }

PimplUsingUniquePtr& PimplUsingUniquePtr::operator=(const PimplUsingUniquePtr & other) {
    if(this != &other) {
        *m_pimpl = *(other.m_pimpl);
    }
    return *this;
}

/*****
    END OF FILE
**********/

