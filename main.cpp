#include "journal.h"

#include <QApplication>

template <class T>
class SmartPointer {
public:
    SmartPointer(T* ptr) : m_ptr(ptr) {}
    ~SmartPointer() {
        delete m_ptr;
    }
    T& operator*() const { return *m_ptr; }
    T* operator->() const { return m_ptr; }
private:
    T* m_ptr;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Journal w;

    w.show();

    return a.exec();
}
