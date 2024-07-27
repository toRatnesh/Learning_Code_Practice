/*****

ep433_cpp23_New_Floating_Point_Types

References
episode https://www.youtube.com/watch?v=YM1nbexgGYw
https://en.cppreference.com/w/cpp/types/floating-point


Fixed width floating-point types
Type name       Literal suffix  Predefined macro	    C language type                     Type properties
                                                                        bits of storage     bits of precision	bits of exponent	max exponent
std::float16_t  f16 or F16      __STDCPP_FLOAT16_T__	_Float16	        16	                11	                5	                15
std::float32_t	f32 or F32      __STDCPP_FLOAT32_T__	_Float32	        32	                24	                8	                127
std::float64_t	f64 or F64      __STDCPP_FLOAT64_T__	_Float64	        64	                53	                11	                1023
std::float128_t	f128 or F128	__STDCPP_FLOAT128_T__	_Float128	        128	                113	                15	                16383
std::bfloat16_t	bf16 or BF16    __STDCPP_BFLOAT16_T__	(N/A)	            16	                8	                8	                127

**********/

#include <print>
#include <stdfloat>

int main() {
    std::float16_t      f16_val =   1.23f16;
    std::float32_t      f32_val =   1.23f32;
    std::float64_t      f64_val =   1.23f64;
    std::float128_t     f128_val =   1.23f128;
    std::bfloat16_t     bf16_val =   1.23bf16;

    std::println("f16_val {}", f16_val);
    std::println("f32_val {}", f32_val);
    std::println("f64_val {}", f64_val);
    std::println("f128_val {}", f128_val);
    std::println("bf16_val {}", bf16_val);

    return 0;
}

/*****
    END OF FILE
**********/


