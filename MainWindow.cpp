#include "MainWindow.h"

#include <QDebug>
#include <QFile>
#include <QIODevice>

MainWindow::MainWindow(QQmlApplicationEngine *engine) :
    viewer(engine)
{
}

void MainWindow::translateText(QString text)    {

    qDebug() << text;
    const char* ch_text = text.toStdString().c_str();

    QRegExp rx1("^[.- ]*$");          //! проверяем морзе
    QRegExp rx2("^[A-z0-9. ]*$");     //! проверяем английскую раскладку

    //! Если черточки и точки то считаем что морзе, иначе если буквы то инглиш
    if(rx1.indexIn(text) != -1){
        QObject *root  = viewer->rootObjects()[0];
        QObject *t_obj = root->findChild<QObject*>("textTarget");
        t_obj->setProperty("text", translateMorse(ch_text));
    }
    else if(rx2.indexIn(text) != -1){        
        text = text.toUpper();

        QObject *root  = viewer->rootObjects()[0];
        QObject *t_obj = root->findChild<QObject*>("textTarget");
        t_obj->setProperty("text", translateEng(ch_text));        
    }
}

void MainWindow::loadFile(QString path) {
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly))
        return;

    QString text = "";

    QTextStream ts_text(&file);
    while(!ts_text.atEnd()) {
        text += ts_text.readLine();
    }

    file.close();

    QObject *root  = viewer->rootObjects()[0];
    QObject *t_obj = root->findChild<QObject*>("textSource");
    t_obj->setProperty("text", text);
}

void MainWindow::saveFile(QString path, QString text) {
    qDebug() << path << "|" << text;
    if(QFile::exists(path + "/morseTrl.txt"))
        QFile::remove(path + "/morseTrl.txt");

    QFile file(path + "/morseTrl.txt");

    if(!file.open(QIODevice::WriteOnly))
        return;

    QTextStream ts_text(&file);
    ts_text << text;

    file.close();
}

QString MainWindow::translateEng(const char* chr) {

    QString returnStr = "";
    for(int i = 0; i < sizeof(chr); i++)   {
        QString s_chr = QString(chr[i]);
        returnStr += engToMorse(s_chr);
    }

    return returnStr;
}

QString MainWindow::translateMorse(const char* chr) {

    QString returnStr = "";

    QString s_word = "";
    int i = 0;

    qDebug() << "sizeoff: " << sizeof(chr);
    while(i < sizeof(chr)){
        qDebug() << "index: " << i;
        qDebug() << "chr[i]: " << chr[i];

        if(chr[i] == ' '){
            returnStr += morseToEng(s_word);
            s_word = "";

            if((i+1) < sizeof(chr))
                if(chr[i+1] == ' ') {
                    returnStr += morseToEng("  ");
                    i += 1;
                }
        }
        else
            s_word += QString(chr[i]);

        qDebug() << "s_word: " << s_word;

        i++;
    }
    returnStr += morseToEng(s_word);

    return returnStr;
}

QString MainWindow::engToMorse(QString str) {
    if(str == "A")
        return ".- ";
    else if(str == "B")
        return "-... ";
    else if(str == "C")
        return "-.-. ";
    else if(str == "D")
        return "-.. ";
    else if(str == "E")
        return ". ";
    else if(str == "F")
        return "..-. ";
    else if(str == "G")
        return "--. ";
    else if(str == "H")
        return ".... ";
    else if(str == "I")
        return ".. ";
    else if(str == "J")
        return ".--- ";
    else if(str == "K")
        return "-.- ";
    else if(str == "L")
        return ".-.. ";
    else if(str == "M")
        return "-- ";
    else if(str == "N")
        return "-. ";
    else if(str == "O")
        return "--- ";
    else if(str == "P")
        return ".--. ";
    else if(str == "Q")
        return "--.- ";
    else if(str == "R")
        return ".-. ";
    else if(str == "S")
        return "... ";
    else if(str == "T")
        return "- ";
    else if(str == "U")
        return "..- ";
    else if(str == "V")
        return "...- ";
    else if(str == "W")
        return ".-- ";
    else if(str == "X")
        return "-..- ";
    else if(str == "Y")
        return "-.-- ";
    else if(str == "Z")
        return "--.. ";
    else if(str == " ")
        return "  ";
    else
        return "";
}

QString MainWindow::morseToEng(QString str) {
    if(str == ".-")
        return "A";
    else if(str == "-...")
        return "B";
    else if(str == "-.-.")
        return "C";
    else if(str == "-..")
        return "D";
    else if(str == ".")
        return "E";
    else if(str == "..-.")
        return "F";
    else if(str == "--.")
        return "G";
    else if(str == "....")
        return "H";
    else if(str == "..")
        return "I";
    else if(str == ".---")
        return "J";
    else if(str == "-.-")
        return "K";
    else if(str == ".-..")
        return "L";
    else if(str == "--")
        return "M";
    else if(str == "-.")
        return "N";
    else if(str == "---")
        return "O";
    else if(str == ".--.")
        return "P";
    else if(str == "--.-")
        return "Q";
    else if(str == ".-.")
        return "R";
    else if(str == "...")
        return "S";
    else if(str == "-")
        return "T";
    else if(str == "..-")
        return "U";
    else if(str == "...-")
        return "V";
    else if(str == ".--")
        return "W";
    else if(str == "-..-")
        return "X";
    else if(str == "-.--")
        return "Y";
    else if(str == "--..")
        return "Z";
    else if(str == "  ")
        return " ";
    else
        return "";
}
