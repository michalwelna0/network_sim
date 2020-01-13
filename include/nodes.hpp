#ifndef NETWORK_SIM_NODES_HPP
#define NETWORK_SIM_NODES_HPP
#include "types.hpp"
#include "package.hpp"
#include "storage_types.hpp"
#include "helpers.hpp"
#include <memory>
#include <map>
#include <functional>
#include <optional>



enum class ReceiverType{
    WORKER,STOREHOUSE
};


class IPackageReceiver{

public:
    virtual void receive_package(Package&& p) = 0;
    virtual ReceiverType get_receiver_type() const = 0;
    virtual ElementID get_id() const =0;
    virtual ~IPackageReceiver() = default;

    using const_iterator = std::list<Package>::const_iterator;
    virtual const_iterator begin() const = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() const = 0;
    virtual const_iterator cend() const  = 0;

};


class Storehouse : public IPackageReceiver{

public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::make_unique<PackageQueue>(PackageQueue(PackageQueueType::FIFO))): id_(id), d_(std::move(d)) {}
    void receive_package (Package&& p) override;
    ReceiverType get_receiver_type() const override {return storehouse;}
    ElementID get_id() const override {return id_;}

    const_iterator begin() const override {return d_->begin();}
    const_iterator cbegin() const override {return d_->cbegin();}
    const_iterator end() const override {return d_->end();}
    const_iterator cend() const override {return d_->cend();}

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
    ReceiverType storehouse = ReceiverType::STOREHOUSE;

};


class ReceiverPreferences{

public:
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : rng_(std::move(pg)) {}
    using preferences_t = std::map<IPackageReceiver*, double>;
    using const_iterator = preferences_t::const_iterator;


    void add_receiver(IPackageReceiver* r);
    void remove_receiver(IPackageReceiver* r);
    IPackageReceiver* choose_receiver();
    const preferences_t& get_preferences() const {return preferences_;}

    const_iterator cbegin() const {return preferences_.cbegin();}
    const_iterator cend() const {return preferences_.cend();}
    const_iterator begin() const {return preferences_.begin();}
    const_iterator end() const {return preferences_.end();}

private:
    preferences_t preferences_;
    ProbabilityGenerator rng_;
    void scale_probability();

};


class PackageSender{

private:
    std::optional<Package> PackSenderBufor;

public:
    void send_package();
    const std::optional<Package>& get_sending_buffer() const {return PackSenderBufor;}
    ReceiverPreferences receiver_preferences_;


protected:
    void push_package(Package&& pack);

};


class Ramp : public PackageSender {

public:
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {};
    void deliver_goods(Time t);
    TimeOffset get_delivery_interval() const { return di_; };
    ElementID get_id() const { return id_; }
private:
    ElementID id_;
    TimeOffset di_;

};


class Worker : public PackageSender, public IPackageReceiver{

public:
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);
    TimeOffset get_processing_duration() const {return pd_;}
    Time get_package_processing_start_time() const {return t_;}
    void receive_package (Package&& p) override;
    ReceiverType get_receiver_type() const override {return worker;}
    ElementID get_id() const override {return id_;}


    const_iterator begin() const override {return q_->begin();}
    const_iterator cbegin() const override {return q_->cbegin();}
    const_iterator end() const override {return q_->end();}
    const_iterator cend() const override {return q_->cend();}

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
    std::optional<Package> workerBufor;
    ReceiverType worker = ReceiverType::WORKER;
    Time t_ = 1;

};
#endif //NETWORK_SIM_NODES_HPP
