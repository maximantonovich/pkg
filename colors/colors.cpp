#include "colors.h"
#include "./ui_colors.h"
#include <QWidget>
#include <QGridLayout>
#include <QDialog>
#include <QSlider>
#include <QLineEdit>
#include <algorithm>
#include <cmath>


QSlider* make_slider(const QString& from_color, const QString& to_color)
{
    QSlider* slide = new QSlider(Qt::Horizontal);
    slide->setRange(0, 255);
    slide->setStyleSheet(QString(
        "QSlider::groove:horizontal {"
        "  height: 20px; border-radius: 4px;"
        "  background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "    stop:0 %1, stop:1 %2);"
        "}"
        "QSlider::handle:horizontal {"
        "  width: 12px; background: white; border: 1px solid #333;"
        "}").arg(from_color, to_color));
    return slide;
}


colors::colors(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::colors)
{
    ui->setupUi(this);

    QGridLayout* grid = new QGridLayout(this);

    color = new QColor();

    QLabel* red = new QLabel("Red:");
    QLabel* green = new QLabel("Green:");
    QLabel* blue = new QLabel("Blue: ");

    QLabel* cyan = new QLabel("Cyan:");
    QLabel* magenta = new QLabel("Magenta:");
    QLabel* yellow = new QLabel("Yellow:");
    QLabel* key = new QLabel("Key:");

    QLabel* hue = new QLabel("Hue:");
    QLabel* saturation = new QLabel("Saturation:");
    QLabel* lightness = new QLabel("Lightness:");

    Red_slider   = make_slider("rgb(0,0,0)", "rgb(255,0,0)");
    Green_slider = make_slider("rgb(0,0,0)", "rgb(0,255,0)");
    Blue_slider  = make_slider("rgb(0,0,0)", "rgb(0,0,255)");

    Cyan_slider    = make_slider("rgb(255,255,255)", "rgb(0,255,255)");
    Magenta_slider = make_slider("rgb(255,255,255)", "rgb(255,0,255)");
    Yellow_slider  = make_slider("rgb(255,255,255)", "rgb(255,255,0)");
    Key_slider     = make_slider("rgb(255,255,255)", "rgb(0,0,0)");

    Hue_slider        = make_slider("rgb(255,0,0)", "rgb(255,0,0)");
    Saturation_slider = make_slider("rgb(128,128,128)", "rgb(255,0,0)");
    Lightness_slider  = make_slider("rgb(0,0,0)", "rgb(255,255,255)");

    Hue_slider->setRange(0, 359);
    Saturation_slider->setRange(0, 255);
    Lightness_slider->setRange(0, 255);


    Hue_slider->setStyleSheet(
        "QSlider::groove:horizontal {"
        "  height: 20px; border-radius: 4px;"
        "  background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "    stop:0.000 rgb(255,0,0),"
        "    stop:0.167 rgb(255,255,0),"
        "    stop:0.333 rgb(0,255,0),"
        "    stop:0.500 rgb(0,255,255),"
        "    stop:0.667 rgb(0,0,255),"
        "    stop:0.833 rgb(255,0,255),"
        "    stop:1.000 rgb(255,0,0));"
        "}"
        "QSlider::handle:horizontal {"
        "  width: 12px; background: white; border: 1px solid #333;"
        "}");

    red_num   = new QLineEdit();
    green_num = new QLineEdit();
    blue_num  = new QLineEdit();

    cyan_num    = new QLineEdit();
    magenta_num = new QLineEdit();
    yellow_num  = new QLineEdit();
    key_num     = new QLineEdit();

    hue_num        = new QLineEdit();
    saturation_num = new QLineEdit();
    lightness_num  = new QLineEdit();

    colorPreview = new QLabel(this);
    colorPreview->setMinimumSize(300, 300);
    colorPreview->setFrameShape(QFrame::Box);

    colorDialog = new QColorDialog(this);
    colorDialog->setOption(QColorDialog::NoButtons, true);
    colorDialog->setOption(QColorDialog::DontUseNativeDialog, true);

    pallete_button = new QPushButton("палитра");

    grid->addWidget(red, 0, 0);
    grid->addWidget(Red_slider, 0, 1);
    grid->addWidget(red_num, 0, 2);

    grid->addWidget(green, 1, 0);
    grid->addWidget(Green_slider, 1, 1);
    grid->addWidget(green_num, 1, 2);

    grid->addWidget(blue, 2, 0);
    grid->addWidget(Blue_slider, 2, 1);
    grid->addWidget(blue_num, 2, 2);

    grid->setColumnStretch(0, 0);
    grid->setColumnStretch(1, 1);
    grid->setColumnStretch(2, 0);


    grid->setRowMinimumHeight(3, 50);

    grid->addWidget(cyan, 4, 0);
    grid->addWidget(Cyan_slider, 4, 1);
    grid->addWidget(cyan_num, 4, 2);

    grid->addWidget(magenta, 5, 0);
    grid->addWidget(Magenta_slider, 5, 1);
    grid->addWidget(magenta_num, 5, 2);

    grid->addWidget(yellow, 6, 0);
    grid->addWidget(Yellow_slider, 6, 1);
    grid->addWidget(yellow_num, 6, 2);

    grid->addWidget(key, 7, 0);
    grid->addWidget(Key_slider, 7, 1);
    grid->addWidget(key_num, 7, 2);



    grid->setRowMinimumHeight(8, 50);

    grid->addWidget(hue, 9, 0);
    grid->addWidget(Hue_slider, 9, 1);
    grid->addWidget(hue_num, 9, 2);

    grid->addWidget(saturation, 10, 0);
    grid->addWidget(Saturation_slider, 10, 1);
    grid->addWidget(saturation_num, 10, 2);

    grid->addWidget(lightness, 11, 0);
    grid->addWidget(Lightness_slider, 11, 1);
    grid->addWidget(lightness_num, 11, 2);

    grid->addWidget(pallete_button, 12, 0, 1, 2);
    grid->addWidget(colorPreview, 0, 3, 6, 6);

    connect(Red_slider, &QSlider::valueChanged, this, &colors::on_slider_change);
    connect(Green_slider, &QSlider::valueChanged, this, &colors::on_slider_change);
    connect(Blue_slider, &QSlider::valueChanged, this, &colors::on_slider_change);

    connect(red_num, &QLineEdit::textChanged, this, &colors::on_line_change);
    connect(green_num, &QLineEdit::textChanged, this, &colors::on_line_change);
    connect(blue_num, &QLineEdit::textChanged, this, &colors::on_line_change);

    connect(pallete_button, &QPushButton::clicked, this, &colors::on_pallete_button_change);

    connect(Cyan_slider, &QSlider::valueChanged, this, &colors::on_cmyk_slider_change);
    connect(Magenta_slider, &QSlider::valueChanged, this, &colors::on_cmyk_slider_change);
    connect(Yellow_slider, &QSlider::valueChanged, this, &colors::on_cmyk_slider_change);
    connect(Key_slider, &QSlider::valueChanged, this, &colors::on_cmyk_slider_change);

    connect(cyan_num, &QLineEdit::textChanged, this, &colors::on_cmyk_line_change);
    connect(magenta_num, &QLineEdit::textChanged, this, &colors::on_cmyk_line_change);
    connect(yellow_num, &QLineEdit::textChanged, this, &colors::on_cmyk_line_change);
    connect(key_num, &QLineEdit::textChanged, this, &colors::on_cmyk_line_change);

    connect(Hue_slider, &QSlider::valueChanged, this, &colors::on_hls_slider_change);
    connect(Saturation_slider, &QSlider::valueChanged, this, &colors::on_hls_slider_change);
    connect(Lightness_slider, &QSlider::valueChanged, this, &colors::on_hls_slider_change);

    connect(hue_num, &QLineEdit::textChanged, this, &colors::on_hls_line_change);
    connect(saturation_num, &QLineEdit::textChanged, this, &colors::on_hls_line_change);
    connect(lightness_num, &QLineEdit::textChanged, this, &colors::on_hls_line_change);

    setLayout(grid);

    cmyk = rgbToCmyk(color->red(), color->green(), color->blue());
    hls = rgbToHls (color->red(), color->green(), color->blue());

    updateRGB();
    updateCMYK();
    updateHLS();
}

