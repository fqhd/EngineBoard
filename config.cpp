#include "config.hpp"
#include <QDebug>
#include <fstream>
#include <string>
#include <cctype>

static void trim(std::string& s) {
    size_t first = s.find_first_not_of(" \t");
    if (first == std::string::npos) {
        s.clear();
        return;
    }
    size_t last = s.find_last_not_of(" \t");
    s = s.substr(first, last - first + 1);
}

Config parseConfig(const QString& filename) {
    Config cfg;
    // Default values
    cfg.depth = 4;
    cfg.width = 800;
    cfg.height = 800;

    std::ifstream file(filename.toStdString());
    if (!file.is_open()) {
        qWarning() << "Config file not found. Using defaults.";
        return cfg;
    }

    std::string line;
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty()) continue;

        size_t colon = line.find(':');
        if (colon == std::string::npos) continue;

        std::string key = line.substr(0, colon);
        std::string value = line.substr(colon + 1);
        trim(key);
        trim(value);

        if (key == "engine") {
            cfg.enginePath = QString::fromStdString(value);
        } else if (key == "depth") {
            bool ok;
            int d = QString::fromStdString(value).toInt(&ok);
            if (ok) cfg.depth = d;
            else qWarning() << "Invalid depth value, using default.";
        } else if (key == "width") {
            bool ok;
            int w = QString::fromStdString(value).toInt(&ok);
            if (ok) cfg.width = w;
            else qWarning() << "Invalid width value, using default.";
        } else if (key == "height") {
            bool ok;
            int h = QString::fromStdString(value).toInt(&ok);
            if (ok) cfg.height = h;
            else qWarning() << "Invalid height value, using default.";
        }
    }
    file.close();

    qDebug() << "Config loaded:"
             << "engine =" << cfg.enginePath
             << ", depth =" << cfg.depth
             << ", width =" << cfg.width
             << ", height =" << cfg.height;
    return cfg;
}
