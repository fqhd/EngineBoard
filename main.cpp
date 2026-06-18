#include <QApplication>
#include <QWidget>
#include <iostream>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(800, 600);
    window.setWindowTitle("Hello Qt");
    window.show();

    std::cout << "Hello, World!" << std::endl;

    return app.exec();
}
