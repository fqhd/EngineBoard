#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <iostream>

#include "config.hpp"

// ------------------------------------------------------------------
// Custom widget that draws a centered square checkerboard
// ------------------------------------------------------------------
class ChessBoardWidget : public QWidget {
public:
    explicit ChessBoardWidget(QWidget* parent = nullptr) : QWidget(parent) {
        setMinimumSize(200, 200);  // avoid vanishing

        // Set dark gray background for the whole widget
        setStyleSheet("background-color: #303030;");
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        Q_UNUSED(event);
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, false);

        int w = width();
        int h = height();

        // Determine the size of the square board (use the shorter side)
        int boardPixels = qMin(w, h);
        int squareSize = boardPixels / 8;   // integer division for proper grid

        // Center the board in the window
        int offsetX = (w - squareSize * 8) / 2;
        int offsetY = (h - squareSize * 8) / 2;

        QColor light(240, 217, 181);
        QColor dark(181, 136, 99);

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                QRect rect(offsetX + col * squareSize,
                           offsetY + row * squareSize,
                           squareSize, squareSize);
                painter.fillRect(rect, ((row + col) % 2 == 0) ? light : dark);
            }
        }

        // Draw a border around the whole board
        painter.setPen(Qt::black);
        painter.drawRect(offsetX, offsetY, squareSize * 8, squareSize * 8);
    }
};

// ------------------------------------------------------------------
// Main
// ------------------------------------------------------------------
int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // Parse configuration
    Config config = parseConfig("config.txt");

    // Create the board widget
    ChessBoardWidget board;
    board.setWindowTitle("Chess Board - UCI Client");

    // Apply window dimensions from config
    board.resize(config.width, config.height);

    board.show();

    // Print info
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Engine path: " << config.enginePath.toStdString() << std::endl;
    std::cout << "Depth: " << config.depth << std::endl;
    std::cout << "Window size: " << config.width << "x" << config.height << std::endl;

    return app.exec();
}
