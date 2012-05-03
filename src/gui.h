#include <QtGui/QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QPushButton;

class Gui : public QWidget {
    Q_OBJECT
public:
    Gui(QWidget* parent = 0); 

    bool addInstance(const QString&);
    bool removeInstance(const QString&);
    void launchInstance(const QString&);
    void openInstance(const QString&);

    bool containsInstance(const QString&) const;

private:
    bool checkInstanceName(const QString&);

private slots:
    void addButtonEvent();
    void removeButtonEvent();
    void openButtonEvent();
    void launchButtonEvent();

private:
    QVBoxLayout* mLayout;
    QListWidget* mListWidget;
    QWidget* mButtonContainer;
    QHBoxLayout* mButtonLayout;
    QPushButton* mAddButton;
    QPushButton* mRemoveButton;
    QPushButton* mOpenButton;
    QPushButton* mLaunchButton;
};
