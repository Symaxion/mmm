#include "os.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtGui/QFileDialog>

#include <iostream>
#include <fstream>

#ifndef Q_WS_WIN
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace OS {
    QString shellEscape(const QString& input) {
        QString copy = input;
    #ifdef Q_WS_WIN
        copy.replace("\"","\\\"");
        copy = "\"" + copy + "\"";
    #else
        copy.replace("\'","\\\'");
        copy = "\'" + copy + "\'";
    #endif
        return copy; 
    }


    void prepareInstance(const QString& instance) {
        QDir(kMmmLocation).mkdir(instance);
        QDir().mkdir(instanceMcPath(instance));
    #ifdef Q_WS_MAC
        QDir(kMmmLocation).mkdir(instance + "/Library");
        chflags(qPrintable(kMmmLocation + "/" + instance + "/Library"), 
                UF_HIDDEN);
        symlink("..", qPrintable(kMmmLocation + "/" + instance + 
                "/Library/Application Support"));
    #endif
    }

    void recursiveRemove(const QDir& path) {
        QDirIterator it(path.absolutePath(), QDir::AllEntries | QDir::Hidden | 
                QDir::NoDotAndDotDot);
        while(it.hasNext()) {
            it.next();
            if(it.fileInfo().isDir() && ! it.fileInfo().isSymLink()) {
                recursiveRemove(it.filePath());
            } else {
                QFile::remove(it.filePath());
            }

        }
        QDir().rmdir(path.absolutePath());
    }

    void removeInstance(const QString& instance) {
        recursiveRemove(instancePath(instance));
    }

    QStringList listInstances() {
        return QDir(kMmmLocation).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    }

    QString instancePath(const QString& instance) {
        return kMmmLocation + kPS + instance;
    }

    QString instanceMcPath(const QString& instance) {
    #ifdef Q_WS_MAC
        return instancePath(instance) + "/minecraft";
    #else
        return instancePath(instance) + kPS + ".minecraft";
    #endif    
    }

    QString scriptText(const QString& mc) {
        QString mcpath = shellEscape(mc);
    #if defined(Q_WS_WIN)
        return QString(
            "@echo off\n"
            "set APPDATA=%1\n"
            "SET APPDATA=###%APPDATA%###\n"
            "SET APPDATA=%APPDATA:\"###=%\n"
            "SET APPDATA=%APPDATA:###\"=%\n"
            "SET APPDATA=%APPDATA:###=%\n"
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
            "HOME=$1 java -jar '" + mcpath + "' &\n"
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


    void openFolder(const QString& folder) {
        QString copy = shellEscape(folder);
    #if defined(Q_WS_WIN)
        std::system(qPrintable("explorer " + copy));
    #elif defined(Q_WS_MAC)
        std::system(qPrintable("open " + copy + " &"));
    #else
        std::system(qPrintable("xdg-open " + copy + " &"));
    #endif
    }

    void launchInstance(const QString& name) {
        QString copy = shellEscape(name);
        QString script = shellEscape(kScriptLocation); 

    #ifdef Q_WS_WIN
        std::system(qPrintable("cmd /c \"" + script + " "+ copy+"\""));
    #else
        std::system(qPrintable(script + " " + copy)); 
    #endif
    }
}
