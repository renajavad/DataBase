#include "visual.h"

Visual::Visual(QWidget *parent) : QWidget(parent) {
    tableView();
    ssignals();

    QString pathToDatabase = "/home/student-5/SQLite/project2/people2.db";
    dbManager = new DbManager(pathToDatabase);

    setFixedSize(250, 250);
}

void Visual::addPerson() {
    QString name = line->text();
    if (!name.isEmpty()) {
        if (dbManager->addPerson(name)) {
            QMessageBox::information(this, "Success", "Person added successfully.");
            line->clear();
        } else {
            QMessageBox::warning(this, "Error", "Failed to add person.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Please enter a name.");
    }
}

void Visual::removePerson() {
    QString name = line->text();
    if (!name.isEmpty()) {
        if (dbManager->removePerson(name)) {
            QMessageBox::information(this, "Success", "Person removed successfully.");
            line->clear();
        } else {
            QMessageBox::warning(this, "Error", "Failed to remove person.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Please enter a name.");
    }
}

void Visual::printAll() {
    QDialog *printAllDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(printAllDialog);

    QStringList records;
    QSqlQuery query("SELECT * FROM people");
    while (query.next()) {
        QString name = query.value("name").toString();
        records.append(name);
    }

    QString allRecordsText = "People in list: \n";
    for (const QString& record : records) {
        allRecordsText += record + "\n";
    }

    QTextEdit *textEdit = new QTextEdit(printAllDialog);
    textEdit->setPlainText(allRecordsText);
    textEdit->setReadOnly(true);

    layout->addWidget(textEdit);

    QFont font;
    font.setPointSize(12);
    textEdit->setFont(font);

    printAllDialog->setWindowTitle("Database");
    printAllDialog->resize(400, 400);

    printAllDialog->exec();
}

void Visual::removeAll() {
    if (dbManager->removeAll()) {
        QMessageBox::information(this, "Success", "All records removed successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to remove all records.");
    }
}

void Visual::checkPersonExists() {
    QString name = line->text();
    if (!name.isEmpty()) {
        if (dbManager->personExists(name)) {
            QMessageBox::information(this, "Result", "Person exists.");
        } else {
            QMessageBox::information(this, "Result", "Person does not exist.");
        }
    } else {
        QMessageBox::warning(this, "Error", "Please enter a name.");
    }
}

void Visual::tableView() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(1);

    setStyleSheet("background-color: #D8BFD8");

    lineUp = new QLabel("Name:  ", this);
    lineUp->setStyleSheet("QLabel { font-size: 16px; color: black; }");

    line = new QLineEdit(this);
    line->setStyleSheet("QLineEdit { width: 200px; height: 40px; color: black; background-color: #DA70D6;}");

    addButton = new QPushButton("Add", this);
    addButton->setStyleSheet("QPushButton { width: 150px; height: 50px; background-color: #DA70D6; color: black; }");

    removeButton = new QPushButton("Remove", this);
    removeButton->setStyleSheet("QPushButton { width: 150px; height: 50px; background-color: #DA70D6; color: black; }");

    printButton = new QPushButton("Print All", this);
    printButton->setStyleSheet("QPushButton { width: 150px; height: 50px; background-color: #DA70D6; color: black;}");

    topLayout->addWidget(lineUp);
    topLayout->addWidget(line);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(removeButton);
    buttonsLayout->addWidget(printButton);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonsLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout();
    bottomLayout->setSpacing(1);

    removeAllButton = new QPushButton("Remove All", this);
    removeAllButton->setStyleSheet("QPushButton { width: 150px; height: 50px; background-color: #DA70D6; color: black; }");

    checkExistsButton = new QPushButton("Person Exists", this);
    checkExistsButton->setStyleSheet("QPushButton { width: 150px; height: 50px; background-color: #DA70D6; color: black;}");

    bottomLayout->addWidget(removeAllButton);
    bottomLayout->addWidget(checkExistsButton);

    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
    }

void Visual::ssignals() {
    connect(addButton, &QPushButton::clicked, this, &Visual::addPerson);
    connect(removeButton, &QPushButton::clicked, this, &Visual::removePerson);
    connect(printButton, &QPushButton::clicked, this, &Visual::printAll);
    connect(removeAllButton, &QPushButton::clicked, this, &Visual::removeAll);
    connect(checkExistsButton, &QPushButton::clicked, this, &Visual::checkPersonExists);
}
