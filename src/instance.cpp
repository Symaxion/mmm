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
#include "gui.h"
#include "qstd.h"
#include "message.h"

#include <QtCore/QDir>
#include <QtGui/QMenu>
#include <QtGui/QFileDialog>

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
    if(isDefaultInstance()) return; // Cannot purge default instance!
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

void Instance::removeFromGui() {
    if(isDefaultInstance()) return; // Cannot purge default instance!
    dynamic_cast<Gui*>(listWidget())->removeInstance(this);
}

void Instance::browseForIcon() {
    QString icpath = QFileDialog::getOpenFileName(0,
                    "Select an icon", ".", "*.png");
    if(icpath == "") return;
    if(!QFile::copy(icpath, path().filePath("icon.png"))) {
        Message::error("File copy error", "Error: could not copy file.");
    }

    loadIcon();
}

void Instance::rightClickMenu(const QPoint& p) {
    QMenu m;
    m.addAction("Launch...", this, SLOT(launch()));
    m.addAction("Open Folder...", this, SLOT(openFolder()),
            QKeySequence(Qt::CTRL | Qt::Key_I));
    if(!isDefaultInstance()) {
        m.addSeparator();
        m.addAction("Browse for icon...", this, SLOT(browseForIcon()));
        m.addAction("Remove", this, SLOT(removeFromGui()));
    }
    m.exec(p);
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
    } else if(you == "") {
        return true;
    } else {
        return me < you;
    }
}
