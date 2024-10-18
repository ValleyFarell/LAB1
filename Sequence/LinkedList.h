#include<exception>

using namespace std;

template<class T>
class LinkedList {
    private:
        struct Node {
            T value;
            Node* next;
            Node* prev;
            Node(const T& value, Node *next = nullptr, Node* prev = nullptr) {
                this->value =  value;
                this->next = next;
                this->prev = prev;
            }
        };

        Node* head = nullptr;
        Node* tail = nullptr;
        size_t size = 0;

    public:
        /* перегрузка оператора присвоения */
        LinkedList<T>& operator=(const LinkedList<T>& list) {
            this->head = this->tail = nullptr;
            this->size = 0;
            for(size_t i = 0; i != list.GetLength(); ++i) {
                this->Append(list[i]);
            }
            return *this;
        }
        /* Создать пустой список */
        LinkedList () = default;
        /* Копировать элементы из переданного массива */
        LinkedList (T* items, int count) {
            this->size = 0;
            for (size_t i = 0; i != count; ++i) {
                (*this).Append(items[i]);
            }
        }
        LinkedList (int count) {
            this->size = 0;
            for (size_t i = 0; i != count; ++i) {
                (*this).Append(0);
            }
        }
        /* Копировать элементы из переданного массива */
        LinkedList(std::initializer_list<T> items)
        {
            for (auto &item : items)
            {
                this->Append(item);
            }
        }
        /* Копирующий конструктор */
        LinkedList (const LinkedList <T> & list) {
            for (size_t i = 0; i != list.GetLength(); ++i) {
                T tmp = list.Get(i);
                this->Append(tmp);
            }
        }
        ~LinkedList() {
            this->Clear();
            this->head = nullptr;
            this->tail = nullptr;
        }

        /* Получить первый элемент в списке */
        T GetFirst() {
            return head->value;
        }
        /* Получить последний элемент в списке */
        T GetLast() {
            return tail->value;
        }
        /* Получить элемент в списке по индексу */
        T Get(size_t index) const {
            Node* current = this->head;
            for (size_t i = 0; i != index; ++i) {
                current = current->next;
            }
            return current->value;
        }
        
        /* Получить список из всех элементов, начиная с startIndex и заканчивая endIndex. */
        LinkedList<T> *GetSubList(int startIndex, int endIndex) {
            if (startIndex < 0 || endIndex >= this->size)
                throw out_of_range("Uncorrect indexes!");
                
            LinkedList<T>* newList = new LinkedList<T>;
            Node* current = this->head;
            for (size_t i = 0; i != startIndex; ++i) {
                current = current->next;
            }
            for (size_t i = startIndex; i != endIndex; ++i) {
                newList->Append(current->value);
                current = current->next;
            }
            return newList;
        }
        /* Получить длину списка */
        size_t GetLength() const {
            return this->size;
        }
        /* Добавляет элемент в конец списка */
        void Append(T item) {
            if (this->size == 0) {
                Node* newNode = new Node(item);
                this->head = this->tail = newNode;
                this->size++;
                return;
            }
            Node* newNode = new Node(item);
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
            this->size++;
        }
        /* Добавляет элемент в начало списка */
        void Prepend(T item) {
            if (this->size == 0) {
                Node* newNode = new Node(item);
                this->head = this->tail = newNode;
                this->size++;
                return;
            }
            Node* newNode = new Node(item);
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
            this->size++;
        }
        /* Вставляет элемент в заданную позицию */
        void InsertAt(T item, int index) {
            if (index < 0 || index >= this->size)
                throw out_of_range("Uncorrect indexes!");
    
            this->Append(this->GetLast());
            Node* current = this->tail;
            for (size_t i = this->GetLength() - 1; i != index; --i) {
                current->value = current->prev->value;
                current = current->prev;
            }
            current->value = item;
        }
        void Set(T item, int index) {
            if (index < 0 || index >= this->size)
                throw out_of_range("Uncorrect indexes!");
            Node* current = this->tail;
            for (size_t i = this->GetLength() - 1; i != index; --i) {
                current = current->prev;
            }
            current->value = item;
        }
        /* Сцепляет два списка */
        LinkedList<T> Concat(const LinkedList<T> &list) {
            // LinkedList<T> newList = *this;
            // for (size_t i = 0; i != list.GetLength(); ++i) {
            //     newList.Append(list[i]);
            // }
            this->size += list.GetLength();
            tail->next = list.head;
            return *this;
        }

        void PopFront() {
            Node* tmp = this->head;
            this->head = this->head->next;
            delete tmp;
            this->size--;
        }

        void Clear() {
            Node* curr = this->head;
            int size = static_cast<int>(this->size);
            for (int i = 0; i < size; ++i) {
                this->PopFront();
            }
        }       

        T& operator [] (size_t index) const {
            if (index >= this->size)
                throw out_of_range("Uncorrect index!");
            Node* current = this->head;
            for (size_t i = 0; i != index; ++i) {
                current = current->next;
            }
            return current->value;
        }
};
