/** See mainwindow.cpp for the actual documentation.
 * @author Daniel "3ICE" Berezvai
 * @student_id 262849
 * @email daniel.berezvai@student.tut.fi
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void reset();
    void work();
    void avoidInfiniteLoop();
    void female_checked(bool);
    void male_checked(bool);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
