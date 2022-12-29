/********************

References:
        C++17 - The Complete Guide | Nicolai M. Josuttis

13. Placeholder Types like auto as Template Parameters

13.3 Using decltype(auto) as Template Parameter
    decltype(auto) can be used as template parameter
    
    According to decltype, 
    if expressions instead of names are passed, it deduces the type according to the value category of the expression:
    •   type for a prvalue (e.g., temporaries)
    •   type& for an lvalue (e.g., objects with names)
    •   type&& for an xvalue (e.g., objects casted to rvalue-references, as with std::move()

	NOTE: This program requires g++ version > 12.1

*********************/

#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <cstring>

template<decltype(auto) val>
struct TemplateWithDecltypeAuto {
    void display() { std::clog << "value is : " << val << '\n'; }
};

template<auto val>
struct TemplateWithAuto {
    void display() { std::clog << "value is : " << val << '\n'; }
};

// declare a constant variable of an arbitrary type
template<decltype(auto) val>
constexpr decltype(auto) gval = val;

char gcarr[] = "global char array";

int g_val = 5;
const int cg_val = 7;

int main() {
    
    {
        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        TemplateWithDecltypeAuto<3> t_int;              t_int.display();
        TemplateWithDecltypeAuto<'A'> t_char;           t_char.display();
        TemplateWithDecltypeAuto<true> t_bool;          t_bool.display();
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        TemplateWithAuto<3> t_int;             t_int.display();
        TemplateWithAuto<'A'> t_char;          t_char.display();
        TemplateWithAuto<true> t_bool;         t_bool.display();
        }
        
        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        TemplateWithDecltypeAuto<cg_val> t_cgval;       t_cgval.display();  // 7
        TemplateWithDecltypeAuto<(cg_val)> t_cgval2;    t_cgval2.display(); // &cg_val
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        TemplateWithAuto<cg_val> t_cgval;      t_cgval.display();  // 7
        TemplateWithAuto<(cg_val)> t_cgval2;   t_cgval2.display(); // 7
        }

        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        const int l_cval = 11;
        TemplateWithDecltypeAuto<l_cval> t_lcval;       t_lcval.display();
        //TemplateWithDecltypeAuto<(l_cval)> t_lcval2;  t_lcval2.display(); // error: the address of 'l_cval' is not a valid template argument because it does not have static storage duration
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        const int l_cval = 11;
        TemplateWithAuto<l_cval> t_lcval;      t_lcval.display();
        TemplateWithAuto<(l_cval)> t_lcval2;   t_lcval2.display(); // no compilation error 
        }

        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        static const int l_sval = 13;
        TemplateWithDecltypeAuto<l_sval> t_lsval;       t_lsval.display();  // 13
        TemplateWithDecltypeAuto<(l_sval)> t_lsval2;    t_lsval2.display(); // &l_sval
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        static const int l_sval = 13;
        TemplateWithAuto<l_sval> t_lsval;      t_lsval.display();  // 13
        TemplateWithAuto<(l_sval)> t_lsval2;   t_lsval2.display(); // 13
        }

        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        TemplateWithDecltypeAuto<gcarr> t_gcarr;        t_gcarr.display();  // &gcarr
        memset(gcarr, 0, sizeof(gcarr));
        strncpy(gcarr, "upd_g char array", sizeof(gcarr)-1);
        t_gcarr.display();
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        TemplateWithAuto<gcarr> t_gcarr;       t_gcarr.display();  // &gcarr
        memset(gcarr, 0, sizeof(gcarr));
        strncpy(gcarr, "upd_g char array", sizeof(gcarr)-1);
        t_gcarr.display();
        }

        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        static char l_sarr[] = "static local char array";
        TemplateWithDecltypeAuto<l_sarr> t_lsarr;       t_lsarr.display();
        memset(l_sarr, 0, sizeof(l_sarr));
        strncpy(l_sarr, "upd_ls char array", sizeof(l_sarr)-1);
        t_lsarr.display();
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        static char l_sarr[] = "static local char array";
        TemplateWithAuto<l_sarr> t_lsarr;      t_lsarr.display();
        memset(l_sarr, 0, sizeof(l_sarr));
        strncpy(l_sarr, "upd_ls char array", sizeof(l_sarr)-1);
        t_lsarr.display();
        }
        
        {
        std::clog << "=== Using decltype(auto) as Template Parameter \n";
        [[maybe_unused]] static char l_sarr[] = "static local char array";
        //TemplateWithDecltypeAuto<std::move(l_sarr)> t_lsarr;       t_lsarr.display(); // error: 'char (&&)[24]' is not a valid type for a template non-type parameter
        }
        {
        std::clog << "=== Using auto as Template Parameter \n";
        static char l_sarr[] = "static local char array";
        TemplateWithAuto<std::move(l_sarr)> t_lsarr;      t_lsarr.display();
        memset(l_sarr, 0, sizeof(l_sarr));
        strncpy(l_sarr, "upd_ls char array", sizeof(l_sarr)-1);
        t_lsarr.display();
        }
        
        /*
        int l_val = 9;
        TemplateWithDecltypeAuto<l_val> t_lval;        t_lval.display(); // error: the value of 'l_val' is not usable in a constant expression
        TemplateWithDecltypeAuto<g_val> t_gval;        t_gval.display(); // error: the value of 'g_val' is not usable in a constant expression
        */

    }

    {
        std::clog << "=== declare a constant variable of an arbitrary type deduced from its initial value\n";
        
        auto v_int      = gval<5>;
        static_assert(std::is_same_v<decltype(v_int), int>);
        static_assert(std::is_same_v<decltype(gval<5>), const int>);

        auto v_char     = gval<'A'>;
        static_assert(std::is_same_v<decltype(v_char), char>);
        static_assert(std::is_same_v<decltype(gval<'A'>), const char>);
        
        auto v_bool     = gval<true>;
        static_assert(std::is_same_v<decltype(v_bool), bool>);
        static_assert(std::is_same_v<decltype(gval<true>), const bool>);
        
        auto v_carr1    = gval<gcarr>;
        static_assert(std::is_same_v<decltype(v_carr1), char *>);
        static_assert( ! std::is_same_v<decltype(gval<gcarr>), const char *>);
        static_assert(std::is_same_v<decltype(gval<gcarr>), char * const>);

        static char lcarr[]    = "local static char array";
        auto v_carr2    = gval<lcarr>;
        static_assert(std::is_same_v<decltype(v_carr2), char *>);
        static_assert( ! std::is_same_v<decltype(gval<lcarr>), const char *>);
        static_assert(std::is_same_v<decltype(gval<lcarr>), char * const>);

        /*  FOOLLWING ARE NOT VALID TEMAPLE NON-TYPE PARAMETERS

        char lcarr[]    = "local char array";
        auto v_carr2    = gval<lcarr>;
        auto v2 = gval<5.3>; // 'double' is not a valid type for a template non-type parameter
        
        */
    }

    return 0;
}

/*******
    END OF FILE
*********/
