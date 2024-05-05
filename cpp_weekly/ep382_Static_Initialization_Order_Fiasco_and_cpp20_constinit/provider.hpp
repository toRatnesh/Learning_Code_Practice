
#ifndef PROVIDER_HPP
#define PROVIDER_HPP

#include <string_view>

class Provider {
    std::string_view m_data{"Provider data"};
    public:
    constexpr Provider();
    std::string_view data() const ;

};

/*
    global, non-const variable that is "constant initialized"
    which means, initialized strongly before any dynamic code is executed
    (that is, at compile-time)

    this is just validating my assumptions since it had a constexpr constructor
    it would have been constant initialized anyhow
*/

extern constinit Provider provider;

#endif


