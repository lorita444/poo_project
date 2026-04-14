#pragma once
#include <iostream>
#include <algorithm>
#include <type_traits>


template <typename Container>
class Afisator {
public:
    void afiseaza(const Container& cont) const {
        for (auto& elem : cont) {
            if constexpr (is_pointer_v<typename Container::value_type>)
                cout << *elem << std::endl;
            else
                cout << elem << std::endl;
        }
    }

    template <typename Predicate>
    bool cauta(Container& cont, Predicate predicat) {
        auto it = find_if(cont.begin(), cont.end(), predicat);
        if (it != cont.end()) {
            return true;
        } else {
            return false;
        }
    }
};
