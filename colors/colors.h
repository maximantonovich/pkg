#ifndef COLORS_H
#define COLORS_H

#include <QWidget>
#include <QColor>
#include <QSlider>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QColorDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class colors; }
QT_END_NAMESPACE

struct CMYK
{
    int c = 0;
    int m = 0;
    int y = 0;
    int k = 0;
};

struct HLS
{
    int h = 0;   // 0..359
    int s = 0;   // 0..255
    int l = 0;   // 0..255
};

class colors : public QWidget
{
    Q_OBJECT

public:
    colors(QWidget *parent = nullptr);
    ~colors();

private slots:
    void on_slider_change();
    void on_line_change();
    void on_pallete_button_change();

    void on_cmyk_slider_change();
    void on_cmyk_line_change();

    void on_hls_slider_change();
    void on_hls_line_change();

private:
    Ui::colors *ui;

    // три независимых состояния
    QColor* color;
    CMYK    cmyk;
    HLS     hls;

    QSlider* Red_slider;
    QSlider* Green_slider;
    QSlider* Blue_slider;

    QSlider* Cyan_slider;
    QSlider* Magenta_slider;
    QSlider* Yellow_slider;
    QSlider* Key_slider;

    QSlider* Hue_slider;
    QSlider* Saturation_slider;
    QSlider* Lightness_slider;

    QLineEdit* red_num;
    QLineEdit* green_num;
    QLineEdit* blue_num;

    QLineEdit* cyan_num;
    QLineEdit* magenta_num;
    QLineEdit* yellow_num;
    QLineEdit* key_num;

    QLineEdit* hue_num;
    QLineEdit* saturation_num;
    QLineEdit* lightness_num;

    QLabel* colorPreview;
    QColorDialog* colorDialog;
    QPushButton* pallete_button;


    void updateRGB();
    void updateCMYK();
    void updateHLS();


    static CMYK rgbToCmyk(int r, int g, int b);
    static void cmykToRgb(int c, int m, int y, int k, int& r, int& g, int& b);


    static HLS rgbToHls(int r, int g, int b);
    static bool hlsToRgb(int h, int s, int l, int& r, int& g, int& b);
};

#endif // COLORS_H