#include "module.h"

void module::initFromFile(QFile file)
{
    QString line = file.readAll();
    line.indexOf(QRegularExpression("\b(module)\b"));
}

module::module()
{

}
