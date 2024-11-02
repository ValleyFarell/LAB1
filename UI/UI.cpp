#include<iostream>

#include"../src/memory_utils.h"
#include"../src/vector_utils.h"
#include"UI.h"

int UI::menu() {
    std::cout << "      <<< Меню >>> \n";
    std::cout << "1. Создать SharedPtr \n";
    std::cout << "2. Создать UniquePtr \n";
    std::cout << "3. Вывести список SharedPtr \n";
    std::cout << "4. Вывести список UniquePtr \n";
    std::cout << "5. Выход \n";
    int user_choice;
    std::cin >> user_choice;
    if (user_choice <= 5 && user_choice >= 1)
        return user_choice;
    else {
        std::cout << "  Вы ввели неправильную команду. \n";
        return menu();
    }
}
void UI::unique_create() {
    std::cout << "      <<< UniquePtr >>> \n";
    std::cout << "  Значение: ";
    int value;
    std::cin >> value;
    UniquePtr<int> temp(new int(value));
    unique_vector_.push_back(std::move(temp));
    std::cout << "  UniquePtr создан!\n\n";
}
void UI::shrd_create() {
    std::cout << "      <<< SharedPtr >>> \n";
    std::cout << "  Значение: ";
    int value;
    std::cin >> value;
    SharedPtr<int> temp(new int(value));
    shared_vector_.push_back(std::move(temp));
    std::cout << "  SharedPtr создан!\n\n";
} 
void UI::all_shared_ptrs() { 
    if (shared_vector_.size() == 0) {
        std::cout << "  Список пуст \n"; 
        return;
    }
    std::cout << "      <<< SharedPtrs >>> \n"; 
    printf("  %10s%20s%30s\n", "ptr", "value", "counter"); 
    for (int i = 0; i < shared_vector_.size(); ++i) { 
        printf("%d. %10p%20d%30Ld\n", 
            (i + 1),
            shared_vector_[i].get_pointer(), 
            *(shared_vector_[i]), 
            shared_vector_[i].ref_count()); 
    } 
    
    std::cout << "  Выберите номер умного указателя, который хотите изменить: "; 
    int ptr_choice; 
    std::cin >> ptr_choice; 
    if (ptr_choice <= shared_vector_.size() && ptr_choice >= 1)
        change_shrd(ptr_choice - 1);
    else {
        std::cout << "  Вы ввели неправильный номер! \n";
        menu();
    }
}
void UI::all_unique_ptrs() {
    if (unique_vector_.size() == 0) {
        std::cout << "  Список пуст \n"; 
        return;
    }
    std::cout << "      <<< UniquePtrs >>> \n";
    printf("  %10s%20s\n", "ptr", "value"); 
    for (int i = 0; i < unique_vector_.size(); ++i) { 
        printf("%d. %10p%20d\n",
            (i + 1),
            unique_vector_[i].get_pointer(), 
            *(unique_vector_[i])); 
    } 
    std::cout << "  Выберите номер умного указателя, который хотите изменить: "; 
    int ptr_choice;
    std::cin >> ptr_choice;
    if (ptr_choice <= unique_vector_.size() && ptr_choice >= 1)
        change_unique(ptr_choice - 1);
    else {
        std::cout << "  Вы ввели неправильный номер! \n";
        menu();
    }
}
void UI::change_unique(int ptr_ind) {
    std::cout << "  pointer: " << unique_vector_[ptr_ind].get_pointer() << "\n";
    std::cout << "  value: " << *(unique_vector_[ptr_ind]) << "\n\n";
    std::cout << "  1.  Поменять значение\n";
    std::cout << "  2.  Удалить указатель\n";
    std::cout << "  3.  Переместить в другой указатель(move)\n";
    std::cout << "  4.  Выход \n";
    int user_choice;
    std::cin >> user_choice;
    
    switch (user_choice)
    {
    case 1:
        int new_value;
        std::cout << "  Новое значение: ";
        std::cin >> new_value;
        *unique_vector_[ptr_ind] = new_value;
        std::cout << "  Значение успешно изменено!\n";
        break;
    case 2:
        unique_vector_.erase(ptr_ind);
        std::cout << "  Указатель успешно удалён!\n";
        break;
    case 3:
        int other_ind;
        std::cout << "  Введите номер указателя, в который будет совершено перемещение: ";
        std::cin >> other_ind;
        if (other_ind <= unique_vector_.size() && other_ind >= 1){
            unique_vector_[other_ind - 1] = std::move(unique_vector_[ptr_ind]);
            unique_vector_.erase(ptr_ind);
            std::cout << "  Указатель успешно перемещён!\n";
        }
        else {
            std::cout << "  Вы ввели неправильный номер! \n";
            menu();
        }
        break;
    case 4:
        break;
    default:
        std::cout << "  Вы ввели неправильную команду. \n";
        change_unique(ptr_ind);
        break;
    }
}
void UI::change_shrd(int ptr_ind) {
    std::cout << "  pointer: " << shared_vector_[ptr_ind].get_pointer() << "\n";
    std::cout << "  value: " << *shared_vector_[ptr_ind] << "\n";
    std::cout << "  counter: " << shared_vector_[ptr_ind].ref_count() << "\n\n";
    std::cout << "  1.  Поменять значение\n";
    std::cout << "  2.  Удалить указатель\n";
    std::cout << "  3.  Переместить в другой указатель(move)\n";
    std::cout << "  4.  Копировать в массив\n";
    std::cout << "  5.  Выход \n";
    int user_choice;
    std::cin >> user_choice;
    switch (user_choice)
    {
    case 1:
        int new_value;
        std::cout << "  Новое значение: ";
        std::cin >> new_value;
        *shared_vector_[ptr_ind] = new_value;
        std::cout << "  Значение успешно изменено!\n";
        break;
    case 2:
        shared_vector_.erase(ptr_ind);
        std::cout << "  Указатель успешно удалён!\n";
        break;
    case 3:
        int other_ind;
        std::cout << "  Введите номер указателя, в который будет совершено перемещение: ";
        std::cin >> other_ind;
        shared_vector_[other_ind - 1] = std::move(shared_vector_[ptr_ind]);
        shared_vector_.erase(ptr_ind);
        std::cout << "  Указатель успешно перемещён!\n";
        break;
    case 4:
        shared_vector_.resize(shared_vector_.size() + 1);
        shared_vector_[shared_vector_.size() - 1] = shared_vector_[ptr_ind];
        break;
    case 5:
        break;
    default:
        std::cout << "  Вы ввели неправильную команду. \n";
        change_unique(ptr_ind);
        break;
    }
}

void UI::main_cycle() {
        while(is_run_) {
            int main_choice = menu();
            switch (main_choice)
            {
            case 1:
                shrd_create();
                break;
            case 2:
                unique_create();
                break;
            case 3:
                all_shared_ptrs();
                break;
            case 4:
                all_unique_ptrs();
                break;
            case 5:
                is_run_ = false;
                break;
            }
        }
        std::cout << "  До свидания! \n";
    }