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

#ifndef MMM_INSTANCE_H_
#define MMM_INSTANCE_H_

#include <QtGui/QListWidget>
#include <QtCore/QPoint>

class QDir;

class Instance : public QObject, public QListWidgetItem {
    Q_OBJECT
public:
    Instance(const QString& name, QListWidget* parent = 0);
    Instance(const Instance& other);

    inline QString name() const {
        return text();
    }

    QDir path() const;
    QDir mcpath() const;

    bool exists() const;

    void loadIcon();

    void rightClickMenu(const QPoint&);

    inline bool isDefaultInstance() const {
        return mDefaultInstance;
    }

    bool operator==(const QListWidgetItem& o) const;

    inline bool operator!=(const QListWidgetItem& o) const {
        return !(*this == o);
    }

    bool operator<(const QListWidgetItem& o) const;

    inline bool operator>(const QListWidgetItem& o) const {
        return !(*this < o || *this == o);
    }

    inline bool operator<=(const QListWidgetItem& o) const {
        return (*this < o) || (*this == o);
    }

    inline bool operator>=(const QListWidgetItem& o) const {
        return !(*this < o);
    }

public slots:
    void create();
    void remove();

    void launch() const;
    void openFolder() const;
    void removeFromGui();
private:
    bool mDefaultInstance;
};


#endif /* MMM_INSTANCE_H_ */
