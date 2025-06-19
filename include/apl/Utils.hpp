//
// Created by Doktorov Alexander on 5/27/25.
// Copyright (c) 2025 Nikiet. All rights reserved.
//

#ifndef ALARM_POINT_LIB_UTILS_HPP
#define ALARM_POINT_LIB_UTILS_HPP

APL_NAMESPACE_BEGIN

#include <type_traits>

// Base template: Copy all qualifiers from `From` to `To`
template <typename From, typename To>
struct copy_qualifiers {
private:
    // Extract core type of `To` (remove existing qualifiers)
    using CoreTo = std::remove_cv_t<std::remove_reference_t<To>>;

    // Copy reference qualifier from `From`
    using WithRef = std::conditional_t<
            std::is_lvalue_reference_v<From>,
            CoreTo&,
            std::conditional_t<
                    std::is_rvalue_reference_v<From>,
                    CoreTo&&,
                    CoreTo
                    >
            >;

    // Copy `const` and `volatile` from `From`
    using WithCV = std::conditional_t<
            std::is_const_v<std::remove_reference_t<From>>,
            std::conditional_t<
                    std::is_volatile_v<std::remove_reference_t<From>>,
                    const volatile WithRef,
                    const WithRef
                    >,
            std::conditional_t<
                    std::is_volatile_v<std::remove_reference_t<From>>,
                    volatile WithRef,
                    WithRef
                    >
            >;

public:
    using type = WithCV;
};

// Helper alias for cleaner syntax
template <typename From, typename To>
using copy_qualifiers_t = typename copy_qualifiers<From, To>::type;

APL_NAMESPACE_END

#endif //ALARM_POINT_LIB_UTILS_HPP
