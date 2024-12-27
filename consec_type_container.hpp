#include <iostream>
#include <algorithm> 
#include <stdexcept> 

template <class T>
class ConsecTypeContainer {
public:
    using iterator = T*;
    using const_iterator = const T*;

    ConsecTypeContainer();
    ~ConsecTypeContainer();
    
    // Конструктор копирования
    ConsecTypeContainer(const ConsecTypeContainer<T>& other);
    
    // Оператор присваивания копирования
    ConsecTypeContainer<T>& operator=(const ConsecTypeContainer<T>& other);

    // Конструктор перемещения
    ConsecTypeContainer(ConsecTypeContainer<T>&& other) noexcept;

    // Оператор присваивания перемещения
    ConsecTypeContainer<T>& operator=(ConsecTypeContainer<T>&& other) noexcept;

    // Получить размер и емкость контейнера
    size_t capacity() const;
    size_t size() const;

    // Проверка на пустоту
    bool empty() const;

    // Итераторы
    iterator begin();
    const_iterator begin() const; // Константный итератор
    iterator end();
    const_iterator end() const; // Константный итератор

    // Добавить элемент в конец контейнера
    void push_back(const T& val);

    // Вставить элемент в контейнер
    void insert(std::size_t position, const T& val);

    // Удалить элемент из контейнера
    void remove(std::size_t position);

    // Зарезервировать и изменить размер памяти
    void reserve(size_t capacity);
    void resize(size_t size);

    // Доступ по индексу
    T& operator[](size_t index);
    const T& operator[](size_t index) const; // Константный доступ

    // Вывод всех элементов контейнера
    void print_all() const;

private:
    size_t m_Size;
    size_t m_Capacity;
    T* m_Buffer;
};

// Конструктор по умолчанию
template <class T>
ConsecTypeContainer<T>::ConsecTypeContainer() : m_Size(0), m_Capacity(0), m_Buffer(nullptr) {}

// Конструктор копирования
template <class T>
ConsecTypeContainer<T>::ConsecTypeContainer(const ConsecTypeContainer<T>& other) {
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;
    m_Buffer = new T[m_Capacity];
    std::copy(other.m_Buffer, other.m_Buffer + m_Size, m_Buffer);
}

// Оператор присваивания
template <class T>
ConsecTypeContainer<T>& ConsecTypeContainer<T>::operator=(const ConsecTypeContainer<T>& other) {
    if (this != &other) { // Проверка на самоприсваивание
        delete[] m_Buffer; // Освобождение старого буфера
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Buffer = new T[m_Capacity];
        std::copy(other.m_Buffer, other.m_Buffer + m_Size, m_Buffer);
    }
    return *this;
}

// Конструктор перемещения
template <class T>
ConsecTypeContainer<T>::ConsecTypeContainer(ConsecTypeContainer<T>&& other) noexcept 
    : m_Size(other.m_Size), m_Capacity(other.m_Capacity), m_Buffer(other.m_Buffer) {
    other.m_Buffer = nullptr; // Освобождаем ресурс в перемещаемом объекте
    other.m_Size = 0; // Сбрасываем размеры перемещаемого объекта
    other.m_Capacity = 0; // Обнуляем емкость перемещаемого объекта
}

// Оператор присваивания перемещения
template <class T>
ConsecTypeContainer<T>& ConsecTypeContainer<T>::operator=(ConsecTypeContainer<T>&& other) noexcept {
    if (this != &other) { // Проверка на самоприсваивание
        delete[] m_Buffer; // Освобождение старого буфера
        m_Size = other.m_Size;
        m_Capacity = other.m_Capacity;
        m_Buffer = other.m_Buffer;

        other.m_Buffer = nullptr; // Освобождаем ресурс в перемещаемом объекте
        other.m_Size = 0; // Сбрасываем размеры перемещаемого объекта
        other.m_Capacity = 0; // Обнуляем емкость перемещаемого объекта
    }
    return *this;
}

