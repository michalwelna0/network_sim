#ifndef NETWORK_SIM_NODES_HPP
#define NETWORK_SIM_NODES_HPP
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include <memory>
#include <map>
#include <functional>



/*enum class ReceiverType{
    Ramp = 1,
    Worker = 2,
    Storehouse = 3
};
*/

class IPackageReceiver{
public:
    virtual void receive_package(Package&& p) = 0;
    //virtual ReceiverType get_receiver_type() const = 0;
    virtual ElementID get_id() const =0;


};


class Storehouse : public IPackageReceiver{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d): id_(id), d_(std::move(d)) {}
    void receive_package (Package&& p) override;
    //ReceiverType get_receiver_type() const override;
    ElementID get_id() const override {return id_;}
private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;

};


class ReceiverPreferences{

public:
    //ReceiverPreferences(std::function<ProbabilityGenerator(void)> ptr) do zrobienia nie wiem o co chodzi diablowi
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;
    using iterator = preferences_t::iterator;
    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const_iterator cbegin() const {return preferences_.cbegin();}
    const_iterator cend() const {return preferences_.cend();}
    iterator begin() {return preferences_.begin();}
    iterator end() {return preferences_.end();}

private:
    static preferences_t preferences_;

};


class PackageSender{

public:
    void send_package();
    std::pair<Package, bool> get_sending_buffer() const;
    ReceiverPreferences receiver_preferences_;

protected:
    void push_package(Package&&);



};


class Ramp : public PackageSender{

public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; };
    ElementID get_id() const { return id_; }

private:
    ElementID id_;
    TimeOffset di_;

};


class Worker : public PackageSender, IPackageReceiver{
public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<PackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return pd_;}
    Time get_package_processing_start_time() const {return t_;}
    void receive_package (Package&& p) override;
    //ReceiverType get_receiver_type() const override;
    ElementID get_id() const override {return id_;}

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<PackageQueue> q_;
    Time t_;


};
#endif //NETWORK_SIM_NODES_HPP
