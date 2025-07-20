#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

class CPU
{
public:
    virtual void show() = 0;
    ~CPU() {}
};

class Mainboard
{
public:
    virtual void print() = 0;
    ~Mainboard() {}
};

class IntelCPU : public CPU
{
public:
    void show() override
    {
        cout << "Intel CPU GOOD" << endl;
    }
};

class AMDCPU : public CPU
{
public:
    void show() override
    {
        cout << "AMD CPU GOOD" << endl;
    }
};

class IntelMainBoard : public Mainboard
{
public:
    void print() override
    {
        cout << "Intel Mainboard GOOD" << endl;
    }
};

class AMDMainBoard : public Mainboard
{
public:
    void print() override
    {
        cout << "AMD Mainboard GOOD" << endl;
    }
};

class AbstractFactory
{
public:
    virtual CPU *createCPU() = 0;
    virtual Mainboard *createMainboard() = 0;
    virtual ~AbstractFactory() {}
};

class IntelFactory : public AbstractFactory
{
public:
    CPU *createCPU() override
    {
        return new IntelCPU();
    }

    Mainboard *createMainboard() override{
        return new IntelMainBoard();
    }
};


class AMDFactory : public AbstractFactory
{
public:
    CPU *createCPU() override
    {
        return new AMDCPU();
    }

    Mainboard *createMainboard() override{
        return new AMDMainBoard();
    }
};



int main()
{
    unique_ptr<AbstractFactory> fac1(new IntelFactory());
    unique_ptr<CPU> pcpu(fac1->createCPU());
    unique_ptr<Mainboard> pmab(fac1->createMainboard());
    pcpu->show();
    pmab->print();

    
    cout << endl;
    unique_ptr<AbstractFactory> fac2(new AMDFactory());
    unique_ptr<CPU> pcpu2(fac2->createCPU());
    unique_ptr<Mainboard> pmab2(fac2->createMainboard());
    pcpu2->show();
    pmab2->print();
    return 0;
}
