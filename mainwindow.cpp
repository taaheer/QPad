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

void MainWindow::handleFileOperation(const QString &path, const QString &operation)
{
    if(path.isEmpty())
    {
        return;
    }

    QFile file{path};

    if(operation == "open")
    {
        if(!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Fail", "File could not be open");
            return;
        }
    }
    else if(operation == "save")
    {
        if(!file.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this, "Fail", "File could not be saved");
            return;
        }
    }

    filePath = path;

    if(operation == "open")
    {
        QTextStream in(&file);
        QString text{in.readAll()};
        ui->textEdit->setText(text);
    }
    else if(operation == "save")
    {
        QTextStream out(&file);
        QString text{ui->textEdit->toPlainText()};
        out << text;
        if(!file.flush())
        {
            QMessageBox::warning(this, "Warning", "file could not be flused");
        }
    }
}


void MainWindow::on_actionOpen_triggered()
{
    QString path{QFileDialog::getOpenFileName(this, "Open a file")};
    handleFileOperation(path, "open");
}


void MainWindow::on_actionSave_triggered()
{
    if(filePath.isEmpty())
    {
        on_actionSave_as_triggered();
    }
    else
    {
        handleFileOperation(filePath, "save");
    }
}


void MainWindow::on_actionSave_as_triggered()
{
    QString path{QFileDialog::getSaveFileName(this, "Save as")};
    handleFileOperation(path, "save");
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

