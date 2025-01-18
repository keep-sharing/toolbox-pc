#include "basicmethod.h"

BasicMethod::BasicMethod()
{

}

QString basicChangeNameLoraFreq(QString src)
{
    src.replace("EU868","868").replace("US915","915").replace("AU915","915").replace("CN470","470").replace("AS923","915")
           .replace("KR920","915").replace("EU433","433").replace("IN865","868").replace("RU864","868");
    src.replace("864","868").replace("865","868").replace("923","915").replace("920","915");
    src.remove("-0080-0000").remove("-0080-0001");

    return src;
}
