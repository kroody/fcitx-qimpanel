#include <QDebug>
#include <QBitmap>
#include <QColor>
#include <QDir>
#include <QFile>
#include <QFontMetrics>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QTextStream>

#include "skinsogou.h"

SkinSogou::SkinSogou() : SkinBase()
{

}

SkinSogou::~SkinSogou()
{

}

QColor SkinSogou::uint2color(const unsigned int value)
{
    return QColor(qRed(value), qGreen(value), qBlue(value));
}

bool SkinSogou::loadSkin(const QString skinPath)
{
    init();

    QFile sogouSkinConfFile(skinPath + "sogou_skin.conf");
    if (!sogouSkinConfFile.exists())
        return false;

    if (!sogouSkinConfFile.open(QIODevice::ReadOnly))
        return false;

    QString line;
    QString key, value;

    /// parse ini file content
    bool general = false;
    bool display = false;
    bool scheme_h1 = false;
    bool scheme_v1 = false;
    bool statusbar = false;
    QColor pinyin_color, zhongwen_color, zhongwen_first_color;

    int fontPixelSize = 12;

    QTextStream textStream(sogouSkinConfFile.readAll());

    do {

        line = textStream.readLine();

        if (line.isEmpty() || line.at(0) == '#')
            continue;

        if (line.at(0) == '[') {
            general = (line == "[General]");
            display = (line == "[Display]");
            scheme_h1 = (line == "[Scheme_H1]");
            scheme_v1 = (line == "[Scheme_V1]");
            statusbar = (line == "[StatusBar]");

            continue;
        }

        if (!line.contains('='))
            continue;

        key = line.split('=').at(0);
        value = line.split('=').at(1);

        if (value.isEmpty())
            continue;

        if (display) {
            if (key == "font_size")
                setFontSize(value.toInt());
            else if (key == "pinyin_color"){
                pinyin_color = uint2color(value.toUInt());
//                setInputColor(pinyin_color);
            } 
            else if (key == "zhongwen_color"){
                zhongwen_color = uint2color(value.toUInt());
//                setOtherColor(zhongwen_color);
            }
            else if (key == "zhongwen_first_color"){
                zhongwen_first_color = uint2color(value.toUInt());
//                setFirstCandColor(zhongwen_first_color);
            }
       }else if (scheme_h1) {
            if (key == "pic") {
//                setInputBackImg("file:/" + skinPath + value);
            }
       } else if (statusbar) {
            if (key == "pic") {
                //setTipsImg("file:/" + skinPath + value);
            }
       }
        

        setFontSize(13);
        setCandFontSize(13);
        setInputColor(value2color("17 80 131"));
        setIndexColor(value2color("3 0 0"));
        setFirstCandColor(value2color("17 80 131"));
        setOtherColor(value2color("3 0 0"));

        setInputBackImg("file://usr/share/fcitx/skin/ubuntukylin-light1/input.png");
        setTipsImg("file://usr/share/fcitx/skin/ubuntukylin-light1/tips.png");
        setBackArrowImg("file://usr/share/fcitx/skin/ubuntukylin-light1/prev.png");
        setForwardArrowImg("file://usr/share/fcitx/skin/ubuntukylin-light1/next.png");

        setAdjustWidth(10);
        setAdjustHeight(-30);
        setMarginLeft(8);
        setMarginTop(8);
        setMarginRight(8);
        setMarginBottom(8);
        setHorizontalTileMode("Stretch");
        setVerticalTileMode("Stretch");
        setInputStringPosX(0);
        setInputStringPosY(10);
        setOutputCandPosX(0);
        setOutputCandPosY(34);
        setBackArrowPosX(10);
        setBackArrowPosY(6);
        setForwardArrowPosX(30);
        setForwardArrowPosY(6);

 

    } while (!line.isNull());

    sogouSkinConfFile.close();
    return true;
}