colors::~colors()
{
    delete ui;
}


void colors::on_slider_change()
{
    color->setRed(Red_slider->value());
    color->setGreen(Green_slider->value());
    color->setBlue(Blue_slider->value());

    cmyk = rgbToCmyk(color->red(), color->green(), color->blue());
    hls = rgbToHls (color->red(), color->green(), color->blue());

    updateRGB();
    updateCMYK();
    updateHLS();
}

void colors::on_line_change()
{
    int col;

    col = red_num->text().toInt();
    if (col >= 0 && col <= 255) color->setRed(col);

    col = green_num->text().toInt();
    if (col >= 0 && col <= 255) color->setGreen(col);

    col = blue_num->text().toInt();
    if (col >= 0 && col <= 255) color->setBlue(col);

    cmyk = rgbToCmyk(color->red(), color->green(), color->blue());
    hls = rgbToHls (color->red(), color->green(), color->blue());

    updateRGB();
    updateCMYK();
    updateHLS();
}

void colors::on_pallete_button_change()
{
    QColor chosen = QColorDialog::getColor(*color, this, "Выберите цвет");
    if (chosen.isValid())
    {
        *color = chosen;

        cmyk = rgbToCmyk(color->red(), color->green(), color->blue());
        hls = rgbToHls (color->red(), color->green(), color->blue());

        updateRGB();
        updateCMYK();
        updateHLS();
    }
}


