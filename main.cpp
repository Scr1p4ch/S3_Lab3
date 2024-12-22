#include <iostream>

#include "HashTable/Hash.h"
#include "HashTable/HashTable.h"
#include "HashTable/List.h"
#include "HashTable/IDictionary.h"
#include "Problems/MostFrequent.h"

#include "Tests/PtrWrapperTest.h"
#include "Tests/DynamicArrayTest.h"
#include "Tests/IDictionaryTest.h"
#include "Tests/SparceVectorTest.h"

#include "Utility/FirstLabUtility/Sequence.h"
#include "Problems/AlphabetIndex/Rows.h"
#include "Problems/AlphabetIndex/HelperFunctions.h"
#include "Problems/AlphabetIndex/AlphabetIndex.h"

#include "Problems/SparceVector.h"



#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QMainWindow>
#include <QLabel>
#include <QFileDialog>
#include <QLineEdit>
#include <QIntValidator>
#include <QComboBox>
#include <QObject>
#include <QTextEdit>
#include <QEventLoop>
#include <QTimer>
#include <QSplitter>


void delay(int milliseconds) {
    QEventLoop loop;
    QTimer::singleShot(milliseconds, &loop, &QEventLoop::quit);
    loop.exec();
}

void runAllTests(QTextEdit* logWidget) {
    logWidget->append("DynamicArrayTest - запущен");
    delay(500);
    DynamicArrayTest();
    logWidget->append("DynamicArrayTest - пройден");

    logWidget->append("PtrWrapperTest - запущен");
    delay(500);
    PtrWrapperTest();
    logWidget->append("PtrWrapperTest - пройден");

    logWidget->append("SparceVectorTest - запущен");
    delay(500);
    sparceVectorTest();
    logWidget->append("SparceVectorTest - пройден");

    logWidget->append("IDictionaryTest - запущен");
    delay(500);
    IDictionaryTest();
    logWidget->append("IDictionaryTest - пройден");
    delay(500);

    logWidget->append("Все тесты успешно выполнены!");
}

void thirdBtnClick(QTextEdit* logWidget) {
    logWidget->clear(); // Очищаем лог перед запуском тестов
    runAllTests(logWidget);
}

QWidget* createFirstWindow(QStackedWidget* stackedWidget) {
    QWidget* widget = new QWidget;

    widget->setWindowTitle("Lab3");
    widget->setMinimumWidth(650);
    widget->setMinimumHeight(500);

    auto* layout = new QVBoxLayout(widget);

    auto* btn1 = new QPushButton("Алфавитный указатель", widget);
    auto* btn2 = new QPushButton("Наиболее частые подпоследовательности", widget);
    auto* btn3 = new QPushButton("Запустить тесты", widget);
    auto* logWidget = new QTextEdit(widget); // Виджет для отображения логов
    logWidget->setReadOnly(true);

    layout->addWidget(btn1);
    layout->addWidget(btn2);
    layout->addWidget(btn3);
    layout->addWidget(logWidget);

    widget->setStyleSheet(R"(
        QWidget {
            background-color: lightGray; 
        }
        QPushButton {
            background-color: #2e7d32;  
            color: white;               
            border: 2px solid #1b5e20;  
            padding: 20px 40px;         
            font-size: 16px;            
            border-radius: 5px;         
        }
        QPushButton:hover {
            background-color: #388e3c;  
        }
        QPushButton:pressed {
            background-color: #1b5e20;  
        }
    )");

    QObject::connect(btn1, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(1); });
    QObject::connect(btn2, &QPushButton::clicked, [=]() { stackedWidget->setCurrentIndex(2); });
    QObject::connect(btn3, &QPushButton::clicked, [=]() { thirdBtnClick(logWidget); });

    return widget;
}


