#ifndef MAP_PREVIEW_H
#define MAP_PREVIEW_H

#include <QWidget>

namespace Ui {
class map_preview;
}

class map_preview : public QWidget
{
    Q_OBJECT

public:
    explicit map_preview(QWidget *parent = nullptr);
    ~map_preview();
   void  loding_map();

private:
    Ui::map_preview *ui;
};

#endif // MAP_PREVIEW_H