void colors::on_cmyk_slider_change()
{
    cmyk.c = Cyan_slider->value();
    cmyk.m = Magenta_slider->value();
    cmyk.y = Yellow_slider->value();
    cmyk.k = Key_slider->value();

    int r, g, b;
    cmykToRgb(cmyk.c, cmyk.m, cmyk.y, cmyk.k, r, g, b);
    color->setRgb(r, g, b);

    hls = rgbToHls(r, g, b);

    updateRGB();
    updateHLS();
    updateCMYK();

}

void colors::on_cmyk_line_change()
{
    int col;

    col = cyan_num->text().toInt();
    if (col >= 0 && col <= 255) cmyk.c = col;

    col = magenta_num->text().toInt();
    if (col >= 0 && col <= 255) cmyk.m = col;

    col = yellow_num->text().toInt();
    if (col >= 0 && col <= 255) cmyk.y = col;

    col = key_num->text().toInt();
    if (col >= 0 && col <= 255) cmyk.k = col;

    int r, g, b;
    cmykToRgb(cmyk.c, cmyk.m, cmyk.y, cmyk.k, r, g, b);
    color->setRgb(r, g, b);

    hls = rgbToHls(r, g, b);

    updateRGB();
    updateCMYK();
    updateHLS();
}


void colors::on_hls_slider_change()
{
    hls.h = Hue_slider->value();
    hls.s = Saturation_slider->value();
    hls.l = Lightness_slider->value();

    int r, g, b;
    hlsToRgb(hls.h, hls.s, hls.l, r, g, b);
    color->setRgb(r, g, b);

    cmyk = rgbToCmyk(r, g, b);

    updateRGB();
    updateCMYK();
    updateHLS();
}

void colors::on_hls_line_change()
{
    int col;

    col = hue_num->text().toInt();
    if (col >= 0 && col <= 359) hls.h = col;

    col = saturation_num->text().toInt();
    if (col >= 0 && col <= 255) hls.s = col;

    col = lightness_num->text().toInt();
    if (col >= 0 && col <= 255) hls.l = col;

    int r, g, b;
    hlsToRgb(hls.h, hls.s, hls.l, r, g, b);
    color->setRgb(r, g, b);

    cmyk = rgbToCmyk(r, g, b);

    updateRGB();
    updateCMYK();
    updateHLS();
}


void colors::updateRGB()
{
    Red_slider->blockSignals(true);
    Green_slider->blockSignals(true);
    Blue_slider->blockSignals(true);

    red_num->blockSignals(true);
    green_num->blockSignals(true);
    blue_num->blockSignals(true);

    Red_slider->setSliderPosition(color->red());
    Green_slider->setSliderPosition(color->green());
    Blue_slider->setSliderPosition(color->blue());

    red_num->setText(QString::number(color->red()));
    green_num->setText(QString::number(color->green()));
    blue_num->setText(QString::number(color->blue()));

    colorPreview->setStyleSheet(QString("background-color: %1;").arg(color->name()));

    Red_slider->blockSignals(false);
    Green_slider->blockSignals(false);
    Blue_slider->blockSignals(false);

    red_num->blockSignals(false);
    green_num->blockSignals(false);
    blue_num->blockSignals(false);
}

void colors::updateCMYK()
{
    Cyan_slider->blockSignals(true);
    Magenta_slider->blockSignals(true);
    Yellow_slider->blockSignals(true);
    Key_slider->blockSignals(true);

    cyan_num->blockSignals(true);
    magenta_num->blockSignals(true);
    yellow_num->blockSignals(true);
    key_num->blockSignals(true);

    Cyan_slider->setSliderPosition(cmyk.c);
    Magenta_slider->setSliderPosition(cmyk.m);
    Yellow_slider->setSliderPosition(cmyk.y);
    Key_slider->setSliderPosition(cmyk.k);

    cyan_num->setText(QString::number(cmyk.c));
    magenta_num->setText(QString::number(cmyk.m));
    yellow_num->setText(QString::number(cmyk.y));
    key_num->setText(QString::number(cmyk.k));

    colorPreview->setStyleSheet(QString("background-color: %1;").arg(color->name()));

    Cyan_slider->blockSignals(false);
    Magenta_slider->blockSignals(false);
    Yellow_slider->blockSignals(false);
    Key_slider->blockSignals(false);

    cyan_num->blockSignals(false);
    magenta_num->blockSignals(false);
    yellow_num->blockSignals(false);
    key_num->blockSignals(false);
}

