#include <wtypes.h>
#include <QCoreApplication>
#include <QDebug>
#include <AdvMotApi.h>

#define MAX_CNT 100

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<__LINE__<<"*** Test Demo: ***";


    ULONG ret ;
    HAND devHandle;
    HAND axHandle[MAX_CNT];
    ULONG devNum = 0;
    ULONG devCnt = 0;
    ULONG bufferLen = 1024;
    ULONG axisCntPerDev = 0;
    DEVLIST devList[MAX_CNT];

    //USHORT i;

    do
    {
        //1. Get Available devices:

        ret = Acm_GetAvailableDevs(devList, MAX_CNT, &devCnt);
        //qDebug()<<__LINE__<<__LINE__<<ret;
        if(0 != ret)
        {
            qDebug()<<__LINE__<<"no device available";
            break;
        }
        //qDebug()<<__LINE__<<__LINE__<<ret;

        //2. Open Device:

        devNum = devList[0].dwDeviceNum;
        ret = Acm_DevOpen(devNum, &devHandle);
        if(0 != ret)
        {
            qDebug()<<__LINE__<<"Open device failed";
            system("pause");
            break;
        }
        qDebug()<<__LINE__<<"Open Device succeed";

        //3. If open device successfully, get necessary property:
        bufferLen = sizeof(axisCntPerDev);
        ret = Acm_GetProperty(devHandle, FT_DevAxesCount, &axisCntPerDev,&bufferLen);
        if(SUCCESS != ret)
        {
            Acm_DevClose(&devHandle);
            qDebug()<<__LINE__<<"Failed get device properties...";
            system("pause");
            break;
        }
        qDebug()<<__LINE__<<"Get Properties successcully";
        for(quint8 i = 0; i<axisCntPerDev;i++)
        {
            ret = Acm_AxOpen(devHandle, i, &axHandle[i]);
            if(0 != ret)
            {
                qDebug()<<__LINE__<<"Open axis_0 is failed ";
                system("pause");
                break;
            }
        }
        qDebug()<<__LINE__<<"Open axis successfully";

        // a PTP motion:

        ret = Acm_AxMoveRel(axHandle[0], 10000);
        if(0 != ret)
        {
            qDebug()<<__LINE__<<"move axis_0 failed";
            system("pause");
            break;
        }
        qDebug()<<__LINE__<<"PTP move succeed";

        //4. close device:
        for(qint8 i = 0; i<axisCntPerDev; i++)
        {
            ret = Acm_AxClose(&axHandle[i]);
            if(0 != ret)
            {
                qDebug()<<__LINE__<<"Close failed";
                system("pause");
                break;
            }
        }

        Acm_DevClose(&devHandle);
        system("pause");
        break;
    }
    while(0);
    return a.exec();
}