// Деструктор
template <class T>
ConsecTypeContainer<T>::~ConsecTypeContainer() {
    delete[] m_Buffer;
}

// Проверка на пустоту
template <class T>
bool ConsecTypeContainer<T>::empty() const {
    return m_Size == 0;
}

// Получение итераторов
template <class T>
typename ConsecTypeContainer<T>::iterator ConsecTypeContainer<T>::begin() {
    return m_Buffer;
}

template <class T>
typename ConsecTypeContainer<T>::const_iterator ConsecTypeContainer<T>::begin() const {
    return m_Buffer;
}

template <class T>
typename ConsecTypeContainer<T>::iterator ConsecTypeContainer<T>::end() {
    return m_Buffer + m_Size;
}

template <class T>
typename ConsecTypeContainer<T>::const_iterator ConsecTypeContainer<T>::end() const {
    return m_Buffer + m_Size;
}

// Метод для добавления элемента в конец контейнера
template <class T>
void ConsecTypeContainer<T>::push_back(const T& val) {
    if (m_Size >= m_Capacity) {
        reserve(m_Capacity == 0 ? 1 : m_Capacity * 2);
    }
    m_Buffer[m_Size++] = val;
}

// Метод для вставки элемента в контейнер
template <class T>
void ConsecTypeContainer<T>::insert(std::size_t position, const T& val) {
    if (position > m_Size) {
        throw std::out_of_range("insert() error: invalid position");
    }
    resize(m_Size + 1);
    std::copy_backward(m_Buffer + position, m_Buffer + m_Size - 1, m_Buffer + m_Size);
    m_Buffer[position] = val;
}

// Метод для удаления элемента из контейнера
template <class T>
void ConsecTypeContainer<T>::remove(std::size_t position) {
    if (position >= m_Size) {
        throw std::out_of_range("remove() error: invalid position");
    }
    std::copy(m_Buffer + position + 1, m_Buffer + m_Size, m_Buffer + position);
    resize(m_Size - 1);
}

// Метод для резервирования памяти
template <class T>
void ConsecTypeContainer<T>::reserve(size_t capacity) {
    if (capacity <= m_Capacity) return; // Ничего не делаем, если новая мощность меньше или равна текущей
    T* newBuffer = new T[capacity];
    if (m_Buffer) {
        std::copy(m_Buffer, m_Buffer + m_Size, newBuffer);
        delete[] m_Buffer;
    }
    m_Buffer = newBuffer;
    m_Capacity = capacity;
}

// Метод для изменения размера контейнера
template <class T>
void ConsecTypeContainer<T>::resize(size_t size) {
    if (size > m_Capacity) {
        reserve(size);
    }
    m_Size = size;
}

// Получить емкость контейнера
template <class T>
size_t ConsecTypeContainer<T>::capacity() const {
    return m_Capacity;
}

// Получить размер контейнера
template <class T>
size_t ConsecTypeContainer<T>::size() const {
    return m_Size;
}

// Доступ по индексу
template <class T>
T& ConsecTypeContainer<T>::operator[](size_t index) {
    if (index >= m_Size) {
        throw std::out_of_range("operator[]: index out of range");
    }
    return m_Buffer[index];
}

template <class T>
const T& ConsecTypeContainer<T>::operator[](size_t index) const {
    if (index >= m_Size) {
        throw std::out_of_range("operator[]: index out of range");
    }
    return m_Buffer[index];
}

// Вывод всех элементов контейнера
template <class T>
void ConsecTypeContainer<T>::print_all() const {
    if (empty()) {
        std::cout << "Container is empty." << std::endl;
        return;
    }
    std::cout << "Container elements: ";
    for (size_t i = 0; i < m_Size; ++i) {
        std::cout << m_Buffer[i] << " ";
    }
    std::cout << std::endl;
}

