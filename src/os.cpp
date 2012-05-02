#include "os.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtGui/QFileDialog>

#include <iostream>
#include <fstream>

#ifndef Q_WS_WIN
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace OS {
    void prepareInstance(const QString& instance) {
        QDir(kMmmLocation).mkdir(instance);
    #ifdef Q_WS_MAC
        QDir(kMmmLocation).mkdir(instance + "/Library");
        chflags(qPrintable(kMmmLocation + "/" + instance + "/Library"), 
                UF_HIDDEN);
        symlink("..", qPrintable(kMmmLocation + "/" + instance + 
                "/Library/Application Support"));
    #endif
    }

    QString scriptText(const QString& mcpath) {
    #if defined(Q_WS_WIN)
        return QString(
            "@echo off\n"
            "set APPDATA=%1\n"
            + mcpath + "\n"
        );
    #elif defined(Q_WS_MAC)
        return QString(
            "#!/bin/bash\n"
            "HOME=$1 open '" + mcpath + "' &\n"
        );
    #else
        return QString(
            "#!/bin/bash\n"
            "HOME=$1 java -jar '" + mcpath + "'\n"
        );
    #endif
    }

    void createScript(const QString& mcpath) {
        QString script = scriptText(mcpath);

        std::ofstream s(qPrintable(kScriptLocation), 
                std::ios_base::trunc);

        s << qPrintable(script);
    #ifndef Q_WS_WIN
        if(chmod(qPrintable(kScriptLocation), 0777)) {
            perror("mmm");
            exit(1);
        }
    #endif
    }

    bool isInitialized() {
        return QFile(kScriptLocation).exists();
    }

    void initialize() {
        QDir d;
        d.mkpath(kMmmLocation);

        QString path = getMinecraftApp();
        
        createScript(path);
    }

    QString getMinecraftApp() {
        return QFileDialog::getOpenFileName(0, 
                "Select your Minecraft application", ".", kAppExtension);
    }
}
