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

#include "gui.h"

#include "os.h"
#include "instance.h"
#include "message.h"

#include <QtCore/QRegExp>
#include <QtCore/QTimer>
#include <QtGui/QMouseEvent>
#include <QtGui/QShortcut>
#include <QtGui/QInputDialog>
#include <QtGui/QMenu>
#include <QtGui/QLineEdit>
#include <QtGui/QFrame>

#include <QtCore/QDebug>

class AddInstanceButton : public QListWidgetItem {
public:
    AddInstanceButton(QListWidget* w = 0) :
            QListWidgetItem("", w), mNormal(":img/add.png") {
        setIcon(mNormal);
    }

    inline bool operator==(const QListWidgetItem&) const { return false; }
    inline bool operator!=(const QListWidgetItem&) const { return true;  }
    inline bool operator< (const QListWidgetItem&) const { return false; }
    inline bool operator> (const QListWidgetItem&) const { return true;  }
    inline bool operator<=(const QListWidgetItem&) const { return false; }
    inline bool operator>=(const QListWidgetItem&) const { return true;  }

private:
    QIcon mNormal;
};

Gui::Gui(QWidget* parent) : QListWidget(parent) {
    this->setViewMode(QListView::IconMode);
    this->setIconSize(QSize(48,48));
    this->setGridSize(QSize(112,96));
    this->setMovement(QListView::Static);
    this->setWordWrap(true);
    this->setWrapping(true);
    this->setResizeMode(QListView::Adjust);
    this->setSortingEnabled(true);

    this->addItem(new Instance("Default", this));

    foreach(QString s, OS::listInstances()) {
        this->insertInstance(s);
    }

    mAddButton = new AddInstanceButton(this);
    mAddButton->setFlags(mAddButton->flags() & ~Qt::ItemIsSelectable);
    this->addItem(mAddButton);

    // Connections
    connect(this, SIGNAL(itemClicked(QListWidgetItem*)),
            this, SLOT(onItemClick(QListWidgetItem*)));
    connect(this, SIGNAL(itemActivated(QListWidgetItem*)),
            this, SLOT(onItemActivate(QListWidgetItem*)));

    // Shortcuts
    QShortcut* del = new QShortcut(
#ifdef Q_WS_MAC
    Qt::Key_Backspace
#else
    Qt::Key_Delete
#endif
    , this);
    connect(del, SIGNAL(activated()), this, SLOT(onDeleteKey()));

    QShortcut* openfolder = new QShortcut(Qt::CTRL | Qt::Key_I,
            this);
    connect(openfolder, SIGNAL(activated()), this, SLOT(onOpenInstance()));

    QShortcut* newinst = new QShortcut(QKeySequence::New, this);
    connect(newinst, SIGNAL(activated()), this, SLOT(addInstance()));

    // Context menu
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)),
        this, SLOT(onContextMenu(const QPoint&)));
} 


bool Gui::containsInstance(const QString& name) const {
    for(int i = 0; i < count(); ++i) {
        if(Instance* inst = dynamic_cast<Instance*>(item(i))) {
            if(inst->name() == name) return true;
        }
    }
    return false;
}

void Gui::onItemClick(QListWidgetItem* item) {
    // Check if this is the add button
    if(!dynamic_cast<Instance*>(item)) {
        addInstance();
    }
}

void Gui::onItemActivate(QListWidgetItem* item) {
    // Check if this is an instance
    if(Instance* inst = dynamic_cast<Instance*>(item)) {
        inst->launch();
    }
}

void Gui::onDeleteKey() {
    QList<QListWidgetItem*> list = selectedItems();
    if(list.count() == 0) return;
    Instance* inst = dynamic_cast<Instance*>(list[0]);
    if(inst && inst->name() != "Default") {
        removeInstance(inst);
    }
}

void Gui::onContextMenu(const QPoint& p) {
    //QPoint gp = this->viewport()->mapToGlobal(p);
    QListWidgetItem* it = this->itemAt(p);

    Instance* in;
    if(it && (in = dynamic_cast<Instance*>(it))) {
        in->rightClickMenu(this->viewport()->mapToGlobal(p));
    } else {
        QMenu m;
        m.addAction("New instance...", this, SLOT(addInstance()),
                QKeySequence::New);
        m.exec(this->viewport()->mapToGlobal(p));
    }
}

bool Gui::addInstance() {
    QString name = QInputDialog::getText(this, "Name your new instance",
            "Please give a name to the new instance: ");
    if(name == "") return false;

    if(!checkInstanceName(name)) {
        // Name invalid
        Message::error("Error", "That name contains invalid characters.\n"
                "You can only use a-z, A-Z, 0-9, '-', '_', '.', '(', ')' and "
                "spaces.");
        return false;
    }

    if(containsInstance(name)) {
        // Duplicate item
        Message::error("Error",
                "You already have an instance with that name.");
        return false;
    }

    Instance* i = insertInstance(name);
    i->create();

    return true;
}

Instance* Gui::insertInstance(const QString& name) {
    Instance* inst = new Instance(name, this);

    addItem(inst);

    return inst;
}


bool Gui::removeInstance(Instance* inst) {
    if(Message::question("Are you sure?",
            "Are you sure you want to remove the instance \""+
            inst->name()+"\"?") == QMessageBox::Yes) {
        takeItem(row(inst));
        inst->remove();
        delete inst;
        return true;
    }
    return false;
}


void Gui::onOpenInstance() const {
    QList<QListWidgetItem*> list = selectedItems();
    if(list.count() == 0) return;
    Instance* inst = dynamic_cast<Instance*>(list[0]);
    if(inst) {
        inst->openFolder();
    }
}

bool Gui::checkInstanceName(const QString& name) const {
    return QRegExp("[a-zA-Z0-9 \\-_.()]+").exactMatch(name);
}





