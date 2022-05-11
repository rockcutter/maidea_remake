#pragma once
#include <memory>

template <class T, class Head, class... Tail>
class MultipleUnique {
private:

	template<class U, class... W>
	struct helper {
		static void Make(std::vector<std::unique_ptr<T>>& arr) {
			arr.emplace_back(std::make_unique<U>());
			helper<W...>::Make(arr);
		}
	};

	template<class U>
	struct helper<U> {
		static void Make(std::vector<std::unique_ptr<T>>& arr) {
			arr.emplace_back(std::make_unique<U>());
		}
	};
public:
	static void Make(std::vector<std::unique_ptr<T>>& arr) {
		MultipleUnique::helper<Head, Tail...>::Make(arr);
	}


};
