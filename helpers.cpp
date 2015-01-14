#include "helpers.h"

//------------------------------------------------------------------------------------------------------------

double rectRange(QRect A, QRect B)
{
    QPoint ac = A.center();
    QPoint bc = B.center();
    return sqrt(pow(ac.x()-bc.x(),2) +
                pow(ac.y()-bc.y(),2));
}
//---------------------------------------------------------------------------
/*
InputSystem::InputSystem()
{
}
InputSystem::~InputSystem()
{
        ;
}
void InputSystem::addListener(InputComponent * l)
{
        listeners.push_back(l);
}
void InputSystem::removeListener(InputComponent * l)
{
        listeners.remove(l);
}
void InputSystem::clear()
{
        listeners.clear();
}
void InputSystem::update()
{
        kbState newResult = kbState::get(KB_STATE_BOOLEAN_FORMAT);
        for (int i=0; i<256; i++)
        {
                if (newResult[i]!=prevResult[i])
                {
                        uint vk = ((newResult[i]==1) ? KEY_DOWN : KEY_UP)+ i;
                        for (std::list<InputComponent*>::iterator i = listeners.begin(); i!=listeners.end(); i++)
                                (*i)->keyUpdate(vk);
                }
        }
        prevResult = newResult;
}*/

kbState kbState::get(int format)
{
        kbState out;
        GetKeyboardState(out.state);
        if (format == KB_STATE_WINAPI_FORMAT);
        else if (format == KB_STATE_BOOLEAN_FORMAT)
        {
                for (int i=0; i<256; i++)
                        out.state[i] = (out.state[i]&128)?1:0;
                return out;
        }
        return out;
}
//---------------------------------------------------------------------------

