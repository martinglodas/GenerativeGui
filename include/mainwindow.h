#pragma once

#include <QString>
#include <QToolBar>
#include <QDockWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QSlider>
#include <QTimeEdit>
#include <QMainWindow>
#include <QMenu>
#include <QStatusBar>
#include <memory>
#include <QLabel>
#include <OpenGL/gldisplay.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GLDisplay *getGlPanel() const {return gl_panel;}
    QTabWidget *getTabs() {return tabs;}
    QMenu *getMainMenu() {return mainMenu;}
    void setMessage(const char *msg);
    void setRulerLabel(const char *msg);
    QSlider *getCurrentTimeSlider() {return _advance_slider;}
    QPushButton *get_ruler_button() {return _ruler_comput_btn;}
    QLabel *get_ruler_label() {return ruler_text;}

private:
    QToolBar *tools;
    QDockWidget *dock;
    QTabWidget *tabs;
    QMenu *mainMenu;
    GLDisplay *gl_panel;
    QStatusBar *status_bar;
    QLabel *status_text;
    QLabel *fps_text;
    QLabel *time_text;
    QLabel *ruler_text;

    // Toolbar simulation widgets
    QPushButton *_ruler_comput_btn;
    QPushButton *_play_pause_btn;
    QPushButton *_stop_btn;
    QTimeEdit *_start_time_selector;
    QTimeEdit *_end_time_selector;
    QSlider *_time_scale_slider;
    QSlider *_advance_slider;

    QString _style;


signals:

public slots:
    void playPauseSwap();
    void stopClicked();
    void setStartTime(const QTime &time);
    void setStopTime(const QTime &time);
    void setCurrentTime(int value);
    void setTimeScale(int value);
};
