#include<iostream>
#include<cassert>
#include<chrono>
#include<memory>

#include"tests/tests.h"
#include"UI/UI.h"

int main() {
    bool is_test = false;
    if (!is_test) {
        UI ui;
        ui.main_cycle();
    } else {
        copy_shared_test();
        move_shared_test();
        counter_shared_test();
        move_unique_test();
        std_shared_test();
        std_unique_test();
        std::cout << "ALL TESTS ARE PASSED! \n";
    }
}
