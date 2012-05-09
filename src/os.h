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

#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QStringList>

#include <cstdlib>

namespace OS {

    const QString kPS = 
    #if defined(Q_WS_WIN)
        "\\"
    #else
        "/"
    #endif
    ;

    const QString kAppExtension = 
    #if defined(Q_WS_WIN)
        "*.exe"
    #elif defined(Q_WS_MAC)
        "*.app"
    #else
        "*.jar"
    #endif
    ;

    const QString kDefaultInstance = 
    #if defined(Q_WS_WIN)
        QString(std::getenv("APPDATA"))
    #else
        QDir::homePath()
    #endif
    ;

    const QString kDefaultInstanceMcPath = 
    #if defined(Q_WS_MAC) 
        kDefaultInstance + "/Library/Application Support/minecraft";
    #else
        kDefaultInstance + kPS +".minecraft";
    #endif
    ;

    const QString kMmmLocation = 
    #if defined(Q_WS_WIN)
        QString(std::getenv("APPDATA")) + "\\.mmm"
    #elif defined(Q_WS_MAC)
        QDir::homePath() + "/Library/Application Support/MMM"
    #else
        QDir::homePath() + "/.mmm"
    #endif
    ;

    const QString kScriptName = 
    #if defined(Q_WS_WIN)
        "mmm-windows.bat"
    #elif defined(Q_WS_MAC)
        "mmm-mac.sh"
    #else
        "mmm-linux.sh"
    #endif
    ;

    const QString kScriptLocation = kMmmLocation + kPS + kScriptName;

    QString getMinecraftApp();

    void prepareInstance(const QString&);

    void removeInstance(const QString&);

    QStringList listInstances();

    QString instancePath(const QString&);

    QString instanceMcPath(const QString&);

    QString scriptText(const QString&);

    void createScript(const QString&);

    bool isInitialized();

    void initialize();

    void openFolder(const QString&);

    void launchInstance(const QString&);
}
