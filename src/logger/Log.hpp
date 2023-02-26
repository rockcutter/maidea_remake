#pragma once
#include <iostream>
#include <climits>

/// @brief Debug時Log出力はデフォルトでfalseになっているので、Enableして使う。非型テンプレートパラメータに入れる値ごとに、ログのON/OFFが可能(同じパラメータのテンプレートごとに設定が共有される)
/// @tparam LogCategory ログのカテゴリを指定する。列挙子を入れると便利
template <auto LogCategory = INT_MAX>
class Logger{
private:
    inline static bool debugFlag       = false;
    inline static std::ostream ostream = std::cout;

public:
    template <typename ...Args>
    void Debug(Args... args){
        if(!this->debugFlag) return;

        (this->ostream << ... << args);
        this->ostream << std::endl;
    }

    void SetStream(std::ostream& ostream){
        this->ostream = ostream;
    }

    void Enable(){
        this->debugFlag = true;
    }

    void Disable(){
        this->debugFlag = true;
    }
};