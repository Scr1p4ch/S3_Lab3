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

#include <QLineEdit>
#include <QScrollBar>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QStackedWidget>
#include <QMainWindow>
#include <QLabel>
#include <QList>
#include <QFileDialog>
#include <QLineEdit>
#include <QIntValidator>
#include <QComboBox>
#include <QObject>
#include <QTextEdit>
#include <QEventLoop>
#include <QTimer>
#include <QSplitter>
#include <QTextCursor>
#include <QTextCharFormat>
#include <QTextBrowser>
#include <QBrush>



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

    // Первая часть (маленький текстовый виджет с гиперссылками)
    auto* smallTextWidget = new QTextBrowser(widget);
    smallTextWidget->setOpenLinks(false);

    // Вторая часть (большой текстовый виджет)
    auto* largeTextWidget = new QTextEdit(widget);
    largeTextWidget->setPlaceholderText("Текст из bookOutput.txt");
    largeTextWidget->setReadOnly(true);

    splitter->addWidget(smallTextWidget);
    splitter->addWidget(largeTextWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 3);


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

        if (pageSize <= 0 || rowSize <= 0) {
            QMessageBox::warning(widget, "Ошибка", "Размер страницы и размер строки должны быть больше нуля!");
            return;
        }

        try {
            startBuildingIndex(filePath.toStdString(), pageSize, rowSize);

            QFile outputFile("D:/LabWorks/S3_Lab3/Tests/output.txt");
            QFile bookOutputFile("D:/LabWorks/S3_Lab3/Tests/bookOutput.txt");

            if (outputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QString content;
                QTextStream in(&outputFile);
                while (!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList parts = line.split(":");
                    if (parts.size() == 2) {
                        QString word = parts[0].trimmed();
                        QString occurrences = parts[1].trimmed();
                        content.append(QString("<a href='%1'>%1</a>: %2<br>").arg(word, occurrences));
                    }
                }
                smallTextWidget->setHtml(content);
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

    QObject::connect(smallTextWidget, &QTextBrowser::anchorClicked, [=](const QUrl& url) {
    QString word = url.toString(); // Слово из клика
    static QTextCursor cursor(largeTextWidget->document());
    static QString lastWord; // Для отслеживания последнего слова

    // Если выбрано новое слово, начинаем поиск с начала документа
    if (lastWord != word) {
        cursor = QTextCursor(largeTextWidget->document());
        cursor.movePosition(QTextCursor::Start);
        lastWord = word;
    }

    // Сброс предыдущего выделения
    QTextEdit::ExtraSelection clearSelection;
    clearSelection.cursor = cursor;
    clearSelection.format.setBackground(Qt::transparent);
    largeTextWidget->setExtraSelections({clearSelection});

    // Поиск слова в тексте
    cursor = largeTextWidget->document()->find(word, cursor);

    // Если слово не найдено с текущей позиции, начать поиск заново
    if (cursor.isNull()) {
        cursor = QTextCursor(largeTextWidget->document());
        cursor.movePosition(QTextCursor::Start);
        cursor = largeTextWidget->document()->find(word, cursor);
    }

    if (!cursor.isNull()) {
        QTextEdit::ExtraSelection selection;
        selection.cursor = cursor;
        selection.format.setBackground(Qt::yellow);
        largeTextWidget->setExtraSelections({selection});

        // Установить курсор и прокрутить к нему
        largeTextWidget->setTextCursor(cursor);
        largeTextWidget->ensureCursorVisible();

        // Принудительно центрируем строку с курсором
        QRect cursorRect = largeTextWidget->cursorRect(cursor);
        largeTextWidget->verticalScrollBar()->setValue(
            largeTextWidget->verticalScrollBar()->value() + cursorRect.top() - largeTextWidget->height() / 2
        );

        // Перемещаем курсор на следующий символ, чтобы при следующем клике не находить то же слово
        cursor.movePosition(QTextCursor::NextCharacter);
    } else {
        QMessageBox::information(widget, "Не найдено", QString("Слово '%1' не найдено в тексте.").arg(word));
    }
});



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
        QTextEdit, QTextBrowser {
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

QWidget* createThirdWindow(QStackedWidget* stackedWidget) {
    QWidget* widget = new QWidget;

    widget->setWindowTitle("Third Window");
    widget->setMinimumWidth(500);
    widget->setMinimumHeight(400);

    // Основной макет
    auto* mainLayout = new QVBoxLayout(widget);

    // Кнопка "Назад"
    auto* backButton = new QPushButton("Назад", widget);
    backButton->setFixedSize(100, 30);
    QObject::connect(backButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(0);
    });

    // Поля для ввода lmin и lmax
    auto* lminInput = new QLineEdit(widget);
    lminInput->setPlaceholderText("lmin (неотрицательное число)");
    lminInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* lmaxInput = new QLineEdit(widget);
    lmaxInput->setPlaceholderText("lmax (неотрицательное число)");
    lmaxInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(lminInput);
    inputLayout->addWidget(lmaxInput);

    // Поле для ввода строки
    auto* stringInput = new QLineEdit(widget);
    stringInput->setPlaceholderText("Строка (до 50 символов, без пробелов)");
    stringInput->setMaxLength(50);
    QObject::connect(stringInput, &QLineEdit::textChanged, [=](const QString& text) {
        if (text.contains(' ')) {
            stringInput->setText(text.simplified().replace(" ", ""));
        }
    });

    // Кнопка запуска
    auto* startButton = new QPushButton("Запустить", widget);
    startButton->setFixedSize(150, 30);

    // Поле для лога (текстовое поле)
    auto* logOutput = new QTextBrowser(widget);
    logOutput->setReadOnly(true);
    logOutput->setFrameStyle(QFrame::Box | QFrame::Plain);
    logOutput->setStyleSheet("background-color: #f5f5f5; padding: 5px; font-size: 14px; text-align: left;");
    logOutput->setOpenLinks(false); // Отключение стандартной обработки ссылок

    // Добавьте переменную для отслеживания текущей позиции
    int currentIndex = 0;

    // Обработка кнопки запуска
    QObject::connect(startButton, &QPushButton::clicked, [=, &currentIndex]() mutable {
    QString lminText = lminInput->text();
    QString lmaxText = lmaxInput->text();
    QString inputText = stringInput->text();

    if (lminText.isEmpty() || lmaxText.isEmpty() || inputText.isEmpty()) {
        QMessageBox::warning(widget, "Ошибка", "Все поля должны быть заполнены!");
        return;
    }

    int lmin = lminText.toInt();
    int lmax = lmaxText.toInt();

    if (lmin > lmax) {
        QMessageBox::warning(widget, "Ошибка", "lmin не может быть больше lmax!");
        return;
    }

    if (lmax <= 0 || lmin <= 0) {
        QMessageBox::warning(widget, "Ошибка", "Числа должны быть больше нуля!");
        return;
    }

    try {
        // Вызов функции
        FileOutTheMostFrequentSubsequence(inputText.toStdString(), lmin, lmax);

        currentIndex = 0; // Сбрасываем индекс

        // Чтение результата из файла
        QString logFilePath = "D:/LabWorks/S3_Lab3/Tests/Subsequence.txt";
        QFile logFile(logFilePath);
        if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString content = logFile.readAll();

            // Форматирование результата в ссылки
            QStringList lines = content.split("\n", Qt::SkipEmptyParts);
            QString formattedContent;

            for (const QString& line : lines) {
                QStringList parts = line.split("\t", Qt::SkipEmptyParts);
                if (parts.size() >= 2) {
                    QString subsequence = parts[0].split(":")[1].trimmed();
                    QString count = parts[1].split(":")[1].trimmed();

                    formattedContent += QString("<a href=\"%1\">%1</a>: %2<br>").arg(subsequence).arg(count);
                }
            }

            logOutput->setHtml(formattedContent);

            // Удаляем предыдущий обработчик, если он существует
            QObject::disconnect(logOutput, &QTextBrowser::anchorClicked, nullptr, nullptr);

            // Обработка клика по ссылке
            QObject::connect(logOutput, &QTextBrowser::anchorClicked, [=, &currentIndex](const QUrl& link) mutable {
                QString subsequence = link.toString(); // Получаем текст ссылки

                // Поиск следующего вхождения, начиная с текущего индекса
                int startIndex = inputText.indexOf(subsequence, currentIndex);

                if (startIndex == -1) {
                    // Если не найдено, начать поиск с начала строки
                    startIndex = inputText.indexOf(subsequence, 0);
                }

                if (startIndex != -1) {
                    // Установить выделение
                    stringInput->setSelection(startIndex, subsequence.length());
                    
                    // Обновить currentIndex для учета перекрывающихся вхождений
                    currentIndex = startIndex + 1; // Сдвигаем только на 1 символ
                }
            });

            logFile.close();
        } else {
            logOutput->setPlainText("Не удалось открыть Subsequence.txt");
        }
    } catch (const std::exception& ex) {
        QMessageBox::critical(widget, "Ошибка", QString("Произошла ошибка: %1").arg(ex.what()));
    }
});


    // Добавление виджетов в макет
    mainLayout->addWidget(backButton);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(stringInput);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(logOutput);

    // Стилизация
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
        QTextEdit, QTextBrowser {
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

/*
QWidget* createThirdWindow(QStackedWidget* stackedWidget) {
    QWidget* widget = new QWidget;

    widget->setWindowTitle("Third Window");
    widget->setMinimumWidth(500);
    widget->setMinimumHeight(400);

    // Основной макет
    auto* mainLayout = new QVBoxLayout(widget);

    // Кнопка "Назад"
    auto* backButton = new QPushButton("Назад", widget);
    backButton->setFixedSize(100, 30);
    QObject::connect(backButton, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentIndex(0);
    });

    // Поля для ввода lmin и lmax
    auto* lminInput = new QLineEdit(widget);
    lminInput->setPlaceholderText("lmin (неотрицательное число)");
    lminInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* lmaxInput = new QLineEdit(widget);
    lmaxInput->setPlaceholderText("lmax (неотрицательное число)");
    lmaxInput->setValidator(new QIntValidator(1, 10000, widget));

    auto* inputLayout = new QHBoxLayout();
    inputLayout->addWidget(lminInput);
    inputLayout->addWidget(lmaxInput);

    // Поле для ввода строки
    auto* stringInput = new QLineEdit(widget);
    stringInput->setPlaceholderText("Строка (до 50 символов, без пробелов)");
    stringInput->setMaxLength(50);
    QObject::connect(stringInput, &QLineEdit::textChanged, [=](const QString& text) {
        if (text.contains(' ')) {
            stringInput->setText(text.simplified().replace(" ", ""));
        }
    });

    // Кнопка запуска
    auto* startButton = new QPushButton("Запустить", widget);
    startButton->setFixedSize(150, 30);

    // Поле для лога (текстовое поле)
    auto* logOutput = new QTextBrowser(widget);
    logOutput->setReadOnly(true);
    logOutput->setFrameStyle(QFrame::Box | QFrame::Plain);
    logOutput->setStyleSheet("background-color: #f5f5f5; padding: 5px; font-size: 14px; text-align: left;");
    logOutput->setOpenLinks(false); // Отключение стандартной обработки ссылок

    // Добавьте переменную для отслеживания текущей позиции
    int currentIndex = 0;

    // Обработка кнопки запуска
    QObject::connect(startButton, &QPushButton::clicked, [=, &currentIndex]() mutable {
        QString lminText = lminInput->text();
        QString lmaxText = lmaxInput->text();
        QString inputText = stringInput->text();

        if (lminText.isEmpty() || lmaxText.isEmpty() || inputText.isEmpty()) {
            QMessageBox::warning(widget, "Ошибка", "Все поля должны быть заполнены!");
            return;
        }

        int lmin = lminText.toInt();
        int lmax = lmaxText.toInt();

        if (lmin > lmax) {
            QMessageBox::warning(widget, "Ошибка", "lmin не может быть больше lmax!");
            return;
        }

        if (lmax <= 0 || lmin <= 0) {
            QMessageBox::warning(widget, "Ошибка", "Числа должны быть больше нуля!");
            return;
        }

        try {
            // Вызов функции
            FileOutTheMostFrequentSubsequence(inputText.toStdString(), lmin, lmax);

            // Чтение результата из файла
            QString logFilePath = "D:/LabWorks/S3_Lab3/Tests/Subsequence.txt";
            QFile logFile(logFilePath);
            if (logFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QString content = logFile.readAll();

                // Форматирование результата в ссылки
                QStringList lines = content.split("\n", Qt::SkipEmptyParts);
                QString formattedContent;

                for (const QString& line : lines) {
                    QStringList parts = line.split("\t", Qt::SkipEmptyParts);
                    if (parts.size() >= 2) {
                        QString subsequence = parts[0].split(":")[1].trimmed();
                        QString count = parts[1].split(":")[1].trimmed();

                        formattedContent += QString("<a href=\"%1\">%1</a>: %2<br>").arg(subsequence).arg(count);
                    }
                }

                logOutput->setHtml(formattedContent);

                // Обработка клика по ссылке
            QObject::connect(logOutput, &QTextBrowser::anchorClicked, [=, &currentIndex](const QUrl& link) mutable {
                QString subsequence = link.toString(); // Получаем текст ссылки

                // Поиск следующего вхождения, начиная с текущего индекса
                int startIndex = inputText.indexOf(subsequence, currentIndex);

                if (startIndex == -1) {
                    // Если не найдено, начать поиск с начала строки
                    startIndex = inputText.indexOf(subsequence, 0);
                }

                if (startIndex != -1) {
                    // Установить выделение
                    stringInput->setSelection(startIndex, subsequence.length());
                    
                    // Обновить currentIndex для учета перекрывающихся вхождений
                    currentIndex = startIndex + 1; // Сдвигаем только на 1 символ
                }
            });


                logFile.close();
            } else {
                logOutput->setPlainText("Не удалось открыть Subsequence.txt");
            }
        } catch (const std::exception& ex) {
            QMessageBox::critical(widget, "Ошибка", QString("Произошла ошибка: %1").arg(ex.what()));
        }
    });

    // Добавление виджетов в макет
    mainLayout->addWidget(backButton);
    mainLayout->addLayout(inputLayout);
    mainLayout->addWidget(stringInput);
    mainLayout->addWidget(startButton);
    mainLayout->addWidget(logOutput);

    // Стилизация
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
        QTextEdit, QTextBrowser {
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
*/

int main(int argc, char* argv[]) {

    try {
        QApplication app(argc, argv);

        auto* mainWindow = new QWidget;
        auto* stackedWidget = new QStackedWidget(mainWindow);

        stackedWidget->addWidget(createFirstWindow(stackedWidget));
        stackedWidget->addWidget(createSecondWindow(stackedWidget));
        stackedWidget->addWidget(createThirdWindow(stackedWidget));

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