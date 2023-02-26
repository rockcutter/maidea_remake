#pragma once
#include <iostream>
#include <climits>
#include <chrono>

/// @brief Debug時Log出力はデフォルトでfalseになっているので、Enableして使う。非型テンプレートパラメータに入れる値ごとに、ログのON/OFFが可能(同じパラメータのテンプレートごとに設定が共有される)
/// @tparam LogCategory ログのカテゴリを指定する。列挙子を入れると便利
template <auto LogCategory = INT_MAX>
class Logger {
private:
    static bool debugFlag            = false;
    static std::ostream& ostream     = std::cout;
    static std::string categoryName  = "";

public:
    template <typename ...Args>
    void Debug(Args... args) {
        if (!this->debugFlag) return;
        std::cout << "[" << std::chrono::system_clock::now() << "]";
        std::cout << "[Debug]";
        if(this->categoryName != ""){
            std::cout << "[" << this->categoryName << "]";
        }
        std::cout << ": ";
        (this->ostream << ... << args);
        this->ostream << std::endl;
    }

    void SetCategoryName(std::string_view catName) {
        this->categoryName = std::string{ catName };
    }

    void SetStream(std::ostream& ostream) {
        this->ostream = ostream;
    }

    void Enable() {
        this->debugFlag = true;
    }

    void Disable() {
        this->debugFlag = true;
    }
};