#include <wtypes.h>
#include <QCoreApplication>
#include <QDebug>
#include <AdvMotApi.h>

#define MAX_CNT 100

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Hello Servo";


    ULONG errcde;
    //HAND devHandle;
    //HAND axHandle[MAX_CNT];
    //ULONG devNum, devCnt, axixCntPerDev;
    ULONG devCnt = 0;
    DEVLIST devList[MAX_CNT];

    //USHORT i;

    errcde = Acm_GetAvailableDevs(devList, MAX_CNT, &devCnt);
    qDebug()<<__LINE__<<errcde;
    if(0 != errcde)
    {
        qDebug()<<"no device";
        getchar();
        return 0;
    }
    qDebug()<<__LINE__<<errcde;


    return a.exec();
}
