#include "dynarr.h"

// Проверка значения на соответствие диапазону
static inline void ensure_in_range_int(int v, int lo, int hi) {
    if (v < lo || v > hi) {
        throw std::invalid_argument("value out of allowed range");
    }
}

// Проверка индекса на соответствие границам массива
static inline void ensure_index(std::size_t idx, std::size_t n) {
    if (idx >= n) {
        throw std::out_of_range("index out of range");
    }
}

// Конструктор - создание массива заданного размера
IntDynArray::IntDynArray(std::size_t n) : data_(nullptr), n_(n) {
    data_ = new int[n_];
    std::fill(data_, data_ + n_, 0);  // инициализация нулями
}

// Деструктор - освобождение памяти
IntDynArray::~IntDynArray() {
    delete[] data_;
}

// Конструктор копирования - создание копии массива
IntDynArray::IntDynArray(const IntDynArray& other) : data_(nullptr), n_(other.n_) {
    data_ = new int[n_];
    std::copy(other.data_, other.data_ + n_, data_);  // копирование данных
}

// Получение элемента по индексу
int IntDynArray::get(std::size_t idx) const {
    ensure_index(idx, n_);
    return data_[idx];
}

// Установка значения элемента по индексу
void IntDynArray::set(std::size_t idx, int value) {
    ensure_index(idx, n_);
    ensure_in_range_int(value, MIN_VAL, MAX_VAL);
    data_[idx] = value;
}

// Добавление элемента в конец массива
void IntDynArray::push_back(int value) {
    ensure_in_range_int(value, MIN_VAL, MAX_VAL);
    int* nd = new int[n_ + 1];           // создание нового массива большего размера
    std::copy(data_, data_ + n_, nd);   // копирование существующих данных
    nd[n_] = value;                     // добавление нового элемента
    delete[] data_;                     // освобождение старой памяти
    data_ = nd;                         // обновление указателя
    ++n_;                               // увеличение размера
}

// Поэлементное сложение массивов
void IntDynArray::add(const IntDynArray& other) {
    for (std::size_t i = 0; i < n_; ++i) {
        int rhs = (i < other.n_) ? other.data_[i] : 0;  // если индекс выходит за границы, используем 0
        data_[i] += rhs;
    }
}

// Поэлементное вычитание массивов
void IntDynArray::sub(const IntDynArray& other) {
    for (std::size_t i = 0; i < n_; ++i) {
        int rhs = (i < other.n_) ? other.data_[i] : 0;  // если индекс выходит за границы, используем 0
        data_[i] -= rhs;
    }
}

// Вывод массива в поток
void IntDynArray::print(std::ostream& os) const {
    for (std::size_t i = 0; i < n_; ++i) {
        if (i) os << ' ';  // пробел между элементами (кроме первого)
        os << data_[i];
    }
    os << '\n';
}
