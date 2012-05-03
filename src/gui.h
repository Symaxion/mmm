#include <QtGui/QWidget>

class QVBoxLayout;
class QHBoxLayout;
class QListWidget;
class QPushButton;

class Gui : public QWidget {
    Q_OBJECT
public:
    Gui(QWidget* parent = 0); 

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