QWidget* createSecondWindow(QStackedWidget* stackedWidget) {
    QWidget* widget = new QWidget;

    widget->setWindowTitle("Second Window");
    widget->setMinimumWidth(650);
    widget->setMinimumHeight(500);

    // Основной макет окна
    auto* mainLayout = new QVBoxLayout(widget);

    // Кнопка "Назад"
    auto* backButton = new QPushButton("Назад", widget);
    backButton->setFixedSize(100, 30);
    QObject::connect(backButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(0);
    });

    // Поле выбора файла
    auto* fileButton = new QPushButton("Выбрать файл", widget);
    fileButton->setFixedSize(150, 30);
    QLineEdit* filePathInput = new QLineEdit(widget);
    filePathInput->setPlaceholderText("Выбранный файл");
    filePathInput->setReadOnly(true);

    auto* fileLayout = new QHBoxLayout();
    fileLayout->addWidget(fileButton);
    fileLayout->addWidget(filePathInput);

    QObject::connect(fileButton, &QPushButton::clicked, [=]() {
        QString filePath = QFileDialog::getOpenFileName(widget, "Выберите файл");
        if (!filePath.isEmpty()) {
            filePathInput->setText(filePath);
        }
    });

    // Поля для ввода чисел
    auto* pageSizeInput = new QLineEdit(widget);
    pageSizeInput->setPlaceholderText("Размер страницы");
    pageSizeInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* rowSizeInput = new QLineEdit(widget);
    rowSizeInput->setPlaceholderText("Размер строки");
    rowSizeInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(pageSizeInput);
    inputLayout->addWidget(rowSizeInput);

    // Кнопка запуска
    auto* startButton = new QPushButton("Построить индекс", widget);
    startButton->setFixedSize(150, 30);

    // Разделитель экрана (1 к 3)
    auto* splitter = new QSplitter(Qt::Horizontal, widget);

    // Первая часть (маленький текстовый виджет)
    auto* smallTextWidget = new QTextEdit(widget);
    smallTextWidget->setPlaceholderText("Текст из output.txt");
    smallTextWidget->setReadOnly(true);
    smallTextWidget->setMinimumWidth(100);

    // Вторая часть (большой текстовый виджет)
    auto* largeTextWidget = new QTextEdit(widget);
    largeTextWidget->setPlaceholderText("Текст из bookOutput.txt");
    largeTextWidget->setReadOnly(true);

    splitter->addWidget(smallTextWidget);
    splitter->addWidget(largeTextWidget);
    splitter->setStretchFactor(0, 1); // Устанавливаем соотношение 1
    splitter->setStretchFactor(1, 3); // Устанавливаем соотношение 3

    QObject::connect(startButton, &QPushButton::clicked, [=]() {
        QString filePath = filePathInput->text();
        QString pageSizeText = pageSizeInput->text();
        QString rowSizeText = rowSizeInput->text();

        if (filePath.isEmpty() || pageSizeText.isEmpty() || rowSizeText.isEmpty()) {
            QMessageBox::warning(widget, "Ошибка", "Заполните все поля и выберите файл!");
            return;
        }

        int pageSize = pageSizeText.toInt();
        int rowSize = rowSizeText.toInt();

        try {
            startBuildingIndex(filePath.toStdString(), pageSize, rowSize);

            // Чтение текста из файлов
            QFile outputFile("D:/LabWorks/S3_Lab3/Tests/output.txt");
            QFile bookOutputFile("D:/LabWorks/S3_Lab3/Tests/bookOutput.txt");

            if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                smallTextWidget->setText(outputFile.readAll());
                outputFile.close();
            } else {
                smallTextWidget->setText("Не удалось открыть output.txt");
            }

            if (bookOutputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                largeTextWidget->setText(bookOutputFile.readAll());
                bookOutputFile.close();
            } else {
                largeTextWidget->setText("Не удалось открыть bookOutput.txt");
            }

        } catch (const std::exception& ex) {
            QMessageBox::critical(widget, "Ошибка", QString("Произошла ошибка: %1").arg(ex.what()));
        }
    });

    // Добавление виджетов в основной макет
    mainLayout->addWidget(backButton);
    mainLayout->addLayout(fileLayout);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(splitter);

    widget->setStyleSheet(R"(
        QPushButton {
            background-color: #2e7d32;
            color: white;
            border: 1px solid #1b5e20;
            padding: 5px 15px;
            font-size: 14px;
            border-radius: 5px;
        }
        QPushButton:hover {
            background-color: #388e3c;
        }
        QPushButton:pressed {
            background-color: #1b5e20;
        }
        QTextEdit {
            border: 1px solid #bdbdbd;
            font-size: 14px;
        }
        QLineEdit {
            border: 1px solid #bdbdbd;
            padding: 5px;
            font-size: 14px;
        }
    )");

    return widget;
}



int main(int argc, char* argv[]) {

    try {
        QApplication app(argc, argv);

        auto* mainWindow = new QWidget;
        auto* stackedWidget = new QStackedWidget(mainWindow);

        stackedWidget->addWidget(createFirstWindow(stackedWidget));
        stackedWidget->addWidget(createSecondWindow(stackedWidget));

        auto* mainLayout = new QVBoxLayout(mainWindow);
        mainLayout->addWidget(stackedWidget);

        mainWindow->setLayout(mainLayout);
        mainWindow->resize(450, 300);
        mainWindow->show();

        return app.exec();
    } catch (const std::exception& ex) {
        qCritical() << "Exception: " << ex.what();
        return -1;
    } catch(...) {
        qCritical() << "Unknown exception occurred!";
        return -1;
    }


}