void keyHistory::updateKey(uint spKey)
{
        bool up = (spKey&0xFF00) == KEY_UP;
        if (index == KH_BUFFER_BOUND)
        {
                for (int i=0; i<KH_BUFFER_BOUND; i++)
                {
                        keys[i]=keys[i+1];
                        keyTime[i]=keyTime[i+1];
                        keyUp[i] = keyUp[i+1];
                }
                keys[KH_BUFFER_BOUND] = spKey&0xFF;
                keyUp[KH_BUFFER_BOUND]= up;
                keyTime[KH_BUFFER_BOUND] = ::GetTickCount();
        }
        else
        {
                keys[index] = spKey&0xFF;
                keyUp[index]= up;
                keyTime[index] = ::GetTickCount();
                index++;
        }
}
bool keyHistory::testCombo(QString c) const
{
        QString combo = c;
        combo = combo.replace(" ", "").replace(".", "*");

        int _keys [16]; memset(_keys,0,16);
        int lastkey = 0;
        QStringList dcomp;
        dcomp = combo.split("-");

        uint maxLen = dcomp.at(0).toInt();
        combo = dcomp.at(1).toLocal8Bit();
        bool mode = 0;

        QByteArray ba = combo.toLatin1();
        for (int i=0; i<combo.length(); i++)
        {
                if (ba.data()[i] == '!')
                {
                        mode = 1;
                        continue;
                }
                else    if (i!=0)
                                if (ba.data()[i-1] != '!')
                                        mode = 0;
                _keys[lastkey] = mode?KEY_UP:KEY_DOWN;
                if (ba.data()[i] == '>')
                        _keys[lastkey] += VK_RIGHT;
                else if (ba.data()[i] == '<')
                        _keys[lastkey] += VK_LEFT;
                else if (ba.data()[i] == '^')
                        _keys[lastkey] += VK_UP;
                else if (ba.data()[i] == '*')
                        _keys[lastkey] += VK_DOWN;
                else
                        _keys[lastkey] += ba.data()[i];
                lastkey++;
        }
        bool comboFound = false;
        for (int ki = 0; ki<KH_BUFFER_SIZE+1-lastkey; ki++)
        {
                if (getSKey(ki) == 0)
                        break;
                for (int ci=0; ci<lastkey;ci++)
                {
                        if (getSKey(ki+ci) != _keys[ci])
                        {
                                comboFound = false;
                                break;
                        }
                        else if ((ci == lastkey-1) && (getSKey(ki+ci) == _keys[ci]))
                        {
                                if ((keyTime[ki+ci] - keyTime[ki]) < maxLen)
                                if (::GetTickCount()-keyTime[ki+ci] < 1000)
                                {
                                        comboFound = true;
                                        break;
                                }
                        }
                }
                if (comboFound)
                        break;
        }
        return comboFound;

}
//---------------------------------------------------------------------------
PhysForce operator+ (const PhysForce& pf1, const PhysForce& pf2)
{
        double sfVecL = pf1.power*pf1.fVecLeft + pf2.power*pf2.fVecLeft;
        double sfVecT = pf1.power*pf1.fVecTop + pf2.power*pf2.fVecTop;
        double sfp = fabs(sfVecL) + fabs(sfVecT);
        sfVecL/=sfp; sfVecT/=sfp;
        double spVecL = pf1.impulse*pf1.pVecLeft + pf2.impulse*pf2.pVecLeft;
        double spVecT = pf1.impulse*pf1.pVecTop + pf2.impulse*pf2.pVecTop;
        double spp = fabs(spVecL) + fabs(spVecT);
        spVecL/=spp; spVecT/=spp;
        double sip = sfp+spp;

        return PhysForce::create(sfp,spp,sip,sfVecL,sfVecT,spVecL,sfVecT);

}
PhysForce::PhysForce()
{
        init(0.,0.,0.,0.,0.,0.,0.);
}
PhysForce::~PhysForce()
{
;
}
void PhysForce::init(double f, double p, double i, double fVecL, double fVecT, double pVecL, double pVecT)
{
        power=f;
        impulse=p;
        inertia=i;
        fVecLeft = fVecL;
        fVecTop  = fVecT;
        pVecLeft = pVecL;
        pVecTop  = pVecT;
        iVecLeft = iVecTop = 0.;
        initTime = ::GetTickCount();
        active = true;
}
PhysForce PhysForce::create(double f, double p, double i, double fVecL, double fVecT, double pVecL, double pVecT)
{
        PhysForce pf;
        pf.init(f,p,i,fVecL,fVecT,pVecL,pVecT);
        return pf;
}
double PhysForce::getVl()
{
        if (done)
                return 0.;
        if (active)
                return power*fVecLeft*double(::GetTickCount())/1000. + impulse*pVecLeft;
        else
        {
                double inertiaForce = inertia*double(::GetTickCount()-stopTime)/1000.;
                if (inertiaForce >= impulse)
                {
                        done = true;
                        return 0.;
                }
                return impulse*pVecLeft - inertiaForce*iVecLeft;
        }
}
double PhysForce::getVt()
{
        if (done)
                return 0.;
        if (active)
                return power*fVecTop*double(::GetTickCount())/1000. + impulse*pVecTop;
        else
        {
                double inertiaForce = inertia*double(::GetTickCount()-stopTime)/1000.;
                if (inertiaForce >= impulse)
                {
                        done = true;
                        return 0.;
                }
                return impulse*pVecTop - inertiaForce*iVecTop;
        }
}
void PhysForce::stop()
{
        active = false;

        pVecLeft += power*fVecLeft*double(::GetTickCount())/1000.;
        pVecTop  += power*fVecTop*double(::GetTickCount())/1000.;
        double pVecCoef = fabs(pVecLeft) + fabs(pVecTop);
        impulse  *= pVecCoef;
        pVecLeft /= pVecCoef;
        pVecTop  /= pVecTop;

        iVecLeft = -pVecLeft;
        iVecTop  = -pVecTop;
        stopTime = ::GetTickCount();
}
void PhysForce::start()
{
        active = true;
        initTime = ::GetTickCount();
}
//---------------------------------------------------------------------------
void PhysObject::addForce(QString name, double f, double p, double i, double fVecLeft, double fVecTop, double pVecLeft, double pVecTop)
{
        PhysForce pf = PhysForce::create(f,p,i,fVecLeft, fVecTop, pVecLeft, pVecTop);
        forces[name]=pf;
}
void PhysObject::stopForce(QString name)
{
        std::map<QString,PhysForce>::iterator it = forces.find(name);
        if (it != forces.end())
                it->second.stop();
}
void PhysObject::startForce(QString name)
{
        std::map<QString,PhysForce>::iterator it = forces.find(name);
        if (it != forces.end())
                it->second.start();
}
void PhysObject::invert(QString name, bool horForce, bool vertForce)
{
        std::map<QString,PhysForce>::iterator it = forces.find(name);
        if (it != forces.end())
        {
                if (horForce)
                {
                        it->second.fVecLeft *= -1.;
                        it->second.pVecLeft *= -1.;
                        it->second.iVecLeft *= -1.;
                }
                if (vertForce)
                {
                        it->second.fVecTop *= -1.;
                        it->second.pVecTop *= -1.;
                        it->second.iVecTop *= -1.;
                }
        }
}
void PhysObject::removeForce(QString name)
{
        std::map<QString,PhysForce>::iterator it = forces.find(name);
        if (it != forces.end())
                forces.erase(it);
}
double PhysObject::getVl()
{
        double vl=0;
        map_foreach(QString,PhysForce,it,forces)
                vl+=it->second.getVl();
        return vl;
}
double PhysObject::getVt()
{
        double vt=0;
        map_foreach(QString,PhysForce,it,forces)
                vt+=it->second.getVt();
        return vt;
}
//---------------------------------------------------------------------------
QStringList ReadFileStrings(QString filename)
{
    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QStringList list;

    while(!in.atEnd())
    {
        QString line = in.readLine();
        list.append(line);
    }
    file.close();
    return list;
}


QImage *createTransparentImage(QString filename, QRgb trColor)
{
    QImage * img = new QImage(filename);
    QImage * transparentImage = new QImage(*img);
    img->convertToFormat(QImage::Format_ARGB32);
    QImage mask = img->createMaskFromColor(trColor);
    transparentImage->fill(QColor::fromRgba(qRgba(0,0,0,0)));

    QPainter p(transparentImage);
    p.setRenderHint(QPainter::Antialiasing, true);
    p.setClipRegion(QRegion(QBitmap::fromImage(mask)));
    p.drawImage(QPoint(0,0),*img);

    delete img;
    return transparentImage;
}


void drawImageOnImage(QImage *context, QImage *image, QPoint offset)
{
    QPainter p(context);
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
    p.drawImage(offset,*image);
}



QImage *copyImage(QImage *src)
{
    QImage *context = new QImage(src->width(), src->height(), src->format());
    context->fill(QColor::fromRgba(qRgba(0,0,0,0)));
    //Do some stuff in tmpImage
    QPainter p(context);
    p.setCompositionMode(QPainter::CompositionMode_SourceOver);
    p.drawImage(QPoint(0,0),*src);
    return context;
}


keyHistory::keyHistory(int size)
{

}
