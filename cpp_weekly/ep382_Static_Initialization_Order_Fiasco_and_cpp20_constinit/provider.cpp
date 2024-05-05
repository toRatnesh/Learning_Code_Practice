
#include "provider.hpp"

constexpr Provider::Provider(){  }

std::string_view Provider::data() const { 
    return m_data; 
}

constinit Provider provider;