void colors::updateHLS()
{
    Hue_slider->blockSignals(true);
    Saturation_slider->blockSignals(true);
    Lightness_slider->blockSignals(true);

    hue_num->blockSignals(true);
    saturation_num->blockSignals(true);
    lightness_num->blockSignals(true);

    Hue_slider->setSliderPosition(hls.h);
    Saturation_slider->setSliderPosition(hls.s);
    Lightness_slider->setSliderPosition(hls.l);

    hue_num->setText(QString::number(hls.h));
    saturation_num->setText(QString::number(hls.s));
    lightness_num->setText(QString::number(hls.l));

    colorPreview->setStyleSheet(QString("background-color: %1;").arg(color->name()));

    Hue_slider->blockSignals(false);
    Saturation_slider->blockSignals(false);
    Lightness_slider->blockSignals(false);

    hue_num->blockSignals(false);
    saturation_num->blockSignals(false);
    lightness_num->blockSignals(false);
}



CMYK colors::rgbToCmyk(int r, int g, int b)
{
    CMYK out;

    if (r == 0 && g == 0 && b == 0)
    {
        out.k = 255;
        return out;
    }

    int c = 255 - r;
    int m = 255 - g;
    int y = 255 - b;

    int k = std::min({c, m, y});

    if (k < 255)
    {
        c = (c - k) * 255 / (255 - k);
        m = (m - k) * 255 / (255 - k);
        y = (y - k) * 255 / (255 - k);
    }
    else
    {
        c = m = y = 0;
    }

    out.c = c;
    out.m = m;
    out.y = y;
    out.k = k;
    return out;
}

void colors::cmykToRgb(int c, int m, int y, int k,
                       int& r, int& g, int& b)
{
    c = std::clamp(c, 0, 255);
    m = std::clamp(m, 0, 255);
    y = std::clamp(y, 0, 255);
    k = std::clamp(k, 0, 255);

    r = (255 - c) * (255 - k) / 255;
    g = (255 - m) * (255 - k) / 255;
    b = (255 - y) * (255 - k) / 255;
}




HLS colors::rgbToHls(int r, int g, int b)
{
    HLS out;

    float red   = r / 255.0f;
    float green = g / 255.0f;
    float blue  = b / 255.0f;

    float max = std::max({red, green, blue});
    float min = std::min({red, green, blue});

    float H = 0.0f, S = 0.0f, L = (max + min) / 2.0f;

    if (max != min)
    {
        float delta = max - min;

        S = delta / (L < 0.5f ? max + min : 2.0f - max - min);

        if      (max == red)   H = (green - blue) / delta;
        else if (max == green) H = 2.0f + (blue - red) / delta;
        else                  H = 4.0f + (red - green) / delta;

        H *= 60.0f;
        if (H < 0.0f) H += 360.0f;
    }

    if (max == min)
    {
        out.h = -1;
        out.s = 0;
    }
    else
    {
        out.h = std::clamp((int)(std::round(H)), 0, 359);
        out.s = std::clamp((int)(std::round(S * 255.0f)), 0, 255);
    }

    out.l = std::clamp((int)(std::round(L * 255.0f)), 0, 255);

    return out;
}



static double hlsValue(double H, double M1, double M2)
{
    while (H < 0.0)
    {
        H += 360.0;
    }
    while (H >= 360.0)
    {
        H -= 360.0;
    }

    if (H < 60.0)
        return M1 + (M2 - M1) * (H / 60.0);
    if (H < 180.0)
        return M2;
    if (H < 240.0)
        return M1 + (M2 - M1) * ((240.0 - H) / 60.0);
    return M1;
}



bool colors::hlsToRgb(int h, int s, int l, int& r, int& g, int& b)
{

    double H = h;
    double S = s / 255.0;
    double L = l / 255.0;


    double M2;
    if (L > 0.5)
        M2 = L + S - L * S;
    else
        M2 = L * (1.0 + S);

    double M1 = 2.0 * L - M2;


    if (S == 0.0)
    {
        if (H < 0.0)
        {
            return false;
        }


        r = std::clamp((int)(std::round(L * 255.0)), 0, 255);
        g = r;
        b = r;
        return true;
    }


    double R = hlsValue(H + 120.0, M1, M2);
    double G = hlsValue(H, M1, M2);
    double B = hlsValue(H - 120.0, M1, M2);

    r = std::clamp((int)(std::round(R * 255.0)), 0, 255);
    g = std::clamp((int)(std::round(G * 255.0)), 0, 255);
    b = std::clamp((int)(std::round(B * 255.0)), 0, 255);
    return true;
}
