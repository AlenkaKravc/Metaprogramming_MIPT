#include <iostream>
#include <vector>
#include <cstring>


class interfaceA;

class interfaceB;

class interfaceC;

class interfaceA {

protected:

    int valueA;
    int indexA;

public:

    void setValueA(int value) {
        valueA = value;
    }

    int getValueA() {
        return valueA;
    }

    virtual void request() = 0;

    virtual void request(int indexB) = 0;

    virtual void update(int value) = 0;

    virtual void addSubscription(int index) = 0;
};

class interfaceB {

protected:

    bool isReady = true;
    int valueB;
    int indexB;

public:

    void setValueB(int value) {
        valueB = value;
    }

    int getValueB() {
        return valueB;
    }

    void setStatus(bool state) {
        isReady = state;
    }

    bool checkReady() {
        return isReady;
    }

    virtual void respond(interfaceA *A) = 0;

    virtual void respond(int indexB , interfaceA *A) = 0;

    virtual void subscribe(int indexB , interfaceA *A) = 0;
};

class interfaceC {

public:
    virtual void notifySubscribersB(int indexB , int value) = 0;

    virtual void subscribersB(int indexB , interfaceA *A) = 0;
};


class A : public interfaceA {
    interfaceB *obj;
public:
    A(int index , interfaceB *obj) {
        this->obj = obj;
        this->indexA = index;
    }

    void request() {
        obj->respond(this);
    }

    void request(int indexB) {
        obj->respond(indexB , this);
    }

    void update(int value) {
        this->setValueA(value);
    }

    void addSubscription(int indexB) {
        obj->subscribe(indexB , this);
    }

    void printValue() {
        std::cout << "Index A: " << indexA << "; value: " << valueA << std::endl;
    }
};

class B : public interfaceB {

    interfaceC *obj;

public:

    B(int index , interfaceC *obj) {
        this->obj = obj;
        this->indexB = index;
    }

    void respond(interfaceA *A) {
        A->update(this->valueB);
    }

    void respond(int indexB , interfaceA *A) {
        if (this->indexB == indexB)
            A->update(this->valueB);
    }

    void notifySubscribers(int value) {
        obj->notifySubscribersB(indexB , value);
    }

    void subscribe(int indexB , interfaceA *A) {
        obj->subscribersB(indexB , A);
    }

    void printValue() {
        std::cout << "Index B: " << indexB << "; value: " << valueB << std::endl;
    }
};

template<char Type>
class Pattern : public interfaceB , public interfaceC {

    std::vector<std::pair<int , interfaceA *>> subscribersA;
    std::vector<interfaceB *> objectsB;

public:
    Pattern() {}

    void addB(interfaceB *B) {
        objectsB.push_back(B);
    }


    // ------Proxy ------//

    void respond(interfaceA *A) {
        if (Type == 'P') {
            if (objectsB[0]->checkReady()) {
                objectsB[0]->respond(A);
            }
        } else {
            std::cout << "Err: wrong type" << std::endl;
        }
    }


    // ------Mediator ------//

    void respond(int indexB , interfaceA *A) {
        if (Type == 'M') {
            for (int i = 0; i < objectsB.size(); i++) {
                objectsB[i]->respond(indexB , A);
            }
        } else {
            std::cout << "Err: wrong type" << std::endl;
        }
    }


    // ------Observer ------//

    void subscribe(int indexB , interfaceA *A) {
        if (Type == 'O')
            subscribersA.push_back(std::make_pair(indexB , A));
        else {
            std::cout << "Err: wrong type" << std::endl;
        }
    }

    void notifySubscribersB(int indexB , int value) {
        if (Type == 'O')
            for (int i = 0; i < subscribersA.size(); i++) {
                if (subscribersA[i].first == indexB)
                    subscribersA[i].second->update(value);
            }
        else {
            std::cout << "Err: wrong type" << std::endl;
        }
    }

    void subscribersB(int indexB , interfaceA *A) {
        if (Type == 'O')
            this->subscribe(indexB , A);
        else {
            std::cout << "Err: wrong type" << std::endl;
        }
    }

};


int main() {


    //PROXY
    std::cout << "----PROXY----" << std::endl << std::endl;

    Pattern<'P'> *pattern_proxy;
    pattern_proxy = new Pattern<'P'>();

    A *a_p = new A(1 , pattern_proxy);
    B *b_p = new B(1 , pattern_proxy);

    pattern_proxy->addB(b_p);
    b_p->setValueB(100);

    a_p->request();
    a_p->printValue();



    //MEDIATOR
    std::cout << std::endl << "----MEDIATOR----" << std::endl << std::endl;

    Pattern<'M'> *pattern_mediator;
    pattern_mediator = new Pattern<'M'>();

    A *a_m = new A(1 , pattern_mediator);

    B *b1_m = new B(1 , pattern_mediator);
    pattern_mediator->addB(b1_m);
    b1_m->setValueB(100);

    a_m->request(1);
    a_m->printValue();


    B *b2_m = new B(2 , pattern_mediator);
    pattern_mediator->addB(b2_m);
    b2_m->setValueB(200);

    a_m->request(2);
    a_m->printValue();

    B *b3_m = new B(3 , pattern_mediator);
    pattern_mediator->addB(b3_m);
    b3_m->setValueB(300);


    a_m->request(3);
    a_m->printValue();



    //OBSERVER
    std::cout << std::endl << "----OBSERVER----" << std::endl << std::endl;

    Pattern<'O'> *pattern_observer;
    pattern_observer = new Pattern<'O'>();

    A *a1_o = new A(1 , pattern_observer);
    A *a2_o = new A(2 , pattern_observer);

    B *b1_o = new B(1 , pattern_observer);
    B *b2_o = new B(2 , pattern_observer);
    B *b3_o = new B(3 , pattern_observer);

    pattern_observer->addB(b1_o);
    pattern_observer->addB(b2_o);
    pattern_observer->addB(b3_o);

    b1_o->setValueB(100);
    b2_o->setValueB(200);
    b3_o->setValueB(300);

    //test 1//
    a1_o->addSubscription(1);
    a2_o->addSubscription(1);

    b1_o->notifySubscribers(500);

    a1_o->printValue();
    a2_o->printValue();


    //test 2//
    a1_o->addSubscription(3);
    a2_o->addSubscription(3);

    b3_o->notifySubscribers(700);

    a1_o->printValue();
    a2_o->printValue();

    return 0;
}