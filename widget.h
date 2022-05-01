#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

using Settings = std::unordered_map<std::string, std::variant<int, std::string>>;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void SetSettings(const Settings & settings);

private slots:
    void on_save_pushButton_clicked();

    void on_load_pushButton_clicked();

    void on_save_pushButton_pressed();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
