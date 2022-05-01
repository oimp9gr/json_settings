#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QMessageBox>
#include <unordered_map>
#include <fstream>
#include <regex>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_save_pushButton_clicked()
{
    QString s =
R"({
    "x": %1,
    "y": %2,
    "width": %3,
    "height": %4,
    "text": "%5"
})";
    int x = ui->target_pushButton->pos().x();
    int y = ui->target_pushButton->pos().y();
    int width = ui->target_pushButton->size().width();
    int height = ui->target_pushButton->size().height();
    QString text = ui->target_pushButton->text();

    auto result = s.arg(x).arg(y).arg(width).arg(height).arg(text);

    QFile file("B:\\qt_projects\\variant_1\\settings.json");
    file.open(QFile::WriteOnly);
    QTextStream stream(&file);
    stream << result;
    file.close();
}

std::optional<std::string> ReadJSON(const std::string & path) {
    if (auto fin = std::ifstream(path)) {
        std::string result;
        getline(fin, result, '\0');
        return result;
    }
    return std::nullopt;
}
/*
{
    "x": 10,
    "y": 20,
    "width": 50,
    "height": 100,
    "text": "qwe"
}

*/
Settings ParseSettings(const std::string & data) {
    std::stringstream ss(data);
    std::string row;
    Settings settings;
    while(getline(ss, row)) {
        auto pattern = std::regex(R"(^\s*\"(\w+)\"\s*\:\s*\"?(.+?)\"?,?\s*$)");
        std::smatch sm;
        auto res = std::regex_search(row, sm, pattern);
        if (res) {
            if (sm[1].str() == "text") settings[sm[1].str()] = sm[2].str();
            else settings[sm[1].str()] = stoi(sm[2].str());
        }
    }
    return settings;
}

void Widget::SetSettings(const Settings & settings) {
    int x = std::get<int>(settings.at("x"));
    int y = std::get<int>(settings.at("y"));
    int width = std::get<int>(settings.at("width"));
    int height = std::get<int>(settings.at("height"));
    std::string text = std::get<std::string>(settings.at("text"));

    ui->target_pushButton->move(x, y);
    ui->target_pushButton->resize(width, height);
    ui->target_pushButton->setText(QString::fromStdString(text));
}

void Widget::on_load_pushButton_clicked()
{
    if (std::optional<std::string> text = ReadJSON("B:\\qt_projects\\variant_1\\settings.json")) {
        auto settings = ParseSettings(text.value());
        SetSettings(settings);
    } else {
        QMessageBox message_box;
        message_box.setText("File is not open");
        message_box.exec();
    }
}


void Widget::on_save_pushButton_pressed()
{

}

