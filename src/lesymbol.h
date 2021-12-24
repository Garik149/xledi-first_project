#ifndef LESYMBOL_H
#define LESYMBOL_H

#include <QGraphicsItem>
#include "defines.h"
#include "logicelement.h"

class LESymbol : public QGraphicsPolygonItem
{
    LogicElement* pt_le;

public:
    LESymbol();
     LESymbol(LogicElement* _pt_le);
    ~LESymbol();

//    enum {Type = UserType + 14};
//    enum TypeItem{Element, PortIn, PortOut, Null};
//    static size_t countItem;
//
//    explicit ItemLEdi(TypeItem typeItem, uint countPinIn = 2, uint countPinOut = 1,
//                      QPoint pos = {0,0}, QGraphicsItem *parent = nullptr);
//
//    virtual int type() const override { return Type; }
//    TypeItem typeItem() const { return myTypeItem; }
//    QPolygonF polygon() const { return myPolygon; }
//    inline const QPoint getPin() const { return QPoint(myCountPinIn,myCountPinOut); }
//    inline const QVector<Pin*>* getOutPins() const { return &vectorOutPins; }
//    inline const QVector<Pin*>* getInPins() const { return &vectorInPins; }
//    QString stringTypeItem(TypeItem typeItem);
//    inline const QString getNameModule() const { return nameModule->toPlainText(); }
//    inline QString& getNameElement() const { return nameElement->getString(); }
//    inline Pin* findPin(QString namePin) const { return mapPins.value(namePin); }
//    void resetPins(QVector<Pin*> vectorIn, QVector<Pin*> vectorOut);
//    void resetItem(QString nameMod, QString nameElem);
//
//    bool insertFlag;
//    QRectF rect() const {return rectItem;}
//
//private:
//    QMap<QString, Pin*> mapPins{};
    QGraphicsTextItem *nameModule;
//    TextItemLEdi *nameElement;
//    TypeItem myTypeItem;
//    QPolygonF myPolygon;
    QRectF rectItem;
//    uint myCountPinIn;
//    uint myCountPinOut;
//    QVector<Pin*> vectorInPins{};
//    QVector<Pin*> vectorOutPins{};
//
//    void resize(const uint& countPin);
//    void pinAlignment(Pin::TypePin firstType, Pin::TypePin secondType, QPointF firstPos,
//                      QPointF secondPosuint, uint firstCount, uint secondCount);
//    QPointF binding(QPointF point);
//    void generatPin();
//
//protected:
//    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
//    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
//
//signals:
//    void sigNameChanged(QString oldName, QString newName);
//
//public slots:
//    void slotNameChanged(QString oldName, QString newName) {emit sigNameChanged(oldName, newName);}

};

#endif // LESYMBOL_H
