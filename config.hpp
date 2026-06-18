#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <QString>

struct Config {
    QString enginePath;   // path to UCI engine
    int depth;            // search depth
    int width;            // initial window width
    int height;           // initial window height
};

// Parse the configuration file (default: "config.txt")
Config parseConfig(const QString& filename = "config.txt");

#endif // CONFIG_HPP
