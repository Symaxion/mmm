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

#include "instance.h"

#include "os.h"
#include "qstd.h"

#include <QtCore/QDir>

#include <QtCore/QDebug>

Instance::Instance(const QString& name, QListWidget* parent) :
        QListWidgetItem(name, parent), mDefaultInstance(name == "Default"){
    loadIcon();
}

Instance::Instance(const Instance& other) : QListWidgetItem(other),
            mDefaultInstance(other.mDefaultInstance) {
}

QDir Instance::path() const {
    if(name() == "Default") return OS::kDefaultInstance;
    else return OS::kMmmLocation + OS::kPS + name();
}

QDir Instance::mcpath() const {
    if(name() == "Default") return OS::kDefaultInstanceMcPath;
#ifdef Q_WS_MAC
    return path().absolutePath() + "/minecraft";
#else
    return path().absolutePath() + OS::kPS + ".minecraft";
#endif
}

bool Instance::exists() const {
    return path().exists();
}

void Instance::create() {
    OS::prepareInstance(path());
    qstd::mkdir(mcpath().absolutePath());
}

void Instance::remove() {
    qstd::deltree(path().absolutePath());
}

void Instance::launch() const {
    OS::launchInstance(path().absolutePath());
}

void Instance::openFolder() const {
    if(name() == "Default") {
        OS::openFolder(OS::kDefaultInstanceMcPath);
    } else {
        OS::openFolder(mcpath().absolutePath());
    }
}


void Instance::loadIcon() {
    if(isDefaultInstance()) {
        setIcon(QIcon(":/img/mc-block-glow.png"));
    } else if(path().exists("icon.png")) {
        setIcon(QIcon(path().filePath("icon.png")));
    } else {
        setIcon(QIcon(":/img/mc-block.png"));
    }
}

bool Instance::operator==(const QListWidgetItem& o) const {
    return text() == o.text();
}

bool Instance::operator<(const QListWidgetItem& o) const {
    QString me = text().toLower();
    QString you = o.text().toLower();

    if(me == you) {
        return false;
    } else if(me == "default") {
        return true;
    } else if(you == "default") {
        return false;
    } else if(you == "add new instance...") {
        return true;
    } else {
        return me < you;
    }
}
