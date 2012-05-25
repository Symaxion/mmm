/*
 * Multi Minecraft Manager (MMM)
 * Copyright (c) Frank "SeySayux" Erens <seysayux@gmail.com>
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *    distribution.
 */

#include "os.h"

#include <QtCore/QFile>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include <QtGui/QFileDialog>

#include <QtCore/QDebug>

#include <iostream>
#include <fstream>

#ifndef Q_WS_WIN
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include "qstd.h"
#include "message.h"

namespace OS {
    QString shellEscape(const QString& input) {
        QString copy = input;
    #ifdef Q_WS_WIN
        copy.replace("/", "\\");
        copy.replace("\"","\\\"");
        copy = "\"" + copy + "\"";
    #else
        copy.replace("\'","\\\'");
        copy = "\'" + copy + "\'";
    #endif
        return copy; 
    }


    void prepareInstance(const QDir& instance) {
        QString instpath = instance.absolutePath();
        qstd::mkdir(instpath);
    #ifdef Q_WS_MAC
        instance.mkdir("Library");
        chflags(qPrintable(instpath + "/Library"),
                UF_HIDDEN);
        symlink("..", qPrintable(instpath + "/Library/Application Support"));
    #endif
    }

    QStringList listInstances() {
        return QDir(kMmmLocation).entryList(QDir::Dirs | QDir::NoDotAndDotDot);
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
            "HOME=$1 open " + mcpath + " &\n"
        );
    #else
        return QString(
            "#!/bin/bash\n"
            "HOME=$1 java -jar " + mcpath + " &\n"
        );
    #endif
    }

    void createScript(const QString& mcpath) {
        QString script = scriptText(mcpath);

        std::ofstream s(qPrintable(kScriptLocation), 
                std::ios_base::trunc);

        s << qPrintable(script);
    #ifndef Q_WS_WIN
        if(qstd::chmod(kScriptLocation, 0777)) {
            perror("mmm");
            exit(1);
        }
    #endif
    }

    bool isInitialized() {
        return QFile(kScriptLocation).exists();
    }

    void initialize() {
        qstd::mkdirs(kMmmLocation);

        QString path;

        while((path = getMinecraftApp()) == "") {
            Message::error("Please select your Minecraft application",
                    "For MMM to function, you need to select your Minecraft "
                    "launcher application first.");
        }
        
        createScript(path);
    }

    QString getMinecraftApp() {
        return QFileDialog::getOpenFileName(0,
                "Select your Minecraft application", ".", kAppExtension);
    }


    void openFolder(const QString& folder) {
        QString copy = shellEscape(folder);
        qDebug() << "Opening folder" << copy;
    #if defined(Q_WS_WIN)
        qstd::system("explorer "+copy);
    #elif defined(Q_WS_MAC)
        qstd::system("open " + copy + " &");
    #else
        qstd::system("xdg-open " + copy + " &");
    #endif
    }

    void launchInstance(const QString& path) {
        QString copy = shellEscape(path);
        QString script = shellEscape(kScriptLocation); 

    #ifdef Q_WS_WIN
        qstd::system("cmd /c \"" + script + " "+ copy+"\"");
    #else
        qstd::system(script + " " + copy);
    #endif
    }
}
