#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlApplicationEngine>


class MainWindow : public QObject
{
    Q_OBJECT

public:
    explicit MainWindow(QQmlApplicationEngine *engine);

public slots:
    void translateText(QString text);        //!< Принимаем текст и отправляем обратно
    void saveFile(QString path, QString text);             //!< Сохраняем файл
    void loadFile(QString path);             //!< Загружаем файл

private:
    QString translateEng(const char* chr);   //!< Отправляем на перевод инглиша
    QString translateMorse(const char* chr); //!< Отправляем на перевод морзе
    QString engToMorse(QString str);         //!< Конвертим букву инглиш в морзе
    QString morseToEng(QString str);         //!< Конвертим букву морзе в инглиш

private:
    QQmlApplicationEngine *viewer;
};

#endif // MAINWINDOW_H
