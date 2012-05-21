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

#ifndef MMM_MESSAGE_H_
#define MMM_MESSAGE_H_

#include <QtGui/QMessageBox.h>

namespace Message {
    inline QMessageBox::StandardButton error(const QString& t,
            const QString& s) {
        return QMessageBox::critical(0, t, s);
    }

    inline QMessageBox::StandardButton info(const QString& t,
            const QString& s) {
        return QMessageBox::information(0, t, s);

    }

    inline QMessageBox::StandardButton question(const QString& t,
            const QString& s, QMessageBox::StandardButtons opts =
            QMessageBox::Yes | QMessageBox::No) {
        return QMessageBox::question(0, t, s,
                opts);

    }

    inline QMessageBox::StandardButton warning(const QString& t,
            const QString& s) {
        return QMessageBox::warning(0, t, s);

    }
}

#endif /* MMM_MESSAGE_H_ */
