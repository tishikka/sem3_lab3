#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    Node();
    T m_Value;
    Node<T>* m_Prev;
    Node<T>* m_Next;
};

template <typename T>
Node<T>::Node() : m_Prev(nullptr), m_Next(nullptr) {}

template <typename T>
class ListTypeContainer {
private:
    Node<T>* m_Head;
    Node<T>* m_Tail;
    size_t m_Size;

public:
    ListTypeContainer();
    ~ListTypeContainer();

    void push_back(const T& val);
    void pop_back();
    void remove(std::size_t position);
    void insert(std::size_t position, const T& val);
    void erase(const T& val); 
    size_t size() const;
    T operator[](std::size_t position) const;
    void print_all() const;
};

template <typename T>
ListTypeContainer<T>::ListTypeContainer() : m_Head(nullptr), m_Tail(nullptr), m_Size(0) {}

template <typename T>
ListTypeContainer<T>::~ListTypeContainer() {
    while (m_Head) {
        pop_back();
    }
}

template <typename T>
void ListTypeContainer<T>::push_back(const T& val) {
    Node<T>* node = new Node<T>;
    node->m_Value = val;

    if (m_Tail) {
        m_Tail->m_Next = node;
        node->m_Prev = m_Tail;
        m_Tail = node;
    } else {
        m_Head = m_Tail = node;
    }
    m_Size++;
}

template <typename T>
void ListTypeContainer<T>::pop_back() {
    if (m_Size == 0) {
        std::cout << "pop_back() error: container is empty" << std::endl;
        return;
    }

    Node<T>* delNode = m_Tail;
    m_Tail = m_Tail->m_Prev;

    if (m_Tail) {
        m_Tail->m_Next = nullptr;
    } else {
        m_Head = nullptr; // Список стал пустым
    }

    delete delNode;
    m_Size--;
}

template <typename T>
void ListTypeContainer<T>::remove(std::size_t position) {
    if (position >= m_Size) {
        std::cerr << "remove() error: invalid position" << std::endl;
        return;
    }

    Node<T>* temp = m_Head;
    for (std::size_t i = 0; i < position; ++i) {
        temp = temp->m_Next;
    }

    if (temp->m_Prev) {
        temp->m_Prev->m_Next = temp->m_Next;
    } else {
        m_Head = temp->m_Next; // Удаляем голову
    }

    if (temp->m_Next) {
        temp->m_Next->m_Prev = temp->m_Prev;
    } else {
        m_Tail = temp->m_Prev; // Удаляем хвост
    }

    delete temp;
    m_Size--;
}

template <typename T>
void ListTypeContainer<T>::insert(std::size_t position, const T& val) {
    if (position > m_Size) {
        std::cerr << "insert() error: invalid position" << std::endl;
        return;
    }

    Node<T>* node = new Node<T>;
    node->m_Value = val;

    if (position == 0) {
        node->m_Next = m_Head;
        if (m_Head) {
            m_Head->m_Prev = node;
        } else {
            m_Tail = node; // Список был пуст
        }
        m_Head = node;
    } else {
        Node<T>* temp = m_Head;
        for (std::size_t i = 0; i < position - 1; ++i) {
            temp = temp->m_Next;
        }
        node->m_Next = temp->m_Next;
        node->m_Prev = temp;
        temp->m_Next = node;

        if (node->m_Next) {
            node->m_Next->m_Prev = node;
        } else {
            m_Tail = node; // Вставка в конец
        }
    }
    m_Size++;
}


template <typename T>
void ListTypeContainer<T>::erase(const T& val) {
    Node<T>* current = m_Head;
    while (current) {
        if (current->m_Value == val) {
            if (current->m_Prev) {
                current->m_Prev->m_Next = current->m_Next;
            } else {
                m_Head = current->m_Next; // Удаляем голову
            }

            if (current->m_Next) {
                current->m_Next->m_Prev = current->m_Prev;
            } else {
                m_Tail = current->m_Prev; // Удаляем хвост
            }
            delete current;
            m_Size--;
            return; 
        }
        current = current->m_Next;
    }
    std::cerr << "erase() error: value not found" << std::endl;
}


template <typename T>
size_t ListTypeContainer<T>::size() const {
    return m_Size;
}

template <typename T>
T ListTypeContainer<T>::operator[](std::size_t position) const {
    if (position >= m_Size) {
        throw std::out_of_range("operator[] error: index out of range");
    }

    Node<T>* temp = m_Head;
    for (std::size_t i = 0; i < position; ++i) {
        temp = temp->m_Next;
    }

    return temp->m_Value;
}

template <typename T>
void ListTypeContainer<T>::print_all() const {
    Node<T>* current = m_Head;
    while (current) {
        std::cout << current->m_Value << " ";
        current = current->m_Next;
    }
    std::cout << std::endl;
}
