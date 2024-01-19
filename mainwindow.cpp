#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    filePath = "";
    ui->textEdit->setText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString path{QFileDialog::getOpenFileName(this, "Open a file")};

    if(path.isEmpty())
    {
        return;
    }

    QFile file{path};

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Fail", "File could not be open");
        return;
    }

    filePath = path;

    QTextStream in(&file);
    QString text{in.readAll()};
    ui->textEdit->setText(text);
}

bool MainWindow::isFileCanBeSave(QFile &file)
{
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Fail", "File could not be saved");
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::saveFile(QFile &file)
{
    QTextStream out(&file);
    QString text{ui->textEdit->toPlainText()};
    out << text;

    if(!file.flush())
    {
        QMessageBox::warning(this, "Warning", "file could not be flused");
    }
    file.close();
}


void MainWindow::on_actionSave_triggered()
{
    if(filePath.isEmpty() || filePath.isNull())
    {
        on_actionSave_as_triggered();
    }
    else
    {
        QFile file{filePath};
        if(isFileCanBeSave(file))
        {
            saveFile(file);
        }
    }
}


void MainWindow::on_actionSave_as_triggered()
{
    QString path{QFileDialog::getSaveFileName(this, "Save as")};

    if(path.isEmpty())
    {
        return;
    }

    QFile file{path};

    if(isFileCanBeSave(file))
    {
        saveFile(file);
        filePath = path;
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    if(ui->textEdit->canPaste())
    {
        ui->textEdit->paste();
    }
    else
    {
        QMessageBox::warning(this, "Paste fail", "Unable to paste");
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About", " Notepad Written in Qt Widgets");
}


void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this, "About Qt");
}

