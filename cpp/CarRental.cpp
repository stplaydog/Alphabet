#include <iostream>
#include <cstdlib>
#include <cassert>
#include <memory>
#include <vector>

// 1)  I think there is no need to add "big three", because every variable is shallow copy;
// 2)  Destructor is declare as virtual, because there are possible differentiated actions,
//     not just deallocations;
// 3)  Classes are self evident, much comments are unneccessary;
// 4)  Decorator pattern is an overkill, we should not over design at the very beginning;
// 5)  The class design conforms to Google coding standard, and checked by cpplint;
// 6)  dynamic cast is used to avoid fat interface;
// 7)  Assert is used for testing, there are many other test frameworks for more complicated cases;
// 8)  Aggregation is used because car might be moved to other rental places;
// 9)  Exception conditions are also considered, because this system might be provided as 
//     a third party library or service, I only use ID to represent exceptions to save space; 
// 10) One possible caveat is that C++11 is used, which migth introduce compatibility issues. 
// 11) Sequential lookup is expensive, there would be better solutions. 

using namespace std;

class Car
{
public:
    Car(const string &plate, const string &brand) :
        m_plate(plate),      m_brand(brand)
    {
    }
    virtual ~Car() {};

    virtual int maxSeats() = 0;

protected:
    string m_plate; ///< plate could be a string like "BWA 9840"
    string m_brand; ///< such as "BMW"
};

class SUV : public Car
{
public:
    SUV(const string &plate, const string &brand, 
        int   numSeats,      bool extraCapacity = false) :
        Car(plate, brand), 
        m_numSeats(numSeats), 
        m_extraCapacity(extraCapacity)
    {
    }

    ~SUV() {}

    int maxSeats()
    {
        return m_extraCapacity ? m_numSeats + 3 : m_numSeats; 
    }

private:
    int  m_numSeats;      ///< different SUV might have different number of seats
    bool m_extraCapacity; ///< optional
};

class Sedan : public Car
{
public:
    Sedan(const string &plate, const string &brand, 
          int   numSeats,      bool sportPackage = false) :
          Car(plate, brand), 
          m_numSeats(numSeats), 
          m_sportPackage(sportPackage)
    {
    }

    ~Sedan() {}

    int maxSeats()
    {
        return m_numSeats ; 
    }

    bool hasSportPackage() { return m_sportPackage; }

private:
    int  m_numSeats;      ///< different SUV might have different number of seats
    bool m_sportPackage;  ///< if have the extra sport package
};

class CarRental
{
public:

    enum CAR_TYPE
    {
        SUV = 0,
        SEDAN,
        NUM_CAR_TYPE
    };

    enum EXCEPTION_CODE
    {
        NOT_ENOUGH_CAPACITY = 1000,
        NO_CAR_AVAILABLE,
        NOT_OUR_CAR,
        NUM_EXCEPTIONS
    };

    CarRental(int capacity) :
        m_capacity(capacity)
    {}
    ~CarRental(){}

    bool addCar(shared_ptr<Car> car) 
    {
        bool ret = false;
        if(m_rented.size() + m_available.size() >= m_capacity)
        {
            ret = false;
            throw NOT_ENOUGH_CAPACITY;
        }
        else
        {
            m_available.push_back(car);
            ret = true;
        }
        return ret;
    }

    int numAvailable() { return m_available.size(); }
    int numRented()    { return m_rented.size();    }

    shared_ptr<Car> rentCar(CAR_TYPE type)
    {
        shared_ptr<Car> ret;
        switch(type)
        {
            case SUV:
            {
                for(auto iter = m_available.begin(); iter != m_available.end(); ++iter)
                {
                    shared_ptr<Car> tmp = *iter;
                    shared_ptr<Sedan> p = dynamic_pointer_cast<Sedan>(tmp);
                    if(!p)
                    {
                        ret = tmp;
                        m_available.erase(iter);
                        m_rented.push_back(tmp);
                        break;
                    }
                }
                break;
            }
            case SEDAN:
            {
                for(auto iter = m_available.begin(); iter != m_available.end(); ++iter)
                {
                    shared_ptr<Car> tmp = *iter;
                    if(shared_ptr<Sedan> p = dynamic_pointer_cast<Sedan>(tmp))
                    {
                        ret = tmp;
                        m_available.erase(iter);
                        m_rented.push_back(tmp);
                        break;
                    }
                }
                break;
            } 
        }

        if(!ret)
            throw NO_CAR_AVAILABLE;
        return ret;
    }

    bool returnCar(shared_ptr<Car> toBeReturn)
    {
        bool ret = false;
        for(auto iter = m_rented.begin(); iter != m_rented.end(); ++iter)
        {
            shared_ptr<Car> tmp = *iter;
            if(tmp == toBeReturn)
            {
                m_rented.erase(iter);
                m_available.push_back(tmp);
                ret = true;
                break;
            }
        }
        if(!ret)
            throw NOT_OUR_CAR; 
        return ret;
    }

    typedef vector<shared_ptr<Car>> CarList;


private:
    CarList m_available;
    CarList m_rented;
    int     m_capacity;
};

int main(int argc, char* argv[])
{
    shared_ptr<Car> suv1(make_shared<SUV>(string("firstsuv"), string("audi"), 10, true));
    assert(suv1->maxSeats() == 13);

    shared_ptr<Car> sed1(make_shared<Sedan>(string("firstsuv"), string("audi"), 10, true));
    assert(sed1->maxSeats() == 10);
    if(shared_ptr<Sedan> p = dynamic_pointer_cast<Sedan>(sed1))
    {
        assert(p->hasSportPackage() == true);
    }

    CarRental rental(10);
    rental.addCar(suv1);
    rental.addCar(sed1);
    try
    {
        for(int i=0; i<9; i++)
        {
            string randplate(to_string(rand()%1000));
            shared_ptr<Car> suv(make_shared<SUV>(randplate, string("audi"), 10, true));
            rental.addCar(suv);
        }
    }
    catch (CarRental::EXCEPTION_CODE e)
    {
        if(e == CarRental::NOT_ENOUGH_CAPACITY)
            cout<<"Not enough space, reject new car."<<endl;
    }

    shared_ptr<Car> suv2; 
    shared_ptr<Car> sed2; 
    shared_ptr<Car> sed3; 
    try
    {
        suv2 = rental.rentCar(CarRental::SUV);
        assert(rental.numAvailable()==9 && rental.numRented()==1);

        sed2 = rental.rentCar(CarRental::SEDAN);
        assert(rental.numAvailable()==8 && rental.numRented()==2);

        sed3 = rental.rentCar(CarRental::SEDAN);
        assert(rental.numAvailable()==8 && rental.numRented()==2);
    }
    catch (CarRental::EXCEPTION_CODE e)
    {
        if(e == CarRental::NO_CAR_AVAILABLE)
            cout<<"There is no car of your type available."<<endl;
    }

    try
    {
        rental.returnCar(suv2);
        assert(rental.numAvailable()==9 && rental.numRented()==1);

        shared_ptr<Car> suv4(make_shared<SUV>(string("othersuv"), string("BMW"), 10, true));
        rental.returnCar(suv4);
    }
    catch (CarRental::EXCEPTION_CODE e)
    {
        if(e == CarRental::NOT_OUR_CAR)
            cout<<"Your return your car to the wrong place."<<endl;
    }
}
