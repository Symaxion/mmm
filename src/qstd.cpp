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

#include "qstd.h"

#include <QtCore/QFile.h>
#include <QtCore/QDir.h>
#include <QtCore/QDirIterator.h>

#include <cstdlib>

#ifndef Q_WS_WIN
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace qstd {
    bool mkdir(const QString& s) {
    	QDir d;
    	return d.mkdir(s);
    }

    bool mkdirs(const QString& s) {
    	QDir d;
    	return d.mkpath(s);
    }

    void deltree(const QString& s) {
        QDirIterator it(s, QDir::AllEntries | QDir::Hidden |
                QDir::NoDotAndDotDot);
        while(it.hasNext()) {
            it.next();
            if(it.fileInfo().isDir() && ! it.fileInfo().isSymLink()) {
                deltree(it.filePath());
            } else {
                QFile::remove(it.filePath());
            }

        }
        QDir().rmdir(s);
    }

    int system(const QString& s) {
    	return std::system(qPrintable(s));
    }

    int chmod(const QString& s) {
    #ifndef Q_WS_WIN
        return chmod(qPrintable(s));
    #else
        return -1;
    #endif
    }
}
