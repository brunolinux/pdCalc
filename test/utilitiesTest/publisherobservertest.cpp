#include "publisherobservertest.h"
#include "src/utilities/publisher.h"
#include "src/utilities/observer.h"
#include "src/utilities/exception.h"

using std::set;
using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;

#include <string>

class StringEventData : public pdCalc::EventData
{
public:
    StringEventData(string s) : str_(s) {}
    const string& state() const { return str_; }

private:
    string str_;
};


class ConcretePublisher: private pdCalc::Publisher
{
public:
    ConcretePublisher();
    ~ConcretePublisher();

    void registerSingleEvent(const string& name = "singleEvent");
    std::set<string> listEvents() const;

    using pdCalc::Publisher::attach;
    using pdCalc::Publisher::listEventObservers;
    using pdCalc::Publisher::raise;
    using pdCalc::Publisher::detach;

private:
    void registerMultipleEvents();

    ConcretePublisher(const ConcretePublisher&) = delete;
    ConcretePublisher& operator=(const ConcretePublisher&) = delete;
    ConcretePublisher(ConcretePublisher&&) = delete;
    ConcretePublisher& operator=(ConcretePublisher&&) = delete;
};

class ConcreteObserver : public pdCalc::Observer
{
public:
    ConcreteObserver(const string& );
    ~ConcreteObserver();

    bool notified() const { return notified_; }
    void setNotified(bool b) { notified_ = b; }
    const string& state() const { return state_; }
protected:
    void notifyImpl(std::shared_ptr<pdCalc::EventData>) override;


private:
    ConcreteObserver(const ConcreteObserver&) = delete;
    ConcreteObserver& operator=(const ConcreteObserver&) = delete;
    ConcreteObserver(ConcreteObserver&&) = delete;
    ConcreteObserver& operator=(ConcreteObserver&&) = delete;

    bool notified_;
    string state_;
};

ConcretePublisher::ConcretePublisher()
{
    registerSingleEvent();
    registerMultipleEvents();
}

ConcretePublisher::~ConcretePublisher()
{ }

void ConcretePublisher::registerSingleEvent(const string& name)
{
    registerEvent(name);
    return;
}

void ConcretePublisher::registerMultipleEvents()
{
    vector<string> events = { "multipleEventOne", "multipleEventTwo"};
    registerEvents(events);
    return;
}

set<string> ConcretePublisher::listEvents() const
{
    return pdCalc::Publisher::listEvents();
}

ConcreteObserver::ConcreteObserver(const std::string& name)
: Observer{name}
, notified_{false}
, state_{""}
{
}

ConcreteObserver::~ConcreteObserver()
{ }

void ConcreteObserver::notifyImpl(std::shared_ptr<pdCalc::EventData> data)
{
    notified_ = true;
    std::shared_ptr<StringEventData> p = std::dynamic_pointer_cast<StringEventData>(data);
    if(p) state_ = p->state();
    return;
}

void PublisherObserverTest::init()
{
    pt_ = new ConcretePublisher;
}

void PublisherObserverTest::cleanup()
{
    delete pt_;
}

void PublisherObserverTest::testRegister()
{
    // note that register calls appear in Publisher constructor
    auto events = pt_->listEvents();
    auto end = events.end();

    QVERIFY(events.find("singleEvent") != end);
    QVERIFY(events.find("multipleEventOne") != end);
    QVERIFY(events.find("multipleEventTwo") != end);

    return;
}

void PublisherObserverTest::testRegisterDuplicate()
{
    try
    {
        pt_->registerSingleEvent("singleEvent");
    }
    catch(pdCalc::Exception& e)
    {
        QCOMPARE(e.what(), string{"Event already registered"});
    }
}

