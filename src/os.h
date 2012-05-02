#include <QtCore/QString>
#include <QtCore/QDir>

#include <cstdlib>

namespace OS {
    

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

    const QString kMmmLocation = 
    #if defined(Q_WS_WIN)
        QString(std::getenv("APPDATA")) + "/.mmm"
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

    const QString kScriptLocation = kMmmLocation + "/" + kScriptName;

    QString getMinecraftApp();

    void prepareInstance(const QString&);

    QString scriptText(const QString&);

    void createScript(const QString&);

    bool isInitialized();

    void initialize();
}
