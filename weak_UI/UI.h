#include<iostream>
#include"../src/SharedPtr.h"
#include"../src/UniquePtr.h"
#include"../Sequence/ArraySequence.h"

class UI {
private:
    ArraySequence<SharedPtr<int>*> sharedArray;
    ArraySequence<UniquePtr<int>*> uniqueArray;
    bool isRun = true;
    int mainMenu() {
        std::cout << "      <<< Меню >>> \n";
        std::cout << "1. Создать SharedPtr \n";
        std::cout << "2. Создать UniquePtr \n";
        std::cout << "3. Вывести список SharedPtr \n";
        std::cout << "4. Вывести список UniquePtr \n";
        std::cout << "5. Выход \n";
        int userChoice;
        std::cin >> userChoice;
        if (userChoice <= 5 && userChoice >= 1)
            return userChoice;
        else {
            std::cout << "  Вы ввели неправильную команду. \n";
            return mainMenu();
        }
    }

    void unqPtrCreating() {
        std::cout << "      <<< UniquePtr >>> \n";
        std::cout << "  Значение: ";
        int value;
        std::cin >> value;
        uniqueArray.Append(new UniquePtr<int>(value));
        std::cout << "  UniquePtr создан!\n\n";
    }

    void shrdPtrCreating() {
        std::cout << "      <<< SharedPtr >>> \n";
        std::cout << "  Значение: ";
        int value;
        std::cin >> value;
        sharedArray.Append(new SharedPtr<int>(value));
        std::cout << "  SharedPtr создан!\n\n";
    } 

    void allSharedPtr() { 
        if (sharedArray.GetLength() == 0) {
            std::cout << "  Список пуст \n"; 
            return;
        }
        std::cout << "      <<< SharedPtrs >>> \n"; 
        printf("  %10s%20s%30s\n", "ptr", "value", "counter"); 
        for (int i = 0; i < sharedArray.GetLength(); ++i) { 
            printf("%d. %10p%20d%30Ld\n", 
                (i + 1),
                sharedArray.Get(i)->getPtr(), 
                sharedArray.Get(i)->getValue(), 
                sharedArray.Get(i)->getCounterValue()); 
        } 
        
        std::cout << "  Выберите номер умного указателя, который хотите изменить: "; 
        int prtChoice; 
        std::cin >> prtChoice; 
        changeShrdPtr(prtChoice - 1);
    }

    void allUniquePtr() {
        if (uniqueArray.GetLength() == 0) {
            std::cout << "  Список пуст \n"; 
            return;
        }
        std::cout << "      <<< UniquePtrs >>> \n";
        printf("  %10s%20s\n", "ptr", "value"); 
        for (int i = 0; i < uniqueArray.GetLength(); ++i) { 
            printf("%d. %10p%20d\n",
                (i + 1),
                uniqueArray.Get(i)->getPtr(), 
                uniqueArray.Get(i)->getValue()); 
        } 
        std::cout << "  Выберите номер умного указателя, который хотите изменить: "; 
        int ptrChoice;
        std::cin >> ptrChoice;
        changeUnqPtr(ptrChoice - 1);
    }

    void changeUnqPtr(int ptrIndex) {
        std::cout << "  pointer: " << uniqueArray[ptrIndex]->getPtr() << "\n";
        std::cout << "  value: " << uniqueArray[ptrIndex]->getValue() << "\n\n";
        std::cout << "  1.  Поменять значение\n";
        std::cout << "  2.  Удалить указатель\n";
        std::cout << "  3.  Переместить в другой указатель(move)\n";
        std::cout << "  4.  Выход \n";
        int userChoice;
        std::cin >> userChoice;
        
        switch (userChoice)
        {
        case 1:
            int newValue;
            std::cout << "  Новое значение: ";
            std::cin >> newValue;
            uniqueArray[ptrIndex]->ChangeValue(newValue);
            std::cout << "  Значение успешно изменено!\n";
            break;
        case 2:
            uniqueArray.DeleteByIndex(ptrIndex);
            std::cout << "  Указатель успешно удалён!\n";
            break;
        case 3:
            int otherPtr;
            std::cout << "  Введите номер указателя, в который будет совершено перемещение: ";
            std::cin >> otherPtr;
            *uniqueArray[otherPtr - 1] = move(*uniqueArray[ptrIndex]);
            uniqueArray.DeleteByIndex(ptrIndex);
            std::cout << "  Указатель успешно перемещён!\n";
            break;
        case 4:
            break;
        default:
            std::cout << "  Вы ввели неправильную команду. \n";
            changeUnqPtr(ptrIndex);
            break;
        }
    }

    void changeShrdPtr(int ptrIndex) {
        std::cout << "  pointer: " << sharedArray[ptrIndex]->getPtr() << "\n";
        std::cout << "  value: " << sharedArray[ptrIndex]->getValue() << "\n";
        std::cout << "  counter: " << sharedArray[ptrIndex]->getCounterValue() << "\n\n";
        std::cout << "  1.  Поменять значение\n";
        std::cout << "  2.  Удалить указатель\n";
        std::cout << "  3.  Переместить в другой указатель(move)\n";
        std::cout << "  4.  Копировать в массив\n";
        std::cout << "  5.  Выход \n";
        int userChoice;
        std::cin >> userChoice;
        switch (userChoice)
        {
        case 1:
            int newValue;
            std::cout << "  Новое значение: ";
            std::cin >> newValue;
            sharedArray[ptrIndex]->ChangeValue(newValue);
            std::cout << "  Значение успешно изменено!\n";
            break;
        case 2:
            sharedArray.DeleteByIndex(ptrIndex);
            std::cout << "  Указатель успешно удалён!\n";
            break;
        case 3:
            int otherPtr;
            std::cout << "  Введите номер указателя, в который будет совершено перемещение: ";
            std::cin >> otherPtr;
            *sharedArray[otherPtr - 1] = move(*sharedArray[ptrIndex]);
            sharedArray.DeleteByIndex(ptrIndex);
            std::cout << "  Указатель успешно перемещён!\n";
            break;
        case 4:
            sharedArray.Append(new SharedPtr<int>(*sharedArray.Get(ptrIndex)));
            break;
        case 5:
            break;
        default:
            std::cout << "  Вы ввели неправильную команду. \n";
            changeUnqPtr(ptrIndex);
            break;
        }
    }

public:
    void mainCycle() {
        while(isRun) {
            int mainChoice = mainMenu();
            switch (mainChoice)
            {
            case 1:
                shrdPtrCreating();
                break;
            case 2:
                unqPtrCreating();
                break;
            case 3:
                allSharedPtr();
                break;
            case 4:
                allUniquePtr();
                break;
            case 5:
                isRun = false;
                break;
            }
        }
        std::cout << "  До свидания! \n";
    }
};