void PublisherObserverTest::testAttachObservers()
{
    pt_->attach("singleEvent", make_unique<ConcreteObserver>("singleEventObserver"));

    try {
        pt_->attach("singleEvent", make_unique<ConcreteObserver>("singleEventObserver"));
    }  catch (pdCalc::Exception& e) {
        QCOMPARE(e.what(), string("Observer already attached to publisher"));
    }

    auto obsSetMultipleEventOne = pt_->listEventObservers("multipleEventOne");
    QVERIFY(obsSetMultipleEventOne.size() == 0);

    auto obsSet = pt_->listEventObservers("singleEvent");
    auto end = obsSet.end();
    QVERIFY(obsSet.find("singleEventObserver") != end);
    QCOMPARE(obsSet.find("madeupEvent"), end);

    pt_->attach("multipleEventOne", make_unique<ConcreteObserver>("observerOne"));
    pt_->attach("multipleEventOne", make_unique<ConcreteObserver>("observerTwo"));

    obsSet = pt_->listEventObservers("multipleEventOne");
    end = obsSet.end();
    QVERIFY(obsSet.find("observerOne") != end);
    QVERIFY(obsSet.find("observerTwo") != end);
    QCOMPARE(obsSet.find("madeUpEvent"), end);

    return;
}

void PublisherObserverTest::testRaiseEvent()
{
    // bad form (holding raw ptr to unique_ptr) for real code--ok for testing
    auto p1 = new ConcreteObserver{"observerOne"};
    auto p2 = new ConcreteObserver{"observerTwo"};

    pt_->attach("multipleEventOne", unique_ptr<pdCalc::Observer>{p1});
    pt_->attach("multipleEventOne", unique_ptr<pdCalc::Observer>{p2});

    // check that event has not been raised
    QCOMPARE(p1->notified(), false);
    QCOMPARE(p1->notified(), false);

    // check that raising a not observed event did not trigger observation
    pt_->raise("multipleEventTwo", std::make_shared<pdCalc::EventData>());

    QCOMPARE(p1->notified(), false);
    QCOMPARE(p1->notified(), false);

    // check that raising observed event was indeed observed
    pt_->raise("multipleEventOne", std::make_shared<pdCalc::EventData>());

    QCOMPARE(p1->notified(), true);
    QCOMPARE(p1->notified(), true);

    return;
}

void PublisherObserverTest::testDetachObservers()
{
    auto raw = new ConcreteObserver("observerOne");
    unique_ptr<pdCalc::Observer> p1{raw};

    pt_->attach("multipleEventOne", std::move(p1));
    pt_->attach("multipleEventOne", make_unique<ConcreteObserver>("observerTwo"));

    set<string> obsSetMultipleEventOne = pt_->listEventObservers("multipleEventOne");
    QVERIFY(obsSetMultipleEventOne.size() == 2);

    QVERIFY(p1 == nullptr);
    p1 = pt_->detach("multipleEventOne", "observerOne");

    obsSetMultipleEventOne = pt_->listEventObservers("multipleEventOne");
    auto end = obsSetMultipleEventOne.end();
    QVERIFY(obsSetMultipleEventOne.find("observerTwo") != end);
    QCOMPARE(obsSetMultipleEventOne.find("observerOne"), end);

    QVERIFY(p1 != nullptr);
    QCOMPARE(p1.get(), raw);

    try
    {
        pt_->detach("madeUpEvent", "observerTwo");
    }
    catch(pdCalc::Exception& e)
    {
        QCOMPARE(e.what(), string{"Publisher does not support event 'madeUpEvent'"});
    }

    try
    {
        pt_->detach("multipleEventOne", "observerOne");
    }
    catch(pdCalc::Exception& e)
    {
        QCOMPARE(e.what(), string{"Cannot detach observer because observer not found"});
    }

    return;
}


void PublisherObserverTest::testGetState()
{
    auto raw = new ConcreteObserver{"observer"};
    QCOMPARE(raw->state(), string{""});

    pt_->attach("singleEvent", unique_ptr<pdCalc::Observer>{raw});
    pt_->raise( "singleEvent", std::make_shared<StringEventData>( "sample state" ) );

    QCOMPARE(raw->state(), string{"sample state"});

    return;
}
