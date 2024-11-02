#include<iostream>
#include"../src/memory_utils.h"
#include"../src/vector_utils.h"

class UI {
private:
    Vector<SharedPtr<int>> shared_vector;
    Vector<UniquePtr<int>> unique_vector;
    bool is_run = true;
    int menu();
    void unique_create();
    void shrd_create();
    void all_shared_ptrs();
    void all_unique_ptrs();
    void change_unique(int ptr_ind);
    void change_shrd(int ptr_ind);
public:
    void main_cycle();
};
